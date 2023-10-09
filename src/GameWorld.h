#ifndef GAMEWORLD_H
#define GAMEWORLD_H

#include "Particule.h"
#include <iostream>
#include <cstdlib>
#include <vector>

using namespace std;

class GameWorld
{
public:
	std::vector<Particule*> SystemeParticules;//<<< Vector de la STL pour stocker les particules à considérer dans les calculs

	//Constructors

	GameWorld();
};

#endif