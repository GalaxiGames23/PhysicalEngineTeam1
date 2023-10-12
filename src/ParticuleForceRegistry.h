#ifndef PARTICULEFORCEREGISTRY_H
#define PARTICULEFORCEREGISTRY_H

#include "Particule.h"
#include "ParticuleForceGenerator.h"

#include <cstdlib>

//Permet de savoir quel g�n�rateur affecte quelle particule
class ParticuleForceRegistry
{
	//enregistrement d'une force et de son g�n�rateur
	struct ParticuleForceRegistration {
		Particule* particule;
		ParticuleForceGenerator* fg;
	};

	//le type Registre est un tableau dynamique d'enregistrements
	typedef std::vector<ParticuleForceRegistration> Registre;

public:

	Registre registre;//<<< stocke le registre

	//constructor
	ParticuleForceRegistry();

	//Ajout dans le registre
	void add(Particule* particule, ParticuleForceGenerator* fg);

	//Retrait du registre
	void remove(Particule* particule, ParticuleForceGenerator* fg);

	//Supprime le registre, pas les forces ni les g�n�rateurs
	void clear();

	//Pour chauqe �l�ment du registre, appelle l'updateForce du force generator avec la particule associ�e
	void updateForces(float duration);
};

#endif