#include "Box.h"
#include "of3dPrimitives.h"
#include <ofGraphics.h>

Box::Box(Particule centerOfMass, Matrix3 orientationMat, Vector omega, Vector alpha, Vector scale, Vector size)
	: Rigid(centerOfMass,orientationMat,omega,alpha, scale)
{
	this->size = size;
}

void Box::draw()
{
	ofBoxPrimitive myBox;

	myBox.set(size.get_x(), size.get_y(), size.get_z()); // Utilisez 500 pour les dimensions x, y et z, ce qui crée une boîte cube

	// Définissez la position de la boîte

	myBox.setSideColor(myBox.SIDE_FRONT, ofColor(255, 0, 0));
	myBox.setSideColor(myBox.SIDE_LEFT, ofColor(0, 255, 0));
	myBox.setSideColor(myBox.SIDE_RIGHT, ofColor(0, 0, 255));
	myBox.setSideColor(myBox.SIDE_TOP, ofColor(255, 255, 0));
	myBox.setSideColor(myBox.SIDE_BACK, ofColor(255, 0, 255));
	myBox.setSideColor(myBox.SIDE_BOTTOM, ofColor(0, 255, 255));
	ofPushMatrix();
	ofTranslate(this->centerOfMass.GetPosition().toVec3());
	ofScale(this->scale.toVec3());

	std::cout << orientationMat.toMatrix4x4() << "\n";
	ofMultMatrix(orientationMat.toMatrix4x4());
	myBox.draw();
	ofPopMatrix();
}
