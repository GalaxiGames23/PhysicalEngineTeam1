#include "Particule.h"
#include "Quaternion.h"
#include "Matrix3.h"
#include "Matrix4.h"
#include "Vector.h"

class Rigid
{
private:
	Particule centerOfMass;//<<<centre de masse, particule sur laquelle est appliqu�e l'int�gration lin�aire
	Quaternion orientationQuat;//<<<quaternion d'orientation du corps rigide, mis � jour avec l'int�gration rotationnelle
	Matrix3 orientationMat;//<<<matrice d'orientation du corps rigide, mise � jour chaque frame gr�ce au quaternion et � la formule de conversion
	Vector omega;//<<<vitesse angulaire, mise � jour par l'int�grateur rotationnel chaque frame
	Vector alpha;//<<<acc�l�ration angulaire, mise � jour par l'int�grateur rotationnel chaque frame

public:
	//constructeurs
	Rigid(){} //par d�faut
	Rigid(const Rigid& rigid);
	Rigid(Particule centerOfMass, Quaternion orientationQuat, Matrix3 orientationMat, Vector omega, Vector alpha);
	//destructeur
	~Rigid(){}

	//getters, inline
	Particule* GetCenterOfMass() { return &this->centerOfMass; }
	Quaternion GetOrientationQuat() { return this->orientationQuat; }
	Matrix3 GetOrientationMat() { return this->orientationMat; }
	Vector GetOmega() { return this->omega; }
	Vector GetAlpha() { return this->alpha; }

	//setters, inline
	void SetCenterOfMass(Particule center) { this->centerOfMass = center; }
	void SetOrientationQuat(Quaternion quat) { this->orientationQuat = quat; }
	void SetOrientationMat(Matrix3 orientation) { this->orientationMat = orientation; }
	void SetOmega(Vector omega) { this->omega = omega; }
	void SetAlpha(Vector alpha) { this->alpha = alpha; }

	// Int�grateurs du RigidBody
	void RigidIntegrator(float duration); // Call IntegrateEulerWithAccum of centerOfMass & AngularIntegrator
	void AngularIntegrator(float duration);
	void ClearAccum();//appelle le clear accum du centre de masse

};

