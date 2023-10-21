#pragma once
#include "ParticuleForceGenerator.h"
#include "PlayerController.h"

class InputForce : public ParticuleForceGenerator
{
	private:
        PlayerController *controller;
        double power = 1000;
        bool isForward = true;
        int positiveDirection = 1;
    public:
        InputForce(PlayerController* p, bool isForward, int positiveDirection);
        //update de la force sur une particule
        virtual void updateForce(Particule* particule, float duration);


};