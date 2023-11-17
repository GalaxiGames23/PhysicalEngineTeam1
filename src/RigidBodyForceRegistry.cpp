#include "RigidBodyForceRegistry.h"

RigidBodyForceRegistry::RigidBodyForceRegistry()
{

}

void RigidBodyForceRegistry::add(Rigid* rigidBody, RigidBodyForceGenerator* fg)
{
	// Cr�ation de la struct particule / ParticuleForceGenerator avec les entr�es
	RigidBodyForceRegistration entry;
	entry.rigidBody = rigidBody;
	entry.fg = fg;
	// Ajout de la struct ParticuleForceRegistration
	registre.push_back(entry);
}

void RigidBodyForceRegistry::remove(Rigid* rigidBody, RigidBodyForceGenerator* fg)
{
	
	// Recherche de la struct d'entr�e dans le registre et supression
	for (auto it = registre.begin(); it != registre.end();)
	{
		printf("ERASED");
		if (it->fg == fg && it->rigidBody == rigidBody)
		{
			registre.erase(it);
			return;
		}
		else ++it;
	}
}

void RigidBodyForceRegistry::clear()
{
	// On vide le registre des forces apr�s mise � jour compl�te
	registre.clear();
}

void RigidBodyForceRegistry::updateForces(float duration)
{
	for (RigidBodyForceRegistration x : registre)
	{
		// Mise � jour de toutes les forces ajout�es au registre
		x.fg->updateForce(x.rigidBody, duration);
	}
}