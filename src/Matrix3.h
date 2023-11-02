#pragma once
#include <array>

class Matrix3
{

private:
	/* Aspect de la matrice:
	*  [0 1 2]
	*  [3 4 5]
	*  [6 7 8]
	* */
	std::array<float, 9> coefficients; //<<<coefficients de la matrice

public:
	//constructeurs
	Matrix3();
	Matrix3(const Matrix3& m);
	Matrix3(int coefs[9]);

	//destructeur
	~Matrix3();

	//opérateurs
	Matrix3& operator*(const Matrix3& m);
	Matrix3& operator+(const Matrix3& m);
	Matrix3& operator-(const Matrix3& m);
	bool operator==(const Matrix3& m);
	bool operator!=(const Matrix3& m);

	//setter
	void SetCoefficients(std::array<float, 9> coefs);
	void SetCoefficient(int row, int column); //<<<gestion plus "traditionnelle" des matrices

	//getter
	float GetCoefficient(int i);
	float GetCoefficient(int row, int column);

	//inverse de la matrice
	Matrix3& Invers();

	//transposée de la matrice
	Matrix3& Transposed();

	//déterminant de la matrice
	float Determinant();
};

