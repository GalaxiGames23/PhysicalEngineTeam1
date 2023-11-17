#include "Input.h"

#include <ofAppRunner.h>
#include "Box.h"
#include "of3dUtils.h"
#include "RigidBodyForceRegistry.h"
#include "RigidBodyForce.h"

//set un vecteur avec une norme current_norm, un angle current_angle1 et un angle current_angle2 (choisi par l'utilisateur)
void Input::setInput(Vector& v) const
{
	v.set(cos(current_angle1) * cos(current_angle2) * current_norm, current_norm * sin(current_angle1), current_norm * cos(current_angle1) * sin(current_angle2));
}


//Changer la norme
void Input::changeNorm(bool positive)
{
	int valeur = positive ? 1 : -1;
	double last_frame = ofGetLastFrameTime();
	double time_frame = last_frame == 0 ? 0.01 : last_frame;
	double new_val = current_norm + (valeur * speed_norm * time_frame );
	if (new_val > 0 && new_val < max_norm)
	{
		current_norm = new_val;
	}
}

//Changer l'angle tétha
void Input::changeAngle1(int positive)
{
	double last_frame = ofGetLastFrameTime();
	double time_frame = last_frame == 0 ? 0.01 : last_frame;
	current_angle1 += fmod(speed_angle * time_frame * positive, 2 * PI);
}

//Changer l'angle phi
void Input::changeAngle2(int positive)
{
	double last_frame = ofGetLastFrameTime();
	double time_frame = last_frame == 0 ? 0.01 : last_frame;
	current_angle2 += fmod(speed_angle * time_frame * positive, 2 * PI);
}

void Input::removeInput(InputRegistre* registre, std::vector<InputRegistre*> &allInput)
{
	auto it = std::find(allInput.begin(), allInput.end(), registre);

	// Vérifiez si l'élément a été trouvé avant de le retirer
	if (it != allInput.end()) {
		allInput.erase(it); // Retirez l'élément
		delete registre->fg;
		delete registre;
	}
}

void Input::changePosition(const Vector &deltaPosition)
{
	printForcePosition = printForcePosition + deltaPosition;
}



//Effacer le vecteur
void Input::reset()
{
	current_angle1 = 0;
	current_angle2 = 0;
	current_norm = 100;
}

void Input::calculSomePoints(Vector& velocity, Vector& position, Vector & gravity, Ground &ground)
{
	double vy = velocity.get_y();
	double g =  gravity.get_y();
	double delta = vy * vy - 2 * g * (position.get_y() - ground.yCoord);
	if (delta >= 0) //Calcule du point d'impact
	{
		double t1 = (-vy - sqrt(delta)) / g;
		if (t1 > 0)
		{
			ground.impact_point.set(velocity.get_x() * t1 + position.get_x(), ground.yCoord, velocity.get_z() * t1 + position.get_z());
		}
		double t2 = (-vy + sqrt(delta)) / g;
		if (t2 > 0)
		{
			ground.impact_point.set(velocity.get_x() * t2 + position.get_x(), ground.yCoord, velocity.get_z() * t2 + position.get_z());
		}
	}

	//Calcule du maximum
	double tmax = -vy / g;
	if (tmax > 0)
	{
		max_point.set(velocity.get_x() * tmax + position.get_x(), 0.5 * g * tmax * tmax + vy * tmax + position.get_y(), velocity.get_z() * tmax + position.get_z());
	}
	else
	{
		max_point = position;
	}
}

void Input::updateFromGui(double x, double y, double z, double radius, double theta, double phi, double xm, double ym, double zm)
{
	printForcePosition.set(x, y, z);
	this->current_norm = radius;
	this->current_angle1 = theta * 2 * PI / 360;
	this->current_angle2 = phi * 2 * PI / 360;

	if (inputRigid.rb != nullptr)
		inputRigid.rb->SetCenterofMass(xm, ym, zm);
	
}

void Input::preSpawnRigid(Camera *myCam, Particule* moonParticle)
{
	if (inputRigid.rb == nullptr)
	{
		inputRigid.rb = new Box(Particule(1.0, Vector(500, 500, 0), Vector(0, 0, 0), 15), Vector(0, 0, 0), Matrix3({ 1,0,0,0,1,0,0,0,1 }), Vector(0, 0, 0), Vector(0,0,0), Vector(1, 1, 1), Vector(20, 20, 20));
		inputRigid.forces.clear();
		myCam->isActivated = true;
		myCam->setParticuleFollow(inputRigid.rb->GetCenter()->GetPosition() + Vector(0,0,-100), inputRigid.rb->GetCenter());
	}
	else
	{
		delete inputRigid.rb;
		inputRigid.rb = nullptr;
		myCam->isActivated = false;
		myCam->setParticuleFollow(moonParticle->GetPosition() + Vector(-1000, 0, 0), moonParticle);
		for (RigidBodyForce* force : inputRigid.forces) delete force;
		inputRigid.forces.clear();
	}
}


void Input::addForceToSpawningRegistry()
{
	if (inputRigid.rb != nullptr)
	{
		Vector force;
		setInput(force);
		inputRigid.forces.push_back(new RigidBodyForce(inputRigid.rb->GetCenter()->GetPosition() + printForcePosition, force));
	}
	
}

void Input::spawnRigid(std::vector<Rigid*>& rigidBodies, RigidBodyForceRegistry &registreRigids)
{
	if (inputRigid.rb != nullptr)
	{
		rigidBodies.push_back(inputRigid.rb);
		for (RigidBodyForce* force : inputRigid.forces)
			registreRigids.add(inputRigid.rb, force);

		inputRigid.rb = nullptr;
		inputRigid.forces.clear();
	}
}

void Input::draw()
{
	if (inputRigid.rb != nullptr)
	{
		ofEnableDepthTest();
		inputRigid.rb->draw();
		ofDisableDepthTest();
		ofSetColor(ofColor::white);
		Vector force;
		setInput(force);
		ofDrawArrow((inputRigid.rb->GetCenter()->GetPosition() + printForcePosition).toVec3(), (inputRigid.rb->GetCenter()->GetPosition() + printForcePosition + force).toVec3(), 2);
		ofSetColor(ofColor::black);
		for (RigidBodyForce* force : inputRigid.forces) force->draw();
		
		
	}
}




