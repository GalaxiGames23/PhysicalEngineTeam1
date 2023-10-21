#pragma once
#include "Camera.h"
#include "Particule.h"
class PlayerController
{
	private:
		Particule* particule = NULL;
		Camera* cam = NULL;
	public:
		PlayerController() {};
		PlayerController(Particule* particule, Camera* cam);

		
		void changeController(Particule* particule, Camera* cam);
		Vector getForwardDirection(double amount);
		Vector getRightDirection(double amount);

		Particule* getFocusParticule() { return particule; }
		bool isActive() { return particule != NULL && cam != NULL; }
};