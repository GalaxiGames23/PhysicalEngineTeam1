#include "ParticuleSpring.h"

/////Constructors
ParticuleSpring::ParticuleSpring()
{
	this->k = 0;
	this->l0 = 0;

	this->v = Vector(0.0f, 0.0f, 0.0f);
	this->p2 = &Particule();
	this->isP2P = false;
}

ParticuleSpring::ParticuleSpring(double k, double l0, Particule* p2) {
	this->k = k;
	this->l0 = l0;

	this->p2 = p2;
	this->isP2P = true;
}

ParticuleSpring::ParticuleSpring(double k, double l0, Vector v) {
	this->k = k;
	this->l0 = l0;

	this->v = v;
	this->p2 = &Particule();
	this->isP2P = false;
}

////////

void ParticuleSpring::updateForce(Particule* p1, float duration)
{
	double l; // Longueur actuelle entre les deux points
	Vector direction; // Direction entre les deux points
	Vector force; // Force de ressort résultante

	if (this->isP2P)
	{
		l = p1->GetPosition().distance(this->p2->GetPosition());
		direction = (this->p2->GetPosition() - p1->GetPosition()).normalisation();

		Vector force = this->k * (this->l0 - l) * direction;
		this->p2->addForce(Vector() - force);
	}
	else
	{
		l = p1->GetPosition().distance(this->v);
		direction = (this->v - p1->GetPosition()).normalisation();

		Vector force = this->k * (this->l0 - l) * direction;
	}
	p1->addForce(force);
}