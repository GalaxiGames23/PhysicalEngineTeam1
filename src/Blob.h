#ifndef BLOB_H
#define BLOB_H
#include <vector>
#include "Camera.h"
#include "of3dGraphics.h"
#include "PlayerController.h"
#include "Sphere.h"
#include <cstdio>

class GameWorld;
struct BlobSpring;


class Blob
{
	struct BlobParticule;
	/*Structure permettant de sauvegarder les forces*/
	struct SpringExtended
	{
		BlobSpring* save_Force = NULL;
		BlobParticule* particle = NULL;
	};
	/*Structure permettant de definir un graphe*/
	struct BlobParticule
	{
		int layerforSplit;
		Sphere *particle;
		std::vector<SpringExtended*> neighboor;
		int color = 0;

	};

	
	private:
		int nbBlob = 10; //nombre de particule initialement
		int currentnbBlob = 10; //nombre de particule actuellement
		float massBlob = 10; // masse de chaque particule
		float ressortK = 10; // constante du ressort
		int begin_radius = 20; // rayon pour la création des particules
		double begin_angle = PI/2.0f; //angle pour la création des particules
		Vector init_position = Vector(0,0,0); //position initiale

		std::vector<BlobParticule*> particlesArray; //toutes les particules du graphe
		BlobParticule * mainParticule = NULL; // particule centrale
		BlobParticule* extremumParticule = NULL; //particule sur un coté du graphe
		GameWorld* refGameWorld = NULL;

		/*Effacer le blob*/
		void clearBlob();
		/*Faire apparaitre les particules et leur liaison*/
		void spawnAllParticule();
		/*Compter le nombre actuel de particule dans notre blob, et leur donner visuellement tous la même couleur*/
		void countBlobParticule();
		
	public:
		Blob(){};
		Blob(Vector init_position, int nb_Blob, int mass_blob, float ressort_k, Camera *cam, PlayerController *p, GameWorld *	g);
		~Blob();
		/*Respawn du blob*/
		void respawn();
		/*Séparer le blob en deux parties a peu près égale*/
		void split();
		/*Fusionner au moins deux blob distincts en un seul gros blob*/
		void join();
		/*Dessiner les liaisons entre deux particules voisines*/
		void draw();

		int get_current_size() { return currentnbBlob; }
		

};

#endif BLOB_H