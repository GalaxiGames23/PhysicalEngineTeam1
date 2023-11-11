#include "Rigid.h"

Rigid::Rigid(const Rigid& rigid) 
{
	this->centerOfMass = rigid.centerOfMass;
	this->orientationQuat = rigid.orientationQuat;
	this->orientationMat = rigid.orientationMat;
	this->omega = rigid.omega;
	this->alpha = rigid.alpha;
	this->scale = rigid.scale;
}

Rigid::Rigid(Particule centerOfMass, Matrix3 orientationMat, Vector omega, Vector alpha, Vector scale)
{
	this->centerOfMass = centerOfMass;
	this->orientationQuat = orientationMat.toQuaternion();
	this->orientationMat = orientationMat;
	this->omega = omega;
	this->alpha = alpha;
	this->scale = scale;
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
	std::cout << "omega Vector " << omega << "\n";
	Quaternion w = Quaternion(0, this->omega);
	this->orientationQuat = (w * this->orientationQuat) * this->orientationQuat * 0.5 * duration;  // Set orientationQuat
	std::cout << "Quaternion " << orientationQuat << "\n";
	this->orientationMat = this->orientationQuat.ToMatrix(); // Set orientationMat
}

void Rigid::ClearAccum() 
{
	this->centerOfMass.clearAccum();
}