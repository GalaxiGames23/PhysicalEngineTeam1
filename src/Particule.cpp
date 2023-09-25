#include "Particule.h"
// Constructors

Particule::Particule()
{
	this->mass = 0;
	this->position = Vector();
	this->velocity = Vector();
	this->c = ofColor::aqua;

	this->lastPosition = Vector(0, 0, 0);
	isPresetVerlet = false;
}

Particule::Particule(double mass, Vector position, Vector velocity)
{
	this->mass = mass;
	this->position = position;
	this->velocity = velocity;
	this->c = ofColor::aqua;

	this->lastPosition = Vector(0, 0, 0);
	isPresetVerlet = false;
}

Particule::Particule(double mass, Vector position, Vector velocity, ofColor c)
{

	this->mass = mass;
	this->position = position;
	this->velocity = velocity;
	this->c = c;

	this->lastPosition = Vector(0, 0, 0);
	isPresetVerlet = false;
}

// ToString
ostream& operator<< (ostream& out, const Particule& particule)
{
	out << "--- Particule ---\nMass : " << particule.mass << "\nTime : " << particule.position << "\n Distance : " << particule.velocity << "\n-----------------";
	return out;
}

// Integrators
void Particule::IntegrateEuler(float duration, Vector gravity, float damping)
{
	if (this->isPresetVerlet) // Calcul of last position if change of integration mode
	{
		this->velocity = 1 / duration * (this->position - this->lastPosition);
		isPresetVerlet = false;
	}
	this->velocity = pow(damping, duration) * this->velocity + duration * gravity;
	this->position =  this->position + duration * this->velocity;
}

void Particule::IntegrateVerlet(float duration, Vector gravity)
{
	if (!this->isPresetVerlet) // Calcul of last position if first call or change of integration mode
	{
		this->lastPosition = this->position - duration * this->velocity;
		isPresetVerlet = true;
	}
	Vector storeActualPos = this->position;
	this->position = 2 * this->position - this->lastPosition + pow(duration, 2) * gravity;
	this->lastPosition = storeActualPos;
}


// Manage collisions
void Particule::onCollisionDetected(vector<Particule*>& allParticles)
{
	auto it = std::find(allParticles.begin(), allParticles.end(), this);
	if (it != allParticles.end()) {
		allParticles.erase(it);
		delete(this);
	}
	
}

Vector Particule::calculGravitationAccelerationWith(Particule* p)
{
	
	double d = p->GetPosition().distance(position);
	double G = 0.5;
	Vector axe = ((p->GetPosition()) - position).normalisation();
	if (d < 20)
	{
		axe = -1 * axe;
	}
	return G * p->GetMass() / (d * d) * axe;
}
