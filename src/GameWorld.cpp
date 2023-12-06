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
		if (rigidBodies[i]->GetCenter()->GetPosition().get_y() >= 500)
		{
			octree.eraseRigid(rigidBodies[i]);
			rigidBodies.erase(rigidBodies.begin() + i);
		}
		else
		{
		rigidBodies[i]->RigidIntegrator(duration);

		//on vide l'accumulateur
		rigidBodies[i]->ClearAccums();

		}

	}

	vector<RigidPair*> allCollisionFrame =  octree.allPossibleCollision();
	boxPairs = octree.convertToBox(allCollisionFrame);

	/*TO DO: TRAITEMENT DES COLLISIONS*/
	HandleCollisions();


	octree.freePossibleCollision(allCollisionFrame, boxPairs);

	//gestion de la trace 
	UpdateTrace(duration);

	myCam->setPosition();
	basicCam->setPosition();
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

	Vector pointCollision = Vector(); // Point de collision des boxes
	Plane plan = Plane();
	Vector normal;
	switch (collidingVertices.size())
	{
	case 1:
		pointCollision = *collidingVertices[0];
		break;
	case 2:
		pointCollision = 0.5f * (*collidingVertices[0] + *collidingVertices[1]);
		break;
	case 4:
		// Calcul de la normale du plan à partir de deux vecteurs du plan
		 normal = (*collidingVertices[0] - *collidingVertices[1]).prod_vector(*collidingVertices[0] - *collidingVertices[2]);
		plan = Plane(normal, *collidingVertices[3]);
		pointCollision = plan.ComputeR(box1->GetCenter()->GetPosition());
		break;
	default:
		return false;
		break;
	}

	std::cout << "Detect collision" << std::endl;
	
	////// TO DO : Traiter les collisions (avec Point collision pour les deux boites en point d'application)
	////// A noter : Pour la direction de la force : Utiliser la direction du vecteur vitesse de la boite concernée (Pas hesiter à redemander)

	return true;

}