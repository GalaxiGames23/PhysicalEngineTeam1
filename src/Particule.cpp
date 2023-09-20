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
	this->lastPosition = Vector(0, 0, 0);
}

// ToString
ostream& operator<< (ostream& out, const Particule& particule)
{
	out << "--- Particule ---\nMass : " << particule.invertMass << "\nTime : " << particule.position << "\n Distance : " << particule.velocity << "\n-----------------";
	return out;
}

// Integrators
void Particule::IntegrateEuler(float duration, Vector gravity, float damping)
{
	this->velocity = pow(damping, duration) * this->velocity + duration * gravity;
	this->position = pow(damping, duration) * this->position + duration * this->velocity;
}

void Particule::SetFirstLastPosition(float duration) {
	this->lastPosition = this->position - duration * this->velocity;
}


void Particule::IntegrateVerlet(float duration, Vector gravity)
{
	Vector storeActualPos = this->position;
	this->position = 2 * this->position - this->lastPosition + pow(duration, 2) * gravity;
	this->lastPosition = storeActualPos;
}