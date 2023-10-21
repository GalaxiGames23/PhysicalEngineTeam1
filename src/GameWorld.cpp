#include "GameWorld.h"

//Constructeur par défaut
GameWorld::GameWorld()
{
	registre = ParticuleForceRegistry();
	worldGravity = ParticuleGravity();
	myBlob = NULL;
	Sphere* particule = new Sphere(5.0f,Vector(100,100,0),Vector(0,0,0), 0.5f);
	systemeSpheres.push_back(particule);
	ParticuleSpring* spring = new ParticuleSpring(0.5f, 10.0f, Vector(100,150,0));
	Spring* entry = new Spring();
	entry->particule1 = particule;
	entry->spring = spring;
	springList.push_back(entry);
	
	Sphere* particule2 = new Sphere(20.0f, Vector(200, 50, 0), Vector(0, 0, 0), 3, ofColor::white, 0.5f);
	systemeSpheres.push_back(particule2);
}

void GameWorld::UpdateLogic(float duration) 
{
	//ajoute les forces au registre
	addForces();

	//update des forces
	registre.updateForces(duration);

	//clear du registre
	registre.clear();

	// Recherche et traitement des collisions
	dealCollisions(duration);

	//intégration de chaque particule
	for (int i = 0; i < systemeSpheres.size(); ++i)
	{
		systemeSpheres[i]->IntegrateEulerWithAccum(duration);
		

		//on vide l'accumulateur
		systemeSpheres[i]->clearAccum();

		//std::cout << systemeSpheres[i]->GetPosition() << endl;
	}
	myCam->setPosition();
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
	
	for (InputRegistre * input : inputRegistre)
	{
		registre.add(input->particule, input->fg);
	}
}

void GameWorld::dealCollisions(float duration)
{
	Vector gravity = worldGravity.GetGravity();
	for (Sphere* s1 : systemeSpheres)
	{
		for (Sphere* s2 : systemeSpheres)
		{
			if ((s1 != s2) && s1->isColliding(s2)) { // 2 particules entrent en collision
				s1->AddVelocityOnColliding(s2);
			}
		}
		if (s1->GetPosition().get_y() + s1->GetRadius() > ground.yCoord) // La sphère touche le sol
		{
			s1->SetPosition(Vector(s1->GetPosition().get_x(), ground.yCoord - s1->GetRadius(), s1->GetPosition().get_z()));

			/*std::cout << "v: " << s1->GetVelocity().norm()*duration << endl;
			std::cout << "g t: " << (gravity * s1->GetMass()).norm() * duration << endl;*/
			if (s1->GetVelocity().get_y() < 0)
			{
				return;
			}
			if (  s1->GetVelocity().get_y() < (12*duration * gravity*s1->GetMass()).get_y())
			{
				
				s1->NullifyVelocityAlongNormal(Vector(0, 1, 0));

			}
			else 
			{
				s1->AddVelocityOnColliding(ground.yCoord);
			}
					/*ParticuleGravity* inversGravity = new ParticuleGravity(Vector() - s1->GetAccumForce());
					registre.add(s1, inversGravity);*/
			
			
			/*
			if ((worldGravity.GetGravity().prod_vector(s1->GetDirection())).norm() != 0)
			{
				ParticuleFrictionStatic* forceStatic = new ParticuleFrictionStatic(this->worldGravity.GetGravity());
				registre.add(s1, forceStatic);
			}
			else
			{
				if (gravity == s1->GetAccumForce() && (duration * gravity).norm() > s1->GetVelocity().norm())
				{
					ParticuleGravity *inversGravity = new ParticuleGravity(Vector() - s1->GetAccumForce());
					registre.add(s1, inversGravity);
				}
				else
				{
					s1->AddVelocityOnColliding(ground.yCoord);
				}
			}
			*/
		}
	}
}
