#pragma once
#include "Rigid.h"
#include <math.h>
#include <cmath>
#include <array>

#include "Plane.h"
#include "Vector.h"

#include "of3dPrimitives.h"
#include <ofGraphics.h>
#include <of3dGraphics.h>

class Box : public Rigid
{
private:

	Matrix3 CreateJ(Particule center);

public:



	std::vector<Plane*> GetPlanes();
	std::vector<Vector*> GetVertices();


	///// Functions /////

	Box() : Rigid() 
	{ 
	};

	Box(Particule center,Matrix3 orientationMat, Vector omega, Vector alpha, Vector scale, Vector size);

	virtual void draw() override; //<<<dessine le cube
};