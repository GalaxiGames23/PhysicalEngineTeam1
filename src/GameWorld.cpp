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
		if (rigidBodies[i]->GetCenter()->GetPosition().get_y() >= 1300|| abs(rigidBodies[i]->GetCenter()->GetPosition().get_x()) >= 1300|| abs(rigidBodies[i]->GetCenter()->GetPosition().get_z()) >= 1300)
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
	

	// Déplacement des boîtes (par pointage)
	box1->GetCenter()->AddTPOnColliding(box2->GetCenter());
	box2->GetCenter()->AddTPOnColliding(box1->GetCenter());


	// Ajout des forces de collision aux 2 boîtes

	double expNormForce = 200;

	RigidBodyForce *forceCollisionsBox1 = new RigidBodyForce(collisionPoint, expNormForce * box2->GetCenter()->GetVelocity().normalisation());
	RigidBodyForce *forceCollisionsBox2 = new RigidBodyForce(collisionPoint, expNormForce * box1->GetCenter()->GetVelocity().normalisation());

	registreRigids.add(box1, forceCollisionsBox1);
	registreRigids.add(box2, forceCollisionsBox2);
}

////////////////////////DEMOS/////////////////////*
//2 boîtes cubiques
void GameWorld::Demo1() {
	//lancer une boite
	Box* box1 = new Box(Particule(1.0, Vector(0, 0, 0), Vector(0, 0, 0), 15), Matrix3({ 1,0,0,0,1,0,0,0,1 }), Vector(0, 0, 0), Vector(0, 0, 0), Vector(1, 1, 1), Vector(20, 20, 20));
	this->rigidBodies.push_back(box1);
	RigidBodyForce* force = new RigidBodyForce(box1->GetCenter()->GetPosition(), Vector(100, 0, 0));
	this->registreRigids.add(box1, force);

	this->octree.addRigid(box1);

	//lancer une deuxième boîte boite
	Box* box2 = new Box(Particule(1.0, Vector(100, 0, 0), Vector(0, 0, 0), 15), Matrix3({ 1,0,0,0,1,0,0,0,1 }), Vector(0, 0, 0), Vector(0, 0, 0), Vector(1, 1, 1), Vector(20, 20, 20));
	this->rigidBodies.push_back(box2);
	RigidBodyForce* force2 = new RigidBodyForce(box2->GetCenter()->GetPosition(), Vector(-100, 0, 0));
	this->registreRigids.add(box2, force2);

	this->octree.addRigid(box2);
}

//3 boîtes non cubes
void GameWorld::Demo2()
{
	//lancer une boite
	Box* box1 = new Box(Particule(1.0, Vector(0, 0, 0), Vector(0, 0, 0), 15), Matrix3({ 1,0,0,0,1,0,0,0,1 }), Vector(0, 0, 0), Vector(0, 0, 0), Vector(1, 1, 1), Vector(20, 20, 20));
	this->rigidBodies.push_back(box1);
	RigidBodyForce* force = new RigidBodyForce(box1->GetCenter()->GetPosition(), Vector(100, 0, 0));
	this->registreRigids.add(box1, force);

	this->octree.addRigid(box1);

	//lancer une boîte boite
	Box* box2 = new Box(Particule(1.0, Vector(100, 0, 0), Vector(0, 0, 0), 15), Matrix3({ 1,0,0,0,1,0,0,0,1 }), Vector(0, 0, 0), Vector(0, 0, 0), Vector(1, 1, 1), Vector(20, 15, 5));
	this->rigidBodies.push_back(box2);
	RigidBodyForce* force2 = new RigidBodyForce(box2->GetCenter()->GetPosition(), Vector(-100, 10, 0));
	this->registreRigids.add(box2, force2);

	this->octree.addRigid(box2);

	//lancer une boite
	Box* box3 = new Box(Particule(1.0, Vector(50, 0, 90), Vector(0, 0, 0), 15), Matrix3({ 1,0,0,0,1,0,0,0,1 }), Vector(0, 0, 0), Vector(0, 0, 0), Vector(1, 1, 1), Vector(20, 10, 30));
	this->rigidBodies.push_back(box3);
	RigidBodyForce* force3 = new RigidBodyForce(box3->GetCenter()->GetPosition(), Vector(0, 30, -200));
	this->registreRigids.add(box3, force3);

	this->octree.addRigid(box3);
}

