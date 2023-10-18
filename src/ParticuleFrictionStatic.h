#ifndef PARTICULEFRICTIONSTATIC_H
#define PARTICULEFRICTIONSTATIC_H

#include "ParticuleForceGenerator.h"
#include "Vector.h"

class ParticuleFrictionStatic :
    public ParticuleForceGenerator
{
private:
    double us; // Coefficient de friction statique

public:

    //constructors
    ParticuleFrictionStatic();
    ParticuleFrictionStatic(double us);

    //getters
    double GetStaticCoeff() { return this->us; }

    //update de la force sur une particule
    virtual void updateForce(Particule* particule, float duration);

};

#endif