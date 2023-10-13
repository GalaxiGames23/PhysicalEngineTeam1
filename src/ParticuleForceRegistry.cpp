#include "ParticuleForceRegistry.h"

ParticuleForceRegistry::ParticuleForceRegistry()
{

}

void ParticuleForceRegistry::add(Particule* particule, ParticuleForceGenerator* fg)
{
	//on cr�e une entr�e
	ParticuleForceRegistration entry;
	entry.particule = particule;
	entry.fg = fg;

	//on ajoute l'entr�e 
	registre.push_back(entry);
}

void ParticuleForceRegistry::remove(Particule* particule, ParticuleForceGenerator* fg)
{
	//on trouve l'entr�e dans le registre et on la supprime
	for (auto it = registre.begin(); it != registre.end();)
	{
		if (it->fg == fg && it->particule == particule)
		{
			registre.erase(it);
			return;
		}
		else
		{
			++it;
		}
	}
}

void ParticuleForceRegistry::clear()
{
	registre.clear();
}

void ParticuleForceRegistry::updateForces(float duration)
{
	for (ParticuleForceRegistration x : registre)
	{
		x.fg->updateForce(x.particule, duration);
	}
}