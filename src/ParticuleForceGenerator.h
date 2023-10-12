#ifndef PARTICULEFORCEGENERATOR_H
#define PARTICULEFORCEGENERATOR_H

#include "Particule.h"

class ParticuleForceGenerator
{
public:
	//update de la force sur une particule
	virtual void updateForce(Particule* particule, float duration) = 0;
};

#endif