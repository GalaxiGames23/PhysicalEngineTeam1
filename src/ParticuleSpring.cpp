#include "ParticuleSpring.h"

//////// Constructors ////////

ParticuleSpring::ParticuleSpring()
{
	this->k = 0;
	this->l0 = 0;

	this->v = Vector(0.0f, 0.0f, 0.0f);
	this->p2 = &Particule();
	this->isP2P = false;
	this->HarmonicInitialized = false;
}

// Constructeur ressort Particule / Particule
ParticuleSpring::ParticuleSpring(double k, double l0, Particule* p2) {
	this->k = k;
	this->l0 = l0;

	this->p2 = p2;
	this->isP2P = true;
	this->HarmonicInitialized = false;
}

// Constructeur ressort Particule / Point
ParticuleSpring::ParticuleSpring(double k, double l0, Vector v) {
	this->k = k;
	this->l0 = l0;

	this->v = v;
	this->p2 = &Particule();
	this->isP2P = false;
	this->HarmonicInitialized = false;
}


//////// Methods ////////

void ParticuleSpring::updateForce(Particule* p1, float duration)
{
	double l; // Longueur actuelle entre les deux points
	Vector direction; // Direction entre les deux points
	Vector force; // Force de ressort résultante


	if (this->isP2P) // Ressort Particule / Particule
	{
		l = p1->GetPosition().distance(this->p2->GetPosition());
		direction = Vector() - (this->p2->GetPosition() - p1->GetPosition()).normalisation();

		force = this->k * (this->l0 - l) * direction; // F = K * (l - l0)
		this->p2->addForce(Vector() - force); // Principe d'action / réaction entre 2 objets dynamiques
	}
	else // Ressort Particule / Point
	{
		l = p1->GetPosition().distance(this->v);
		direction = Vector()-(this->v - p1->GetPosition()).normalisation();

		force = this->k * (this->l0 - l) * direction;
		// Pas d'action / réaction car le point est un objet statique
	}
	p1->addForce(force);

	/*if (force != Vector(0, 0, 0) && !this->HarmonicInitialized)
	{
		p1->SetUpHarmonic();
		std::cout << "ok" << endl;
		if (this->isP2P) p2->SetUpHarmonic();
		this->HarmonicInitialized = true;
	}

	if (this->HarmonicInitialized)
	{
		
		p1->HarmonicMovementDamping(this->k,0.5 , duration);
		if (this->isP2P) p2->HarmonicMovementDamping(this->k,0.5, duration);
	}*/
}