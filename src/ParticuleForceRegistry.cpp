#include "ParticuleForceRegistry.h"

ParticuleForceRegistry::ParticuleForceRegistry()
{

}

void ParticuleForceRegistry::add(Particule* particule, ParticuleForceGenerator* fg)
{
	//on crée une entrée
	ParticuleForceRegistration entry;
	entry.particule = particule;
	entry.fg = fg;

	//on ajoute l'entrée 
	registre.push_back(entry);
}

void ParticuleForceRegistry::remove(Particule* particule, ParticuleForceGenerator* fg)
{
	//on crée une entrée
	ParticuleForceRegistration entry;
	entry.particule = particule;
	entry.fg = fg;

	//on trouve et supprime l'entrée du registre
	
}

void ParticuleForceRegistry::clear()
{

}

void ParticuleForceRegistry::updateForces(float duration)
{
	for (ParticuleForceRegistration x : registre)
	{
		x.fg->updateForce(x.particule, duration);
	}
}