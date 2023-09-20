#include "Particule.h"

// Constructors

Particule::Particule()
{
	this->invertMass = 0;
	this->position = Vector();
	this->velocity = Vector();
}

Particule::Particule(double invertMass, Vector position, Vector velocity)
{
	this->invertMass = invertMass;
	this->position = position;
	this->velocity = velocity;
}

// ToString
ostream& operator<< (ostream& out, const Particule& particule)
{
	out << "--- Particule ---\nMass : " << particule.invertMass << "\nTime : " << particule.position << "\n Distance : " << particule.velocity << "\n-----------------";
	return out;
}

// Integrator
void Particule::Integrate(float duration, Vector gravity, float damping)
{
	this->velocity = pow(damping, duration) * this->velocity + duration * gravity;
	this->position = pow(damping, duration) * this->position + duration * this->velocity;
}