#ifndef GAMEWORLD_H
#define GAMEWORLD_H

#include "Particule.h"
#include "ParticuleForceGenerator.h"
#include "ParticuleForceRegistry.h"
#include "ParticuleGravity.h"
#include "ParticuleSpring.h"
#include <iostream>
#include <cstdlib>
#include <vector>

using namespace std;

class GameWorld
{
	struct Spring {
		Particule* particule1;
		ParticuleSpring* spring;
	};

public:
	std::vector<Particule*> systemeParticules;//<<< Vector de la STL pour stocker les particules à considérer dans les calculs

	std::vector<ParticuleForceGenerator*> forces; //<<< forces présentes dans le gameworld

	std::vector<Spring*> springList;

	ParticuleGravity worldGravity;

	ParticuleForceRegistry registre; //<<<registre des forces

	//Constructors

	GameWorld();

	//calcule les nouvelles position de chaque 
	void UpdateLogic(float duration);

private:
	
	//ajoute les forces au registre
	void addForces();
};

#endif