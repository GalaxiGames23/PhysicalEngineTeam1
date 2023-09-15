#include "Particule.h"

// Constructors

Particule::Particule() {
	this->invertMass = 0;
	this->time = 0;
	this->distance = 0;
}

Particule::Particule(double invertMass, double time, double distance) {
	this->invertMass = invertMass;
	this->time = time;
	this->distance = distance;
}

// ToString
ostream& operator<< (ostream& out, const Particule& particule)
{
	out << "--- Particule ---\nMass : " << particule.invertMass << "\nTime : " << particule.time << "\n Distance : " << particule.distance << "\n-----------------";
	return out;
}

// Integrator

