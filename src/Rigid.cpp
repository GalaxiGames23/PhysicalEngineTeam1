#include "Rigid.h"

Rigid::Rigid(const Rigid& rigid) 
{
	this->centerOfMass = rigid.centerOfMass;
	this->orientationQuat = rigid.orientationQuat;
	this->orientationMat = rigid.orientationMat;
	this->omega = rigid.omega;
	this->alpha = rigid.alpha;
	this->scale = rigid.scale;

	this->J = rigid.J;
	this->accumTorque = rigid.accumTorque;
}

Rigid::Rigid(Particule centerOfMass, Matrix3 orientationMat, Vector omega, Vector alpha, Vector scale)
{
	this->centerOfMass = centerOfMass;
	this->orientationQuat = orientationMat.toQuaternion();
	this->orientationMat = orientationMat;
	this->omega = omega;
	this->alpha = alpha;

	this->scale = scale;
	this->J = Matrix3(); // Valeur par d�faut pour les RigidBody non h�rit�s !
	this->accumTorque = Vector(); // Accumulateur vide � l'initialisation
}


// Int�grateurs du RigidBody

void Rigid::RigidIntegrator(float duration)
{
	this->centerOfMass.IntegrateEulerWithAccum(duration);
	this->AngularIntegrator(duration);
}

void Rigid::AngularIntegrator(float duration)
{
	Matrix3 JInversRotat = this->orientationMat * this->J.Invers() * this->orientationMat.Transposed(); // Calcul du tenseur d'inertie en fonction de l'orientation
	this->alpha = JInversRotat * this->accumTorque; // Calcul de l'acc�l�ration angulaire

	this->omega = this->omega + this->alpha * duration; // Set omega

	Quaternion w = Quaternion(0, this->omega);
	this->orientationQuat = this->orientationQuat + (w * this->orientationQuat) * 0.5 * duration;  // Set orientationQuat
	this->orientationQuat = this->orientationQuat * (1 / this->orientationQuat.Norm()); // Normalisation of orientationQuat

	this->orientationMat = this->orientationQuat.ToMatrix(); // Set orientationMat
}

void Rigid::ClearAccums() 
{
	this->centerOfMass.clearAccum();
	this->accumTorque = Vector(0, 0, 0);
}



void Rigid::addTorque(const Vector force, const Vector pointAppli)
{
	Vector l = force - pointAppli; // Calcul du bras de levier
	this->accumTorque = this->accumTorque + force * l;
}