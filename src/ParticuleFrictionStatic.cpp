#include "ParticuleFrictionStatic.h"

/////Constructors
ParticuleFrictionStatic::ParticuleFrictionStatic()
{
	this->us = 0.0f;
}

ParticuleFrictionStatic::ParticuleFrictionStatic(double us) {
	this->us = us;
}

////////
void ParticuleFrictionStatic::updateForce(Particule* p, float duration) // To Update just after gravity !!!
{
	Vector r; // Vecteur normal � la direction et oppos� aux forces
	Vector direction; // Direction de la force de friction
	Vector force; // Force de friction r�sultante

	direction = Vector() - p->GetDirection();
	r = Vector() - (p->GetAccumForce() + p->GetAccumForce().projection(p->GetDirection()));

	force = us * r.norm() * direction;
	p->addForce(force);
}