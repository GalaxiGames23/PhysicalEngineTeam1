#include "TestQuaternion.h"
#include "../../src/Quaternion.h"
#include "../../src/Matrix3.h"
#include "../../src/Vector.h"
bool testQuaternionAddition()
{
	Quaternion q1 = Quaternion(1, Vector(1, 4, 5));
	Quaternion q2 = Quaternion(2, Vector(4, 2, 3));
	Quaternion qExpected = Quaternion(3, Vector(5, 6, 8));
	return qExpected == q1 + q2;
}

bool testQuaternionSub()
{
	Quaternion q1 = Quaternion(2, Vector(4, 1, 2));
	Quaternion q2 = Quaternion(3, Vector(5,2,4));
	Quaternion qExpected = Quaternion(-1, Vector(-1,-1,-2));
	return qExpected == (q1 - q2);
}

bool testQuaternionMult()
{
	Quaternion q1 = Quaternion(3, Vector(2, 4, 1));
	Quaternion q2 = Quaternion(4, Vector(3,5,2));
	Quaternion qExpected = Quaternion(-16, Vector(20,30,8));
	return qExpected == (q1 * q2);
}


bool testQuaternionNorm()
{
	Quaternion q1 = Quaternion(4, Vector(4, 2, 0));
	return 6 == (q1.Norm());
}

bool testQuaternionScalarProd()
{
	Quaternion q1 = Quaternion(3, Vector(2,4,1));
	Quaternion q2 = Quaternion(1, Vector(3,5,2));
	return 31 == (q1.ScalarProduct( q2));
}

bool testQuaternionNegation()
{
	Vector v = Vector(1, 4, 5);
	Quaternion q = Quaternion(1, v);
	q = q.Negation();
	Vector result = q.GetV();
	return result.get_x() == -1 && result.get_y() == -4 && result.get_z() == -5 && q.GetW() == -1;
}

bool testQuaternionConjugate()
{
	Vector v = Vector(1, 4, 5);
	Quaternion q = Quaternion(1, v);
	q = q.Conjugated();
	Vector result = q.GetV();
	return result.get_x() == -1 && result.get_y() == -4 && result.get_z() == -5 && q.GetW() == 1;
}

bool testQuaternionInvers()
{
	Vector v = Vector(10, 10, 10);
	Quaternion q = Quaternion(10, v);
	Quaternion qExpected = Quaternion(0.025, Vector(-0.025, -0.025, -0.025));
	return qExpected == q.Invers();
}

bool testQuaternionDiff() 
{
	Quaternion q1 = Quaternion(3, Vector(2, 4, 1));
	Quaternion q2 = Quaternion(1, Vector(3, 5, 2));
	
	return q1.Difference(q2) == Quaternion(31, Vector(10, 10, 3));
}

bool testQuaternionConversion()
{
	Quaternion q1 = Quaternion(0.8, Vector(0.2, 0.2, 0.6));
	Matrix3 m = q1.ToMatrix();
	Matrix3 mExpected = Matrix3({ 0.2,-0.88,0.56,1.04,0.2,-0.08,-0.08,0.56,0.84 });
	return mExpected == m;
}
