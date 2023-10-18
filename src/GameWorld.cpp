#include "GameWorld.h"

//Constructeur par d�faut
GameWorld::GameWorld()
{
	registre = ParticuleForceRegistry();
	worldGravity = ParticuleGravity();
}

void GameWorld::UpdateLogic(float duration) 
{

	//ajoute les forces au registre
	addForces();

	//update des forces
	registre.updateForces(duration);

	//clear du registre
	registre.clear();

	//int�gration de chaque particule
	for (int i = 0; i < systemeParticules.size(); ++i)
	{
		std::cout << systemeParticules[i]->GetAccumForce() << endl;
		systemeParticules[i]->IntegrateEulerWithAccum(duration);

		//on vide l'accumulateur
		systemeParticules[i]->clearAccum();
	}
}

void GameWorld::addForces()
{
	//gestion de la gravit�
	for (Particule* particule : systemeParticules)
	{
		registre.add(particule, &worldGravity);
	}
}
