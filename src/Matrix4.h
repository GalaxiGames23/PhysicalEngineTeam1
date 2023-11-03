#pragma once
#include <array>

class Matrix4
{
private:
	/* Aspect de la matrice:
	*  [0  1   2  3]
	*  [4  5   6  7]
	*  [8  9  10 11]
	*  [12 13 14 15]
	* */
	std::array<float, 16> coefficients; //<<<coefficients de la matrice

public:
	//constructeurs
	Matrix4();
	Matrix4(const Matrix4& m);
	Matrix4(std::array<float, 16> coefs);

	//destructeur
	~Matrix4() {}

	//opérateurs
	Matrix4& operator*(const Matrix4& m);
	Matrix4& operator+(const Matrix4& m);
	Matrix4& operator-(const Matrix4& m);
	bool operator==(const Matrix4& m);
	bool operator!=(const Matrix4& m);

	//setter
	void SetCoefficients(std::array<float, 16> coefs);
	void SetCoefficient(int row, int column); //<<<gestion plus "traditionnelle" des matrices

	//getter
	float GetCoefficient(int i);
	float GetCoefficient(int row, int column);

	//inverse de la matrice
	Matrix4& Invers();

	//transposée de la matrice
	Matrix4& Transposed();

	//déterminant de la matrice
	float Determinant();
};

