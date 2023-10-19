#include "Particule.h"

//////// Phase 1 ////////


// Constructor Particule
Particule::Particule()
{
	this->InversMass = 0;
	this->position = Vector();
	this->velocity = Vector();
	this->AccumForce = Vector(0, 0, 0);

	this->lastPosition = Vector(0, 0, 0);
	this->e = 1;
	isPresetVerlet = false;
}
//Constructor Particule with parameters mass, position and velocity
Particule::Particule(double mass, Vector position, Vector velocity, double e)
{
	this->InversMass = 1/mass;
	this->position = position;
	this->velocity = velocity;
	this->AccumForce = Vector(0, 0, 0);

	this->lastPosition = Vector(0, 0, 0);
	this->e = e;
	isPresetVerlet = false;
}


// Operator << with particule (ofstring)
ostream& operator<< (ostream& out, const Particule& particule)
{
	out << "--- Particule ---\nMass : " << 1/particule.InversMass << "\nTime : " << particule.position << "\n Distance : " << particule.velocity << "\n-----------------";
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


//////// Phase 2 ////////

void Particule::addForce(const Vector& force)
{
	AccumForce = AccumForce + force;
}

void Particule::clearAccum()
{
	AccumForce = Vector(0, 0, 0);
}

// Phase 2 : Euler integration with AccumForces
void Particule::IntegrateEulerWithAccum(float duration)
{
	//Set the particule's velocity using Euler integration with AccumForces
	this->velocity = this->velocity + duration * this->AccumForce;

	//Set the particule's position using Euler integration
	this->position = this->position + duration * this->velocity;
}



Vector Particule::GetDirection()
{
		return this->velocity.normalisation();
}

void Particule::HarmonicMovement(double K, float duration) //////// To think about (add to prior integrators)
{
	this->time += duration;
	double w0 = sqrt(K * this->InversMass);
	this->position = Vector() - pow(w0, 2) * cos(w0 * this->time) * this->position.normalisation() + this->position;
}

void Particule::HarmonicMovementDamping(double K, double c, float duration) //////// To think about (add to prior integrators)
{
	this->time += duration;
	double w0 = sqrt(K * this->InversMass);
	double E = c / (2 * sqrt(1/this->InversMass * K));

	double wd = w0 * sqrt(1 - pow(E, 2));
	Vector K1 = this->position0; ////////////// Set position0 & velocity0 at first exe
	Vector K2 = w0 * this->position0 + this->velocity0;

	this->position = (K1 * cos(wd * time) + K2 * sin(wd * time)) * exp(-E * w0 * time) + this->position;
}

double Particule::distanceParticules(Particule* p)
{
	return this->position.distance(p->position);
}

void Particule::AddVelocityOnColliding(Particule* p)
{
	Vector n = (this->position - p->position).normalisation();
	double d = this->distanceParticules(p);

	double num = (this->e + 1) * (this->velocity - p->velocity).prod_scalar(n);
	double denom = (this->InversMass + p->InversMass) * n.square_norm();
	double K = 1 / denom * num;

	this->velocity = this->velocity - this->InversMass * K * n;
	this->position = this->position + p->InversMass / (this->InversMass + p->InversMass) * d * n;
}

void Particule::AddVelocityOnColliding(double groundY)
{
	Vector n = Vector(0, -1, 0);
	double d = abs(this->position.get_y() - groundY);

	double num = (this->e + 1) * this->velocity.prod_scalar(n);
	double denom = this->InversMass * n.square_norm();
	double K = 1 / denom * num;

	this->velocity = this->velocity - this->InversMass * K * n;
	this->position = this->position + d * n;
}