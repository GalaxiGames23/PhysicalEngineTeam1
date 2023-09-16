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

void Input::change_angle1(bool positive)
{
	int valeur = positive ? 1 : -1;
	double last_frame = ofGetLastFrameTime();
	double time_frame = last_frame == 0 ? 0.01 : last_frame;
	current_angle1 += fmod(speed_angle * time_frame * valeur, 2 * M_PI);
}

void Input::change_angle2(bool positive)
{
	int valeur = positive ? 1 : -1;
	double last_frame = ofGetLastFrameTime();
	double time_frame = last_frame == 0 ? 0.01 : last_frame;
	current_angle2 += fmod(speed_angle * time_frame * valeur, 2 * M_PI);
}

void Input::reset()
{
	current_angle1 = 0;
	current_angle2 = 0;
	current_norm = 100;
}




