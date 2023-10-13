#ifndef PARTICULEGRAVITY_H
#define PARTICULEGRAVITY_H

#include "ParticuleForceGenerator.h"
#include "Vector.h"

class ParticuleGravity :
    public ParticuleForceGenerator
{
private:
    Vector gravity;

public:

    //constructors
    ParticuleGravity();
    ParticuleGravity(Vector gravity);

    //getters
    Vector GetGravity() { return this->gravity; }

    //update de la force sur une particule
    virtual void updateForce(Particule* particule, float duration);
};

#endif