#include "ParticuleForceRegistry.h"

ParticuleForceRegistry::ParticuleForceRegistry()
{

}

void ParticuleForceRegistry::add(Particule* particule, ParticuleForceGenerator* fg)
{
	// Création de la struct particule / ParticuleForceGenerator avec les entrées
	ParticuleForceRegistration entry;
	entry.particule = particule;
	entry.fg = fg;

	// Ajout de la struct ParticuleForceRegistration
	registre.push_back(entry);
}

void ParticuleForceRegistry::remove(Particule* particule, ParticuleForceGenerator* fg)
{
	// Recherche de la struct d'entrée dans le registre et supression
	for (auto it = registre.begin(); it != registre.end();)
	{
		if (it->fg == fg && it->particule == particule)
		{
			registre.erase(it);
			return;
		}
		else ++it;
	}
}

void ParticuleForceRegistry::clear()
{
	// On vide le registre des forces après mise à jour complète
	registre.clear();
}

void ParticuleForceRegistry::updateForces(float duration)
{
	for (ParticuleForceRegistration x : registre)
	{
		// Mise à jour de toutes les forces ajoutées au registre
		x.fg->updateForce(x.particule, duration);
	}
}