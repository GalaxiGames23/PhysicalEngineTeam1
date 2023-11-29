#include "Plane.h"


///// Contructor /////

Plane::Plane(Vector normal, Vector point)
{
	this->normal = normal.normalisation();
	this->point = point;
}

///// Functions /////

double Plane::ComputeT(Vector Q)
{
	return this->normal.prod_scalar(Q - this->point);
}

Vector Plane::ComputeR(Vector Q)
{
	return Q - this->ComputeT(Q) * this->normal;
}