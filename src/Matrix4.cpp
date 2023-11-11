#include "Matrix4.h"
#include "Matrix3.h"
#include <cstdio>
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
	for (int i = 0; i < 16; ++i)
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

Matrix4::Matrix4(float coefs[16])
{
	for (int i = 0; i < 16; ++i)
	{
		this->coefficients[i] = coefs[i];

	}
}

Matrix4::Matrix4(const Matrix3& m)
{
	for (int i = 0; i < 9; ++i)
	{
		this->coefficients[i] = m.GetCoefficient(i);
	}
	this->coefficients[9] = 0;
	this->coefficients[10] = 0;
	this->coefficients[11] = 0;
	this->coefficients[12] = 0;
	this->coefficients[13] = 0;
	this->coefficients[14] = 0;
	this->coefficients[15] = 1;

}

Matrix4 Matrix4::operator*(const Matrix4& m)
{
	Matrix4 result = Matrix4();

	//to modify
	result.coefficients[0] = this->coefficients[0] * m.coefficients[0] + this->coefficients[1] * m.coefficients[4] + this->coefficients[2] * m.coefficients[8] + this->coefficients[3] * m.coefficients[12];
	result.coefficients[1] = this->coefficients[0] * m.coefficients[1] + this->coefficients[1] * m.coefficients[5] + this->coefficients[2] * m.coefficients[9] + this->coefficients[3] * m.coefficients[13];
	result.coefficients[2] = this->coefficients[0] * m.coefficients[2] + this->coefficients[1] * m.coefficients[6] + this->coefficients[2] * m.coefficients[10] + this->coefficients[3] * m.coefficients[14];
	result.coefficients[3] = this->coefficients[0] * m.coefficients[3] + this->coefficients[1] * m.coefficients[7] + this->coefficients[2] * m.coefficients[11] + this->coefficients[3] * m.coefficients[15];

	result.coefficients[4] = this->coefficients[4] * m.coefficients[0] + this->coefficients[5] * m.coefficients[4] + this->coefficients[6] * m.coefficients[8] + this->coefficients[7] * m.coefficients[12];
	result.coefficients[5] = this->coefficients[4] * m.coefficients[1] + this->coefficients[5] * m.coefficients[5] + this->coefficients[6] * m.coefficients[9] + this->coefficients[7] * m.coefficients[13];
	result.coefficients[6] = this->coefficients[4] * m.coefficients[2] + this->coefficients[5] * m.coefficients[6] + this->coefficients[6] * m.coefficients[10] + this->coefficients[7] * m.coefficients[14];
	result.coefficients[7] = this->coefficients[4] * m.coefficients[3] + this->coefficients[5] * m.coefficients[7] + this->coefficients[6] * m.coefficients[11] + this->coefficients[7] * m.coefficients[15];

	result.coefficients[8] = this->coefficients[8] * m.coefficients[0] + this->coefficients[9] * m.coefficients[4] + this->coefficients[10] * m.coefficients[8] + this->coefficients[11] * m.coefficients[12];
	result.coefficients[9] = this->coefficients[8] * m.coefficients[1] + this->coefficients[9] * m.coefficients[5] + this->coefficients[10] * m.coefficients[9] + this->coefficients[11] * m.coefficients[13];
	result.coefficients[10] = this->coefficients[8] * m.coefficients[2] + this->coefficients[9] * m.coefficients[6] + this->coefficients[10] * m.coefficients[10] + this->coefficients[11] * m.coefficients[14];
	result.coefficients[11] = this->coefficients[8] * m.coefficients[3] + this->coefficients[9] * m.coefficients[7] + this->coefficients[10] * m.coefficients[11] + this->coefficients[11] * m.coefficients[15];

	result.coefficients[12] = this->coefficients[12] * m.coefficients[0] + this->coefficients[13] * m.coefficients[4] + this->coefficients[14] * m.coefficients[8] + this->coefficients[15] * m.coefficients[12];
	result.coefficients[13] = this->coefficients[12] * m.coefficients[1] + this->coefficients[13] * m.coefficients[5] + this->coefficients[14] * m.coefficients[9] + this->coefficients[15] * m.coefficients[13];
	result.coefficients[14] = this->coefficients[12] * m.coefficients[2] + this->coefficients[13] * m.coefficients[6] + this->coefficients[14] * m.coefficients[10] + this->coefficients[15] * m.coefficients[14];
	result.coefficients[15] = this->coefficients[12] * m.coefficients[3] + this->coefficients[13] * m.coefficients[7] + this->coefficients[14] * m.coefficients[11] + this->coefficients[15] * m.coefficients[15];

	return result;
}

