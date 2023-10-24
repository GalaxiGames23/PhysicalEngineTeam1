#include "Blob.h"
#include "GameWorld.h"
#include "ofApp.h"

void Blob::clearBlob()
{

	for (BlobParticule* particle : particlesArray) //suprimer les forces du blob
	{
		int n = refGameWorld->blobList.size();
		for (int i = 0; i < n; i++)
		{
			BlobSpring* p = refGameWorld->blobList.back();
			refGameWorld->blobList.pop_back();
			delete p->cable;
			delete p->spring->spring;
			delete p->spring;
			delete p;

			int neighboorCount = particle->neighboor.size();
			for (int i = 0; i < neighboorCount; i++)
			{
				SpringExtended* se = particle->neighboor.back();
				particle->neighboor.pop_back();

				delete se;
			}
			
		}
		

	}
	for (BlobParticule* particle : particlesArray)//suprimer les particules du blob
	{
		auto it = std::find(refGameWorld->systemeSpheres.begin(), refGameWorld->systemeSpheres.end(), particle->particle);
		if (it != refGameWorld->systemeSpheres.end()) {
			refGameWorld->systemeSpheres.erase(it);
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
	this->currentnbBlob = nbBlob;
	this->massBlob = mass_blob;
	this->ressortK = ressort_k;
	this->refGameWorld = g;
	this->init_position = init_position;
	mainParticule = new BlobParticule();
	mainParticule->layerforSplit= 0;
	mainParticule->particle = new Sphere(massBlob, init_position, Vector(0,0,0), 0.5);
	particlesArray.push_back(mainParticule);
	refGameWorld->systemeSpheres.push_back(mainParticule->particle);
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
	while (count < nbBlob - 1) //Création des particules autour de sphère de plus en plus grandes
	{
		if ( phi >= PI)
		{
			phi = 0;
			theta += diff_angle;
			if (theta >= PI) 
			{
				theta = 0;
				radius += begin_radius;
				layer++;
				diff_angle /= 2;
			}
		}
		position = radius * Vector(cos(phi) * cos(theta), sin(theta), cos(theta) * sin(phi));

		if (last_position.norm() == 0) // Privilégier la symétrie
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
		p->particle = new Sphere(massBlob, init_position + position, Vector(0, 0, 0), 0.5);
		p->layerforSplit = layer;
		particlesArray.push_back(p);
		refGameWorld->systemeSpheres.push_back(p->particle);
		count++;
	

	}

	int n = particlesArray.size();
	for (int i = 0; i < n; i++) // Création des ressorts/cables entre les particules
	{
		BlobParticule* p1 = particlesArray[i];
		float c = 0.7;
		while (p1->neighboor.size() < 4 && c < 5)
		{
			
			for (int j = 0; j < n; j++)
			{

				if (i != j)
				{
					BlobParticule* p2 = particlesArray[j];
					bool alreadyin = false;
					for (SpringExtended* se : p1->neighboor)
					{
						if (se->particle->particle == p2->particle)
						{
							alreadyin = true;
						}
					}

					if (!alreadyin && p1->particle->GetPosition().distance(p2->particle->GetPosition()) < c * begin_radius) // Si les particules sont assez proches
					{
						SpringExtended* f1 = new SpringExtended();
						f1->particle = p2;
						SpringExtended* f2 = new SpringExtended();
						f2->particle = p1;
						Cable *cable = new Cable();
						cable->particule1 = p1->particle;
						cable->particule2 = p2->particle;
						cable->e = 1;
						cable->distance =  2*begin_radius*c;
						Spring* spring = new Spring();
						spring->particule1 = p1->particle;
						spring->spring = new ParticuleSpring(ressortK,  begin_radius *0.9*c, p2->particle);
						BlobSpring *force = new BlobSpring();
						force->cable = cable;
						force->spring = spring;
						f1->save_Force = force;
						f2->save_Force = force;
						refGameWorld->blobList.push_back(force);
						p1->neighboor.push_back(f1);
						p2->neighboor.push_back(f2);
					}
				}
				
			}
			c += 0.1;
		}
	}
	extremumParticule = particlesArray.back();
}

void Blob::countBlobParticule()
{
	std::queue<BlobParticule*> myQueue;
	myQueue.push(mainParticule);
	int count = 1;
	int color = mainParticule->color + 1;
	while (!myQueue.empty()) // Compter le nombre de particule du graphe connexe appartenant à la particule que l'utilisateur controle
	{
		BlobParticule* p = myQueue.front();
		 myQueue.pop();
		p->color = color + 2;

		for (SpringExtended* neighboor : p->neighboor)
		{
			if (neighboor->particle->color != p->color)
			{
				count++;
				neighboor->particle->color = p->color;
				myQueue.push(neighboor->particle);

			}
		}

	}
	currentnbBlob = count;
	extremumParticule = mainParticule;

	myQueue.push(mainParticule);
	color = mainParticule->color + 1;
	while (!myQueue.empty()) // Changer la couleur d'un graphe connexe
	{
		BlobParticule* p = myQueue.front();
		myQueue.pop();
		p->color = color + 2;

		for (SpringExtended* neighboor : p->neighboor)
		{
			if (neighboor->particle->color != p->color)
			{
				neighboor->particle->color = p->color;
				myQueue.push(neighboor->particle);
				p->particle->SetColor(double(currentnbBlob) / nbBlob * 250);
				neighboor->particle->particle->SetColor(double(currentnbBlob) / nbBlob * 250);

			}
		}

	}
}


Blob::~Blob()
{
	clearBlob();
}

void Blob::split()
{
	int n = this->currentnbBlob;
	std::queue<BlobParticule*> myQueue;
	if (n > 1) // Si il y a plus de 1 particule
	{
		myQueue.push(extremumParticule);
		int count = n/2 - 1;
		int color = myQueue.front()->color + 1;
		myQueue.front()->color = color;
		myQueue.front()->particle->SetColor(500);
		while ( count > 0 && !myQueue.empty()) // Parcours en largeur pour déterminer un graphe avec nb/2 sommet
		{
			BlobParticule* p = myQueue.front();
			myQueue.pop();
			p->color = color;
			
			for (SpringExtended* neighboor : p->neighboor)
			{
				if (neighboor->particle->color != p->color)
				{
					neighboor->particle->color = p->color;
					myQueue.push(neighboor->particle);
					p->particle->SetColor( 50);

					count--;
					if (count < 0)
					{
						myQueue.push(p);
						break;
					}
				}
			}
		}

		while (!myQueue.empty())// Couper les arêtes qui vont vers l'exterieur du graphe
		{
			BlobParticule* p = myQueue.front();
			myQueue.pop();
			int countNeighboor = p->neighboor.size();
			for (int i = 0; i < countNeighboor; i++) // Pour chaque voisin 
			{
				SpringExtended *other = p->neighboor.back();
				p->neighboor.pop_back();
				if (other->particle->color != p->color) // On regarde le groupe du voisin, si c'est pas le même
				{
					int countNeighboor2= other->particle->neighboor.size();
					for (int j = 0; j < countNeighboor2; j++) //suppression de la particule p dans le voisin (car ils ne le sont plus)
					{
						SpringExtended* neighboor2 = other->particle->neighboor.back();
						other->particle->neighboor.pop_back();
						if (neighboor2->particle == p)
						{
							break;
						}
						other->particle->neighboor.insert(other->particle->neighboor.begin(), neighboor2);
					}
					auto id = std::find(refGameWorld->blobList.begin(), refGameWorld->blobList.end(), other->save_Force); //supression du ressort reliant les deux particules
					if (id != refGameWorld->blobList.end()) {
						refGameWorld->blobList.erase(id);
						delete other->save_Force; 
						delete other;
					}
					else
					{
						printf("THERE IS A PROBLEME");
					}

				}
				else
				{
					p->neighboor.insert(p->neighboor.begin(), other);
				}
			}
		}
		countBlobParticule();
		
	}


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
		for (SpringExtended* p2: p1->neighboor)
		{
			Vector v1 = p1->particle->GetPosition();
			Vector v2 = p2->particle->particle->GetPosition();
			ofSetLineWidth(3.0); // Épaisseur de la ligne
			ofDrawLine(v1.get_x(), v1.get_y(), v1.get_z(), v2.get_x(), v2.get_y(), v2.get_z());
			ofDrawLine(v1.get_x(), v1.get_y(), v1.get_z(), v2.get_x(), v2.get_y(), v2.get_z());
		}
	}
}

void Blob::join()
{
	int n = this->currentnbBlob;
	if (n < nbBlob) // S'il n'y a pas toutes les particules
	{
		int n = particlesArray.size();
		for (int i = 0; i < n; i++)
		{
			BlobParticule* p1 = particlesArray[i];
			float c = 0.7;
			while (p1->neighboor.size() < 4 && c < 5)
			{

				for (int j = 0; j < n; j++)
				{

					if (i != j)
					{
						BlobParticule* p2 = particlesArray[j];
						bool alreadyin = false;
						for (SpringExtended* se : p1->neighboor)
						{
							if (se->particle->particle == p2->particle)
							{
								alreadyin = true;
							}
						}

						if (!alreadyin && p1->color != p2->color && p1->particle->GetPosition().distance(p2->particle->GetPosition()) < c * begin_radius) // si deux particules sont de couleur différente, pas connectés et assez proches
						{
							if ((p1->neighboor.size() < 3 &&p2->neighboor.size() < 3) || p1->color != p2->color)
							{
								SpringExtended* f1 = new SpringExtended();
								f1->particle = p2;
								SpringExtended* f2 = new SpringExtended();
								f2->particle = p1;
								Cable* cable = new Cable();
								cable->particule1 = p1->particle;
								cable->particule2 = p2->particle;
								cable->e = 1;
								cable->distance =  2 * begin_radius;
								Spring* spring = new Spring();
								spring->particule1 = p1->particle;
								spring->spring = new ParticuleSpring(ressortK,begin_radius, p2->particle);
								BlobSpring* force = new BlobSpring();
								force->cable = cable;
								force->spring = spring;
								f1->save_Force = force;
								f2->save_Force = force;
								refGameWorld->blobList.push_back(force);
								p1->neighboor.push_back(f1);
								p2->neighboor.push_back(f2);
							}
							
						}
					}

				}
				c += 0.1;
			}
		}
	}
	countBlobParticule();
}
