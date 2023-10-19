#include "GameWorld.h"

//Constructeur par défaut
GameWorld::GameWorld()
{
	registre = ParticuleForceRegistry();
	worldGravity = ParticuleGravity();
	myBlob = NULL;
	Particule* particule = new Particule(5.0f,Vector(100,100,0),Vector(0,0,0));
	systemeParticules.push_back(particule);
	ParticuleSpring* spring = new ParticuleSpring(0.5f, 10.0f, Vector(100,150,0));
	Spring* entry = new Spring();
	entry->particule1 = particule;
	entry->spring = spring;
	springList.push_back(entry);
	

}

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
		systemeParticules[i]->IntegrateEulerWithAccum(duration);
		

		//on vide l'accumulateur
		systemeParticules[i]->clearAccum();
	}
	myCam->setPosition();
}

void GameWorld::addForces()
{
	//gestion de la gravité
	for (Particule* particule : systemeParticules)
	{
		registre.add(particule, &worldGravity);
	}

	for (Spring* spring : springList)
	{
		registre.add(spring->particule1,spring->spring);
	}
}
