#pragma once
#include "Camera.h"
#include "Particule.h"
class PlayerController
{
	private:
		Particule* particule = NULL;
		Camera* cam = NULL;
		float movingSpeed = 1000;
	public:
		PlayerController() {};
		PlayerController(Particule* particule, Camera* cam);

		void moveParticuleForward(double amount);
		void moveParticuleRight(double amount);

};