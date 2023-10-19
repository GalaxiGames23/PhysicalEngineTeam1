#include "GameWorld.h"

//Constructeur par défaut
GameWorld::GameWorld()
{
	registre = ParticuleForceRegistry();
	worldGravity = ParticuleGravity();

	Sphere* sphere = new Sphere(5.0f,Vector(100,100,0),Vector(0,0,0), 1);
	systemeSpheres.push_back(sphere);

	ParticuleSpring* spring = new ParticuleSpring(0.5f, 10.0f, Vector(100,150,0));
	Spring* entry = new Spring();
	entry->particule1 = sphere;
	entry->spring = spring;
	springList.push_back(entry);

}

void GameWorld::UpdateLogic(float duration) 
{

	//ajoute les forces au registre
	addForces();

	//clear du registre
	registre.clear();

	//update des forces
	registre.updateForces(duration);

	// Recherche et traitement des collisions
	dealCollisions(duration);

	//intégration de chaque particule
	for (int i = 0; i < systemeSpheres.size(); ++i)
	{
		systemeSpheres[i]->IntegrateEulerWithAccum(duration);

		//on vide l'accumulateur
		systemeSpheres[i]->clearAccum();
	}
}

void GameWorld::addForces()
{
	//gestion de la gravité
	for (Particule* particule : systemeSpheres)
	{
		registre.add(particule, &worldGravity);
	}

	for (Spring* spring : springList)
	{
		registre.add(spring->particule1,spring->spring);
	}
}

void GameWorld::dealCollisions(float duration)
{
	Vector gravity = worldGravity.GetGravity();
	for (Sphere* s1 : systemeSpheres)
	{
		for (Sphere* s2 : systemeSpheres)
		{
			if ((s1 != s2) && s1->isColliding(s2)) {
				s1->AddVelocityOnColliding(s2);
			}
		}
		if (s1->GetPosition().get_y() >= ground.yCoord)
		{
			if ((worldGravity.GetGravity().projection(s1->GetDirection())).norm() != 0)
			{
				ParticuleFrictionStatic forceStatic = ParticuleFrictionStatic();
				registre.add(s1, &forceStatic);
			}
			else
			{
				if (gravity == s1->GetAccumForce() && (duration * gravity).norm() > s1->GetVelocity().norm())
				{
					ParticuleGravity inversGravity = ParticuleGravity(Vector() - s1->GetAccumForce());
					registre.add(s1, &inversGravity);
				}
				else
				{
					s1->AddVelocityOnColliding(ground.yCoord);
				}
			}
		}
	}
}