//croisement avec plus d'angle
void GameWorld::Demo3()
{
	//lancer une boite
	Box* box1 = new Box(Particule(1.0, Vector(0, 0, 0), Vector(0, 0, 0), 15), Matrix3({ 1,0,0,0,1,0,0,0,1 }), Vector(0, 0, 0), Vector(0, 0, 0), Vector(1, 1, 1), Vector(20, 20, 20));
	this->rigidBodies.push_back(box1);
	RigidBodyForce* force = new RigidBodyForce(box1->GetCenter()->GetPosition(), Vector(100, 0, 20));
	this->registreRigids.add(box1, force);

	this->octree.addRigid(box1);

	//lancer une deuxième boîte boite
	Box* box2 = new Box(Particule(1.0, Vector(100, -50, 0), Vector(0, 0, 0), 15), Matrix3({ 1,0,0,0,1,0,0,0,1 }), Vector(0, 0, 0), Vector(0, 0, 0), Vector(1, 1, 1), Vector(20, 20, 20));
	this->rigidBodies.push_back(box2);
	RigidBodyForce* force2 = new RigidBodyForce(box2->GetCenter()->GetPosition(), Vector(-100, 100, 0));
	this->registreRigids.add(box2, force2);

	this->octree.addRigid(box2);
}

//feux d'artifice
void GameWorld::Demo4()
{
	for (int i = 0; i < 10; ++i)
	{
		//lancer une boite
		Box* box1 = new Box(Particule(1.0, Vector(200*cos(i/10.0f), 0, 200*sin(i/10.0f)), Vector(0, 0, 0), 15), Matrix3({1,0,0,0,1,0,0,0,1}), Vector(0, 0, 0), Vector(0, 0, 0), Vector(1, 1, 1), Vector(20+i*2, 20+i*3, 20-i));
		this->rigidBodies.push_back(box1);
		RigidBodyForce* force = new RigidBodyForce(box1->GetCenter()->GetPosition(), (Vector()-box1->GetCenter()->GetPosition()).normalisation()*10);
		this->registreRigids.add(box1, force);

		this->octree.addRigid(box1);
	}
}

//masses différentes
void GameWorld::Demo5()
{
	//lancer une boite
	Box* box1 = new Box(Particule(1.0, Vector(0, 0, 0), Vector(0, 0, 0), 15), Matrix3({ 1,0,0,0,1,0,0,0,1 }), Vector(0, 0, 0), Vector(0, 0, 0), Vector(1, 1, 1), Vector(20, 20, 20));
	this->rigidBodies.push_back(box1);
	RigidBodyForce* force = new RigidBodyForce(box1->GetCenter()->GetPosition(), Vector(100, 0, 0));
	this->registreRigids.add(box1, force);

	this->octree.addRigid(box1);

	//lancer une deuxième boîte boite
	Box* box2 = new Box(Particule(50.0, Vector(150, -100, 0), Vector(0, 0, 0), 15), Matrix3({ 1,0,0,0,1,0,0,0,1 }), Vector(0, 0, 0), Vector(0, 0, 0), Vector(1, 1, 1), Vector(30, 20, 30));
	this->rigidBodies.push_back(box2);
	RigidBodyForce* force2 = new RigidBodyForce(box2->GetCenter()->GetPosition(), Vector(-100, 0, 0));
	this->registreRigids.add(box2, force2);

	this->octree.addRigid(box2);
}