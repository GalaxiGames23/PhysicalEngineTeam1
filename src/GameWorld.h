#ifndef GAMEWORLD_H
#define GAMEWORLD_H

#include "Particule.h"
#include "ParticuleForceGenerator.h"
#include "ParticuleForceRegistry.h"
#include "ParticuleGravity.h"
#include "ParticuleSpring.h"
#include "ParticuleFrictionStatic.h"
#include "Ground.h"
#include "Sphere.h"
#include <iostream>
#include <cstdlib>
#include <vector>

using namespace std;

class GameWorld
{
	struct Spring {
		Sphere* particule1;
		ParticuleSpring* spring;
	};

public:
	std::vector<Sphere*> systemeSpheres;//<<< Vector de la STL pour stocker les sphères à considérer dans les calculs

	std::vector<ParticuleForceGenerator*> forces; //<<< forces présentes dans le gameworld

	std::vector<Spring*> springList;

	ParticuleGravity worldGravity;

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