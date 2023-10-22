#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
	input.set_Input(v);
	gameworld->myCam = new Camera(moonParticle->GetPosition() + Vector(-1000,0,0), moonParticle);
	myController = new PlayerController();

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
	ofSetColor(ofColor::brown);
	ofDrawBox(glm::vec3(0, ground.yCoord + 20, 0), 10000, 10, 1000); //Dessine le sol
	ofSetColor(ofColor::white);
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

	
	

	if (gameworld->myCam->isActivated)
	{
		gameworld->myCam->endCam();
	}

	ofPushStyle();
	ofSetupScreenOrtho();
	//ofSetDrawBitmapMode(OF_BITMAPMODE_MODEL);
	ofScale(2, 2);
	//dessine les commandes
	ofDrawBitmapString("Commands:\nZQSD : diriger la particule du blob controlee (clavier AZERTY)\nB : spawn/despawn le blob\nH : deplacer le sol\nL : Split le blob\nO : rassembler le blob\nK/J : bouger la caméra\nM: activer la caméra trackant le blob\nESPACE : demo de particule simple\nX : demo de ressort\nC : demo de câble\nV : demo de tige", 10, 10);
	
	if (gameworld->myBlob != NULL)
	{
		ofScale(0.5, 0.5);
		ofScale(3, 3);
		timer += ofGetLastFrameTime();
		ofDrawBitmapString(std::to_string(gameworld->myBlob->get_current_size()), ofGetWidth()/3 - 30, 15 + cos(3*timer) * 2) ;
	}
	else
	{
		ofDrawBitmapString("NO BLOB SPAWNED", ofGetWidth() /2 - 130, 20 );
	}
	
	ofPopStyle();
}


//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
	switch (key) {
		//blob
	case 'b': if (gameworld->myBlob == NULL) gameworld->myBlob = new Blob(Vector(300,500, 0),20, 4, 2, gameworld->myCam, myController, gameworld);
			else
	{
		delete gameworld->myBlob;
		gameworld->myBlob = NULL;
	}
		break;
		//bouger le sol
	case 'h': input.ground_key = true;
		break;
		//split le blob
	case 'l': if (gameworld->myBlob != NULL) { gameworld->myBlob->split(); }
		break;
		//rassembler le blob
	case 'o': if (gameworld->myBlob != NULL) { gameworld->myBlob->join(); }
			break;
			//bouger la camera
	case 'k': gameworld->myCam->changeNorm(-ofGetLastFrameTime());
		break;
	case 'j': gameworld->myCam->changeNorm(ofGetLastFrameTime());
		break;
		//activer/descativer la camera
	case 'm': gameworld->myCam->isActivated = !gameworld->myCam->isActivated;
		break;
		//controles ZQSD
	case 'z': if (input.forward_key == NULL && myController->isActive())
	{
		input.forward_key = new InputRegistre();
		input.forward_key->particule = myController->getFocusParticule();
		input.forward_key->fg = new InputForce(myController, true, 1);
		gameworld->inputRegistre.push_back(input.forward_key);
	}
		break;
	case 's':  if (input.backward_key == NULL && myController->isActive())
	{
		input.backward_key = new InputRegistre();
		input.backward_key->particule = myController->getFocusParticule();
		input.backward_key->fg = new InputForce(myController, true, -1);
		gameworld->inputRegistre.push_back(input.backward_key);
	}
		break;
	case 'd':if (input.right_key == NULL && myController->isActive())
	{
		input.right_key = new InputRegistre();
		input.right_key->particule = myController->getFocusParticule();
		input.right_key->fg = new InputForce(myController, false, 1);
		gameworld->inputRegistre.push_back(input.right_key);
	}
		break;
	case 'q': if (input.left_key== NULL && myController->isActive())
	{
		input.left_key = new InputRegistre();
		input.left_key->particule = myController->getFocusParticule();
		input.left_key->fg = new InputForce(myController, false, -1);
		gameworld->inputRegistre.push_back(input.left_key);
	}
		break;
	case ' ': gameworld->demoParticule();
		break;
	case 'x':gameworld->demoRessort();
		break;
	case 'c':gameworld->demoCable();
		break;
	case 'v': gameworld->demoTige();
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
	case 'z':
		input.remove_input(input.forward_key, gameworld->inputRegistre);
		input.forward_key = NULL;
		break;
	case 's': 
		input.remove_input(input.backward_key, gameworld->inputRegistre);
		input.backward_key = NULL;
		break;
	case 'd':
		input.remove_input(input.right_key, gameworld->inputRegistre);
		input.right_key = NULL;
		break;
	case 'q': 
		input.remove_input(input.left_key, gameworld->inputRegistre);
		input.left_key = NULL;
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
