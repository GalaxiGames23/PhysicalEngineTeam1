#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
	input.set_Input(v);
	gameworld->myCam = new Camera(moonParticle->GetPosition() + Vector(-1000,0,0), moonParticle);
	myController = new PlayerController();

	//set up de l'harmonique de l'hud
	HUDParticule = Particule(0.5f, Vector(-10000,-20, 0), Vector(0, 0, 0), 1.0f);
	HUDParticule.SetUpHarmonic();
	lastRigidCount = 0;

	displayTrace = true;
	gameworld->myCam->isActivated = false;
}

//--------------------------------------------------------------
void ofApp::update()
{
	double delta = ofGetLastFrameTime();

	//////PHASE 2/////

	gameworld->UpdateLogic(delta);

	HUDParticule.HarmonicMovementDamping(1.0f, 0.1f, delta);
}

ofVbo vbo;
//--------------------------------------------------------------
void ofApp::draw()
{

	if (gameworld->myCam->isActivated)
	{
		gameworld->myCam->beginCam();

	}
	ofEnableDepthTest();


	// Configurez la boîte avec la taille souhaitée
	
	ofSetColor(ofColor::white);

	//draw les sphères
	for (Sphere* particule : gameworld->systemeSpheres)
	{
		ofSetColor(particule->GetColor());
		ofDrawSphere(particule->GetPosition().toVec3(), particule->GetRadius());
	}
	ofSetColor(ofColor::white);

	/////////////PHASE 3/////////////////
	for (Rigid* rigidBody : gameworld->rigidBodies)
	{
		rigidBody->draw();
	}

	//draw la trace
	if (displayTrace) {
		ofSetColor(ofColor::orange);
		for (Vector v : gameworld->GetTrace()) {
			ofDrawSphere(v.toVec3(), 5.0f);
		}
		ofSetColor(ofColor::white);
	}
	

	if (gameworld->myCam->isActivated)
	{
		gameworld->myCam->endCam();
	}

	/////////////////////////HUD//////////////////
	ofPushStyle();
	ofSetupScreenOrtho();
	//ofSetDrawBitmapMode(OF_BITMAPMODE_MODEL);
	//dessine les commandes
	ofDrawBitmapString("Commands:\n", 10, 10);
	ofSetDrawBitmapMode(OF_BITMAPMODE_MODEL);

	//Affichage du compte de rigid bodies
	ofScale(3, 3);
	timer += ofGetLastFrameTime();

	int count = gameworld->rigidBodies.size();

	//HUD set up check
	if (count != lastRigidCount) {
		//le compte du blob a changé, on reset l'harmonique
		lastRigidCount = count;
		HUDParticule.SetPosition(HUDParticule.GetPos0());
		HUDParticule.SetVelocity(HUDParticule.GetVel0());
		HUDParticule.SetUpHarmonic();
	}

	//HUD Harmonic
	ofDrawBitmapString(std::to_string(count), ofGetWidth() / 3 - 30, 40 + HUDParticule.GetPosition().get_y());
	
	ofPopStyle();
}


//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
	Box* box;
	switch (key) {
		//clear la trace
	case 'r': gameworld->ClearTrace();
		break;
		//toggle on/off la trace
	case 't': displayTrace = !displayTrace;
		break;
			//bouger la camera
	case 'k': gameworld->myCam->changeNorm(-ofGetLastFrameTime());
		break;
	case 'j': gameworld->myCam->changeNorm(ofGetLastFrameTime());
		break;
		//activer/descativer la camera
	case 'm': gameworld->myCam->isActivated = !gameworld->myCam->isActivated;
		break;
	case ' ':
		box = new Box(Particule(1.0, Vector(500, 500, 0), Vector(100, 0, 0), 15), Matrix3({ 1,-1,0,1,1,0,0,0,1 }), Vector(0, 0, 0), Vector(1, -1, 1), Vector(1, 1, 1), Vector(200, 200, 200));
		gameworld->myCam->setParticuleFollow(Vector(0, 0, 0), box->GetCenterOfMass());
		gameworld->rigidBodies.push_back(box);
		break;
	default: break;
	}

	input.set_Input(v);
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key)
{
	
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y )
{
	if (gameworld->myCam->isActivated)
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
