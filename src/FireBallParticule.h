#pragma once

#include "Particule.h"
#define _USE_MATH_DEFINES

#include <cmath>

class FireBallParticule : public Particule
{
	private :
		int nbSpawnParticle = 4;
		int randomNBSpawn = 2;
		double norm = 50.0;
		int randomNorm = 10;
		double angle = 1.0;
		double randomAngle = 0.5;
	
	public:
		FireBallParticule() : Particule() {};
		FireBallParticule(double invertMass, Vector position, Vector velocity) :Particule(invertMass, position, velocity) {this->c = ofColor::paleVioletRed;};
		void onCollisionDetected(vector<Particule*>& allParticles) override;

};