#include "Matrix3.h"
#include "Quaternion.h"
#include <cstdio>
Matrix3::Matrix3() 
{
	//Matrice identité
	coefficients.fill(0);
	coefficients[0] = 1;
	coefficients[4] = 1;
	coefficients[8] = 1;
}

Matrix3::Matrix3(const Matrix3& m) 
{
	for (int i = 0; i < 9; ++i)
	{
		this->coefficients[i] = m.coefficients[i];
	}
}

Matrix3::Matrix3(std::array<float, 9> coefs)
{
	for (int i = 0; i < 9; ++i)
	{
		this->coefficients[i] = coefs[i];
	}
}

Matrix3::Matrix3(float coefs[9])
{
	for (int i = 0; i < 9; ++i)
	{
		this->coefficients[i] = coefs[i];

	}
}

Matrix3 Matrix3::operator*(const Matrix3& m) 
{
	Matrix3 result = Matrix3();

	result.coefficients[0] = this->coefficients[0] * m.coefficients[0] + this->coefficients[1] * m.coefficients[3] + this->coefficients[2] * m.coefficients[6];
	result.coefficients[1] = this->coefficients[0] * m.coefficients[1] + this->coefficients[1] * m.coefficients[4] + this->coefficients[2] * m.coefficients[7];
	result.coefficients[2] = this->coefficients[0] * m.coefficients[2] + this->coefficients[1] * m.coefficients[5] + this->coefficients[2] * m.coefficients[8];
	result.coefficients[3] = this->coefficients[3] * m.coefficients[0] + this->coefficients[4] * m.coefficients[3] + this->coefficients[5] * m.coefficients[6];
	result.coefficients[4] = this->coefficients[3] * m.coefficients[1] + this->coefficients[4] * m.coefficients[4] + this->coefficients[5] * m.coefficients[7];
	result.coefficients[5] = this->coefficients[3] * m.coefficients[2] + this->coefficients[4] * m.coefficients[5] + this->coefficients[5] * m.coefficients[8];
	result.coefficients[6] = this->coefficients[6] * m.coefficients[0] + this->coefficients[7] * m.coefficients[3] + this->coefficients[8] * m.coefficients[6];
	result.coefficients[7] = this->coefficients[6] * m.coefficients[1] + this->coefficients[7] * m.coefficients[4] + this->coefficients[8] * m.coefficients[7];
	result.coefficients[8] = this->coefficients[6] * m.coefficients[2] + this->coefficients[7] * m.coefficients[5] + this->coefficients[8] * m.coefficients[8];

	return result;
}

Matrix3 Matrix3::operator*(const float& a)
{
	Matrix3 result = Matrix3();

	for (int i = 0; i < 9; ++i)
	{
		result.coefficients[i] = this->coefficients[i] * a;
	}

	return result;
}

Vector Matrix3::operator*(const Vector& v)
{
	double x = v.get_x() * this->coefficients[0] + v.get_y() * this->coefficients[1] + v.get_z() * this->coefficients[2];
	double y = v.get_x() * this->coefficients[3] + v.get_y() * this->coefficients[4] + v.get_z() * this->coefficients[5];
	double z = v.get_x() * this->coefficients[6] + v.get_y() * this->coefficients[7] + v.get_z() * this->coefficients[8];

	return Vector(x, y, z);
}


Matrix3 Matrix3::operator+(const Matrix3& m) 
{
	Matrix3 result = Matrix3();

	for (int i = 0; i < 9; ++i)
	{
		result.coefficients[i] = this->coefficients[i] + m.coefficients[i];
	}

	return result;
}

Matrix3 Matrix3::operator-(const Matrix3& m) 
{
	Matrix3 result = Matrix3();

	for (int i = 0; i < 9; ++i)
	{
		result.coefficients[i] = this->coefficients[i] - m.coefficients[i];
	}

	return result;
}

Matrix3& Matrix3::operator=(const Matrix3& m)
{
	for (int i = 0; i < 9; ++i)
	{
		this->coefficients[i] = m.coefficients[i];
	}

	return *this;
}

bool Matrix3::operator==(const Matrix3& m) 
{
	bool toReturn = true;

	for (int i = 0; i < 9; ++i)
	{
		if (this->coefficients[i] != m.coefficients[i]) 
		{
			toReturn = false;
		}
	}

	return toReturn;
}

bool Matrix3::operator!=(const Matrix3& m) 
{
	bool toReturn = true;

	for (int i = 0; i < 9; ++i)
	{
		if (this->coefficients[i] != m.coefficients[i])
		{
			toReturn = false;
		}
	}

	return !toReturn;
}

void Matrix3::SetCoefficients(std::array<float, 9> coefs)
{
	for (int i = 0; i < 9; ++i)
	{
		this->coefficients[i] = coefs[i];
	}
}

void Matrix3::SetCoefficient(int i, float coef)
{
	if (i < 9 && i >= 0)
	{
		this->coefficients[i] = coef;
	}
}

void Matrix3::SetCoefficient(int row, int column, float coef) 
{
	if (row < 1 || row>3 || column < 1 || column>3) return;
	//position dans l'array
	int i = (row-1) * 3 + (column-1);

	this->coefficients[i] = coef;
}

