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

double Quaternion::Norm()
{
	return sqrt(pow(this->w, 2) + this->v.square_norm());
}

double Quaternion::ScalarProduct(Quaternion& q)
{
	return this->w * q.w + this->v.prod_scalar(q.v);
}

Quaternion Quaternion::Negation()
{
	return Quaternion(-this->w, this->v.Negation());
}

Quaternion Quaternion::Conjugated()
{

}

Quaternion Quaternion::Invers()
{

}



Vector Vector::operator *(const Vector& v) const
{
	return Vector(x * v.x, y * v.y, z * v.z);
}

