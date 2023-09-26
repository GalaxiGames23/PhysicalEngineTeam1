#pragma once

#include "ofMain.h"
#include "Vector.h"
#include "Particule.h"
#include "BouncingParticule.h"
#include "FireBallParticule.h"
#include "Input.h"
#include "Ground.h"
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

		std::vector<Particule*> SystemeParticules;//<<< Vector de la STL pour stocker les particules à considérer dans les calculs
			
		std::vector<Vector> TracePositions; //<<< Vector de la STL pour stocker les positions de la trace des particules quand l'option est activée

		const float verticalGravity = 9.81f * 5; //<<< Norme de la gravité (fixe à la gravité terrestre)
		Vector &gravity = Vector(0, verticalGravity, 0) ; //<<< Vecteur des forces appliquée / d'accélération (fixe à la gravité)
		float damping = 1.0f; //<<< Coefficient de frottement (fixe pour l'absence de frottements)
		Particule* moonParticle = new Particule(900000, Vector(1000, 400, 0), Vector(0, 0, 0), ofColor::blueSteel, true);
		double current_mass = 5;
		float timer;
		bool isEuler; //<<< Mode d'intégration de la position des particules
};
