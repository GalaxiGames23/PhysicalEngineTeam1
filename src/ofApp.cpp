#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
	input.setInput(v);
	gameworld->myCam = new Camera(moonParticle->GetPosition() + Vector(-1000,0,0), moonParticle);
	gameworld->basicCam = new Camera(moonParticle->GetPosition() + Vector(0, 0, -500), moonParticle);
	myController = new PlayerController();

	//set up de l'harmonique de l'hud
	HUDParticule = Particule(0.5f, Vector(-10000,-20, 0), Vector(0, 0, 0), 1.0f);
	HUDParticule.SetUpHarmonic();
	lastRigidCount = 0;
	gameworld->basicCam->isActivated = true;
	displayTrace = true;

	direction.setName("Direction Force");
	
	direction.add(radius.set("radius", 200, 0, 500));
	direction.add(theta.set("theta", 0, -180, 180));
	direction.add(phi.set("phi", 0, -180,180));

	position.setName("Position Force");
	position.add(x.set("x", 0, -10, 10));
	position.add(y.set("y", 0, -10, 10));
	position.add(z.set("z", 0, -10, 10));
	gui.setup(direction);
	gui.add(position);
	gui.setPosition(10, ofGetHeight() - 250);


}

//--------------------------------------------------------------
void ofApp::update()
{
	double delta = ofGetLastFrameTime();

	//////PHASE 2/////

	gameworld->UpdateLogic(delta);

	HUDParticule.HarmonicMovementDamping(1.0f, 0.1f, delta);

	//////PHASE 3/////
	input.updateFromGui(x, y, z, radius, theta, phi);
	
}

ofVbo vbo;
//--------------------------------------------------------------
void ofApp::draw()
{
	gui.draw();
	if (gameworld->myCam->isActivated)
	{
		gameworld->myCam->beginCam();

	}
	else
	{
		gameworld->basicCam->beginCam();
	}

	// Configurez la boîte avec la taille souhaitée
	
	ofSetColor(ofColor::white);

	//draw les sphères
	for (Sphere* particule : gameworld->systemeSpheres)
	{
		ofSetColor(particule->GetColor());
		ofDrawSphere(particule->GetPosition().toVec3(), particule->GetRadius());
	}
	ofSetColor(ofColor::white);
	ofEnableDepthTest();
	/////////////PHASE 3/////////////////
	for (Rigid* rigidBody : gameworld->rigidBodies)
	{
		rigidBody->draw();
	}
	ofDisableDepthTest();
	input.draw();


	//draw la trace
	if (displayTrace) {
		ofSetColor(ofColor::orange);
		for (Vector v : gameworld->GetTrace()) {
			ofDrawSphere(v.toVec3(), 2.0f);
		}
		ofSetColor(ofColor::white);
	}
	

	if (gameworld->myCam->isActivated)
	{
		gameworld->myCam->endCam();
	}
	else
	{
		gameworld->basicCam->endCam();
	}

	/////////////////////////HUD//////////////////
	ofPushStyle();
	ofSetupScreenOrtho();
	//ofSetDrawBitmapMode(OF_BITMAPMODE_MODEL);
	//dessine les commandes
	ofDrawBitmapString("Commands:\n c: Spawn rigidBody\n v: add Force To spawning rigidBody\n space: launch rigidBody\n m: Enable/Disable Follow Cam\n k/j : change cam zoom\n e + mouse: rotate around\n t: toggle previosu positions on/off\n r: reset previous positions", 10, 10);
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
		//lancer une boite
		input.spawnRigid(gameworld->rigidBodies, gameworld->registreRigids);
		break;
	case 'c':
		//commencer la création d'une boite
		input.preSpawnRigid(gameworld->myCam, moonParticle);
		break;
	case 'v':
		//valider un vecteur
		input.addForceToSpawningRegistry();
		break;
	case 'e':
		input.move_cam = true;
		break;
	default: break;
	}

	input.setInput(v);
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key)
{
	switch (key) {
	case 'e': input.move_cam = false;
		break;
	default: break;
	}
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y )
{
	if (gameworld->myCam->isActivated && input.move_cam)
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
	gui.setPosition(10, ofGetHeight() - 250);
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg)
{

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo)
{ 
	
}
