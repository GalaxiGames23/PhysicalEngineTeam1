#include "ParticuleForceRegistry.h"

ParticuleForceRegistry::ParticuleForceRegistry()
{

}

void ParticuleForceRegistry::add(Particule* particule, ParticuleForceGenerator* fg)
{
	// Cr�ation de la struct particule / ParticuleForceGenerator avec les entr�es
	ParticuleForceRegistration entry;
	entry.particule = particule;
	entry.fg = fg;

	// Ajout de la struct ParticuleForceRegistration
	registre.push_back(entry);
}

void ParticuleForceRegistry::remove(Particule* particule, ParticuleForceGenerator* fg)
{
	// Recherche de la struct d'entr�e dans le registre et supression
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
	// On vide le registre des forces apr�s mise � jour compl�te
	registre.clear();
}

void ParticuleForceRegistry::updateForces(float duration)
{
	for (ParticuleForceRegistration x : registre)
	{
		// Mise � jour de toutes les forces ajout�es au registre
		x.fg->updateForce(x.particule, duration);
	}
}