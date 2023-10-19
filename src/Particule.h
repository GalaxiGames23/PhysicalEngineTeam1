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
	bool isStatic = false;

	////////Phase 2/////
	Vector AccumForce; //<<<Force résultante pour la particule
	float time = 0;
	Vector position0;
	Vector velocity0;
	
protected :
	bool isPresetVerlet;
	Vector position;
	Vector velocity;
	double InversMass;
	double e; // Coefficient d'élasticité

public:
	// Constructors
	Particule();
	Particule(double mass, Vector position, Vector velocity, double e);
	// Setters
	void SetMass(double mass) { this->InversMass = 1/mass; }
	void SetPosition(Vector position) { this->position = position; }
	void SetLastPosition(Vector lastPosition) { this->lastPosition = lastPosition; }
	void SetVelocity(Vector velocity) { this->velocity = velocity; }

	// Getters
	double GetMass() { return  1 / this->InversMass; }
	Vector GetPosition() { return this->position; }
	Vector GetLastPosition() { return this->lastPosition; }
	Vector GetVelocity() { return this->velocity; }
	bool particleCanMove() { return !isStatic; }
	Vector GetAccumForce() { return this->AccumForce; }

	Vector GetDirection();


	// ToString
	friend ostream& operator<< (ostream&, const Particule& particle);
	
	// Integrators
	void IntegrateEuler(float duration, Vector gravity, float damping);
	void IntegrateVerlet(float duration, Vector gravity, float damping);


	// Manage collisions
	virtual void onCollisionDetected( vector<Particule*> &allParticles);
	Vector calculGravitationAccelerationWith(Particule* p);

	////////Phase 2/////
	void addForce(const Vector& force); //AccumForce += force
	void clearAccum();// vide l'accumulateur

	void IntegrateEulerWithAccum(float duration);

	void HarmonicMovement(double K, float time); // K : Constante d'élasticité
	void HarmonicMovementDamping(double K, double c, float time); // K : Constante de friction

	double distanceParticules(Particule* p);

	void AddVelocityOnColliding(Particule* p);
	void AddVelocityOnColliding(double groundY);

	void SetUpHarmonic();
};

#endif