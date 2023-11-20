#pragma once
#include "Rigid.h"

class RigidBodyForceGenerator
{
public:
	//update de la force sur un corps rigide
	virtual void updateForce(Rigid* rigidBody, float duration) = 0;
	virtual void draw() = 0;
};

