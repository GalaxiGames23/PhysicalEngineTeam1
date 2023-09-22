#pragma once
#include "Particule.h"

class FireBallParticule : public Particule
{
private:
	int nbBounce = 2;
public:
	FireBallParticule() : Particule() {};
	BouncingParticule(double invertMass, Vector position, Vector velocity) :Particule(invertMass, position, velocity) {
		this->c = ofColor::magenta;
	};
	void BouncingParticule::onCollisionDetected(vector<Particule*>& allParticles, int index) override;

};