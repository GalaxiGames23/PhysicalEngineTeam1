#include "ParticuleFrictionStatic.h"

//////// Constructors ////////

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


//////// Methods ////////

void ParticuleFrictionStatic::updateForce(Particule* p, float duration)
{
	Vector n; // Vecteur normal à la direction et opposé aux forces
	Vector direction; // Direction de la force de friction
	Vector force; // Force de friction résultante
	Vector gk;

	direction = Vector() - p->GetDirection();

	gk = g.projection(p->GetDirection());
	n = Vector() - (g + gk);
	force = us * n.norm() * direction; // F = us * n

	if (gk.norm() <= force.norm())
	{
		force = Vector() - g;
	}
	p->addForce(force);
}