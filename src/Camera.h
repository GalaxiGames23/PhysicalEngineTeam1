#pragma once
#include "Vector.h"
#include "Particule.h"
#include "ofCamera.h"
#define PI 3.14159265358979323846

//Camera qui permet de tourner autour d'une particule
class Camera
{
	private:
		double rollAngle = 0; //<<< angle permettant la rotation roll
		double pitchAngle = 0;//<<< angle permettant la rotation pitch
		double norm = 0;//<<< norm séparant la caméra de la particule
		float speedZoom = 800;//<<< vitesse pour zoomer
		float speedAngle = 0.4;//<<< vitesse pour tourner
		Vector position = Vector(0,0,0);//<<< position de la caméra
		Particule* followParticule = NULL; //<<< particule cible de la caméra
		ofCamera cam; //<<< Caméra openFrameworks
		double maxAngle = 80 * (PI / 180.0); //<<< angle verticale maximum

		

	public:
		bool isActivated = false;

		Camera();
		Camera(Vector startPosition, Particule *followParticule);

		void changeNorm(double changeValue);
		void changeRollAngle(double changeValue);
		void changePitchAngle(double changeValue);

		/*Changer la particule cible, et mettre une nouvelle position a la caméra*/
		void setParticuleFollow(Vector startPosition, Particule *newParticule);

		Vector getPosition();
		void beginCam();
		void endCam();


		void setPosition();
		

};