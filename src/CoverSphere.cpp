#include "CoverSphere.h"

CoverSphere::CoverSphere(Rigid* rb)
{
	this->rb = rb;
	this->radius = rb->GetSize().norm();
	this->center = rb->GetCenter()->GetPosition();
}