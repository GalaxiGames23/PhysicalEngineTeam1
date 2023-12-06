#ifndef GAMEWORLD_H
#define GAMEWORLD_H

#include "Particule.h"
#include "Sphere.h"
#include "Box.h"
#include "BoxPair.h"


#include "ParticuleForceGenerator.h"
#include "ParticuleForceRegistry.h"

#include "RigidBodyForceRegistry.h"
#include "RigidBodyForce.h"

#include "ParticuleGravity.h"
#include "ParticuleFrictionStatic.h"
#include "ParticuleFrictionCinetic.h"

#include "Input.h"
#include "InputForce.h"
#include "Octree.h"

#include <iostream>
#include <cstdlib>
#include <vector>

using namespace std;


class GameWorld
{
	//////////////////////////////////////// PUBLIC ////////////////////////////////////////
public:

	//////////////////////////////////////// PHASE 2 ////////////////////////////////////////

	////// Objets physiques //////
	std::vector<Sphere*> systemeSpheres;//<<< Vector de la STL pour stocker les sphères à considérer dans les calculs


	////// Forces //////
	ParticuleForceRegistry registre; //<<< Registre des forces (clear à chaque frame)

	ParticuleGravity worldGravity;
	ParticuleFrictionCinetic worldAirFriction;
	
	////// Inputs //////
	Camera* myCam;

	Octree octree;

	////// Inputs //////
	Camera* basicCam;
	std::vector<InputRegistre*> inputRegistre;

	////// Constructeur ////////
	GameWorld();

	////// Appplication de la logique du monde ////////
	void UpdateLogic(float duration); // Résultat = Calcul des nouvelles position de chaque objet

	////////////////////////////////////////////////// PHASE 3 /////////////////////////////////////////////

	////// Objets physiques //////
	std::vector<Rigid*> rigidBodies;//<<<liste des rigid bodies

	/////////Forces////////
	RigidBodyForceRegistry registreRigids; //<<< Registre des forces pour les rigid bodies (clear à chaque frame)

	/////////gestion de la trace///////
	void ClearTrace() { this->tracePositions.clear(); }//<<<inline, vide la trace, évite d'exposer la trace
	std::vector<Vector> GetTrace() { return this->tracePositions; }//<<<inline, getter, retourne les positions de la trace pour affichage, évite d'exposer la trace

	//////////////////////////////////////// PRIVATE ////////////////////////////////////////
private:
	//////////////////////////////////////// PHASE 2 ////////////////////////////////////////

	////// Calcul et application de la physique ////////

	void addForces(); // Ajout des forces au registre

	////////////////////////////////////////////////// PHASE 3 /////////////////////////////////////////////

	double timer;//<<<timer pour la trace
	std::vector<Vector> tracePositions; //<<< Vector de la STL pour stocker les positions de la trace des particules quand l'option est activée
	void UpdateTrace(float duration);//<<<update la trace selon l'état du timer
	

	////////////////////////////////////////////////// PHASE 4 /////////////////////////////////////////////

	////// Recherche des collisions //////
	std::vector<BoxPair*> boxPairs;//<<<liste des rigid bodies

	void HandleCollisions();
	bool DetectCollisions(Box* box1, Box* box2);
	void ResolveCollisions(Box* box1, Box* box2, Vector pointCollision);
};

#endif