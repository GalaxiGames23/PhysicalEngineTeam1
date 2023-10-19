#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
	input.set_Input(v);
	input.SetDessinerTrace(false);
	input.SetAfficherPositions(false);
	input.calculSomePoints(v, init_point, gameworld->worldGravity.GetGravity(), ground);
	timer = 0;
	isEuler = true; // Intégration d'Euler pour la position des particules par défaut
	gameworld->myCam = new Camera(moonParticle->GetPosition() + Vector(-1000,0,0), moonParticle);
	myController = new PlayerController(moonParticle, gameworld->myCam);

}

//--------------------------------------------------------------
void ofApp::update()
{
	double delta = ofGetLastFrameTime();

	//////PHASE 2/////

	gameworld->UpdateLogic(delta);




	//pour la trace, on enregistre une position tous les intervalles fixes
	timer += delta;
	bool temp = timer>0.2f;
	for (int i = 0; i< gameworld->systemeSpheres.size();++i)
	{
		if (!gameworld->systemeSpheres[i]->particleCanMove()) //Si la particule est static, on n'a pas besoin de calculer sa nouvelle position
		{
			continue;
		}
		Vector otherAcceleration = Vector(0, 0, 0);
		if (gameworld->worldGravity.GetGravity().get_y() == 0)
		{
			for (int j = 0; j < gameworld->systemeSpheres.size(); ++j)
			{
				if (i != j)
					otherAcceleration = otherAcceleration + gameworld->systemeSpheres[i]->calculGravitationAccelerationWith(gameworld->systemeSpheres[j]);
			}
		}

		//update de la position de chaque particule avec une des méthodes d'intégration
		if (isEuler)
		{
			gameworld->systemeSpheres[i]->IntegrateEuler(delta, gameworld->worldGravity.GetGravity() + otherAcceleration, damping);
		}
		else
		{
			gameworld->systemeSpheres[i]->IntegrateVerlet(delta, gameworld->worldGravity.GetGravity() + otherAcceleration, damping);
		}

		if(temp)
		{
			//enregistrer les positions pour la trace
			TracePositions.push_back(gameworld->systemeSpheres[i]->GetPosition());
		}
	}
	
	if (temp) { timer = 0; }
	//obligé si on veut parcourir le tableau sans les nouveaux éléments
	vector<Sphere*> save  = gameworld->systemeSpheres;
	//on exécute la fonction de collision
	for (Particule *particule: save)
	{

		//if (particule->GetPosition().get_y() >= ground.yCoord) // si on est plus bas ou égal que le sol
		//{
		//	particule->onCollisionDetected(gameworld->systemeSpheres);
		//}
	}
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
		ofDrawSphere(particule->GetPosition().toVec3(), 10.0f);
	}
	ofSetColor(ofColor::white);



	ofSetColor(ofColor::brown);
	ofDrawBox(glm::vec3(0, ground.yCoord + 20, 0), 10000, 10, 1000); //Dessine le sol
	ofSetColor(ofColor::white);

	if (input.GetDessinerTrace()) //si les traces sont activées par l'utilisateur
	{
		ofSetColor(ofColor::orange);
		int size = TracePositions.size() - gameworld->systemeSpheres.size();
		//affiche la trace
		for (int i = 0; i < size; ++i)
		{
			ofDrawSphere(TracePositions[i].toVec3(), 5.0f);
		}
		ofSetColor(ofColor::white);

		
	}
	
	
	//dessine toutes les particules listées
	for (Sphere* particule : gameworld->systemeSpheres)
	{
		ofSetColor(particule->GetColor());
		ofDrawSphere(particule->GetPosition().toVec3(), 10.0f);
	}
	ofSetColor(ofColor::white);
	


	
	ofSetColor(ofColor::red);
	ofDrawSphere(ground.impact_point.toVec3(), 5.0f); // Dessine le point d'impact prévisionnel
	ofSetColor(ofColor::white);

	ofSetColor(ofColor::darkGrey);
	ofDrawSphere(gameworld->myCam->getPosition().toVec3(), 5.0f); // Dessine le point vertical maximum prévisionnel
	ofSetColor(ofColor::white);
	
	ofDrawSphere(input.max_point.toVec3(), 5.0f); // Dessine le point vertical maximum prévisionnel
	ofSetColor(ofColor::white);
	ofSetColor(ofColor::forestGreen);
	ofDrawSphere(input.max_point.toVec3(), 5.0f); // Dessine le point vertical maximum prévisionnel
	ofSetColor(ofColor::white);
	ofDrawArrow(init_point.toVec3(), v.toVec3() + init_point.toVec3(), 6); // Dessine la flèche du vecteur vitesse

	if (gameworld->myCam->isActivated)
	{
		gameworld->myCam->endCam();
	}

	ofPushStyle();
	ofSetupScreenOrtho();
	//dessine les commandes
	ofDrawBitmapString("Commands:\nc: increase norm\nx: decrease norm\ne & mouse:change angle\ni:change integration mode\nt: show previous positions on/off\nr: clear previous positions\np: display current position values\nspace: spawn normal particle\nb: spawn bouncing particle\nn: spawn fireball particle \nv: no gravity + spawn moon \nf: damping\ng: change gravity\nh & mouse: move ground", 20, 20);
	if (input.GetAfficherPositions()) //Si la position des particules est activée par l'utilisateur
	{
		//affiche la position des particules
		for (int i = 0; i < gameworld->systemeSpheres.size(); ++i)
		{
			ofDrawBitmapString("value: " + ofToString(gameworld->systemeSpheres[i]->GetPosition()), ofGetWidth() - 200, 30 + 15 * (gameworld->systemeSpheres.size() - i - 1));
		}
	}
	if (input.GetDessinerTrace()) //si les traces sont activées par l'utilisateur
	{
		ofDrawBitmapString("Previous Positions: ON", 20, ofGetHeight() - 20);//affiche la mention de ON/OFF pour la trace

	}
	else
	{
		ofDrawBitmapString("Previous Positions: OFF", 20, ofGetHeight() - 20);
	}
	
	// Affiche le mode de calcul de la position
	if (isEuler) { ofDrawBitmapString("Integration Mode : Euler", 20, ofGetHeight() - 40); }
	else { ofDrawBitmapString("Integration Mode : Verlet", 20, ofGetHeight() - 40); }
	// Affiche le mode de calcul de la position
	if (damping == 1.0) { ofDrawBitmapString("Frottements: OFF", 20, ofGetHeight() - 60); }
	else { ofDrawBitmapString("Frottements: ON", 20, ofGetHeight() - 60); }
	
	ofPopStyle();
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
	case ' ': gameworld->systemeSpheres.push_back(new Sphere(current_mass, init_point, v, 1)); // Création d'une particule
		break;
	case 'b': if (gameworld->myBlob == NULL) gameworld->myBlob = new Blob(Vector(300, 300, 0), 35, 10, 50, gameworld->myCam, myController, gameworld);
			else
	{
		delete gameworld->myBlob;
		gameworld->myBlob = NULL;
	}
		break;
	case 'i': isEuler = !isEuler; // Switch du mode d'intégration
		break;
	case 'v':
		if (gameworld->worldGravity.GetGravity().get_y() > 0)
		{
			gameworld->worldGravity.GetGravity().set(0, 0, 0);
			gameworld->systemeSpheres.push_back(moonParticle);
		}
		else
		{
			gameworld->worldGravity.GetGravity().set(0, verticalGravity, 0);
			auto it = std::find(gameworld->systemeSpheres.begin(), gameworld->systemeSpheres.end(), moonParticle);
			if (it != gameworld->systemeSpheres.end()) {
				gameworld->systemeSpheres.erase(it);
			}

		}
		break;
	case 'g': if (gameworld->worldGravity.GetGravity().get_y() > verticalGravity) gameworld->worldGravity.GetGravity().set(0, verticalGravity , 0); //Changer la gravité
			else  gameworld->worldGravity.GetGravity().set(0, verticalGravity * 1.5, 0);
		break;
	case 'r': TracePositions.clear();
		break;
	case 'h': input.ground_key = true;
		break;
	case 'f': if (damping > 0.9f) damping = 0.7f;
			else damping = 1.0f;
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
	input.calculSomePoints(v, init_point, gameworld->worldGravity.GetGravity(), ground);

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key)
{
	switch (key) {
	case 'e':input.angle_key = false;
		break;
	case 'h': input.ground_key= false;
		break;
	default: break;
	}
	

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y )
{
	if (input.angle_key) //Changement d'angle
	{
		int diffx = x - input.last_pos_x;
		int diffy = y - input.last_pos_y;
		if (abs(diffx) > abs(diffy) + 1 && diffx != 0)
		{
			input.change_angle2(diffx);

		}
		else if (abs(diffy) > abs(diffx) + 1 && diffy != 0)
		{
			input.change_angle1(diffy);
		}
		input.set_Input(v);
		input.calculSomePoints(v, init_point, gameworld->worldGravity.GetGravity(), ground);

	}
	else if (input.ground_key)
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
	if (button == 0) //Changement de la position initiale
	{
		init_point.set(x, y, 0);
		input.calculSomePoints(v, init_point, gameworld->worldGravity.GetGravity(), ground);
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
