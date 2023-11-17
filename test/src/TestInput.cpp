#include "TestInput.h"
#include "../../src/Input.h"

Input& input = Input::getInput();

bool testReset()
{
	input.change_norm(true);
	input.change_angle1(true);
	input.change_angle2(true);
	input.reset();
	Vector& v = Vector(0, 0, 0);
	input.set_Input(v);
	return v.get_x() == 100 && v.get_y() == 0 && v.get_z() == 0;

}

bool testSetInput()
{
	input.reset();
	Vector& v = Vector(0, 0, 0);
	input.set_Input(v);
	return v.get_x() == 100 && v.get_y() == 0 && v.get_z() == 0;
}

bool testDecreaseNorm()
{
	input.reset();
	Vector& v = Vector(0, 0, 0);
	input.change_norm(false);
	input.set_Input(v);
	bool firstTest = v.get_x() < 100;
	for (int i = 0; i < 1000; i++)
	{
		input.change_norm(false);
	}

	input.set_Input(v);
	bool secondTest = v.get_x() > 0;

	return firstTest && secondTest;
}



bool testIncreaseNorm()
{
	Vector& v = Vector(0, 0, 0);
	input.reset();
	input.change_norm(true);
	input.change_norm(true);
	input.set_Input(v);
	bool firstTest = v.get_x() > 100;
	for (int i = 0; i < 1000; i++)
	{
		input.change_norm(true);
	}
	input.set_Input(v);
	bool secondTest = v.get_x() < 1000;
	return firstTest && secondTest;
}

bool testIncreaseAngle()
{
	input.reset();
	Vector& v = Vector(0, 0, 0);
	input.change_angle1(1);
	input.set_Input(v);

	return v.get_y() > 0;
}

bool testDecreaseAngle()
{
	input.reset();
	Vector& v = Vector(0, 0, 0);
	input.change_angle1(-1);
	input.set_Input(v);

	return v.get_y() < 0;
}