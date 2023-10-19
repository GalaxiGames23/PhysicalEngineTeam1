#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
	input.set_Input(v);
	gameworld->myCam = new Camera(moonParticle->GetPosition() + Vector(-1000,0,0), moonParticle);
	myController = new PlayerController(moonParticle, gameworld->myCam);

}

//--------------------------------------------------------------
void ofApp::update()
{
	double delta = ofGetLastFrameTime();

	//////PHASE 2/////

	gameworld->UpdateLogic(delta);

}

//--------------------------------------------------------------
void ofApp::draw()
{
	//////PHASE 2/////
	
	if (gameworld->myCam->isActivated)
	{
		gameworld->myCam->beginCam();

	}
	ofSetColor(ofColor::white);
	if (gameworld->myBlob)
	{
		ofSetColor(ofColor::darkCyan);
		gameworld->myBlob->draw();
	}
	for (Sphere* particule : gameworld->systemeSpheres)
	{
		ofSetColor(particule->GetColor());
		ofDrawSphere(particule->GetPosition().toVec3(), particule->GetRadius());
	}
	ofSetColor(ofColor::white);



	ofSetColor(ofColor::brown);
	ofDrawBox(glm::vec3(0, ground.yCoord + 20, 0), 10000, 10, 1000); //Dessine le sol
	ofSetColor(ofColor::white);
	

	if (gameworld->myCam->isActivated)
	{
		gameworld->myCam->endCam();
	}

	ofPushStyle();
	ofSetupScreenOrtho();
	//dessine les commandes
	ofDrawBitmapString("Commands:", 20, 20);
	
	ofPopStyle();
}


//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
	switch (key) {
	case ' ': gameworld->systemeSpheres.push_back(new Sphere(5.0f, init_point, v, 1)); // Création d'une particule
		break;
	case 'b': if (gameworld->myBlob == NULL) gameworld->myBlob = new Blob(Vector(300, 300, 0), 35, 10, 50, gameworld->myCam, myController, gameworld);
			else
	{
		delete gameworld->myBlob;
		gameworld->myBlob = NULL;
	}
		break;
	case 'h': input.ground_key = true;
		break;
	case 'k': gameworld->myCam->changeNorm(-ofGetLastFrameTime());
		break;
	case 'j': gameworld->myCam->changeNorm(ofGetLastFrameTime());
		break;
	case 'm': gameworld->myCam->isActivated = !gameworld->myCam->isActivated;
		break;
	case 'z': myController->moveParticuleForward(ofGetLastFrameTime());
		break;
	case 's':  myController->moveParticuleForward(-ofGetLastFrameTime());
		break;
	case 'd': myController->moveParticuleRight(ofGetLastFrameTime());
		break;
	case 'q': myController->moveParticuleRight(-ofGetLastFrameTime());
		break;
	default: break;
	}

	input.set_Input(v);
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key)
{
	switch (key) {
	case 'h': input.ground_key= false;
		break;
	default: break;
	}
	

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y )
{
	if (input.ground_key)
	{
		int diffy = y - input.last_pos_y;
		
		 if (diffy != 0)
		{
			 ground.change_ground_height(diffy);
		}
		 input.calculSomePoints(v, init_point, gameworld->worldGravity.GetGravity(), ground);
	}
	else if (gameworld->myCam->isActivated)
	{
		int diffx = x - input.last_pos_x;
		int diffy = y - input.last_pos_y;
		if (abs(diffx) > abs(diffy) + 1 && diffx != 0)
		{
			gameworld->myCam->changePitchAngle(-ofGetLastFrameTime() * diffx);

		}
		else if (abs(diffy) > abs(diffx) + 1 && diffy != 0)
		{
			gameworld->myCam->changeRollAngle(-ofGetLastFrameTime() * diffy);
		}
		
	}
	input.last_pos_x = x;
	input.last_pos_y = y;
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button)
{

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button)
{
	
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
