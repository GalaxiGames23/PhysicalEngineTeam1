#ifndef BLOB_H
#define BLOB_H
#include <vector>
#include "Camera.h"
#include "of3dGraphics.h"
#include "PlayerController.h"
#include "Sphere.h"
#include <cstdio>

class GameWorld;

class Blob
{

	struct BlobParticule
	{
		int layerforSplit;
		Sphere *particle;
		std::vector<BlobParticule*> neighboor;

	};
	private:
		int nbBlob = 10;
		float massBlob = 10;
		float ressortK = 10;
		int begin_radius = 50;
		double begin_angle = PI/2.0f;
		Vector init_position = Vector(0,0,0);

		std::vector<BlobParticule*> particlesArray;
		BlobParticule * mainParticule = NULL;
		GameWorld* refGameWorld = NULL;
		void clearBlob();
		void spawnAllParticule();
		
	public:
		Blob(){};
		Blob(Vector init_position, int nb_Blob, int mass_blob, float ressort_k, Camera *cam, PlayerController *p, GameWorld *	g);
		~Blob();
		void respawn();
		void split();
		void join();
		void draw();
		

};

#endif BLOB_H