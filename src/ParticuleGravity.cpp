#include "ParticuleGravity.h"

/////Constructors
ParticuleGravity::ParticuleGravity()
{
	gravity = Vector(0.0f, 9.81f, 0.0f);
}

ParticuleGravity::ParticuleGravity(Vector gravity) {
	this->gravity = gravity;
}

////////
void ParticuleGravity::updateForce(Particule* particule, float duration)
{
	if (particule->GetMass() != 0) // Force appliqu�e uniquement sur les objets non statiques
	{
		particule->addForce(gravity * particule->GetMass()); // P = m * g
	}
}