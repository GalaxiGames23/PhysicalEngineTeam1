#include "glm/glm.hpp"
class Vector
{
	public:
		double x;
		double y;
		double z;
		double w;

		Vector();

		Vector(double x, double y, double z);

		double norm() const;
		double square_norm() const;
		Vector normalisation() const;

		double prod_scalar(const Vector& v) const;

		Vector prod_vector(const Vector& v) const ;

		Vector operator *(const Vector &v) const;
		Vector operator *(const double& a) const;

		Vector operator +(const Vector& v) const;

		friend Vector operator*(const double& a, const Vector& vec);

		Vector operator -(const Vector& v) const;

		glm::vec2 toVec2() const;

		glm::vec3 toVec3() const;
};