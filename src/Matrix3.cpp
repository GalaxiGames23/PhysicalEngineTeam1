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

Matrix3::Matrix3(int coefs[9]) 
{
	for (int i = 0; i < 9; ++i)
	{
		this->coefficients[i] = coefs[i];
	}
}

Matrix3::~Matrix3() 
{

}

Matrix3& Matrix3::operator*(const Matrix3& m) 
{

}

Matrix3& Matrix3::operator+(const Matrix3& m) 
{

}

Matrix3& Matrix3::operator-(const Matrix3& m) 
{

}

bool Matrix3::operator==(const Matrix3& m) 
{

}

bool Matrix3::operator!=(const Matrix3& m) 
{

}

void Matrix3::SetCoefficients(std::array<float, 9> coefs)
{

}

void Matrix3::SetCoefficient(int row, int column) 
{

}

float Matrix3::GetCoefficient(int i) 
{

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