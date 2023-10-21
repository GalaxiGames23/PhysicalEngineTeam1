#include "InputForce.h"

InputForce::InputForce(PlayerController* p, bool isForward, int positiveDirection)
{
	this->controller = p;
	this->positiveDirection = positiveDirection;
	this->isForward = isForward;
}

void InputForce::updateForce(Particule* particule, float duration)
{
	Vector force;
	if (isForward)
	{
		force = controller->getForwardDirection(positiveDirection * power);
	}
	else
	{
		force = controller->getRightDirection(positiveDirection * power);
	}
	particule->addForce(force);
}
