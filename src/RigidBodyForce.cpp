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
	Vector appliedLinearForce = Vector();
	if (rigidBody->GetCenterofMass() == Vector())
	{
		Vector axeProj = rigidBody->GetCenter()->GetPosition() - pointAppli;
		appliedLinearForce = this->force.projection(axeProj);
	}
	else
	{
		Vector newCenterOfMass = rigidBody->GetOrientationMat() * rigidBody->GetCenterofMass();
		appliedLinearForce = this->force.projection(newCenterOfMass);
		// newCenterOfMass = Axe de projection puisque coordonnées de translation du centre de rotation
	}
	rigidBody->AddToAccumCenter(appliedLinearForce);
}

void RigidBodyForce::draw()
{
	ofDrawArrow(pointAppli.toVec3(), (pointAppli + force * 0.05).toVec3(), 10);
}
