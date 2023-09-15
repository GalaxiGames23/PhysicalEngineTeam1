#pragma once

#ifndef PARTICULE_H
#define PARTICULE_H

#include "Vector.h"
#include <iostream>
#include <string>

using namespace std;

class Particule
{
private:
	double invertMass;
	double time;
	double distance;

public:
	// Constructors
	Particule();
	Particule(double invertMass, double time, double distance);

	// Setters
	void SetMass(double mass) { this->invertMass = invertMass; }
	void SetTime(double time) { this->time = time; }
	void SetDistance(double distance) { this->distance = distance; }

	// Getters
	double GetMass() { return this->invertMass; }
	double GetTime() { return this->time; }
	double GetDistance() { return this->distance; }

	// ToString
	friend ostream& operator<< (ostream&, const Particule& particle);

	// Integrator



};

#endif

