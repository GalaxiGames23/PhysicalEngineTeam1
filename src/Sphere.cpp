#include "Sphere.h"

bool Sphere::isColliding(Sphere* sphere)
{
	return this->position.distance(sphere->position) < (this->radius + sphere->GetRadius());
	// Return true if distance between spheres less than radius sum
}
