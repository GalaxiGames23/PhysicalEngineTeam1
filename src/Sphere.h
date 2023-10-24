#ifndef SPHERE_H
#define SPHERE_H

#include "Particule.h"
#include "ofColor.h"

// Create class that inherit Particules, with radius, color and collisions
class Sphere :
    public Particule
{
private :
    double radius = 5; // Sphere's radius
    ofColor color = ofColor::aqua; // Sphere's color

public :
    Sphere(double mass, Vector position, Vector velocity, double e) : Particule(mass, position, velocity, e)
    {
        this->radius = 5;
        this->color = ofColor::aqua;

    }
    Sphere(double mass, Vector position, Vector velocity, double radius, ofColor color, double e) : Particule(mass, position, velocity, e)
    {
        this->radius = radius;
        this->color = color;

    }

    double GetRadius() { return this->radius; }
    ofColor GetColor() { return this->color; }

    void SetRadius(double radius) { this->radius = radius; }
    void SetColor(ofColor color) { this->color = color; }
    bool isColliding(Sphere* sphere); // Detect collisions

};

#endif