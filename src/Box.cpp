#include "Box.h"
#include "of3dPrimitives.h"
#include <ofGraphics.h>
#include <of3dGraphics.h>

Box::Box(Particule centerOfMass, Matrix3 orientationMat, Vector omega, Vector alpha, Vector scale, Vector size)
	: Rigid(centerOfMass,orientationMat,omega,alpha, scale)
{
	this->size = size;
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

	//draw du centre de masse
	ofSetColor(ofColor::blue);
	ofDrawSphere(this->centerOfMass.GetPosition().toVec3(), 10.0f);
	ofSetColor(ofColor::white);

	ofMultMatrix(orientationMat.toMatrix4x4());
	myBox.draw();
	ofPopMatrix();
}
