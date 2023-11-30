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



std::vector<Plane*> Box::GetPlanes()
{
	std::vector<Plane*> boxPlanes; // <<< liste des 6 plans d'une boîte

	for (int j = 0; j < 3; ++j) // Création de tous les plan de la boîte 1
	{
		Vector normal = this->GetOrientationMat().GetColumn(j).normalisation();
		Vector pointFront = this->GetSize().GetCoordByIndex(j) / 2.0f * normal + this->GetCenter()->GetPosition();
		Vector pointBack = this->GetSize().GetCoordByIndex(j) / 2.0f * (-1 * normal) + this->GetCenter()->GetPosition();

		boxPlanes.push_back(new Plane(normal, pointFront));
		boxPlanes.push_back(new Plane(-1 * normal, pointBack));
	}
	return boxPlanes;
}


/*
std::vector<Vector*> Box::GetVertices()
{
	std::vector<Vector*> boxVertices; // <<< liste des 6 sommets d'une boîte

	
	//on récupère les axes
	Vector normalX = this->GetOrientationMat().GetColumn(0).normalisation();
	Vector normalY = this->GetOrientationMat().GetColumn(1).normalisation();
	Vector normalZ = this->GetOrientationMat().GetColumn(2).normalisation();

	//X et Y
	Vector vertex1 = this->GetCenter()->GetPosition() + this->GetSize().get_x() * normalX + this->GetSize().get_y() * normalY;
	boxVertices.push_back(&vertex1);

	//X et -Y
	Vector vertex2 = this->GetCenter()->GetPosition() + this->GetSize().get_x() * normalX - this->GetSize().get_y() * normalY;
	boxVertices.push_back(&vertex2);

	//-X et Y
	Vector vertex3 = this->GetCenter()->GetPosition() - this->GetSize().get_x() * normalX + this->GetSize().get_y() * normalY;
	boxVertices.push_back(&vertex3);

	//-X et -Y
	Vector vertex4 = this->GetCenter()->GetPosition() - this->GetSize().get_x() * normalX - this->GetSize().get_y() * normalY;
	boxVertices.push_back(&vertex4);

	//X et Z
	Vector vertex5 = this->GetCenter()->GetPosition() + this->GetSize().get_x() * normalX + this->GetSize().get_z() * normalZ;
	boxVertices.push_back(&vertex5);

	//X et -Z
	Vector vertex6 = this->GetCenter()->GetPosition() + this->GetSize().get_x() * normalX - this->GetSize().get_z() * normalZ;
	boxVertices.push_back(&vertex6);

	//-X et Z
	Vector vertex7 = this->GetCenter()->GetPosition() - this->GetSize().get_x() * normalX + this->GetSize().get_z() * normalZ;
	boxVertices.push_back(&vertex7);

	//-X et -Z
	Vector vertex8 = this->GetCenter()->GetPosition() - this->GetSize().get_x() * normalX - this->GetSize().get_z() * normalZ;
	boxVertices.push_back(&vertex8);


	return boxVertices;
}
*/

std::vector<Vector*> Box::GetVertices()
{
	std::vector<Vector*> boxVertices; // <<< liste des 6 sommets d'une boîte

	for (int j = 0; j < 2; ++j)
	{
		Vector normal1 = this->GetSize().GetCoordByIndex(j) / 2.0f * this->GetOrientationMat().GetColumn(j).normalisation();
		Vector normal2 = this->GetSize().GetCoordByIndex((j + 1) % 3) / 2.0f * this->GetOrientationMat().GetColumn((j + 1) % 3).normalisation();

		boxVertices.push_back(new Vector(normal1 + normal2 + this->GetCenter()->GetPosition()));
		boxVertices.push_back(new Vector(-1 * normal1 + normal2 + this->GetCenter()->GetPosition()));
		boxVertices.push_back(new Vector(normal1 + -1 * normal2 + this->GetCenter()->GetPosition()));
		boxVertices.push_back(new Vector(-1 * normal1 + -1 * normal2 + this->GetCenter()->GetPosition()));
	}

	return boxVertices;
}