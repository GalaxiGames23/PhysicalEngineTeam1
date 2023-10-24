#ifndef GAMEWORLD_H
#define GAMEWORLD_H

#include "Particule.h"
#include "ParticuleForceGenerator.h"
#include "ParticuleForceRegistry.h"
#include "ParticuleGravity.h"
#include "ParticuleSpring.h"
#include "Blob.h"
#include "ParticuleFrictionStatic.h"
#include "ParticuleFrictionCinetic.h"
#include "Ground.h"
#include "Sphere.h"
#include "InputForce.h"
#include "Input.h"
#include <iostream>
#include <cstdlib>
#include <vector>

using namespace std;

struct Spring {
	Particule* particule1;
	ParticuleSpring* spring;
};

struct Cable {
	Particule* particule1;
	Particule* particule2;

	double e;
	double distance;
};

struct Rod {
	Particule* particule1;
	Particule* particule2;
	double distance;
};

struct BlobSpring
{
	Spring* spring;
	Cable* cable;
};


class GameWorld
{
public:
	////// Objets physiques //////
	std::vector<Sphere*> systemeSpheres;//<<< Vector de la STL pour stocker les sphères à considérer dans les calculs
	Ground& ground = Ground::getGround(); //<<< LE SOL

	////// Liaisons entre objets //////
	std::vector<Spring*> springList; //<<< Liste des ressorts
	std::vector<Cable*> cableList; //<<< Liste des câbles
	std::vector<Rod*> rodList; //<<< Liste des tiges


	////// Forces //////
	ParticuleForceRegistry registre; //<<< Registre des forces (clear à chaque frame)
	ParticuleGravity worldGravity;
	ParticuleFrictionCinetic worldAirFriction;

	////// Blob //////
	Blob *myBlob = NULL;
	std::vector<BlobSpring*> blobList; // Liste des ressorts du blob (gérés séparément)
	
	////// Inputs //////
	Camera* myCam;
	std::vector<InputRegistre*> inputRegistre;


	
	////// Constructeur ////////
	GameWorld();

	////// Appplication de la logique du monde ////////
	void UpdateLogic(float duration); // Résultat = Calcul des nouvelles position de chaque objet

	////// DEMOS ////////
	void demoRessort();
	void demoParticule();
	void demoCable();
	void demoTige();


private:
	////// Calcul et application de la physique ////////

	void addForces(); // Ajout des forces au registre
	void dealCables(); // Gestion des forces appliquées par les câbles
	void dealRods(float duration); // Gestion des forces appliquées par les tiges
	void dealCollisions(float duration); // Gestion des collisions entre objets
};

#endif