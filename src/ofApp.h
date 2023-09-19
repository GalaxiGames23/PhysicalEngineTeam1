#pragma once

#include "ofMain.h"
#include "Vector.h"
#include "Particule.h"
#include "Input.h"
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
		Vector &init_point = Vector(50, 100, 0);

		std::vector<Particule> SystemeParticules //<<< Vector de la STL pour stocker les particules à considérer dans les calculs
			//TO REMOVE: hard code pour les tests 
			= { Particule(5.0f, Vector(500, 30, 2), Vector(0, 0, 0), Vector(0, 0, 0)) , Particule(5.0f, Vector(50, 300, 20), Vector(0, 0, 0), Vector(0, 0, 0)) };
		std::vector<Vector> TracePositions; //<<< Vector de la STL pour stocker les positions de la trace des particules quand l'option est activée
};
