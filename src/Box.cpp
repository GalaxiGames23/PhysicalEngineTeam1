#include "Box.h"


Box::Box(Particule center, Matrix3 orientationMat, Vector omega, Vector alpha, Vector scale, Vector size)
	: Rigid(center,orientationMat,omega,alpha, scale)
{
	this->size = size;
	this->J = CreateJ(center); // Création du tenseur d'inertie par défaut des parrallèlépipèdes avec th de l'axe parallèle
}

Matrix3 Box::CreateJ(Particule center)
{
	// Création de Jcm
	std::array<float, 9> coefsJcm;
	coefsJcm.fill(0);

	coefsJcm[0] = (1.0f / 12.0f) * center.GetMass() * (pow(this->size.get_y(), 2) + pow(this->size.get_z(), 2));
	coefsJcm[4] = (1.0f / 12.0f) * center.GetMass() * (pow(this->size.get_x(), 2) + pow(this->size.get_z(), 2));
	coefsJcm[8] = (1.0f / 12.0f) * center.GetMass() * (pow(this->size.get_x(), 2) + pow(this->size.get_y(), 2));

	Matrix3 Jcm = Matrix3(coefsJcm);
	return Jcm;
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
	ofTranslate(this->centerOfMass.GetPosition().toVec3());
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
	//draw du centre de rotation
	ofSetColor(ofColor::blue);
	ofDrawSphere(GetCenter()->GetPosition().toVec3(), 1.0f);
	ofSetColor(ofColor::white);
	ofEnableDepthTest();
}
