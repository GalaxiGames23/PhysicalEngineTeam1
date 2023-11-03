#include "Matrix3.h"

Matrix3::Matrix3() 
{
	//Matrice identit�
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

float Matrix3::GetCoefficient(int i) 
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

float Matrix3::GetCoefficient(int row, int column) 
{
	if (row < 1 || row>3 || column < 1 || column>3) return 0;
	//position dans l'array
	int i = (row - 1) * 3 + (column - 1);

	return this->coefficients[i];
}

Matrix3 Matrix3::Invers() 
{

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
	//r�gle de sarrus: aei + bfg + cdh - ceg - bdi - afh
	float aei = this->coefficients[0] * this->coefficients[4] * this->coefficients[8];
	float bfg = this->coefficients[1] * this->coefficients[5] * this->coefficients[6];
	float cdh = this->coefficients[2] * this->coefficients[3] * this->coefficients[7];
	float ceg = this->coefficients[2] * this->coefficients[4] * this->coefficients[6];
	float bdi = this->coefficients[1] * this->coefficients[3] * this->coefficients[8];
	float afh = this->coefficients[0] * this->coefficients[5] * this->coefficients[7];

	return aei + bfg + cdh - ceg - bdi - afh;
}