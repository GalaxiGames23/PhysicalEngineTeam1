#include "RigidBodyForce.h"
#include "of3dUtils.h"

RigidBodyForce::RigidBodyForce()
{
	this->pointAppli = Vector();
	this->force = Vector();
}

RigidBodyForce::RigidBodyForce(Vector pointAppli, Vector force, double effectiveTime)
{
	this->pointAppli = pointAppli;
	this->force = force;
	this->effectiveTime = effectiveTime;
}

void RigidBodyForce::updateForce(Rigid* rigidBody, float duration)
{
	if (effectiveTime > -0.5 && effectiveTime <= 0)
	{
		return;
	}

	effectiveTime -= duration;
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
	ofDrawArrow(pointAppli.toVec3(), (pointAppli + force).toVec3(), 10);
}
