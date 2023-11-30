#include "GameWorld.h"

//Constructeur par défaut
GameWorld::GameWorld()
{
	registre = ParticuleForceRegistry();
	registreRigids = RigidBodyForceRegistry();
	worldGravity = ParticuleGravity();
	worldAirFriction = ParticuleFrictionCinetic(0.1, 0.001);
	timer = 0;
}

void GameWorld::UpdateLogic(float duration) 
{
	
	//ajoute les forces au registre
	addForces();

	//update des forces
	registre.updateForces(duration);
	registreRigids.updateForces(duration);
	//clear du registre
	registre.clear();
	registreRigids.clear();

	//intégration de chaque particule
	for (int i = 0; i < systemeSpheres.size(); ++i)
	{
		systemeSpheres[i]->IntegrateEulerWithAccum(duration);
		

		//on vide l'accumulateur
		systemeSpheres[i]->clearAccum();

		//std::cout << systemeSpheres[i]->GetPosition() << endl;
	}

	//intégration à chaque RigidBody
	for (int i = 0; i < rigidBodies.size(); ++i) 
	{
		//destruction des rigid bodies sous un certain seuil
		if (rigidBodies[i]->GetCenter()->GetPosition().get_y() >= 2000)
		{
			rigidBodies.erase(rigidBodies.begin() + i);
		}
		else
		{
		rigidBodies[i]->RigidIntegrator(duration);

		//on vide l'accumulateur
		rigidBodies[i]->ClearAccums();

		}

	}

	//gestion de la trace 
	UpdateTrace(duration);

	myCam->setPosition();
}

void GameWorld::addForces()
{
	//gestion de la gravité et friction de l'air
	for (Particule* particule : systemeSpheres)
	{
		registre.add(particule, &worldGravity);
		registre.add(particule, &worldAirFriction);
	}

	//version rigid bodies
	for (int i = 0; i < rigidBodies.size(); ++i)
	{
		registre.add(rigidBodies[i]->GetCenter(), &worldGravity);
		registre.add(rigidBodies[i]->GetCenter(), &worldAirFriction);
	}

	//forces de controle
	for (InputRegistre * input : inputRegistre)
	{
		registre.add(input->particule, input->fg);
	}

}

//////////////////////PHASE 3////////////////////////////

void GameWorld::UpdateTrace(float duration)
{
	timer += duration;
	bool temp = timer > 0.2f;
	if (temp)
	{
		//enregistrer les positions pour la trace pour tous les rigidbodies
		for (int i = 0; i < rigidBodies.size(); ++i)
		{
			tracePositions.push_back(rigidBodies[i]->GetCenter()->GetPosition());
		}

		timer = 0;
	}
}



void GameWorld::HandleCollisions()
{
	bool isColliding;

	for (int i = 0; i < boxPairs.size(); ++i) // Pour chaque paire de boites à tester
	{
		isColliding = this->DetectCollisions(boxPairs[i]->box1, boxPairs[i]->box2);
		if(!isColliding) this->DetectCollisions(boxPairs[i]->box2, boxPairs[i]->box1);
	}
}

bool GameWorld::DetectCollisions(Box* box1, Box* box2)
{
	std::vector<Vector*> box1Vertices = box1->GetVertices();
	std::vector<Plane*> box2Planes = box2->GetPlanes();

	std::vector<bool> box1VxInBox2 = std::vector<bool>(box1Vertices.size(), false);
	std::vector<Vector*> collidingVertices;


	for (int i = 0; i < box1Vertices.size(); ++i) // Pour chaque plan de la boite 2
	{
		int countInto = 0;
		for (int j = 0; j < box2Planes.size(); ++j) // Pour chaque sommet de la boite 1
		{
			double t = box2Planes[j]->ComputeT(*box1Vertices[i]);
			if (t <= 0) ++countInto;
		}

		if (countInto == box2Planes.size())box1VxInBox2[i] = true;
	}


	for (int i = 0; i < box1VxInBox2.size(); ++i)
	{
		if (box1VxInBox2[i]) collidingVertices.push_back(box1Vertices[i]);
	}

	Vector pointBox1 = Vector(); // Point de collision box1
	Vector pointBox2 = Vector(); // Point de collision box2
	
	switch (collidingVertices.size())
	{
	case 1:
		pointBox1 = *collidingVertices[0];
		////// TO DO : Calcul pointBox2
		break;
	case 2:
		pointBox1 = 0.5f * (*collidingVertices[0] + *collidingVertices[1]);
		////// TO DO : Calcul pointBox2
		break;
	case 4:
		////// TO DO : Calcul pointBox1
		////// TO DO : Calcul pointBox2
		break;

	default:
		return false;
		break;
	}
	
	////// TO DO : Traiter les collisions

	return true;

}