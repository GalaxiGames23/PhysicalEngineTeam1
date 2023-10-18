#include "ParticuleFrictionCinetic.h"

ParticuleFrictionCinetic::ParticuleFrictionCinetic()
{
	this->k1 = 0.0f;
	this->k2 = 0.0f;
}

ParticuleFrictionCinetic::ParticuleFrictionCinetic(double k1, double k2) {
	this->k1 = k1;
	this->k2 = k2;
}


void ParticuleFrictionCinetic::updateForce(Particule* p, float duration)
{
	Vector velocity; // Accesseur a la vitesse de la particule
	Vector direction; // Direction de la force de friction
	Vector force; // Force de friction résultante

	velocity = p->GetVelocity();
	direction = Vector() - velocity.normalisation();
	force = ((this->k1 * velocity.norm()) + (this->k2 * velocity.square_norm())) * direction;

	p->addForce(force);
}