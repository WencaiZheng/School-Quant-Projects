// TestTensorExcel.cpp
//
// Simple program to test tensors.
//
// 2005-12-3 DD kick-off
//
// (C) Datasim Education BV 2004-2006
#include "stdafx.h"
#include <math.h>
#include "VectorsAndMatrices\NumericMatrix.cpp" // Template
#include "Geometry\tensor.cpp"
#include "ExcelDriver.hpp"
#include "ExcelMechanisms.hpp"
#include "ExceptionClasses\DatasimException.hpp"

#include <string>
using namespace std;

double func(double x)
{

	return ::exp((x-0.5)*(x-0.5));
}

double func2(double x)
{
	return exp(-x*x*0.5);
}


int main()
{

	Tensor<double, long> t1(2, 3, 2);

	NumericMatrix<double, long> m(2, 3); // Rows and columns
	m(1,1) = 2.0;
	m(1,2) = 3.0;

	NumericMatrix<double, long> m2(2, 3); // Rows and columns
	m2(1,1) = 22.0;
	m2(1,2) = 43.0;

	t1[1] = m;
	t1[2] = m2;

//	printTensorInExcel(t1);


	// Stress test
//	Tensor<double, long> t4(4, 3, 12);
//	printTensorInExcel(t4);

	long nRows = 4;
	long nColumns = 3;
	long nThird = 12;

	Tensor<double, long> t5(nRows, nColumns, nThird); // 1, 2 and 3 dimms -->

	long startIndex = 1;
	Vector<double, long> xarr(nRows, startIndex, 1.0);
	Vector<double, long> yarr(nColumns, startIndex, 2.0);
	string name("Ten ");

	try
	{
		printTensorInExcel(t5, xarr, yarr, name);
	}

	catch (DatasimException& e)
	{
			e.print();
			return 0;
	}

	printDiscreteFunctionValues(func, 0.0, 1.0, 20, "Exp", "H", "V", "L");
	printDiscreteFunctionValues(func2, -5.0, 5.0, 50, "Gauss", "H", "V", "L");

	return 0;
}
