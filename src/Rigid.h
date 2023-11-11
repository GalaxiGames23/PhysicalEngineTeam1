#include "Particule.h"
#include "Quaternion.h"
#include "Matrix3.h"
#include "Matrix4.h"
#include "Vector.h"

class Rigid
{
protected:
	Particule centerOfMass = Particule();//<<<centre de masse, particule sur laquelle est appliquée l'intégration linéaire
	Quaternion orientationQuat = Quaternion();//<<<quaternion d'orientation du corps rigide, mis à jour avec l'intégration rotationnelle
	Matrix3 orientationMat = Matrix3();//<<<matrice d'orientation du corps rigide, mise à jour chaque frame grâce au quaternion et à la formule de conversion
	Vector omega = Vector();//<<<vitesse angulaire, mise à jour par l'intégrateur rotationnel chaque frame
	Vector alpha = Vector();//<<<accélération angulaire, mise à jour par l'intégrateur rotationnel chaque frame
	Vector scale = Vector();//<<<scale du rigid body, permet de dessiner des boites de tailles differentes

public:
	//constructeurs
	Rigid(){} //par défaut
	Rigid(const Rigid& rigid);
	Rigid(Particule centerOfMass,Matrix3 orientationMat, Vector omega, Vector alpha, Vector scale);
	//destructeur
	~Rigid(){}

	//getters, inline
	Particule* GetCenterOfMass() { return &this->centerOfMass; }
	Quaternion GetOrientationQuat() { return this->orientationQuat; }
	Matrix3 GetOrientationMat() { return this->orientationMat; }
	Vector GetOmega() { return this->omega; }
	Vector GetAlpha() { return this->alpha; }
	Vector GetScale() { return this->scale; }

	//setters, inline
	void SetCenterOfMass(Particule center) { this->centerOfMass = center; }
	void SetOrientationQuat(Quaternion quat) { this->orientationQuat = quat; }
	void SetOrientationMat(Matrix3 orientation) { this->orientationMat = orientation; }
	void SetOmega(Vector omega) { this->omega = omega; }
	void SetAlpha(Vector alpha) { this->alpha = alpha; }
	void SetAxes(Vector scale) { this->scale = scale; }

	// Intégrateurs du RigidBody
	void RigidIntegrator(float duration); // Call IntegrateEulerWithAccum of centerOfMass & AngularIntegrator
	void AngularIntegrator(float duration);
	void ClearAccum();//appelle le clear accum du centre de masse

	virtual void draw() = 0;

};

