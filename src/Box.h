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

	Matrix3 CreateJ(Particule center);

public:

	Box() : Rigid() 
	{ 
		size = Vector();
	};

	Box(Particule center,Matrix3 orientationMat, Vector omega, Vector alpha, Vector scale, Vector size);

	virtual void draw() override; //<<<dessine le cube
};