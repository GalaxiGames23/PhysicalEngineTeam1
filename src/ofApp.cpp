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
}

//--------------------------------------------------------------
void ofApp::update()
{
	for (int i = 0; i<SystemeParticules.size();++i)
	{
		//update de la position de chaque particule avec l'intégration d'Euler
		
		//SystemeParticules[i].IntegrateEuler(ofGetLastFrameTime(), gravity, damping);
		SystemeParticules[i].IntegrateVerlet(ofGetLastFrameTime(), gravity);

		if(input.GetDessinerTrace())
		{
			//enregistrer les positions pour la trace
			TracePositions.push_back(SystemeParticules[i].GetPosition());
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw()
{
	//dessine les commandes
	ofDrawBitmapString("Commands:\nc: increase norm\nx: decrease norm\ne:change angle\nt: show previous positions on/off\np: display current position values", 20, 20);
	//dessine toutes les particules listées
	for (Particule particule : SystemeParticules) 
	{
		ofDrawSphere(particule.GetPosition().toVec3(), 50.0f);
	}
	if (input.GetDessinerTrace())
	{
		//affiche la trace
		for (int i = 0; i < TracePositions.size() - SystemeParticules.size(); ++i)
		{
			ofDrawSphere(TracePositions[i].toVec3(), 5.0f);
		}
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
		if (input.GetDessinerTrace())
		{
			TracePositions.clear();
		}
		break;
	case 'p': input.SetAfficherPositions(!input.GetAfficherPositions());
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
