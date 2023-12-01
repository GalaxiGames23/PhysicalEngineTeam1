#ifndef COVERSPHERE_H
#define COVERSPHERE_H


#include "Rigid.h"

class CoverSphere
{
private:
	Rigid* rb; // <<< RigidBody englob� par la sph�re
	Vector center; // <<< Centre de la sph�re
	double radius; // <<< Rayon de la sph�re la sph�re

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