float Matrix3::GetCoefficient(int i) const
{
	if (i < 9 && i>=0)
	{
		return this->coefficients[i];
	}
	else
	{
		return 0.0f;
	}
}

float Matrix3::GetCoefficient(int row, int column) const
{
	if (row < 1 || row>3 || column < 1 || column>3) return 0;
	//position dans l'array
	int i = (row - 1) * 3 + (column - 1);

	return this->coefficients[i];
}

Matrix3 Matrix3::Invers() 
{
	//A-1 = (1 / det(A)) * adj(A)T
	float det = this->Determinant();

	//non inversible, cas limite qui devra être testé 
	if (det == 0) return Matrix3();

	float invDet = 1 / det;
	Matrix3 adj = this->Adjacent().Transposed();

	Matrix3 result = adj * invDet;

	return result;
}

Matrix3 Matrix3::Transposed() 
{
	Matrix3 result = Matrix3();

	result.coefficients[0] = this->coefficients[0];
	result.coefficients[1] = this->coefficients[3];
	result.coefficients[2] = this->coefficients[6];
	result.coefficients[3] = this->coefficients[1];
	result.coefficients[4] = this->coefficients[4];
	result.coefficients[5] = this->coefficients[7];
	result.coefficients[6] = this->coefficients[2];
	result.coefficients[7] = this->coefficients[5];
	result.coefficients[8] = this->coefficients[8];

	return result;
}

float Matrix3::Determinant()
{
	//règle de sarrus: aei + bfg + cdh - ceg - bdi - afh
	float aei = this->coefficients[0] * this->coefficients[4] * this->coefficients[8];
	float bfg = this->coefficients[1] * this->coefficients[5] * this->coefficients[6];
	float cdh = this->coefficients[2] * this->coefficients[3] * this->coefficients[7];
	float ceg = this->coefficients[2] * this->coefficients[4] * this->coefficients[6];
	float bdi = this->coefficients[1] * this->coefficients[3] * this->coefficients[8];
	float afh = this->coefficients[0] * this->coefficients[5] * this->coefficients[7];

	return aei + bfg + cdh - ceg - bdi - afh;
}

Matrix3 Matrix3::Adjacent()
{
	Matrix3 result = Matrix3();

	/*
	adj(A)T = |  (ei - fh)  -(bi - ch)  (bf - ce) |
            | -(di - fg)   (ai - ci) -(af - cd) |
            |  (dh - eg)  -(ah - bg)  (ae - bd) |
	*/

	//la transposée est faite directement dans ce calcul
	result.coefficients[0] =  (this->coefficients[4] * this->coefficients[8] - this->coefficients[5] * this->coefficients[7]);
	result.coefficients[3] = -(this->coefficients[1] * this->coefficients[8] - this->coefficients[2] * this->coefficients[7]);
	result.coefficients[6] =  (this->coefficients[1] * this->coefficients[5] - this->coefficients[2] * this->coefficients[4]);
	result.coefficients[1] = -(this->coefficients[2] * this->coefficients[8] - this->coefficients[5] * this->coefficients[6]);
	result.coefficients[4] =  (this->coefficients[0] * this->coefficients[8] - this->coefficients[2] * this->coefficients[6]);
	result.coefficients[7] = -(this->coefficients[0] * this->coefficients[5] - this->coefficients[2] * this->coefficients[3]);
	result.coefficients[2] =  (this->coefficients[3] * this->coefficients[7] - this->coefficients[4] * this->coefficients[6]);
	result.coefficients[5] = -(this->coefficients[0] * this->coefficients[7] - this->coefficients[1] * this->coefficients[6]);
	result.coefficients[8] =  (this->coefficients[0] * this->coefficients[4] - this->coefficients[1] * this->coefficients[3]);

	//return adj(A)
	return result;
}

ofMatrix4x4 Matrix3::toMatrix4x4() const
{
	ofMatrix4x4 m;
	m.set(coefficients[0], coefficients[1], coefficients[2], 0, 
		coefficients[3],coefficients[4], coefficients[5], 0, 
		coefficients[6], coefficients[7],coefficients[8], 0, 
		0, 0, 0, 1);
	return m;
}

Quaternion Matrix3::toQuaternion() const
{
	double w = sqrt(1.0 + coefficients[0] + coefficients[4] + coefficients[8]) / 2.0;
	double w4 = (4.0 * w);
	double x = (coefficients[7] - coefficients[5]) / w4;
	double y = (coefficients[2] - coefficients[6]) / w4;
	double z = (coefficients[3] - coefficients[1]) / w4;
	return Quaternion(w, Vector(x,y,z));
}


Vector Matrix3::GetColumn(int columnIndex)
{
	if (columnIndex == 0) return Vector(coefficients[0], coefficients[3], coefficients[6]);
	else if (columnIndex == 1) return Vector(coefficients[1], coefficients[4], coefficients[7]);
	else if (columnIndex == 2) return Vector(coefficients[2], coefficients[5], coefficients[8]);
	else return Vector();
}