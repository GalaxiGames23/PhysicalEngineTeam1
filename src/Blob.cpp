#include "Blob.h"
#include "GameWorld.h"
#include "ofApp.h"

void Blob::clearBlob()
{

	for (BlobParticule* particle : particlesArray)
	{
		int n = refGameWorld->springList.size();
		for (int i = 0; i < n; i++)
		{
			Spring* p = refGameWorld->springList.back();
			refGameWorld->springList.pop_back();
			if (p->particule1 == particle->particle)
			{
				delete p;
			}
			else
			{
				refGameWorld->springList.push_back(p);
			}
		}
		

	}
	for (BlobParticule* particle : particlesArray)
	{
		auto it = std::find(refGameWorld->systemeParticules.begin(), refGameWorld->systemeParticules.end(), particle->particle);
		if (it != refGameWorld->systemeParticules.end()) {
			refGameWorld->systemeParticules.erase(it);
			delete particle->particle;
			delete particle;
		}
		else
		{
			printf("ERROR PARTICLE NOT FOUND IN GAMEWORLD");
		}
		
	}
	particlesArray.clear();
	
}

Blob::Blob(Vector init_position, int nb_Blob, int mass_blob, float ressort_k, Camera* cam, PlayerController* p, GameWorld* g)
{
	this->nbBlob = nb_Blob;
	this->massBlob = mass_blob;
	this->ressortK = ressort_k;
	this->refGameWorld = g;
	this->init_position = init_position;
	mainParticule = new BlobParticule();
	mainParticule->layerforSplit= 0;
	mainParticule->particle = new Particule(massBlob, init_position, Vector(0,0,0));
	particlesArray.push_back(mainParticule);
	refGameWorld->systemeParticules.push_back(mainParticule->particle);
	cam->setParticuleFollow(mainParticule->particle->GetPosition() - Vector(0,0,300), mainParticule->particle);
	p->changeController(mainParticule->particle, cam);
	spawnAllParticule();
}

void Blob::spawnAllParticule()
{
	int count = 0;
	double phi = 0;
	double theta = 0;
	double radius = begin_radius;
	double diff_angle = begin_angle;
	Vector last_position = Vector(0, 0, 0);
	Vector position = Vector(0, 0, 0);
	int layer = 1;
	while (count < nbBlob - 1)
	{
		if ( phi >= PI)
		{
			phi = 0;
			theta += diff_angle;
			if (theta >= PI) // reset on new circle
			{
				theta = 0;
				radius *= 2;
				layer++;
				diff_angle /= 2;
			}
		}
		position = radius * Vector(cos(phi) * cos(theta), sin(theta), cos(theta) * sin(phi));

		if (last_position.norm() == 0)
		{
			last_position = position;
		}
		else
		{
			position = Vector() - last_position;
			last_position = Vector(0, 0, 0);
			if (theta > PI / 2 - 0.05 && theta < PI / 2 + 0.05)
			{
				phi = PI;
			}
			else
			{
				phi += diff_angle;
			}
		}
		
		
		BlobParticule* p = new BlobParticule();
		p->particle = new Particule(massBlob, init_position + position, Vector(0, 0, 0));
		p->layerforSplit = 0;
		particlesArray.push_back(p);
		refGameWorld->systemeParticules.push_back(p->particle);
		count++;
		

		
		

	}

	int n = particlesArray.size();
	for (int i = 0; i < n; i++)
	{
		BlobParticule* p1 = particlesArray[i];
		float c = 0.7;
		while (p1->neighboor.size() <= 2)
		{
			for (int j = 0; j < n; j++)
			{

				if (i != j)
				{
					BlobParticule* p2 = particlesArray[j];
					auto it = std::find(p1->neighboor.begin(), p1->neighboor.end(), p2);
					if (it == p1->neighboor.end() && p1->particle->GetPosition().distance(p2->particle->GetPosition()) < c * begin_radius)
					{
						p2->neighboor.push_back(p1);
						p1->neighboor.push_back(p2);
						Spring* f = new Spring();
						f->particule1 = p1->particle;
						f->spring = new ParticuleSpring(ressortK, 1.1*begin_radius, p2->particle);
						refGameWorld->springList.push_back(f);
					}
				}
				
			}
			c += 0.1;
		}
	}
}


Blob::~Blob()
{

	
	clearBlob();
	
	

}

void Blob::split()
{
}

void Blob::respawn()
{
	clearBlob();
	spawnAllParticule();
}

void Blob::draw()
{
	// Déterminez les deux points entre lesquels vous voulez dessiner le cylindre
	for (BlobParticule *p1 : particlesArray)
	{
		for (BlobParticule* p2: p1->neighboor)
		{

			Vector v1 = p1->particle->GetPosition();
			Vector v2 = p2->particle->GetPosition();
			ofSetLineWidth(3.0); // Épaisseur de la ligne
			ofDrawLine(v1.get_x(), v1.get_y(), v1.get_z(), v2.get_x(), v2.get_y(), v2.get_z());
			ofDrawLine(v1.get_x(), v1.get_y(), v1.get_z(), v2.get_x(), v2.get_y(), v2.get_z());
		}
	}
	

}

void Blob::join()
{
}
