#pragma once
#include "RigidBodyForceGenerator.h"

class RigidBodyForce :
    public RigidBodyForceGenerator
{

private:
    Vector pointAppli;
    Vector force;

public:
    //constructeurs
    RigidBodyForce();
    RigidBodyForce(Vector pointAppli, Vector force);
    
    //update de la force sur un rigidBody
    virtual void updateForce(Rigid* rigidBody, float duration);
};

