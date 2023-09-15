#include "Particule.h"

// Constructors

Particule::Particule()
{
	this->invertMass = 0;
	this->position = Vector();
	this->velocity = Vector();
	this->gravity = Vector(0, -9.81, 0);
}

Particule::Particule(double invertMass, Vector position, Vector velocity, Vector gravity)
{
	this->invertMass = invertMass;
	this->position = position;
	this->velocity = velocity;
	this->gravity = gravity;
}

// ToString
ostream& operator<< (ostream& out, const Particule& particule)
{
	out << "--- Particule ---\nMass : " << particule.invertMass << "\nTime : " << particule.position << "\n Distance : " << particule.velocity << "\n Gravity : " << particule.gravity << "\n-----------------";
	return out;
}

// Integrator
void Particule::Integrate(float duration)
{
	this->velocity = this->velocity + duration * this->gravity;
	this->position = this->position + duration * this->velocity;
}