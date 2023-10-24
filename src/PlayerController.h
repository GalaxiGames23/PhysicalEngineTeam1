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

		/*Changer la particule qui peut se d�placer, ainsi que la cam�ra qui la suit*/
		void changeController(Particule* particule, Camera* cam);
		/*Avoir la direction vers l'avant de la cam�ra*/
		Vector getForwardDirection(double amount);
		/*Avoir la direction vers la droite de la cam�ra*/
		Vector getRightDirection(double amount);

		Particule* getFocusParticule() { return particule; }
		bool isActive() { return particule != NULL && cam != NULL; }
};