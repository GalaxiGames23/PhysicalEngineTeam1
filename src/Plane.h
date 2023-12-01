#ifndef PLANE_H
#define PLANE_H

#include "Vector.h"

class Plane
{
private :
	Vector normal; // <<< Vecteur normal au plan
	Vector point; // <<< Point du plan utlisé comme origine de son repère dans l'espace

public :
	///// Contructor / Destructor /////

	Plane() {};
	Plane(Vector normal, Vector point);
	~Plane() {};

	///// Getters /////

	Vector GetNormal() { return this->normal; };
	Vector GetPoint() { return this->point; };

	///// Setters /////

	Vector SetNormal(Vector normal) { this->normal = normal; };
	Vector SetPoint(Vector point) { this->point = point; };

	///// Functions /////

	double ComputeT(Vector Q); // <<< Retourne la distancce minimale entre le point donné et le plan
	Vector ComputeR(Vector Q); // <<< Retourne le point le plus proche du point Q sur le plan
};

#endif