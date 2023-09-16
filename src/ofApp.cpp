#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
	input.set_Input(v);
}

//--------------------------------------------------------------
void ofApp::update()
{
	//TO REMOVE: pour les tests, à remplacer par l'intégration
	for (int i = 0; i<SystemeParticules.size();++i)
	{
		SystemeParticules[i].SetPosition(SystemeParticules[i].GetPosition() + Vector(0, 1, 0));
	}
}

//--------------------------------------------------------------
void ofApp::draw()
{
	//dessine toutes les particules listées
	for (Particule particule : SystemeParticules) 
	{
		ofDrawSphere(particule.GetPosition().toVec3(), 50.0f);
	}
	//affiche la position des particules
	//TODO:: changer en foreach
	ofDrawBitmapString("value: " + ofToString(SystemeParticules[0].GetPosition()), 10, 10);

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
