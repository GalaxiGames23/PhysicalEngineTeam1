#include "force.h"
#include <cstdio>


//Operateur pour soustraire le vecteur
Force Force::operator -(const Vector& v) const
{
	return Force(v.get_x(), v.get_y(), v.get_z());
}