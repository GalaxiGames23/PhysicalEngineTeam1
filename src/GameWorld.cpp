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
	
	// Ajout des forces au registre
	addForces();

	// Détermination des collisions possibles par l'Octree
	vector<RigidPair*> allCollisionFrame =  octree.allPossibleCollision();
	boxPairs = octree.convertToBox(allCollisionFrame);

	// Détection des collisions dans les collisions possibles
	HandleCollisions();

	// Flush de la mémoire de l'Octree
	octree.freePossibleCollision(allCollisionFrame, boxPairs);

	//////// Traitement des forces et déplacements ////////

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

	box1Vertices.clear();
	box2Planes.clear();
	collidingVertices.clear();
	
	// Résolution des collisions
	ResolveCollisions(box1, box2, pointCollision);

	return true;
}

void GameWorld::ResolveCollisions(Box* box1, Box* box2, Vector collisionPoint)
{
	/*
	float deltaMassBox1 = box1->GetCenter()->GetMass() / (box1->GetCenter()->GetMass() + box2->GetCenter()->GetMass());
	float deltaMassBox2 = box2->GetCenter()->GetMass() / (box1->GetCenter()->GetMass() + box2->GetCenter()->GetMass());

	Vector centreToCentre = box1->GetCenter()->GetPosition() - box2->GetCenter()->GetPosition();

	float distanceBox1 = 0;
	float distanceBox2 = 0;

	for (int i = 0; i < 3; ++i)
	{
		Vector normal1 = box1->GetSize().GetCoordByIndex(i) / 2.0f * box1->GetOrientationMat().GetColumn(i).normalisation();
		Vector projNormal1 = normal1.projection(centreToCentre);
		if (projNormal1.norm() > distanceBox1) distanceBox1 = projNormal1.norm();

		Vector normal2 = box1->GetSize().GetCoordByIndex(i) / 2.0f * box1->GetOrientationMat().GetColumn(i).normalisation();
		Vector projNormal2 = normal2.projection(centreToCentre);
		if (projNormal2.norm() > distanceBox2) distanceBox2 = projNormal2.norm();
	}

	float d = distanceBox1 + distanceBox2 - centreToCentre.norm();

	std::cout << d << endl;
	*/

	// Déplacement des boîtes (par pointage)
	box1->GetCenter()->AddTPOnColliding(box2->GetCenter());
	box2->GetCenter()->AddTPOnColliding(box1->GetCenter());


	// Ajout des forces de collision aux 2 boîtes

	double expNormForce = 200;

	RigidBodyForce *forceCollisionsBox1 = new RigidBodyForce(collisionPoint, expNormForce * box2->GetCenter()->GetVelocity().normalisation());
	RigidBodyForce *forceCollisionsBox2 = new RigidBodyForce(collisionPoint, expNormForce * box1->GetCenter()->GetVelocity().normalisation());

	registreRigids.add(box1, forceCollisionsBox1);
	registreRigids.add(box2, forceCollisionsBox2);

	/*
	Vector directionBox1 = box1->GetCenter()->GetVelocity().normalisation();
	Vector directionBox2 = box2->GetCenter()->GetVelocity().normalisation();

	box1->GetCenter()->SetPosition(box1->GetCenter()->GetPosition() - d * distanceBox1 * directionBox1);
	box2->GetCenter()->SetPosition(box2->GetCenter()->GetPosition() - d * distanceBox2 * directionBox2);
	*/
}