Matrix4 Matrix4::operator*(const float& a)
{
	Matrix4 result = Matrix4();

	for (int i = 0; i < 16; ++i)
	{
		result.coefficients[i] = this->coefficients[i] * a;
	}

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
	int i = (row - 1) * 4 + (column - 1);

	this->coefficients[i] = coef;
}

float Matrix4::GetCoefficient(int i)  const
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

float Matrix4::GetCoefficient(int row, int column)  const
{
	if (row < 1 || row>4 || column < 1 || column>4) return 0;
	//position dans l'array
	int i = (row - 1) * 4 + (column - 1);

	return this->coefficients[i];
}

Matrix4 Matrix4::Invers()
{
	//A-1 = (1 / det(A)) * adj(A)T
	float det = this->Determinant();

	//non inversible, cas limite qui devra être testé 
	if (det == 0) return Matrix4();

	float invDet = 1 / det;
	Matrix4 adj = this->Adjacent().Transposed();

	Matrix4 result = adj * invDet;

	return result;
}

Matrix4 Matrix4::Transposed()
{
	Matrix4 result = Matrix4();

	result.coefficients[0] = this->coefficients[0];
	result.coefficients[1] = this->coefficients[4];
	result.coefficients[2] = this->coefficients[8];
	result.coefficients[3] = this->coefficients[12];

	result.coefficients[4] = this->coefficients[1];
	result.coefficients[5] = this->coefficients[5];
	result.coefficients[6] = this->coefficients[9];
	result.coefficients[7] = this->coefficients[13];

	result.coefficients[8] = this->coefficients[2];
	result.coefficients[9] = this->coefficients[6];
	result.coefficients[10] = this->coefficients[10];
	result.coefficients[11] = this->coefficients[14];

	result.coefficients[12] = this->coefficients[3];
	result.coefficients[13] = this->coefficients[7];
	result.coefficients[14] = this->coefficients[11];
	result.coefficients[15] = this->coefficients[15];

	return result;
}

float Matrix4::Determinant()
{
	//det(A) = a(det(M1) - b(det(M2) + c(det(M3)) - d(det(M4)), on a besoin des sous-matrices 3x3

	Matrix3 M1; //<<<sous-matrice obtenue en supprimant la première ligne et la première colonne
	M1.SetCoefficient(0, this->coefficients[5]);
	M1.SetCoefficient(1, this->coefficients[6]);
	M1.SetCoefficient(2, this->coefficients[7]);
	M1.SetCoefficient(3, this->coefficients[9]);
	M1.SetCoefficient(4, this->coefficients[10]);
	M1.SetCoefficient(5, this->coefficients[11]);
	M1.SetCoefficient(6, this->coefficients[13]);
	M1.SetCoefficient(7, this->coefficients[14]);
	M1.SetCoefficient(8, this->coefficients[15]);

	Matrix3 M2; //<<<sous-matrice obtenue en supprimant la première ligne et la deuxième colonne
	M2.SetCoefficient(0, this->coefficients[4]);
	M2.SetCoefficient(1, this->coefficients[6]);
	M2.SetCoefficient(2, this->coefficients[7]);
	M2.SetCoefficient(3, this->coefficients[8]);
	M2.SetCoefficient(4, this->coefficients[10]);
	M2.SetCoefficient(5, this->coefficients[11]);
	M2.SetCoefficient(6, this->coefficients[12]);
	M2.SetCoefficient(7, this->coefficients[14]);
	M2.SetCoefficient(8, this->coefficients[15]);

	Matrix3 M3; //<<<sous-matrice obtenue en supprimant la première ligne et la troisième colonne
	M3.SetCoefficient(0, this->coefficients[4]);
	M3.SetCoefficient(1, this->coefficients[5]);
	M3.SetCoefficient(2, this->coefficients[7]);
	M3.SetCoefficient(3, this->coefficients[8]);
	M3.SetCoefficient(4, this->coefficients[9]);
	M3.SetCoefficient(5, this->coefficients[11]);
	M3.SetCoefficient(6, this->coefficients[12]);
	M3.SetCoefficient(7, this->coefficients[13]);
	M3.SetCoefficient(8, this->coefficients[15]);

	Matrix3 M4; //<<<sous-matrice obtenue en supprimant la première ligne et la quatrième colonne
	M4.SetCoefficient(0, this->coefficients[4]);
	M4.SetCoefficient(1, this->coefficients[5]);
	M4.SetCoefficient(2, this->coefficients[6]);
	M4.SetCoefficient(3, this->coefficients[8]);
	M4.SetCoefficient(4, this->coefficients[9]);
	M4.SetCoefficient(5, this->coefficients[10]);
	M4.SetCoefficient(6, this->coefficients[12]);
	M4.SetCoefficient(7, this->coefficients[13]);
	M4.SetCoefficient(8, this->coefficients[14]);

	return this->coefficients[0] * M1.Determinant() - this->coefficients[1] * M2.Determinant() + this->coefficients[2] * M3.Determinant() - this->coefficients[3] * M4.Determinant();
}

