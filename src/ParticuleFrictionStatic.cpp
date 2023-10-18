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
	Vector r; // Vecteur normal à la direction et opposé aux forces
	Vector direction; // Direction de la force de friction
	Vector force; // Force de friction résultante
	Vector gk;

	direction = Vector() - p->GetDirection();

	gk = p->GetAccumForce().projection(p->GetDirection());
	r = Vector() - (p->GetAccumForce() + gk);
	force = us * r.norm() * direction;

	if (gk.norm() <= force.norm())
	{
		force = Vector() - p->GetAccumForce();
	}
	p->addForce(force);
}