#include "PlayerController.h"

PlayerController::PlayerController(Particule* particule, Camera* cam)
{
	this->particule = particule;
	this->cam = cam;
}

void PlayerController::moveParticuleForward(double amount)
{
	Vector direction = (particule->GetPosition() - cam->getPosition()).normalisation();
	direction.set(direction.get_x(), 0, direction.get_z());
	particule->SetPosition(particule->GetPosition() + amount * movingSpeed * direction);
	cam->setPosition();
}

void PlayerController::moveParticuleRight(double amount)
{
	Vector direction = (particule->GetPosition() - cam->getPosition()).normalisation().prod_vector(Vector(0,-1,0));
	direction.set(direction.get_x(), 0, direction.get_z());
	particule->SetPosition(particule->GetPosition() + amount * movingSpeed * direction);
	cam->setPosition();
}
