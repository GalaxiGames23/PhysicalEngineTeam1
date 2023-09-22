#include "BouncingParticule.h"

void BouncingParticule::onCollisionDetected(vector<Particule*>& allParticles)
{
	if (nbBounce <= 0)
	{
		Particule::onCollisionDetected(allParticles);
	}
	else if (velocity.get_y() > 0)
	{
		nbBounce -= 1;
		velocity.set(velocity.get_x(), -0.8 * velocity.get_y(), velocity.get_z());
	}
}
