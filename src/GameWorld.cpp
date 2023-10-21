#include "GameWorld.h"

//Constructeur par d�faut
GameWorld::GameWorld()
{
	registre = ParticuleForceRegistry();
	worldGravity = ParticuleGravity();
	worldAirFriction = ParticuleFrictionCinetic(0.1, 0.001);
	myBlob = NULL;

	// Test ressort
	Sphere* particule = new Sphere(5.0f,Vector(100,100,0),Vector(0,0,0), 0.5f);
	systemeSpheres.push_back(particule);
	ParticuleSpring* spring = new ParticuleSpring(0.5f, 10.0f, Vector(100,150,0));
	Spring* entry = new Spring();
	entry->particule1 = particule;
	entry->spring = spring;
	springList.push_back(entry);
	
	Sphere* particulebis = new Sphere(20.0f, Vector(200, 50, 0), Vector(0, 0, 0), 3, ofColor::white, 0.5f);
	systemeSpheres.push_back(particulebis);

	// Test Cable
	Sphere* particule1 = new Sphere(10.0f, Vector(300, 110, 0), Vector(100, 0, 0), 0.5f);
	Sphere* particule2 = new Sphere(10.0f, Vector(300, 100, 0), Vector(0, 0, 0), 0.5f);

	systemeSpheres.push_back(particule1);
	systemeSpheres.push_back(particule2);

	Cable* cable = new Cable();
	cable->particule1 = particule1;
	cable->particule2 = particule2;
	cable->distance = 50;
	cable->e = 0.5;
	cableList.push_back(cable);

	// Test Tige
	Sphere* particule4 = new Sphere(10.0f, Vector(650, 150, 0), Vector(0, 0, 0),5.0f,ofColor::green, 0.5f);
	Sphere* particule3 = new Sphere(10.0f, Vector(600, 100, 0), Vector(0, 0, 0), 5.0f, ofColor::green, 0.5f);

	systemeSpheres.push_back(particule3);
	systemeSpheres.push_back(particule4);

	Rod* tige = new Rod();
	tige->particule1 = particule3;
	tige->particule2 = particule4;
	tige->distance = particule1->distanceParticules(particule2);
	rodList.push_back(tige);
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
	dealCables();
	dealRods();

	//int�gration de chaque particule
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
	//gestion de la gravit�
	for (Particule* particule : systemeSpheres)
	{
		registre.add(particule, &worldGravity);
		registre.add(particule, &worldAirFriction);
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


void GameWorld::dealCables()
{
	for (Cable* cable : cableList)
	{
		if (cable->particule1->distanceParticules(cable->particule2) > cable->distance)
		{
			cable->particule1->AddVelocityOnCable(cable->particule2, cable->e);
			cable->particule2->AddVelocityOnCable(cable->particule1, cable->e);
		}
	}
}

void GameWorld::dealRods()
{
	for (Rod* rod : rodList)
	{
		if (abs(rod->particule1->distanceParticules(rod->particule2)- rod->distance) > 0.1)
		{
			rod->particule1->AddForceOnRod(rod->particule2);
			rod->particule2->AddForceOnRod(rod->particule1);
		}
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
		if (s1->GetPosition().get_y() + s1->GetRadius() > ground.yCoord) // La sph�re touche le sol
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
