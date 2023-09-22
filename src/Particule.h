#ifndef PARTICULE_H
#define PARTICULE_H

#include "ofColor.h"
#include "Vector.h"
#include <ctime>
#include <cmath>
#include <vector>

#include <iostream>
using namespace std;

class Particule
{
private:
	Vector lastPosition;

protected :
	Vector position;
	Vector velocity;
	double mass;
	ofColor c;

public:
	// Constructors
	Particule();
	Particule(double mass, Vector position, Vector velocity);
	Particule(double mass, Vector position, Vector velocity, ofColor c);

	// Setters
	void SetMass(double mass) { this->mass = 1/mass; }
	void SetPosition(Vector position) { this->position = position; }
	void SetLastPosition(Vector lastPosition) { this->lastPosition = lastPosition; }
	void SetVelocity(Vector velocity) { this->velocity = velocity; }

	void SetFirstLastPosition(float duration);

	// Getters
	ofColor GetColor() { return c; }
	double GetMass() { return this-> mass; }
	double InverseMass() { return 1/this->mass; }
	Vector GetPosition() { return this->position; }
	Vector GetLastPosition() { return this->lastPosition; }
	Vector GetVelocity() { return this->velocity; }

	// ToString
	friend ostream& operator<< (ostream&, const Particule& particle);

	// Integrators
	void IntegrateEuler(float duration, Vector gravity, float damping);
	void IntegrateVerlet(float duration, Vector gravity);

	virtual void onCollisionDetected( vector<Particule*> &allParticles);
	Vector calculGravitationAccelerationWith(Particule* p);
};

#endif