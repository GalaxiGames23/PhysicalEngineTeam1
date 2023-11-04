#include "TestRegistre.h"
#include "../../src/ParticuleForceRegistry.h"
#include "../../src/Particule.h"
#include "../../src/ParticuleGravity.h"

bool testRegistreAdd() 
{
	ParticuleForceRegistry registre;
	Vector& vect = Vector(3,2,9);
	Particule &part = Particule(5,vect,vect, 1);
	ParticuleGravity gen = ParticuleGravity(vect);
	registre.add(&part, &gen);
	return part.GetMass() == registre.registre[0].particule->GetMass();
}

bool testRegistreRemove() 
{
	ParticuleForceRegistry registre;
	Vector& vect = Vector(3, 2, 9);
	Particule& part = Particule(5, vect, vect, 1);
	ParticuleGravity gen;
	registre.add(&part, &gen);
	registre.remove(&part, &gen);
	return registre.registre.size() == 0 && part.GetMass() == 5;
}

bool testRegistreClear()
{
	ParticuleForceRegistry registre;
	Vector& vect = Vector(3, 2, 9);
	Particule& part = Particule(5, vect, vect, 1);
	ParticuleGravity gen;
	registre.add(&part, &gen);
	registre.clear();
	return registre.registre.size() == 0 && part.GetMass() == 5;
}