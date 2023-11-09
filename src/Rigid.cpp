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


// Intégrateurs du RigidBody

void Rigid::RigidIntegrator(float duration)
{
	this->centerOfMass.IntegrateEulerWithAccum(duration);
	this->AngularIntegrator(duration);
}

void Rigid::AngularIntegrator(float duration)
{
	this->omega = this->omega + this->alpha * duration; // Set omega
	
	Quaternion w = Quaternion(0, this->omega);
	this->orientationQuat = (w * this->orientationQuat) * this->orientationQuat * 0.5 * duration;  // Set orientationQuat

	this->orientationMat = this->orientationQuat.ToMatrix(); // Set orientationMat
}

void Rigid::ClearAccum() 
{
	this->centerOfMass.clearAccum();
}