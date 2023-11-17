#pragma once
#include "RigidBodyForceGenerator.h"

class RigidBodyForce :
    public RigidBodyForceGenerator
{

private:
    Vector pointAppli;
    Vector force;
    double effectiveTime = -1;

public:
    //constructeurs
    RigidBodyForce();
    RigidBodyForce(Vector pointAppli, Vector force, double effectiveTime);
    
    //update de la force sur un rigidBody
    virtual void updateForce(Rigid* rigidBody, float duration) override;
    virtual void draw() override;
};

