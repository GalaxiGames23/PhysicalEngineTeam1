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
	////// Phase 1 //////
	Vector lastPosition; // (Pour l'int�gration de Verlet)
	bool isStatic = false;

	////// Phase 2 //////
	Vector AccumForce; //<<< Force r�sultante pour la particule

	// Attributs instanci�s � chaque d�but d'oscillation harmonique
	float time = 0; //<<< Temps relatif
	Vector position0; //<<< Position relative
	Vector velocity0; //<<< Vitesse relative
	
protected :
	////// Phase 1 //////
	bool isPresetVerlet; // Pour l'int�gration de Verlet
	Vector position;
	Vector velocity;
	double InversMass;

	////// Phase 2 //////
	double e; // Coefficient d'�lasticit� (Pour les collisions)

public:
	////// Phase 1 //////
	
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
	Vector GetPos0() { return this->position0; }
	Vector GetVel0() { return this->velocity0; }

	// ToString
	friend ostream& operator<< (ostream&, const Particule& particle);
	
	// Integrators
	void IntegrateEuler(float duration, Vector gravity, float damping);
	void IntegrateVerlet(float duration, Vector gravity, float damping);



	////// Phase 2 //////

	// Gestion des forces //
	void addForce(const Vector force); //AccumForce += force
	void clearAccum();// Vide l'accumulateur (force r�sultante = 0)
	void IntegrateEulerWithAccum(float duration); // Calcul de la v�locit� et de la position
	void AddForceOnRod(Particule* p, float duration);

	// Getters exotiques //
	double distanceParticules(Particule* p); // Calcul de la distance entre 2 particules
	Vector GetDirection(); // Calcul de la direction de mouvement d'une particule


	// Mouvements harmoniques //
	void SetUpHarmonic(); // Initialisation des conditions initiales et du temps relatif
	void HarmonicMovement(double K, float time); // K : Constante d'�lasticit�
	void HarmonicMovementDamping(double K, double c, float time); // K : Constante de friction


	// Collisions //
	void AddVelocityOnColliding(Particule* p); // Collision (donc rebond fonction de la masse) avec une autre particule
	void AddVelocityOnColliding(double groundY); // Collision (donc rebond fonction de la masse) avec le sol
	void NullifyVelocityAlongNormal(Vector normale); // Retirer la vitesse en y pour les particules au sol uniquement soumises � la gravit�

	void AddVelocityOnCable(Particule* p, double e); // Collision avec le cable (en longueur maximum) vers la particule reli�e
};

#endif