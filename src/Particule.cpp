#include "Particule.h"

// Constructor Particule
Particule::Particule()
{
	this->mass = 0;
	this->position = Vector();
	this->velocity = Vector();
	this->c = ofColor::aqua;

	this->lastPosition = Vector(0, 0, 0);
	isPresetVerlet = false;
}
//Constructor Particule with parameters mass, position and velocity
Particule::Particule(double mass, Vector position, Vector velocity)
{
	this->mass = mass;
	this->position = position;
	this->velocity = velocity;
	this->c = ofColor::aqua;

	this->lastPosition = Vector(0, 0, 0);
	isPresetVerlet = false;
}
//Constructor Particule with parameters mass, position and velocity and color
Particule::Particule(double mass, Vector position, Vector velocity, ofColor c)
{

	this->mass = mass; //initialize mass of particul
	this->position = position; //initialize position of particule
	this->velocity = velocity; // initialize type object of vector - particule's speed
	this->c = c; //type ofColor for particule's color

	//initialize lastPosition to 0
	this->lastPosition = Vector(0, 0, 0);
	//Initialize "isPresetVerlet" to "false"
	isPresetVerlet = false;
}

// if a particle is static (exemple with moon)
Particule::Particule(double mass, Vector position, Vector velocity, ofColor c, bool isStatic)
{
	this->mass = mass; //initialize mass of particul
	this->position = position; //initialize position of particule
	this->velocity = velocity; // initialize type object of vector - particule's speed
	this->c = c; //type ofColor for particule's color

	//initialize lastPosition to 0
	this->lastPosition = Vector(0, 0, 0);
	//Initialize "isPresetVerlet" to "false"
	isPresetVerlet = false;
	isStatic = isStatic;
}

// Operator << with particule (ofstring)
ostream& operator<< (ostream& out, const Particule& particule)
{
	out << "--- Particule ---\nMass : " << particule.mass << "\nTime : " << particule.position << "\n Distance : " << particule.velocity << "\n-----------------";
	return out;
}

// Integrators

//Euler Integration
void Particule::IntegrateEuler(float duration, Vector gravity, float damping)
{
	if (this->isPresetVerlet) // Calcul of last position if change of integration mode
	{
		//Calculate the velocity using the Verlet integration formule
		this->velocity = 1 / duration * (this->position - this->lastPosition);
		isPresetVerlet = false; //Set the integration mode to Euler
	}
	//Set the particule's velocity using Euler integration with damping and gravity
	this->velocity = pow(damping, duration) * this->velocity + duration * gravity;
	//Set the particule's position using Euler integration
	this->position =  this->position + duration * this->velocity;
}

//Verlet Integration
void Particule::IntegrateVerlet(float duration, Vector gravity, float damping)
{
	if (!this->isPresetVerlet) // Calcul of last position if first call or change of integration mode
	{
		Vector tempV = this->velocity - duration * gravity;
		this->lastPosition = this->position - duration * tempV;
		isPresetVerlet = true;
	}
	Vector storeActualPos = this->position;
	this->position =  2 *  this->position - this->lastPosition + duration * duration * gravity;
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

//Calcul acceleration caused by the gravitation force with particle p
Vector Particule::calculGravitationAccelerationWith(Particule* p)
{
	if (p->GetMass() < 10) // mass to small to consider object
	{
		return Vector(0,0,0);
	}
	double d = p->GetPosition().distance(position);
	double G = 1;
	Vector axe = ((p->GetPosition()) - position).normalisation();
	if (d < 20) //if distance is to small
	{
		axe = -1 * axe; //inverse the force
	}
	return G * p->GetMass() / (d * d) * axe;
}

////////Phase 2/////

void Particule::addForce(const Vector& force)
{
	AccumForce = AccumForce + force;
}

void Particule::clearAccum()
{
	AccumForce = Vector(0, 0, 0);
}

//Phase 2 integration
void Particule::IntegrateWithAccum(float duration)
{
	//Set the particule's velocity using Euler integration with AccumForces
	this->velocity = this->velocity + duration * this->AccumForce;
	//Set the particule's position using Euler integration
	this->position = this->position + duration * this->velocity;
}
