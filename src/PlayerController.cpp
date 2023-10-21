#include "PlayerController.h"

PlayerController::PlayerController(Particule* particule, Camera* cam)
{
	this->particule = particule;
	this->cam = cam;
}

void PlayerController::changeController(Particule* particule, Camera* cam)
{
	this->particule = particule;
	this->cam = cam;
}

Vector PlayerController::getForwardDirection(double amount)
{
	Vector direction = (particule->GetPosition() - cam->getPosition()).normalisation();
	direction.set(direction.get_x(), 0, direction.get_z());
	return amount * direction;
}

Vector PlayerController::getRightDirection(double amount)
{
	Vector direction = (particule->GetPosition() - cam->getPosition()).normalisation().prod_vector(Vector(0,-1,0));
	direction.set(direction.get_x(), 0, direction.get_z());
	return amount * direction;
}
