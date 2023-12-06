#ifndef FORCE_H
#define FORCE_H

#include "src/Vector.h"
#include <cmath>
#include <cstdio>


//creation de la classe force pour l'impl�mentation des forces
class Force 
{

public:
    // Constructeur
    Force(double x, double y, double z) : x(x), y(y), z(z) {}

    // M�thode pour inverser la direction de la force
    Force operator-(const Vector& v) const 
    {
        return Force(x - v.get_x(), y - v.get_y(), z - v.get_z());
    }

private:
    double x; // Vecteur de force � appliquer (x,y,z)
    double y;
    double z;
};


#endif