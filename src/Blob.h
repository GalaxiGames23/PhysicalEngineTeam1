#ifndef BLOB_H
#define BLOB_H
#include <vector>
#include "Camera.h"
#include "of3dGraphics.h"
#include "PlayerController.h"
#include "Sphere.h"
#include <cstdio>

class GameWorld;
struct Spring;


class Blob
{
	struct BlobParticule;

	struct SpringExtended
	{
		Spring* save_Force = NULL;
		BlobParticule* particle = NULL;
	};
	struct BlobParticule
	{
		int layerforSplit;
		Sphere *particle;
		std::vector<SpringExtended*> neighboor;
		int color = 0;

	};

	
	private:
		int nbBlob = 10;
		int currentnbBlob = 10;
		float massBlob = 10;
		float ressortK = 10;
		int begin_radius = 20;
		double begin_angle = PI/2.0f;
		Vector init_position = Vector(0,0,0);

		std::vector<BlobParticule*> particlesArray;
		BlobParticule * mainParticule = NULL;
		BlobParticule* extremumParticule = NULL;
		GameWorld* refGameWorld = NULL;
		void clearBlob();
		void spawnAllParticule();
		void countBlobParticule();
		
	public:
		Blob(){};
		Blob(Vector init_position, int nb_Blob, int mass_blob, float ressort_k, Camera *cam, PlayerController *p, GameWorld *	g);
		~Blob();
		void respawn();
		void split();
		void join();
		void draw();
		int get_current_size() { return currentnbBlob; }
		

};

#endif BLOB_H