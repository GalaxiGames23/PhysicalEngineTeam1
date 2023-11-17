#include "TestInput.h"
#include "../../src/Input.h"

Input& input = Input::getInput();

bool testReset()
{
	input.changeNorm(true);
	input.changeAngle1(true);
	input.changeAngle2(true);
	input.reset();
	Vector& v = Vector(0, 0, 0);
	input.setInput(v);
	return v.get_x() == 100 && v.get_y() == 0 && v.get_z() == 0;

}

bool testSetInput()
{
	input.reset();
	Vector& v = Vector(0, 0, 0);
	input.setInput(v);
	return v.get_x() == 100 && v.get_y() == 0 && v.get_z() == 0;
}

bool testDecreaseNorm()
{
	input.reset();
	Vector& v = Vector(0, 0, 0);
	input.changeNorm(false);
	input.setInput(v);
	bool firstTest = v.get_x() < 100;
	for (int i = 0; i < 1000; i++)
	{
		input.changeNorm(false);
	}

	input.setInput(v);
	bool secondTest = v.get_x() > 0;

	return firstTest && secondTest;
}



bool testIncreaseNorm()
{
	Vector& v = Vector(0, 0, 0);
	input.reset();
	input.changeNorm(true);
	input.changeNorm(true);
	input.setInput(v);
	bool firstTest = v.get_x() > 100;
	for (int i = 0; i < 1000; i++)
	{
		input.changeNorm(true);
	}
	input.setInput(v);
	bool secondTest = v.get_x() < 1000;
	return firstTest && secondTest;
}

bool testIncreaseAngle()
{
	input.reset();
	Vector& v = Vector(0, 0, 0);
	input.changeAngle1(1);
	input.setInput(v);

	return v.get_y() > 0;
}

bool testDecreaseAngle()
{
	input.reset();
	Vector& v = Vector(0, 0, 0);
	input.changeAngle1(-1);
	input.setInput(v);

	return v.get_y() < 0;
}