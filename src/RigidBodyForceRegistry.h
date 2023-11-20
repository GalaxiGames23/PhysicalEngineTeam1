#include "Rigid.h"
#include "RigidBodyForceGenerator.h"

#include <cstdlib>

class RigidBodyForceRegistry
{
	//enregistrement d'une force et de son g�n�rateur
	struct RigidBodyForceRegistration {
		Rigid* rigidBody;
		RigidBodyForceGenerator* fg;
	};

	//le type Registre est un tableau dynamique d'enregistrements
	typedef std::vector<RigidBodyForceRegistration> Registre;

public:

	Registre registre;//<<< stocke le registre

	//constructor
	RigidBodyForceRegistry();

	//Ajout dans le registre
	void add(Rigid* rigidBody, RigidBodyForceGenerator* fg);

	//Retrait du registre
	void remove(Rigid* rigidBody, RigidBodyForceGenerator* fg);

	//Supprime le registre, pas les forces ni les g�n�rateurs
	void clear();

	//Pour chauqe �l�ment du registre, appelle l'updateForce du force generator avec le corps rigide associ�
	void updateForces(float duration);
};

