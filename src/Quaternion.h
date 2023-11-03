#ifndef QUATERNION_H
#define QUATERNION_H

#include "Vector.h"
#include <iostream>
#include <math.h> 

class Quaternion
{
private:
	///// Attributs /////
	double w;
	Vector v;

public:
	///// Constructeurs /////

	Quaternion();
	Quaternion(double w, Vector v);
	Quaternion(Quaternion& q);

	///// Getters /////

	double GetW() { return this->w; };
	Vector GetV() { return this->v; };

	///// Setters /////

	void SetW(double w) { this->w = w; };
	void SetV(Vector v) { this->v = v; };

	void SetVX(double x) { this->v.set_x(x); };
	void SetVY(double y) { this->v.set_y(y); };
	void SetVZ(double z) { this->v.set_z(z); };

	///// Opérations /////

	double Norm() const;
	double ScalarProduct(Quaternion& q) const;

	Quaternion Negation() const;
	Quaternion Conjugated() const;
	Quaternion Invers() const;


	// Operators //

	Quaternion operator *(const Quaternion& q) const;
	Quaternion operator *(const double& a) const;

	Quaternion operator +(const Quaternion& q) const;
	Quaternion operator -(const Quaternion& q) const;

	Quaternion operator ^(const double& t) const;

	bool operator ==(const Quaternion& q) const;
	bool operator !=(const Quaternion& q) const;


	///// To String /////

	friend ostream& operator<< (ostream&, const Quaternion& q);
};

#endif