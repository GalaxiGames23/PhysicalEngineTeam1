#pragma once

#include "Vector.h"
#include <ctime>

#include <iostream>
using namespace std;

class Particule
{
private:
	Vector position;
	Vector velocity;
	Vector gravity;

protected :
	double invertMass;

public:
	// Constructors
	Particule();
	Particule(double invertMass, Vector position, Vector velocity, Vector gravity);

	// Setters
	void SetMass(double invertMass) { this->invertMass = invertMass; }
	void SetPosition(Vector position) { this->position = position; }
	void SetVelocity(Vector velocity) { this->velocity = velocity; }
	void SetGravity(Vector gravity) { this->gravity = gravity; }

	// Getters
	double GetMass() { return this->invertMass; }
	Vector GetPosition() { return this->position; }
	Vector GetVelocity() { return this->velocity; }
	Vector GetGravity() { return this->gravity; }

	// ToString
	friend ostream& operator<< (ostream&, const Particule& particle);

	// Integrator
	void Integrate(float duration);
};