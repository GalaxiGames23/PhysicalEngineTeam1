#pragma once
#include "Rigid.h"
#include <math.h>
#include <cmath>
#include <array>

#include "of3dPrimitives.h"
#include <ofGraphics.h>
#include <of3dGraphics.h>

class Box : public Rigid
{
private:
	Vector size;//<<<Vecteur représentant la longueur, largeur et hauteur du cube

	Matrix3 CreateJ(Particule center, Vector centerOfMass);

public:
	Box() : Rigid() 
	{ 
		size = Vector();
	};

	Box(Particule center, Vector centerOfMass,Matrix3 orientationMat, Vector omega, Vector alpha, Vector scale, Vector size);

	virtual void UpdateJ() override;//<<<permet de recalculer J quand le centre de mnasse se deplace

	virtual void draw() override;
};