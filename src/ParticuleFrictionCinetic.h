#ifndef PARTICULEFRICTIONCINETIC_H
#define PARTICULEFRICTIONCINETIC_H

#include "ParticuleForceGenerator.h"
#include "Vector.h"

class ParticuleFrictionCinetic :
    public ParticuleForceGenerator
{
private:
    double k1; // Coefficient de friction cinetique 1
    double k2; // Coefficient de friction cinetique 2

public:

    //constructors
    ParticuleFrictionCinetic();
    ParticuleFrictionCinetic(double k1, double k2);

    //getters
    float GetCineticCoeff1() { return this->k1; }
    float GetCineticCoeff2() { return this->k2; }

    //update de la force sur une particule
    virtual void updateForce(Particule* particule, float duration);
};

#endif