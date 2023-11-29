#include "CoverSphere.h"

CoverSphere::CoverSphere(Rigid* rb, double radius)
{
	this->rb = rb;
	this->radius = radius;
	this->center = rb->GetCenter()->GetPosition();
}