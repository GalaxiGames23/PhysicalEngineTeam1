#ifndef VECTOR_H
#define VECTOR_H

#include "glm/glm.hpp"

#include <cstdlib>
#include <cmath>
#include "Vector.h"

#include <iostream>

using namespace std;

class Vector
{
	private:
		double x;
		double y;
		double z;
		double w;
	public:
		Vector();

		Vector(double x, double y, double z);

		void set(double x, double y, double z);

		Vector set_x(double y);
		Vector set_y(double y);
		Vector set_z(double y);

		double get_x() const;
		double get_y() const;
		double get_z() const;

		double norm() const;
		double square_norm() const;
		Vector normalisation() const;

		double prod_scalar(const Vector& v) const;

		Vector prod_vector(const Vector& v) const ;

		Vector projection(const Vector& v) const;

		double distance(const Vector& v) const;

		Vector operator *(const Vector &v) const;
		Vector operator *(const double& a) const;

		Vector operator +(const Vector& v) const;
		bool operator ==(const Vector& v) const;
		bool operator !=(const Vector& v) const;

		friend Vector operator*(const double& a, const Vector& vec);
		friend ostream& operator<< (ostream&, const Vector& vec);

		Vector operator -(const Vector& v) const;

		glm::vec2 toVec2() const;

		glm::vec3 toVec3() const;

		Vector Negation() const;
};

#endif