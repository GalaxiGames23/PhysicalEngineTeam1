#pragma once
#include "Rigid.h"

class Box : public Rigid
{
private:
	Vector size;//<<<Vecteur représentant la longueur, largeur et hauteur du cube
public:
	Box() : Rigid() 
	{ 
		size = Vector(); 
	};
	Box(Particule centerOfMass,Matrix3 orientationMat, Vector omega, Vector alpha, Vector scale, Vector size);
	virtual void draw() override;
};