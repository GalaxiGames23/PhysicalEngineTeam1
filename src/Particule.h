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
	Vector lastPosition;

protected :
	Vector position;
	Vector velocity;
	double invertMass;

public:
	// Constructors
	Particule();
	Particule(double invertMass, Vector position, Vector velocity);

	// Setters
	void SetMass(double mass) { this->invertMass = 1/mass; }
	void SetPosition(Vector position) { this->position = position; }
	void SetLastPosition(Vector lastPosition) { this->lastPosition = lastPosition; }
	void SetVelocity(Vector velocity) { this->velocity = velocity; }

	void SetFirstLastPosition(float duration);

	// Getters
	double GetMass() { return 1/this-> invertMass; }
	Vector GetPosition() { return this->position; }
	Vector GetLastPosition() { return this->lastPosition; }
	Vector GetVelocity() { return this->velocity; }

	// ToString
	friend ostream& operator<< (ostream&, const Particule& particle);

	// Integrators
	void IntegrateEuler(float duration, Vector gravity, float damping);
	void IntegrateVerlet(float duration, Vector gravity);
};

#endif