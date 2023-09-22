#include "Input.h"

#include <ofAppRunner.h>




void Input::set_Input(Vector& v) const
{
	v.set(cos(current_angle1) * cos(current_angle2) * current_norm, current_norm * sin(current_angle1), current_norm * cos(current_angle1) * sin(current_angle2));

}



void Input::change_norm(bool positive)
{
	int valeur = positive ? 1 : -1;
	double last_frame = ofGetLastFrameTime();
	double time_frame = last_frame == 0 ? 0.01 : last_frame;
	double new_val = current_norm + (valeur * speed_norm *time_frame );
	if (new_val > 0 && new_val < max_norm)
	{
		current_norm = new_val;
	}
}

void Input::change_angle1(int positive)
{
	double last_frame = ofGetLastFrameTime();
	double time_frame = last_frame == 0 ? 0.01 : last_frame;
	current_angle1 += fmod(speed_angle * time_frame * positive, 2 * M_PI);
}

void Input::change_angle2(int positive)
{
	double last_frame = ofGetLastFrameTime();
	double time_frame = last_frame == 0 ? 0.01 : last_frame;
	current_angle2 += fmod(speed_angle * time_frame * positive, 2 * M_PI);
}

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




