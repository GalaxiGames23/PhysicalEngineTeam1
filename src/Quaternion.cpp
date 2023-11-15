#include "Quaternion.h"

///// Constructeurs /////

Quaternion::Quaternion()
{
	this->w = 0;
	this->v = Vector();
}

Quaternion::Quaternion(double w, Vector v)
{
	this->w = w;
	this->v = v;
}

Quaternion::Quaternion(Quaternion& q)
{
	this->w = q.w;
	this->v = q.v;
}


///// Operations /////

double Quaternion::Norm() const
{
	return sqrt(pow(this->w, 2) + this->v.square_norm());
}

double Quaternion::ScalarProduct(Quaternion& q) const
{
	return this->w * q.w + this->v.prod_scalar(q.v);
}

Quaternion Quaternion::Negation() const
{
	return Quaternion(-this->w, this->v.Negation());
}

Quaternion Quaternion::Conjugated() const
{
	return Quaternion(this->w, this->v.Negation());
}

Quaternion Quaternion::Invers() const
{
	return this->Conjugated() * (1 / (this->Norm() * this->Norm()));
}

Quaternion Quaternion::Difference(Quaternion& q) const
{
	return q * this->Conjugated();
}

Matrix3 Quaternion::ToMatrix() const
{
	std::array<float, 9> coefs;

	coefs[0] = 1 - 2*(pow(this->v.get_y(), 2) + pow(this->v.get_z(), 2));
	coefs[1] = 2 * ((this->v.get_x() * this->v.get_y()) - (this->v.get_z() * this->w));
	coefs[2] = 2 * ((this->v.get_x() * this->v.get_z()) + (this->v.get_y() * this->w));

	coefs[3] = 2 * ((this->v.get_x() * this->v.get_y()) + (this->v.get_z() * this->w));
	coefs[4] = 1 - 2 * (pow(this->v.get_x(), 2) + pow(this->v.get_z(), 2));
	coefs[5] = 2 * ((this->v.get_y() * this->v.get_z()) - (this->v.get_x() * this->w));

	coefs[6] = 2 * ((this->v.get_x() * this->v.get_z()) - (this->v.get_y() * this->w));
	coefs[7] = 2 * ((this->v.get_y() * this->v.get_z()) + (this->v.get_x() * this->w));
	coefs[8] = 1 - 2 * (pow(this->v.get_x(), 2) + pow(this->v.get_y(), 2));
	
	return Matrix3(coefs);
}


// Operators //

Quaternion Quaternion::operator *(const double& a) const
{
	return Quaternion(a * this->w,a * this->v);
}

Quaternion Quaternion::operator *(const Quaternion& q) const
{
	double scalar = this->w * q.w - this->v.prod_scalar(q.v);
	Vector vector = (this->w * q.v) + (q.w * this->v) + (this->v.prod_vector(q.v));

	return Quaternion(scalar, vector);
}

Quaternion Quaternion::operator -(const Quaternion& q) const
{
	return Quaternion(w - q.w, this->v - q.v);
}

Quaternion Quaternion::operator +(const Quaternion& q) const
{
	return Quaternion(this->w + q.w, this->v + q.v);
}

Quaternion Quaternion::operator ^(const double& t) const
{
	double alpha = acos(this->w);

	double scalar = cos(t * alpha);
	Vector vector = (sin(t * alpha) / sin(alpha)) * this->v;

	return Quaternion(scalar, vector);
}


bool Quaternion::operator ==(const Quaternion& q) const
{
	return (this->w == q.w) && (this->v == q.v);
}

bool Quaternion::operator !=(const Quaternion& q) const
{
	return !((this->w == q.w) && (this->v == q.v));
}


///// To String /////

ostream& operator<< (ostream& out, const Quaternion& q)
{
	out << "(" << q.w << " " << q.v << ")";
	return out;
}