#include "RigidBodyForce.h"
#include "of3dUtils.h"

RigidBodyForce::RigidBodyForce()
{
	this->pointAppli = Vector();
	this->force = Vector();
}

RigidBodyForce::RigidBodyForce(Vector pointAppli, Vector force)
{
	this->pointAppli = pointAppli;
	this->force = force;
}

void RigidBodyForce::updateForce(Rigid* rigidBody, float duration)
{
	// Apply Torque
	Vector l = pointAppli - rigidBody->GetCenter()->GetPosition();
	Vector appliedTorque = l.prod_vector(this->force);
	rigidBody->AddTorque(appliedTorque);

	// Apply Linear Force
	rigidBody->AddToAccumCenter(this->force * (1.0f / duration));
}

void RigidBodyForce::draw()
{
	ofDrawArrow(pointAppli.toVec3(), (pointAppli + force * 0.1).toVec3(), 2);
}
