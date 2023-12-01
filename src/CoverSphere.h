#ifndef COVERSPHERE_H
#define COVERSPHERE_H


#include "Rigid.h"

class CoverSphere
{
private:
	Rigid* rb; // <<< RigidBody englobé par la sphère
	Vector center; // <<< Centre de la sphère
	double radius; // <<< Rayon de la sphère la sphère

public :
	///// Contructor / Destructor /////
	
	CoverSphere(Rigid* rb, double radius);
	~CoverSphere() {};

	///// Getters /////

	Rigid* GetRb() { return this->rb;  };
	Vector GetCenter() { return this->center; };
	double GetRadius() { return this->radius; };

	///// Setters /////

	void SetRb(Rigid* rb) { this->rb = rb; };
	void SetCenter(Vector center) { this->center = center; };
	void SetRadius(double radius) { this->radius = radius; };
};

#endif