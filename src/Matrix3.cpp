#include "Matrix3.h"

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

Matrix3& Matrix3::operator*(const Matrix3& m) 
{

}

Matrix3& Matrix3::operator+(const Matrix3& m) 
{
	for (int i = 0; i < 9; ++i)
	{
		this->coefficients[i] += m.coefficients[i];
	}
}

Matrix3& Matrix3::operator-(const Matrix3& m) 
{
	for (int i = 0; i < 9; ++i)
	{
		this->coefficients[i] -= m.coefficients[i];
	}
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
	if (i < 9)
	{
		this->coefficients[i] = coef;
	}
}

void Matrix3::SetCoefficient(int row, int column, float coef) 
{

}

float Matrix3::GetCoefficient(int i) 
{
	if (i < 9)
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

}

Matrix3& Matrix3::Invers() 
{

}

Matrix3& Matrix3::Transposed() 
{

}

float Matrix3::Determinant()
{

}