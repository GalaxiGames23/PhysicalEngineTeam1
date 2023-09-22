#include "Particule.h"
// Constructors

Particule::Particule()
{
	this->mass = 0;
	this->position = Vector();
	this->velocity = Vector();
	this->lastPosition = Vector(0, 0, 0);
	this->c = ofColor::aqua;
}

Particule::Particule(double mass, Vector position, Vector velocity)
{
	this->mass = mass;
	this->position = position;
	this->velocity = velocity;
	this->lastPosition = Vector(0, 0, 0);
	this->c = ofColor::aqua;
}

Particule::Particule(double mass, Vector position, Vector velocity, ofColor c)
{

	this->mass = mass;
	this->position = position;
	this->velocity = velocity;
	this->lastPosition = Vector(0, 0, 0);
	this->c = c;
}

Particule::Particule(double mass, Vector position, Vector velocity, ofColor c, bool isStatic)
{
	this->mass = mass;
	this->position = position;
	this->velocity = velocity;
	this->lastPosition = Vector(0, 0, 0);
	this->c = c;
	this->isStatic = isStatic;
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
	this->velocity = pow(damping, duration) * this->velocity + duration * gravity;
	this->position =  this->position + duration * this->velocity;
}

void Particule::SetFirstLastPosition(float duration) {
	this->lastPosition = this->position - duration * this->velocity;
}


void Particule::IntegrateVerlet(float duration, Vector gravity)
{
	Vector storeActualPos = this->position;
	this->position = 2 * this->position - this->lastPosition + pow(duration, 2) * gravity;
	this->lastPosition = storeActualPos;
}

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
	if (p->GetMass() < 10)
	{
		return Vector(0,0,0);
	}
	double d = p->GetPosition().distance(position);
	double G = 1;
	Vector axe = ((p->GetPosition()) - position).normalisation();
	if (d < 20)
	{
		axe = -1 * axe;
	}
	return G * p->GetMass() / (d * d) * axe;
}
