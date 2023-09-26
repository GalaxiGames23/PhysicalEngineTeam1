#pragma once
#include "Particule.h"


//Classe derivée de Particule qui rebondis lorsqu'elle collisionne
class BouncingParticule : public Particule
{
private:
	int nbBounce = 2;
public:
	BouncingParticule() : Particule() {};
	BouncingParticule(double invertMass, Vector position, Vector velocity) :Particule(invertMass, position, velocity) {
		this->c = ofColor::magenta;
	};
	void onCollisionDetected(vector<Particule*>& allParticles) override;

};