#pragma once
#include "Vector.h"
#include "Particule.h"
#include "ofCamera.h"
#define PI 3.14159265358979323846


class Camera
{
	private:
		double rollAngle = 0;
		double pitchAngle = 0;
		double norm = 0;
		float speedZoom = 800;
		float speedAngle = 0.4;
		Vector position = Vector(0,0,0);
		Particule* followParticule = NULL;
		ofCamera cam;
		double maxAngle = 80 * (PI / 180.0);

		

	public:
		bool isActivated = false;

		Camera();
		Camera(Vector startPosition, Particule *followParticule);

		void changeNorm(double changeValue);
		void changeRollAngle(double changeValue);
		void changePitchAngle(double changeValue);

		void setParticuleFollow(Vector startPosition, Particule *newParticule);

		Vector getPosition();
		void beginCam();
		void endCam();


		void setPosition();
		

};