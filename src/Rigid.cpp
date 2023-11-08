#include "Rigid.h"

Rigid::Rigid(const Rigid& rigid) 
{
	this->centerOfMass = rigid.centerOfMass;
	this->orientationQuat = rigid.orientationQuat;
	this->orientationMat = rigid.orientationMat;
	this->omega = rigid.omega;
	this->alpha = rigid.alpha;
}

Rigid::Rigid(Particule centerOfMass, Quaternion orientationQuat, Matrix3 orientationMat, Vector omega, Vector alpha)
{
	this->centerOfMass = centerOfMass;
	this->orientationQuat = orientationQuat;
	this->orientationMat = orientationMat;
	this->omega = omega;
	this->alpha = alpha;
}