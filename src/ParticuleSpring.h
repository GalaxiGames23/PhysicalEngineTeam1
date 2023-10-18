#ifndef PARTICULESPRING_H
#define PARTICULESPRING_H

#include "ParticuleForceGenerator.h"
#include "Vector.h"
#include "Particule.h"

class ParticuleSpring :
    public ParticuleForceGenerator
{
private:
    double k; // Coefficient élastique
    double l0; // Longueur au repos

    Particule* p2; // Particule accrochée à la particule
    Vector v; // Vecteur accroché à la particule

    bool isP2P; // Vérifie type d'accroche

public:

    //constructors
    ParticuleSpring();
    ParticuleSpring(double k, double l0, Particule* p2);
    ParticuleSpring(double k, double l0, Vector v);

    //getters
    double GetSpringCoeff() { return this->k; }
    double GetEeaseLenght() { return this->l0; }

    //update de la force sur une particule
    virtual void updateForce(Particule* p1, float duration);

};

#endif