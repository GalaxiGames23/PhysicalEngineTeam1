#pragma once
#include "Particule.h"
#include "Quaternion.h"
#include "Matrix3.h"
#include "Matrix4.h"
#include "Vector.h"

class Rigid
{
protected:
	Particule center = Particule();//<<<centre de rotation sur lequel est appliquée l'intégration linéaire
	Vector centerOfMassOffset = Vector();//<<<centre de masse virtuel, décallage avec le centre de l'object
	Quaternion orientationQuat = Quaternion();//<<<quaternion d'orientation du corps rigide, mis à jour avec l'intégration rotationnelle
	Matrix3 orientationMat = Matrix3();//<<<matrice d'orientation du corps rigide, mise à jour chaque frame grâce au quaternion et à la formule de conversion
	Vector omega = Vector();//<<<vitesse angulaire, mise à jour par l'intégrateur rotationnel chaque frame
	Vector alpha = Vector();//<<<accélération angulaire, mise à jour par l'intégrateur rotationnel chaque frame
	Vector scale = Vector();//<<<scale du rigid body, permet de dessiner des boites de tailles differentes

	Matrix3 J = Matrix3(); //<<< Tenseur d'inertie pour le calcul de l'accélération angulaire
	Vector accumTorque = Vector(); //<<< Torque du rigidbody, obtenu à partir 

public:
	//constructeurs
	Rigid(){} //par défaut
	Rigid(const Rigid& rigid);
	Rigid(Particule center, Vector centerOfMass,Matrix3 orientationMat, Vector omega, Vector alpha, Vector scale);
	//destructeur
	~Rigid(){}

	//getters, inline
	Particule* GetCenter() { return &this->center; }
	Quaternion GetOrientationQuat() { return this->orientationQuat; }
	Matrix3 GetOrientationMat() { return this->orientationMat; }
	Vector GetOmega() { return this->omega; }
	Vector GetAlpha() { return this->alpha; }
	Vector GetScale() { return this->scale; }
	Vector GetCenterofMass() { return this->orientationMat * this->centerOfMassOffset + this->center.GetPosition(); }

	//setters, inline
	void SetCenter(Particule center) { this->center = center; }
	void SetOrientationQuat(Quaternion quat) { this->orientationQuat = quat; }
	void SetOrientationMat(Matrix3 orientation) { this->orientationMat = orientation; }
	void SetOmega(Vector omega) { this->omega = omega; }
	void SetAlpha(Vector alpha) { this->alpha = alpha; }
	void SetAxes(Vector scale) { this->scale = scale; }
	void SetCenterofMass(double x, double y, double z) { this->centerOfMassOffset.set(x, y, z); }

	// Intégrateurs du RigidBody
	void RigidIntegrator(float duration); // Call IntegrateEulerWithAccum of centerOfMass & AngularIntegrator
	void AngularIntegrator(float duration);

	void ClearAccums();//appelle le clear accum du centre de masse + clear Accum torque

	void AddTorque(const Vector force); // Fonction d'ajout d'un torque à l'accumTorque à partir d'une force
	void AddToAccumCenter(const Vector force);

	virtual void draw() = 0;//<<<dessine la forme du solide

	virtual void UpdateJ() = 0;//<<<permet de recalculer J quand le centre de mnasse se deplace
};

