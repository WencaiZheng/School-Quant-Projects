// TesExceptionsExcel.cpp
//
// Testing the Excel Driver fom the viewpoint of
// exception handling.
//
// (C) Datasim Education BV 2006
//
#include "stdafx.h"
#include "BitsAndPieces\StringConversions.hpp"
#include "ExcelDriver.hpp"
#include "ExcelMechanisms.hpp"
#include "VectorsAndMatrices\NumericMatrix.cpp" // Template
#include "ExceptionClasses\DatasimException.hpp"

#include <list>
#include <string>
using namespace std;

int main()
{

	long N = 20; long M = 30;
	NumericMatrix<double, long> matrix(N+1, M+1);

	Vector<double, long> xarr(N+1);
	Vector<double, long> yarr(M+1);

	double h1 = 0.1;
	xarr[xarr.MinIndex()] = 0.0;
	for (long i = xarr.MinIndex()+1; i <= xarr.MaxIndex(); i++)
	{
		xarr[i] = xarr[i-1] + h1;
	}

	double h2 = 0.2;
	yarr[yarr.MinIndex()] = 0.0;
	for (long j = yarr.MinIndex()+1; j <= yarr.MaxIndex(); j++)
	{
		yarr[j] = yarr[j-1] + h2;
	}


	list<std::string> rowlabels = convertToString(xarr);
	list<std::string> columnlabels = convertToString(yarr);

	std::string sheetName("First");


	try
	{

		// (x,y) values
	//	printOneExcel(xarr, yarr);
	}
	catch(DatasimException& e)
	{
		e.print();
		return 0;
	}

	try
	{
		int sz = xarr.Size() + 10;
		list<Vector<double, long> > yValues(sz);
		list<string> labels(yValues.size());

		// List of line graphs
	//	printInExcel(xarr, labels, yValues);
	}
	catch(DatasimException& e)
	{
		e.print();
		return 0;
	}

	try
	{	
		// NumericMatrix<double, long> matrix(N+1, M+1); OK

		NumericMatrix<double, long> matrixBad(N+1, M+10);

		// 'Annotated' matrices
	//	printMatrixInExcel(matrixBad, xarr, yarr);
	}
	catch(DatasimException& e)
	{
		e.print();
		return 0;
	}

	try
	{

		NumericMatrix<double, long> matrixBad(N+1, M+10);
		int freq = 1;

		// Matrix rows as line graphs
	//	printMatrixChartsInExcel(freq, matrixBad, xarr, yarr);
	}
	catch(DatasimException& e)
	{
		e.print();
		return 0;
	}

	try
	{
	
		Vector<double, long> yarr2(yarr.Size()+10); // incompatible with yarr

		// Difference of vectors
	//	printDifferenceInExcel(xarr, yarr, yarr2);
	}
	catch(DatasimException& e)
	{
		e.print();
		return 0;
	}

	try
	{

		NumericMatrix<double, long> matrixBad(N+1, M+10);

		// m1 - m2
	//	printMatrixDifferenceInExcel(matrix, matrixBad, xarr, yarr);
	}
	catch(DatasimException& e)
	{
		e.print();
		return 0;
	}

	try
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

		// Print tensor as matrix cells
		printTensorInExcel(t1, xarr, yarr);
	}
	catch(DatasimException& e)
	{
		e.print();

		ExcelDriver& excel = ExcelDriver::Instance();
		excel.MakeVisible(true);	

		excel.printStringInExcel(e.Message(), 1, 1, string("Err"));

		list<string> dump;
		dump.push_back(e.MessageDump()[0]);
		dump.push_back(e.MessageDump()[1]);
		dump.push_back(e.MessageDump()[2]);

		excel.printStringInExcel(dump, 1, 1, string("Err"));

		return 0;
	}

	return 0;
}
