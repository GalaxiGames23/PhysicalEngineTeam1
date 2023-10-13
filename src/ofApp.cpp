#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
	input.set_Input(v);
	input.SetDessinerTrace(false);
	input.SetAfficherPositions(false);
	input.calculSomePoints(v, init_point, gravity, ground);
	timer = 0;
	isEuler = true; // Intégration d'Euler pour la position des particules par défaut
	myCam = new Camera(moonParticle->GetPosition() + Vector(-1000,0,0), moonParticle);
	myController = PlayerController(moonParticle, myCam);

	//LIGNES DE TEST A BOUGER VERS LES CLASSES DE TEST
	/*ParticuleForceRegistry registre;
	Vector& vect = Vector();
	Particule &part = Particule(5,vect,vect);
	ParticuleGravity gen;
	registre.add(&part, &gen);
	std::cout << "Masse particule"<<registre.registre[0].particule->GetMass()<<std::endl;
	//registre.remove(&part, &gen);
	registre.clear();
	std::cout << "taille registre"<<registre.registre.size()<<std::endl;
	std::cout << "Masse particule" << part.GetMass() << std::endl;*/
}

//--------------------------------------------------------------
void ofApp::update()
{
	double delta = ofGetLastFrameTime();
	//pour la trace, on enregistre une position tous les intervalles fixes
	timer += delta;
	bool temp = timer>0.2f;
	for (int i = 0; i<SystemeParticules.size();++i)
	{
		if (!SystemeParticules[i]->particleCanMove()) //Si la particule est static, on n'a pas besoin de calculer sa nouvelle position
		{
			continue;
		}
		Vector otherAcceleration = otherAcceleration = Vector(0, 0, 0);
		if (gravity.get_y() == 0)
		{
			for (int j = 0; j < SystemeParticules.size(); ++j)
			{
				if (i != j)
					otherAcceleration = otherAcceleration + SystemeParticules[i]->calculGravitationAccelerationWith(SystemeParticules[j]);
			}
		}

		//update de la position de chaque particule avec une des méthodes d'intégration
		if (isEuler)
		{
			SystemeParticules[i]->IntegrateEuler(delta, gravity + otherAcceleration, damping);
		}
		else
		{
			SystemeParticules[i]->IntegrateVerlet(delta, gravity + otherAcceleration, damping);
		}

		if(temp)
		{
			//enregistrer les positions pour la trace
			TracePositions.push_back(SystemeParticules[i]->GetPosition());
		}
	}
	
	if (temp) { timer = 0; }
	//obligé si on veut parcourir le tableau sans les nouveaux éléments
	vector<Particule*> save  = SystemeParticules;
	//on exécute la fonction de collision
	for (Particule *particule: save)
	{

		if (particule->GetPosition().get_y() >= ground.yCoord) // si on est plus bas ou égal que le sol
		{
			particule->onCollisionDetected(SystemeParticules);
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw()
{
	if (myCam->isActivated)
	{
		myCam->beginCam();

	}
	ofSetColor(ofColor::white);

	
	ofSetColor(ofColor::brown);
	ofDrawBox(glm::vec3(0, ground.yCoord + 20, 0), 10000, 10, 1000); //Dessine le sol
	ofSetColor(ofColor::white);

	if (input.GetDessinerTrace()) //si les traces sont activées par l'utilisateur
	{
		ofSetColor(ofColor::orange);
		int size = TracePositions.size() - SystemeParticules.size();
		//affiche la trace
		for (int i = 0; i < size; ++i)
		{
			ofDrawSphere(TracePositions[i].toVec3(), 5.0f);
		}
		ofSetColor(ofColor::white);

		
	}
	
	
	//dessine toutes les particules listées
	for (Particule* particule : SystemeParticules)
	{
		ofSetColor(particule->GetColor());
		ofDrawSphere(particule->GetPosition().toVec3(), 10.0f);
	}
	ofSetColor(ofColor::white);
	


	
	ofSetColor(ofColor::red);
	ofDrawSphere(ground.impact_point.toVec3(), 5.0f); // Dessine le point d'impact prévisionnel
	ofSetColor(ofColor::white);

	ofSetColor(ofColor::darkGrey);
	ofDrawSphere(myCam->getPosition().toVec3(), 5.0f); // Dessine le point vertical maximum prévisionnel
	ofSetColor(ofColor::white);

	ofSetColor(ofColor::forestGreen);
	ofDrawSphere(input.max_point.toVec3(), 5.0f); // Dessine le point vertical maximum prévisionnel
	ofSetColor(ofColor::white);
	ofDrawArrow(init_point.toVec3(), v.toVec3() + init_point.toVec3(), 6); // Dessine la flèche du vecteur vitesse

	if (myCam->isActivated)
	{
		myCam->endCam();
	}

	ofPushStyle();
	ofSetupScreenOrtho();
	//dessine les commandes
	ofDrawBitmapString("Commands:\nc: increase norm\nx: decrease norm\ne & mouse:change angle\ni:change integration mode\nt: show previous positions on/off\nr: clear previous positions\np: display current position values\nspace: spawn normal particle\nb: spawn bouncing particle\nn: spawn fireball particle \nv: no gravity + spawn moon \nf: damping\ng: change gravity\nh & mouse: move ground", 20, 20);
	if (input.GetAfficherPositions()) //Si la position des particules est activée par l'utilisateur
	{
		//affiche la position des particules
		for (int i = 0; i < SystemeParticules.size(); ++i)
		{
			ofDrawBitmapString("value: " + ofToString(SystemeParticules[i]->GetPosition()), ofGetWidth() - 200, 30 + 15 * (SystemeParticules.size() - i - 1));
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
	case ' ': SystemeParticules.push_back(new Particule(current_mass, init_point, v)); // Création d'une particule
		break;
	case 'b': SystemeParticules.push_back(new BouncingParticule(current_mass, init_point, v)); // Création d'une particule rebondissante
		break;
	case 'n': SystemeParticules.push_back(new FireBallParticule(current_mass, init_point, v));// Création d'une particule boule de feu
		break;
	case 'i': isEuler = !isEuler; // Switch du mode d'intégration
		break;
	case 'v': 
		if (gravity.get_y() > 0)
		{
			gravity.set(0, 0, 0);
			SystemeParticules.push_back(moonParticle);
		}
		else
		{
			gravity.set(0, verticalGravity, 0);
			auto it = std::find(SystemeParticules.begin(), SystemeParticules.end(), moonParticle);
			if (it != SystemeParticules.end()) {
				SystemeParticules.erase(it);
			}

		}
		break;
	case 'g': if (gravity.get_y() > verticalGravity) gravity.set(0, verticalGravity , 0); //Changer la gravité
			else gravity.set(0, verticalGravity * 1.5, 0);
		break;
	case 'r': TracePositions.clear();
		break;
	case 'h': input.ground_key = true;
		break;
	case 'f': if (damping > 0.9f) damping = 0.7f;
			else damping = 1.0f;
		break;
	case 'k': myCam->changeNorm(-ofGetLastFrameTime());
		break;
	case 'j': myCam->changeNorm(ofGetLastFrameTime());
		break;
	case 'm': myCam->isActivated = !myCam->isActivated;
		break;
	case 'z': myController.moveParticuleForward(ofGetLastFrameTime());
		break;
	case 's':  myController.moveParticuleForward(-ofGetLastFrameTime());
		break;
	case 'd': myController.moveParticuleRight(ofGetLastFrameTime());
		break;
	case 'q': myController.moveParticuleRight(-ofGetLastFrameTime());
		break;
	default: break;
	}

	input.set_Input(v);
	input.calculSomePoints(v, init_point, gravity, ground);

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
		input.calculSomePoints(v, init_point, gravity, ground);

	}
	else if (input.ground_key)
	{
		int diffy = y - input.last_pos_y;
		
		 if (diffy != 0)
		{
			 ground.change_ground_height(diffy);
		}
		 input.calculSomePoints(v, init_point, gravity, ground);
	}
	else if (myCam->isActivated)
	{
		int diffx = x - input.last_pos_x;
		int diffy = y - input.last_pos_y;
		if (abs(diffx) > abs(diffy) + 1 && diffx != 0)
		{
			myCam->changePitchAngle(ofGetLastFrameTime() * diffx);

		}
		else if (abs(diffy) > abs(diffx) + 1 && diffy != 0)
		{
			myCam->changeRollAngle(ofGetLastFrameTime() * diffy);
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
		input.calculSomePoints(v, init_point, gravity, ground);
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
