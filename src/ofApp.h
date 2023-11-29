#pragma once

#include "ofMain.h"
#include "Vector.h"
#include "Particule.h"
#include "Input.h"
#include "Ground.h"
#include "GameWorld.h"
#include "PlayerController.h"
#include "ParticuleGravity.h"
#include "ofxGui/src/ofxGui.h"

#include <iostream>
#include <cstdlib>
#include <vector>

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		
		Vector &v = Vector(0,0,0);
		Input &input = Input::getInput();
		Ground &ground = Ground::getGround();
		Vector &init_point = Vector(300, 300, 0);
		double timer = 0;
		const float verticalGravity = 9.81f * 5; //<<< Norme de la gravit� (fixe � la gravit� terrestre)
		float damping = 1.0f; //<<< Coefficient de frottement (fixe pour l'absence de frottements)
		Sphere* moonParticle = new Sphere(900000, Vector(400, 0, 0), Vector(0, 0, 0), 1);

		/////////PHASE 2//////
		
		PlayerController *myController;
		GameWorld* gameworld = new GameWorld();
		Particule HUDParticule; //<<<particule pour les oscillations de l'HUD
		float lastBlobCount;//<<< pour savoir quand reset l'harmonique

		/////////////////PHASE 3/////////////
		float lastRigidCount;//<<<remplace lastBlobCount pour le HUD de la phase 3
		bool displayTrace;

		ofxPanel gui;


		ofParameterGroup position;

		ofParameter<double> x;
		ofParameter<double> y;
		ofParameter<double> z;

		ofParameterGroup direction;

		ofParameter<double> radius;
		ofParameter<double> theta;
		ofParameter<double> phi;
};
