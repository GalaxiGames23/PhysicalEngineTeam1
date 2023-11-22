#include "Box.h"


Box::Box(Particule center, Vector centerOfMass, Matrix3 orientationMat, Vector omega, Vector alpha, Vector scale, Vector size)
	: Rigid(center, centerOfMass,orientationMat,omega,alpha, scale)
{
	this->size = size;
	this->J = CreateJ(center, centerOfMass); // Création du tenseur d'inertie par défaut des parrallèlépipèdes avec th de l'axe parallèle
}

void Box::UpdateJ() 
{
	this->J = CreateJ(this->center, this->centerOfMassOffset);
}

Matrix3 Box::CreateJ(Particule center, Vector centerOfMass)
{
	// Création de Jcm
	std::array<float, 9> coefsJcm;
	coefsJcm.fill(0);

	coefsJcm[0] = (1.0f / 12.0f) * center.GetMass() * (pow(this->size.get_y(), 2) + pow(this->size.get_z(), 2));
	coefsJcm[4] = (1.0f / 12.0f) * center.GetMass() * (pow(this->size.get_x(), 2) + pow(this->size.get_z(), 2));
	coefsJcm[8] = (1.0f / 12.0f) * center.GetMass() * (pow(this->size.get_x(), 2) + pow(this->size.get_y(), 2));

	Matrix3 Jcm = Matrix3(coefsJcm);

	// Création de Jp
	std::array<float, 9> coefsJp;

	coefsJp[0] = pow(centerOfMass.get_y(), 2) + pow(centerOfMass.get_z(), 2);
	coefsJp[1] = - centerOfMass.get_x() * centerOfMass.get_y();
	coefsJp[2] = -centerOfMass.get_x() * centerOfMass.get_z();

	coefsJp[3] = -centerOfMass.get_x() * centerOfMass.get_y();
	coefsJp[4] = pow(centerOfMass.get_x(), 2) + pow(centerOfMass.get_z(), 2);
	coefsJp[5] = -centerOfMass.get_y() * centerOfMass.get_z();

	coefsJp[6] = -centerOfMass.get_x() * centerOfMass.get_z();
	coefsJp[7] = -centerOfMass.get_y() * centerOfMass.get_z();
	coefsJp[8] = pow(centerOfMass.get_x(), 2) + pow(centerOfMass.get_y(), 2);

	Matrix3 Jp = Matrix3(coefsJp);

	// Création de J
	Matrix3 J = Jcm + Jp * this->center.GetMass();
	return J;
}



void Box::draw()
{
	ofBoxPrimitive myBox;

	myBox.set(size.get_x(), size.get_y(), size.get_z()); // dimensions x, y et z de la boîte

	//couleurs des faces
	myBox.setSideColor(myBox.SIDE_FRONT, ofColor(255, 0, 0));
	myBox.setSideColor(myBox.SIDE_LEFT, ofColor(0, 255, 0));
	myBox.setSideColor(myBox.SIDE_RIGHT, ofColor(0, 0, 255));
	myBox.setSideColor(myBox.SIDE_TOP, ofColor(255, 255, 0));
	myBox.setSideColor(myBox.SIDE_BACK, ofColor(255, 0, 255));
	myBox.setSideColor(myBox.SIDE_BOTTOM, ofColor(0, 255, 255));
	ofPushMatrix();

	// Définition la position et taille de la boîte
	ofTranslate(this->center.GetPosition().toVec3());
	ofScale(this->scale.toVec3());

	//orientation: probleme entre la librairie et nos calculs

	//approche initiale, roation dans le mauvais sens:
	//ofMatrix4x4 orientation = orientationMat.toMatrix4x4();

	//approche fonctionnant:
	ofMatrix4x4 orientation = orientationQuat.Conjugated().ToMatrix().toMatrix4x4();
	ofMultMatrix(orientation);


	myBox.draw();
	ofPopMatrix();
	ofDisableDepthTest();
	//draw du centre de masse
	ofSetColor(ofColor::brown);
	ofDrawSphere(GetCenterofMass().toVec3(), 2.0f);
	//draw du centre de rotation
	ofSetColor(ofColor::blue);
	ofDrawSphere(GetCenter()->GetPosition().toVec3(), 1.0f);
	ofSetColor(ofColor::white);
	ofEnableDepthTest();
}
