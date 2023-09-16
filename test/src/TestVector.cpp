#include "TestVector.h"
#include "../../src/Vector.h"
bool testVectAddition()
{
	Vector v = Vector(40, 50, 90);
	Vector w = Vector(60, 50, 10);
	Vector x = v + w;
	return x.get_x() == 100 && x.get_y() == 100 && x.get_z() == 100;
}

bool testVectMult()
{
	Vector v = Vector(40, 50, 90);
	Vector w = Vector(2, 2, 2);
	Vector x = v * w;
	Vector y = 5 * v;
	return x.get_x() == 80 && x.get_y() == 100 && x.get_z() == 180 && y.get_x() == 200 && y.get_y() == 250 && y.get_z() == 450;
}

bool testVectScalarProd()
{
	Vector v = Vector(2, 4, 7);
	Vector w = Vector(9, 3, 9);
	
	return v.prod_scalar(w) == 93;
}

bool testVectVectProd()
{
	Vector v = Vector(2, 4, 7);
	Vector w = Vector(9, 3, 9);
	Vector x = v.prod_vector(w);
	return x.get_x() == 15 && x.get_y() == 45 && x.get_z() == -30;
}

bool testVectNorm()
{
	Vector v = Vector(2, 3, 5);
	return sqrt(38) == v.norm();
}

bool testVectNormalisation()
{
	Vector v = Vector(4, 4, 0);

	Vector w = v.normalisation();
	
	return w.norm() > 0.99999 && w.norm() < 1.00001;
}