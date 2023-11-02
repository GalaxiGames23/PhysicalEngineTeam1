#ifndef QUATERNION_H
#define QUATERNION_H

#include "Vector.h"

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

	double Norm();
	double ScalarProduct(Quaternion& q);

	Quaternion Negation();
	Quaternion Conjugated();
	Quaternion Invers();


	// Operators //

	Quaternion operator *(Quaternion& q) const;
	Quaternion operator *(const double& a) const;

	Quaternion operator +(Quaternion& q) const;
	Quaternion operator -(Quaternion& q) const;

	Quaternion operator ^(Quaternion& q) const;

	bool operator ==(Quaternion& q) const;
	bool operator !=(Quaternion& q) const;

	friend ostream& operator<< (ostream&, const Quaternion& q);
};

#endif