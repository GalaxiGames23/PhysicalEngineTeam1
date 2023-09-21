#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
	input.set_Input(v);
	input.SetDessinerTrace(false);
	input.SetAfficherPositions(false);

	for (int i = 0; i < SystemeParticules.size(); ++i)
	{
		SystemeParticules[i].SetFirstLastPosition(ofGetLastFrameTime());
	}

	timer = 0;
}

//--------------------------------------------------------------
void ofApp::update()
{
	int index = 0; //<<<compte l'index pour le dernier foreach de destructions de particules

	//pour la trace, on enregistre une position tous les intervalles fixes
	timer += ofGetLastFrameTime();
	bool temp = timer>0.5f;


	for (int i = 0; i<SystemeParticules.size();++i)
	{
		//update de la position de chaque particule avec l'intégration d'Euler
		
		SystemeParticules[i].IntegrateEuler(ofGetLastFrameTime(), gravity, damping);
		//SystemeParticules[i].IntegrateVerlet(ofGetLastFrameTime(), gravity);

		if(temp)
		{
			//enregistrer les positions pour la trace
			TracePositions.push_back(SystemeParticules[i].GetPosition());
		}
	}

	if (temp) { timer = 0; }

	//on détruit les objets sous un certain seuil
	for (Particule particule : SystemeParticules)
	{
		if (particule.GetPosition().get_y() > 1000)
		{
			SystemeParticules.erase(SystemeParticules.begin()+index);
			SystemeParticules.shrink_to_fit();
		}
		else
		{
			//l'incrémentation ne se fait que s'il n'y a pas destruction et resize du vector
			++index;
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw()
{
	ofSetColor(ofColor::white);
	//dessine les commandes
	ofDrawBitmapString("Commands:\nc: increase norm\nx: decrease norm\ne:change angle\nt: show previous positions on/off\nr: clear previous positions\np: display current position values\nspace: spawn particle", 20, 20);
	
	if (input.GetDessinerTrace())
	{
		ofSetColor(ofColor::orange);

		//affiche la trace
		for (int i = 0; i < TracePositions.size() - SystemeParticules.size(); ++i)
		{
			ofDrawSphere(TracePositions[i].toVec3(), 5.0f);
		}
		ofSetColor(ofColor::white);

		//affiche la mention de ON/OFF pour la trace
		ofDrawBitmapString("Previous Positions: ON", 20, ofGetHeight() - 20);
	}
	else
	{
		//affiche la mention de ON/OFF pour la trace
		ofDrawBitmapString("Previous Positions: OFF", 20, ofGetHeight() - 20);
	}
	//dessine toutes les particules listées
	for (Particule particule : SystemeParticules)
	{
		ofDrawSphere(particule.GetPosition().toVec3(), 20.0f);
	}

	if(input.GetAfficherPositions())
	{
		//affiche la position des particules
		for (int i = 0; i < SystemeParticules.size(); ++i)
		{
			ofDrawBitmapString("value: " + ofToString(SystemeParticules[i].GetPosition()), ofGetWidth() - 200, 30 + 15 * (SystemeParticules.size() - i - 1));
		}
	}
	
	ofDrawArrow(init_point.toVec3(), v.toVec3() + init_point.toVec3(), 6);
}


//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
	switch (key) {
	case 'c': input.change_norm(true);
		break;
	case 'x': input.change_norm(false);
		break;
	case 'e': input.angle_key = true;
		break;
	case 't': input.SetDessinerTrace(!input.GetDessinerTrace());
		break;
	case 'p': input.SetAfficherPositions(!input.GetAfficherPositions());
		break;
	case ' ':
		SystemeParticules.push_back(Particule(current_mass, init_point, v));
		break;
	case 'r': TracePositions.clear();
		break;
	default: break;
	}
	input.set_Input(v);
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key)
{
	if (key == 'e')
	{
		input.angle_key = false;
	}
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y )
{
	if (input.angle_key)
	{
		int diffx = x - input.last_pos_x;
		int diffy = y - input.last_pos_y;
		if (abs(diffx) > abs(diffy) + 2 && diffx != 0)
		{
			input.change_angle2(diffx > 0);

		}
		else if (abs(diffy) > abs(diffx) + 2 && diffy != 0)
		{
			input.change_angle1(diffy > 0);
		}
		input.last_pos_x = x;
		input.last_pos_y = y;
		input.set_Input(v);
	}
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button)
{

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button)
{
	if (button == 0)
	{
		init_point.set(x, y, 0);
	}
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button)
{

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y)
{

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y)
{

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h)
{

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg)
{

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo)
{ 

}
