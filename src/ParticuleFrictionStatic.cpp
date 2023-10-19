#include "ParticuleFrictionStatic.h"

/////Constructors
ParticuleFrictionStatic::ParticuleFrictionStatic()
{
	this->us = 0.0f;
	this->g = Vector(0, 9.81f, 0);
}

ParticuleFrictionStatic::ParticuleFrictionStatic(Vector g)
{
	this->us = 1.0f;
	this->g = g;
}

ParticuleFrictionStatic::ParticuleFrictionStatic(Vector g, double us) {
	this->us = us;
	this->g = g;
}

////////
void ParticuleFrictionStatic::updateForce(Particule* p, float duration) // To Update just after gravity !!!
{
	Vector r; // Vecteur normal à la direction et opposé aux forces
	Vector direction; // Direction de la force de friction
	Vector force; // Force de friction résultante
	Vector gk;

	direction = Vector() - p->GetDirection();

	gk = g.projection(p->GetDirection());
	r = Vector() - (g + gk);
	force = us * r.norm() * direction;

	if (gk.norm() <= force.norm())
	{
		force = Vector() - g;
	}
	p->addForce(force);
}