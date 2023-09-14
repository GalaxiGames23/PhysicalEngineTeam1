#include <cstdlib>
#include <cmath>
#include "Vector.h"


Vector::Vector()
{
	x = 0;
	y = 0;
	z = 0;
	w = 1;
}

Vector::Vector(double x, double y, double z) {
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = 1;
}

void Vector::set(double x, double y, double z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

double Vector::norm() const
{
	return sqrt(this->square_norm());
}

double Vector::square_norm() const
{
	return x * x + y * y + z * z;
}

Vector Vector::normalisation() const
{
	const double norm = this->norm();
	if (norm == 0)
	{
		return *this;
	}
	else
	{
		return (1/ norm) * Vector(x, y, z);
	}
}


double Vector::prod_scalar(const Vector& v) const
{
	return x * v.x + y * v.y + z * v.z;
}

Vector Vector::prod_vector(const Vector& v) const
{
	return Vector(y * v.z - v.y * z, z * v.x - v.z * x, x * v.y - v.x * y);
}

Vector Vector::operator *(const Vector& v) const
{
	return Vector(x * v.x, y * v.y, z * v.z);
}
Vector Vector::operator *(const double& a) const
{
	return Vector(a * x, a * y, a * z);
}

Vector Vector::operator +(const Vector& v) const
{
	return Vector(x + v.x, y + v.y, z + v.z);
}

Vector Vector::operator -(const Vector& v) const
{
	return Vector(x - v.x, y - v.y, z - v.z);
}

glm::vec2 Vector::toVec2() const
{
	return glm::vec2(x, y);
}

glm::vec3 Vector::toVec3() const
{
	return glm::vec3(x, y, z);
}


Vector operator*(const double& a, const Vector& v)
{
	return Vector(a * v.x, a * v.y, a * v.z);
}
