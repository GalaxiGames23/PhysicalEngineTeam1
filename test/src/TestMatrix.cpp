#include "TestMatrix.h"
#include "../../src/Matrix3.h"
#include "../../src/Matrix4.h"
#include "../../src/Quaternion.h"
#include <cstdio>
bool testMatrixAddition()
{
	float array[9] = { 1, 2, 3, 4, 5, 6 ,7 , 8, 9 };

	float array2[9] = { 9,8,7,6,5,4,3,2,1 };
	Matrix3 m1 = Matrix3(array);
	Matrix3 m2 = Matrix3(array2);
	Matrix3 mtest1 = m1 + m2;
	bool test1 = true;
	for (int i = 0; i < 9; i++)
	{
		if (mtest1.GetCoefficient(i) != 10)
		{
			test1 = false;
			
		}

	}

	float array3[16] = { 1, 2, 3, 4, 5, 6 ,7 , 8, 9,5,5,5,5,5,5,5 };

	float array4[16] = { 9,8,7,6,5,4,3,2,1,5,5,5,5,5,5,5 };
	
	Matrix4 m3 = Matrix4(array3);
	Matrix4 m4 = Matrix4(array4);
	Matrix4 mtest2 = m3 + m4;
	bool test2 = true;
	for (int i = 0; i < 16; i++)
	{
		if (mtest2.GetCoefficient(i) != 10)
		{
			
			test2 = false;
		}

	}
	return test1 && test2;
}

bool testMatrixSub()
{

	float array[9] = { 9,8,7,6,5,4,3,2,1 };
	Matrix3 m1 = Matrix3(array);
	Matrix3 m2 = Matrix3(array);
	Matrix3 mtest1 = m1 - m2;
	bool test1 = true;
	for (int i = 0; i < 9; i++)
	{
		if (mtest1.GetCoefficient(i) != 0)
		{
			test1 = false;
		}

	}

	float array2[16] = { 9,8,7,6,5,4,3,2,1,8,6,9,7,6,6,5 };
	Matrix4 m3 = Matrix4(array);
	Matrix4 m4 = Matrix4(array);
	Matrix4 mtest2 = m3 - m4;
	bool test2 = true;
	for (int i = 0; i < 16; i++)
	{
		if (mtest2.GetCoefficient(i) != 0)
		{
			test2 = false;
		}
	}

	return test1 && test2;
}

bool testMatrixMult()
{
	float array[9] = { 2,1,1,0,1,0,1,1,2 };
	float array2[9] = { 1,0,1,0,2,0,1,0,1 };
	Matrix3 m1 = Matrix3(array);
	Matrix3 m2 = Matrix3(array2);
	Matrix3 mtest1 = m1 * m2;
	
	Matrix3 mExpected1 = Matrix3({3,2,3,0,2,0,3,2,3});

	Matrix4 m3 = Matrix4({1,2,3,4,1,1,0,4,1,2,4,2,0,0,2,1});
	Matrix4 m4 = Matrix4({5,0,0,2,4,5,6,3,1,2,3,0,2,5,3,1});

	Matrix4 mExpected2 = Matrix4({ 24,36,33,12,17,25,18,9,21,28,30,10,4,9,9,1 });
	
	Matrix4 mtest2 = m3 * m4;
	
	return mtest1 == mExpected1 && mExpected2 == mtest2;
}

bool testMatrixTransposed()
{
	Matrix3 m1 = Matrix3({1,5,9,4,8,6,2,3,4});
	Matrix3 mExpected = Matrix3({ 1,4,2,5,8,3,9,6,4 });

	Matrix4 m2 = Matrix4({1,5,9,4,4,8,6,2,2,3,4,1,3,1,2,7 });
	Matrix4 mExpected2 = Matrix4({ 1,4,2,3,5,8,3,1,9,6,4,2,4,2,1,7 });
	return m1.Transposed() ==mExpected && m2.Transposed() == mExpected2;
}

bool testMatrixInverse()
{
	Matrix3 m1 = Matrix3({ 1,2,-1,-2,0,1,1,-1,0 });
	Matrix3 mExpected = Matrix3({ 1,1,2,1,1,1,2,3,4 });

	Matrix4 m2 = Matrix4({ 1,1,1,0,0,3,1,2,2,3,1,0,1,0,2,1 });
	Matrix4 mExpected2 = Matrix4({ -3, -0.5, 1.5, 1, 1, 0.25, -0.25, -0.5, 3, 0.25, -1.25, -0.5, -3, 0, 1, 1 });
	return m1.Invers() == mExpected && m2.Invers() == mExpected2;
}

bool testMatrixDeterminant()
{
	Matrix3 m1 = Matrix3({ 4,0,6,1,2,5,1,6,9 });

	Matrix4 m2 = Matrix4({ 4,0,2,3,4,5,2,6,5,1,2,3,1,2,0,1});
	return m1.Determinant() == -24 && m2.Determinant() == -4;
}

bool testMatrixAdjacent()
{

	Matrix3 m1 = Matrix3({ 1,2,3,0,1,4,5,6,0 });
	Matrix3 mExpected = Matrix3({ -24,20,-5,18,-15,4,5,-4,1 });

	Matrix4 m2 = Matrix4({ 1,1,1,0,0,3,1,2,2,3,1,0,1,0,2,1 });
	Matrix4 mExpected2 = Matrix4({ 12,-4,-12,12,2,-1,-1,0,-6,1,5,-4,-4,2,2,-4});
	return m1.Adjacent() == mExpected && m2.Adjacent() == mExpected2;
}

bool testMatrixConversion()
{
	Matrix3 m1 = Matrix3({ 0.28,-0.96,0,0.96,0.28,0,0,0,1 });
	Quaternion q = m1.toQuaternion();
	Vector v = q.GetV();
	return q.GetW() < 0.80001 && q.GetW() >0.79999 && v.get_x() == 0 && v.get_y() == 0 && v.get_z() > 0.599999 && v.get_z() < 0.600001;
}

