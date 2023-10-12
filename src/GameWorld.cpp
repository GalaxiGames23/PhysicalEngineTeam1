#include "GameWorld.h"

//Constructeur par défaut
/*GameWorld::GameWorld()
{
	registre = ParticuleForceRegistry();
}*/

void GameWorld::UpdateLogic(float duration) 
{

	//ajoute les forces au registre
	addForces();

	//update des forces
	registre.updateForces(duration);

	//clear du registre
	registre.clear();

	//intégration de chaque particule
	for (int i = 0; i < systemeParticules.size(); ++i)
	{
		systemeParticules[i]->IntegrateWithAccum(duration);

		//on vide l'accumulateur
		systemeParticules[i]->clearAccum();
	}
}

void GameWorld::addForces()
{
	//TODO: ajouter les forces au registre
}
