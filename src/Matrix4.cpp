#include "Matrix4.h"

Matrix4::Matrix4()
{
	//Matrice identité
	coefficients.fill(0);
	coefficients[0] = 1;
	coefficients[5] = 1;
	coefficients[10] = 1;
	coefficients[15] = 1;
}

Matrix4::Matrix4(const Matrix4& m)
{
	for (int i = 0; i < 9; ++i)
	{
		this->coefficients[i] = m.coefficients[i];
	}
}

Matrix4::Matrix4(std::array<float, 16> coefs)
{
	for (int i = 0; i < 16; ++i)
	{
		this->coefficients[i] = coefs[i];
	}
}

Matrix4 Matrix4::operator*(const Matrix4& m)
{
	Matrix4 result = Matrix4();

	//to modify
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

Matrix4 Matrix4::operator+(const Matrix4& m)
{
	Matrix4 result = Matrix4();

	for (int i = 0; i < 16; ++i)
	{
		result.coefficients[i] = this->coefficients[i] + m.coefficients[i];
	}

	return result;
}

Matrix4 Matrix4::operator-(const Matrix4& m)
{
	Matrix4 result = Matrix4();

	for (int i = 0; i < 16; ++i)
	{
		result.coefficients[i] = this->coefficients[i] - m.coefficients[i];
	}

	return result;
}

Matrix4& Matrix4::operator=(const Matrix4& m)
{
	for (int i = 0; i < 16; ++i)
	{
		this->coefficients[i] = m.coefficients[i];
	}

	return *this;
}

bool Matrix4::operator==(const Matrix4& m)
{
	bool toReturn = true;

	for (int i = 0; i < 16; ++i)
	{
		if (this->coefficients[i] != m.coefficients[i])
		{
			toReturn = false;
		}
	}

	return toReturn;
}

bool Matrix4::operator!=(const Matrix4& m)
{
	bool toReturn = true;

	for (int i = 0; i < 16; ++i)
	{
		if (this->coefficients[i] != m.coefficients[i])
		{
			toReturn = false;
		}
	}

	return !toReturn;
}

void Matrix4::SetCoefficients(std::array<float, 16> coefs)
{
	for (int i = 0; i < 16; ++i)
	{
		this->coefficients[i] = coefs[i];
	}
}

void Matrix4::SetCoefficient(int i, float coef)
{
	if (i < 16 && i >= 0)
	{
		this->coefficients[i] = coef;
	}
}

void Matrix4::SetCoefficient(int row, int column, float coef)
{
	if (row < 1 || row>4 || column < 1 || column>4) return;
	//position dans l'array

	//to modify
	int i = (row - 1) * 3 + (column - 1);

	this->coefficients[i] = coef;
}

float Matrix4::GetCoefficient(int i)
{
	if (i < 16 && i >= 0)
	{
		return this->coefficients[i];
	}
	else
	{
		return 0.0f;
	}
}

float Matrix4::GetCoefficient(int row, int column)
{
	if (row < 1 || row>4 || column < 1 || column>4) return 0;
	//position dans l'array

	//to modify
	int i = (row - 1) * 3 + (column - 1);

	return this->coefficients[i];
}

Matrix4 Matrix4::Invers()
{

}

Matrix4 Matrix4::Transposed()
{
	Matrix4 result = Matrix4();

	//to modify
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

float Matrix4::Determinant()
{
	//to modify

	//règle de sarrus: aei + bfg + cdh - ceg - bdi - afh
	float aei = this->coefficients[0] * this->coefficients[4] * this->coefficients[8];
	float bfg = this->coefficients[1] * this->coefficients[5] * this->coefficients[6];
	float cdh = this->coefficients[2] * this->coefficients[3] * this->coefficients[7];
	float ceg = this->coefficients[2] * this->coefficients[4] * this->coefficients[6];
	float bdi = this->coefficients[1] * this->coefficients[3] * this->coefficients[8];
	float afh = this->coefficients[0] * this->coefficients[5] * this->coefficients[7];

	return aei + bfg + cdh - ceg - bdi - afh;
}