Matrix4 Matrix4::Adjacent()
{
	/*
	adj(A) = | C11  -C12  C13  -C14 |
			 | -C21  C22  -C23  C24 |
			 | C31  -C32  -C33  C34 |
			 | -C41  C42  -C43  C44 |
	Où chaque élément Cij est le déterminant d'une sous-matrice 3x3 de A obtenue en supprimant la i-ème ligne et la j-ème colonne de la matrice A
	*/

	//calcul des sous-matrices et de leur déterminant:

	Matrix3 M11; //<<<sous-matrice obtenue en supprimant la première ligne et la première colonne
	M11.SetCoefficient(0, this->coefficients[5]);
	M11.SetCoefficient(1, this->coefficients[6]);
	M11.SetCoefficient(2, this->coefficients[7]);
	M11.SetCoefficient(3, this->coefficients[9]);
	M11.SetCoefficient(4, this->coefficients[10]);
	M11.SetCoefficient(5, this->coefficients[11]);
	M11.SetCoefficient(6, this->coefficients[13]);
	M11.SetCoefficient(7, this->coefficients[14]);
	M11.SetCoefficient(8, this->coefficients[15]);
	float C11 = M11.Determinant();

	Matrix3 M12; //<<<sous-matrice obtenue en supprimant la première ligne et la deuxième colonne
	M12.SetCoefficient(0, this->coefficients[4]);
	M12.SetCoefficient(1, this->coefficients[6]);
	M12.SetCoefficient(2, this->coefficients[7]);
	M12.SetCoefficient(3, this->coefficients[8]);
	M12.SetCoefficient(4, this->coefficients[10]);
	M12.SetCoefficient(5, this->coefficients[11]);
	M12.SetCoefficient(6, this->coefficients[12]);
	M12.SetCoefficient(7, this->coefficients[14]);
	M12.SetCoefficient(8, this->coefficients[15]);
	float C12 = M12.Determinant();

	Matrix3 M13; //<<<sous-matrice obtenue en supprimant la première ligne et la troisième colonne
	M13.SetCoefficient(0, this->coefficients[4]);
	M13.SetCoefficient(1, this->coefficients[5]);
	M13.SetCoefficient(2, this->coefficients[7]);
	M13.SetCoefficient(3, this->coefficients[8]);
	M13.SetCoefficient(4, this->coefficients[9]);
	M13.SetCoefficient(5, this->coefficients[11]);
	M13.SetCoefficient(6, this->coefficients[12]);
	M13.SetCoefficient(7, this->coefficients[13]);
	M13.SetCoefficient(8, this->coefficients[15]);
	float C13 = M13.Determinant();

	Matrix3 M14; //<<<sous-matrice obtenue en supprimant la première ligne et la quatrième colonne
	M14.SetCoefficient(0, this->coefficients[4]);
	M14.SetCoefficient(1, this->coefficients[5]);
	M14.SetCoefficient(2, this->coefficients[6]);
	M14.SetCoefficient(3, this->coefficients[8]);
	M14.SetCoefficient(4, this->coefficients[9]);
	M14.SetCoefficient(5, this->coefficients[10]);
	M14.SetCoefficient(6, this->coefficients[12]);
	M14.SetCoefficient(7, this->coefficients[13]);
	M14.SetCoefficient(8, this->coefficients[14]);
	float C14 = M14.Determinant();

	Matrix3 M21; //<<<sous-matrice obtenue en supprimant la deuxième ligne et la première colonne
	M21.SetCoefficient(0, this->coefficients[1]);
	M21.SetCoefficient(1, this->coefficients[2]);
	M21.SetCoefficient(2, this->coefficients[3]);
	M21.SetCoefficient(3, this->coefficients[9]);
	M21.SetCoefficient(4, this->coefficients[10]);
	M21.SetCoefficient(5, this->coefficients[11]);
	M21.SetCoefficient(6, this->coefficients[13]);
	M21.SetCoefficient(7, this->coefficients[14]);
	M21.SetCoefficient(8, this->coefficients[15]);
	float C21 = M21.Determinant();

	Matrix3 M22; //<<<sous-matrice obtenue en supprimant la deuxième ligne et la deuxième colonne
	M22.SetCoefficient(0, this->coefficients[0]);
	M22.SetCoefficient(1, this->coefficients[2]);
	M22.SetCoefficient(2, this->coefficients[3]);
	M22.SetCoefficient(3, this->coefficients[8]);
	M22.SetCoefficient(4, this->coefficients[10]);
	M22.SetCoefficient(5, this->coefficients[11]);
	M22.SetCoefficient(6, this->coefficients[12]);
	M22.SetCoefficient(7, this->coefficients[14]);
	M22.SetCoefficient(8, this->coefficients[15]);
	float C22 = M22.Determinant();

	Matrix3 M23; //<<<sous-matrice obtenue en supprimant la deuxième ligne et la troisième colonne
	M23.SetCoefficient(0, this->coefficients[0]);
	M23.SetCoefficient(1, this->coefficients[1]);
	M23.SetCoefficient(2, this->coefficients[3]);
	M23.SetCoefficient(3, this->coefficients[8]);
	M23.SetCoefficient(4, this->coefficients[9]);
	M23.SetCoefficient(5, this->coefficients[11]);
	M23.SetCoefficient(6, this->coefficients[12]);
	M23.SetCoefficient(7, this->coefficients[13]);
	M23.SetCoefficient(8, this->coefficients[15]);
	float C23 = M23.Determinant();

	Matrix3 M24; //<<<sous-matrice obtenue en supprimant la deuxième ligne et la quatrième colonne
	M24.SetCoefficient(0, this->coefficients[0]);
	M24.SetCoefficient(1, this->coefficients[1]);
	M24.SetCoefficient(2, this->coefficients[2]);
	M24.SetCoefficient(3, this->coefficients[8]);
	M24.SetCoefficient(4, this->coefficients[9]);
	M24.SetCoefficient(5, this->coefficients[10]);
	M24.SetCoefficient(6, this->coefficients[12]);
	M24.SetCoefficient(7, this->coefficients[13]);
	M24.SetCoefficient(8, this->coefficients[14]);
	float C24 = M24.Determinant();

	Matrix3 M31; //<<<sous-matrice obtenue en supprimant la troisième ligne et la première colonne
	M31.SetCoefficient(0, this->coefficients[1]);
	M31.SetCoefficient(1, this->coefficients[2]);
	M31.SetCoefficient(2, this->coefficients[3]);
	M31.SetCoefficient(3, this->coefficients[5]);
	M31.SetCoefficient(4, this->coefficients[6]);
	M31.SetCoefficient(5, this->coefficients[7]);
	M31.SetCoefficient(6, this->coefficients[13]);
	M31.SetCoefficient(7, this->coefficients[14]);
	M31.SetCoefficient(8, this->coefficients[15]);
	float C31 = M31.Determinant();

	Matrix3 M32; //<<<sous-matrice obtenue en supprimant la troisième ligne et la deuxième colonne
	M32.SetCoefficient(0, this->coefficients[0]);
	M32.SetCoefficient(1, this->coefficients[2]);
	M32.SetCoefficient(2, this->coefficients[3]);
	M32.SetCoefficient(3, this->coefficients[4]);
	M32.SetCoefficient(4, this->coefficients[6]);
	M32.SetCoefficient(5, this->coefficients[7]);
	M32.SetCoefficient(6, this->coefficients[12]);
	M32.SetCoefficient(7, this->coefficients[14]);
	M32.SetCoefficient(8, this->coefficients[15]);
	float C32 = M32.Determinant();

	Matrix3 M33; //<<<sous-matrice obtenue en supprimant la troisième ligne et la troisième colonne
	M33.SetCoefficient(0, this->coefficients[0]);
	M33.SetCoefficient(1, this->coefficients[1]);
	M33.SetCoefficient(2, this->coefficients[3]);
	M33.SetCoefficient(3, this->coefficients[4]);
	M33.SetCoefficient(4, this->coefficients[5]);
	M33.SetCoefficient(5, this->coefficients[7]);
	M33.SetCoefficient(6, this->coefficients[12]);
	M33.SetCoefficient(7, this->coefficients[13]);
	M33.SetCoefficient(8, this->coefficients[15]);
	float C33 = M33.Determinant();

	Matrix3 M34; //<<<sous-matrice obtenue en supprimant la troisième ligne et la quatrième colonne
	M34.SetCoefficient(0, this->coefficients[0]);
	M34.SetCoefficient(1, this->coefficients[1]);
	M34.SetCoefficient(2, this->coefficients[2]);
	M34.SetCoefficient(3, this->coefficients[4]);
	M34.SetCoefficient(4, this->coefficients[5]);
	M34.SetCoefficient(5, this->coefficients[6]);
	M34.SetCoefficient(6, this->coefficients[12]);
	M34.SetCoefficient(7, this->coefficients[13]);
	M34.SetCoefficient(8, this->coefficients[14]);
	float C34 = M34.Determinant();

	Matrix3 M41; //<<<sous-matrice obtenue en supprimant la quatrième ligne et la première colonne
	M41.SetCoefficient(0, this->coefficients[1]);
	M41.SetCoefficient(1, this->coefficients[2]);
	M41.SetCoefficient(2, this->coefficients[3]);
	M41.SetCoefficient(3, this->coefficients[5]);
	M41.SetCoefficient(4, this->coefficients[6]);
	M41.SetCoefficient(5, this->coefficients[7]);
	M41.SetCoefficient(6, this->coefficients[9]);
	M41.SetCoefficient(7, this->coefficients[10]);
	M41.SetCoefficient(8, this->coefficients[11]);
	float C41 = M41.Determinant();

	Matrix3 M42; //<<<sous-matrice obtenue en supprimant la quatrième ligne et la deuxième colonne
	M42.SetCoefficient(0, this->coefficients[0]);
	M42.SetCoefficient(1, this->coefficients[2]);
	M42.SetCoefficient(2, this->coefficients[3]);
	M42.SetCoefficient(3, this->coefficients[4]);
	M42.SetCoefficient(4, this->coefficients[6]);
	M42.SetCoefficient(5, this->coefficients[7]);
	M42.SetCoefficient(6, this->coefficients[8]);
	M42.SetCoefficient(7, this->coefficients[10]);
	M42.SetCoefficient(8, this->coefficients[11]);
	float C42 = M42.Determinant();

	Matrix3 M43; //<<<sous-matrice obtenue en supprimant la quatrième ligne et la troisième colonne
	M43.SetCoefficient(0, this->coefficients[0]);
	M43.SetCoefficient(1, this->coefficients[1]);
	M43.SetCoefficient(2, this->coefficients[3]);
	M43.SetCoefficient(3, this->coefficients[4]);
	M43.SetCoefficient(4, this->coefficients[5]);
	M43.SetCoefficient(5, this->coefficients[7]);
	M43.SetCoefficient(6, this->coefficients[8]);
	M43.SetCoefficient(7, this->coefficients[9]);
	M43.SetCoefficient(8, this->coefficients[11]);
	float C43 = M43.Determinant();

	Matrix3 M44; //<<<sous-matrice obtenue en supprimant la quatrième ligne et la quatrième colonne
	M44.SetCoefficient(0, this->coefficients[0]);
	M44.SetCoefficient(1, this->coefficients[1]);
	M44.SetCoefficient(2, this->coefficients[2]);
	M44.SetCoefficient(3, this->coefficients[4]);
	M44.SetCoefficient(4, this->coefficients[5]);
	M44.SetCoefficient(5, this->coefficients[6]);
	M44.SetCoefficient(6, this->coefficients[8]);
	M44.SetCoefficient(7, this->coefficients[9]);
	M44.SetCoefficient(8, this->coefficients[10]);
	float C44 = M44.Determinant();

	/*
	adj(A) = | C11  -C12  C13  -C14 |
			 | -C21  C22 - C23  C24 |
			 | C31  -C32  C33  -C34 |
			 | -C41  C42  -C43  C44 |
	Où chaque élément Cij est le déterminant d'une sous-matrice 3x3 de A obtenue en supprimant la i-ème ligne et la j-ème colonne de la matrice A
	*/

	Matrix4 result = Matrix4();

	//to modify
	result.coefficients[0] = C11;
	result.coefficients[1] = -C12;
	result.coefficients[2] = C13;
	result.coefficients[3] = -C14;

	result.coefficients[4] = -C21;
	result.coefficients[5] = C22;
	result.coefficients[6] = -C23;
	result.coefficients[7] = C24;

	result.coefficients[8] = C31;
	result.coefficients[9] = -C32;
	result.coefficients[10] = C33;
	result.coefficients[11] = -C34;

	result.coefficients[12] = -C41;
	result.coefficients[13] = C42;
	result.coefficients[14] = -C43;
	result.coefficients[15] = C44;

	return result;
}

ofMatrix4x4 Matrix4::toMatrix4x4() const
{
	ofMatrix4x4 m;
	m.set(coefficients[0], coefficients[1], coefficients[2], coefficients[3], coefficients[4],
		coefficients[5], coefficients[6], coefficients[7], coefficients[8], coefficients[9], 
		coefficients[ 10], coefficients[11], coefficients[12], coefficients[13], coefficients[14], coefficients[15]);
	return m;
}
