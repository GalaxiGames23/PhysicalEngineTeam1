#include "FireBallParticule.h"


void FireBallParticule::onCollisionDetected(vector<Particule*>& allParticles)
{
	
	int nbParticule = nbSpawnParticle + (rand() % 2 * randomNBSpawn) - randomNBSpawn;
	for (int i = 0; i < nbParticule; i++)
	{
		double current_norm = norm + rand() % randomNorm;
		double current_angle1 = angle + (float)(rand() % 50) / 100.f;
		double current_angle2 = i * (3.14 / nbParticule) + (float)(rand() % 50) / 100.f;
		Vector velocity = Vector(cos(current_angle1) * cos(current_angle2) * current_norm, -current_norm * sin(current_angle1), current_norm * cos(current_angle1) * sin(current_angle2));
		allParticles.push_back(new Particule(0.001, position + Vector(0,-20,0), velocity, ofColor::lightGoldenRodYellow));
	}
	Particule::onCollisionDetected(allParticles);
	
}