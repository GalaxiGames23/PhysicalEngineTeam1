#ifndef PARTICULE_H
#define PARTICULE_H

#include "Vector.h"
#include <ctime>
#include <cmath>

#include <iostream>
using namespace std;

class Particule
{
private:
	Vector position;
	Vector velocity;

protected :
	double invertMass;

public:
	// Constructors
	Particule();
	Particule(double invertMass, Vector position, Vector velocity);

	// Setters
	void SetMass(double mass) { this->invertMass = 1/mass; }
	void SetPosition(Vector position) { this->position = position; }
	void SetVelocity(Vector velocity) { this->velocity = velocity; }

	// Getters
	double GetMass() { return 1/this-> invertMass; }
	Vector GetPosition() { return this->position; }
	Vector GetVelocity() { return this->velocity; }

	// ToString
	friend ostream& operator<< (ostream&, const Particule& particle);

	// Integrator
	void Integrate(float duration, Vector gravity, float damping);
};

#endif