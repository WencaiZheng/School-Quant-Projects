// TestMatMul.cpp
//
// Testing matrix multiplication
//
// (C) Datasim Education BV 2006

#include "Complex.hpp"
#include "numericmatrix.cpp"
#include "matrixmechanisms.cpp"

int main()
{

	NumericMatrix<double, long> m1(2,3);
	NumericMatrix<double, long> m2(3,2);

	NumericMatrix<double, long> m3 = m1 * m2;
	print(m3);

	NumericMatrix<Complex, long> m1C(2,3);
	NumericMatrix<Complex, long> m2C(3,2);

	NumericMatrix<Complex, long> m3C = m1C * m2C;

	print(m3C);

	return 0;
}