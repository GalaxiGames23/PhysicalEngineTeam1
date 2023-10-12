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
	//on cr�e une entr�e
	ParticuleForceRegistration entry;
	entry.particule = particule;
	entry.fg = fg;

	//on trouve et supprime l'entr�e du registre
	
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