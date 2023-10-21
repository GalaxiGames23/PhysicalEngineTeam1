#ifndef GAMEWORLD_H
#define GAMEWORLD_H

#include "Particule.h"
#include "ParticuleForceGenerator.h"
#include "ParticuleForceRegistry.h"
#include "ParticuleGravity.h"
#include "ParticuleSpring.h"
#include "Blob.h"
#include "ParticuleFrictionStatic.h"
#include "ParticuleFrictionCinetic.h"
#include "Ground.h"
#include "Sphere.h"
#include "InputForce.h"
#include "Input.h"
#include <iostream>
#include <cstdlib>
#include <vector>

using namespace std;

struct Spring {
	Particule* particule1;
	ParticuleSpring* spring;
};

class GameWorld
{
public:
	std::vector<Sphere*> systemeSpheres;//<<< Vector de la STL pour stocker les sphères à considérer dans les calculs

	std::vector<ParticuleForceGenerator*> forces; //<<< forces présentes dans le gameworld

	std::vector<Spring*> springList;

	std::vector<InputRegistre*> inputRegistre;

	Blob *myBlob = NULL;
	
	Camera* myCam;

	ParticuleGravity worldGravity;

	ParticuleFrictionCinetic worldAirFriction;

	ParticuleForceRegistry registre; //<<<registre des forces

	Ground& ground = Ground::getGround(); // LE SOL

	//Constructors

	GameWorld();

	//calcule les nouvelles position de chaque 
	void UpdateLogic(float duration);

private:
	
	//ajoute les forces au registre
	void addForces();
	void dealCollisions(float duration);
};

#endif