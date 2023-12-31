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

double Vector::get_x() const
{
	return x;
}

double Vector::get_y() const
{
	return y;
}

double Vector::get_z() const
{
	return z;
}

double Vector::GetCoordByIndex(int index)
{
	switch (index)
	{
	case 0: return this->x;
		break;
	case 1: return this->y;
		break;
	case 2: return this->z;
		break;
	default: return 0;
		break;
	}
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

Vector Vector::projection(const Vector& v) const
{
	return this->prod_scalar(v) * v.normalisation();
}


double Vector::prod_scalar(const Vector& v) const
{
	return x * v.x + y * v.y + z * v.z;
}

Vector Vector::set_x(double x)
{
	this->x = x;
	return *this;
}

Vector Vector::set_y(double y)
{
	this->y = y;
	return *this;
}

Vector Vector::set_z(double z)
{
	this->z = z;
	return *this;
}

Vector Vector::prod_vector(const Vector& v) const
{
	return Vector(y * v.z - v.y * z, z * v.x - v.z * x, x * v.y - v.x * y);
}

double Vector::distance(const Vector& v) const
{
	double diffx = x - v.get_x();
	double diffy = y - v.get_y();
	double diffz = z - v.get_z();
	return sqrt(diffx * diffx + diffy * diffy + diffz * diffz);
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

ostream& operator<< (ostream& out, const Vector& vec)
{
	out << "(" << vec.x << ", " << vec.y << ", " << vec.z << ", " << vec.w << ")";
	return out;
}



bool Vector::operator ==(const Vector& v) const
{
	return x == v.x && y == v.y && z == v.z;
}

bool Vector::operator !=(const Vector& v) const
{
	return !(x == v.x && y == v.y && z == v.z);
}


Vector Vector::Negation() const
{
	return Vector(-this->x, -this->y, -this->z);
}