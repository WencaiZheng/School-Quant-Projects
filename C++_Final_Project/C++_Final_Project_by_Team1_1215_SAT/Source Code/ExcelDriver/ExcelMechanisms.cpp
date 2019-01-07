// ExcelMechanisms.cpp
//
// Useful functions for use with Excel.
//
// 2005-11-29 DD kick-off
// 2005-12-16 DD Introduce exception handling (in about functions)
// 2006-2-2 DD print a tensor's matrices at intervals
// 2006-6-14 DD Bug fix PrintInExcel
//
// (C) Datasim Education BV 2005-2006
//

//#ifndef ExcelMechanisms_CPP
//#define ExcelMechanisms_CPP

#include "stdafx.h"
#include "excelmechanisms.hpp"
#include "ExceptionClasses\DatasimException.hpp"
#include "ExcelDriver.hpp"
#include "VectorsAndMatrices\matrixmechanisms.cpp"
//#include "Matrixcheckers.cpp" // Checking aligned data structures
#include <list>
#include <iostream>

// Hard-coded strings
const string comma(", ");
const string bracketL("[");
const string bracketR("]");

void printOneExcel(const Vector<double, long>& x,						
					const Vector<double, long>& functionResult,
					const std::string& title,
					const std::string& horizontal, 
					const std::string& vertical,
					const std::string& legend)
{ 
	// N.B. Excel has a limit of 8 charts; after that you get a run-time error

	// PREC: Type I
	if (x.Size() != functionResult.Size())
	{
		
		string tmp = string("Sizes of vectors are X, Y: ") + getString(x.Size()) + string(comma) + getString(functionResult.Size());

		throw DatasimException(string("Size mismatch of two vectors"), string("PrintOneExcel"),
			tmp);
	}


	cout << "Starting Excel\n";

	ExcelDriver& excel = ExcelDriver::Instance();

	excel.MakeVisible(true);		// Default is INVISIBLE!

	// Workaround
	list<std::string> legendList; legendList.push_back(legend);
	list<Vector<double, long> > functionResultList; functionResultList.push_back(functionResult);

	excel.CreateChart(x, legendList, functionResultList, title, horizontal, vertical);
	
}

void printInExcel(const Vector<double, long>& x,		// X array
					const list<std::string>& labels,					// Names of each vector
					const list<Vector<double, long> >& functionResult,	// The list of Y values
					const std::string& title,
					const std::string& horizontal, 
					const std::string& vertical)
{ // Print a list of Vectors in Excel. Each vector is the output of
  // a finite difference scheme for a scalar IVP

	// PREC: Type I
//	if (x.Size() != labels.size() || x.Size() != functionResult.size())
	// No cheque of x array size
	if (labels.size() != functionResult.size())
	{
		string tmp = "Sizes of vectors are X, Y, Label: " + getString(x.Size()) + comma +
			getString(functionResult.size()) + comma + getString(labels.size());

		throw DatasimException(string("Size mismatch of vectors and labels"), string("PrintInExcel"),
			tmp);
	}


	cout << "Starting Excel\n";

	ExcelDriver& excel = ExcelDriver::Instance();

	excel.MakeVisible(true);		// Default is INVISIBLE!


	excel.CreateChart(x, labels, functionResult, title, horizontal, vertical);

}

// Print a two-dimensional array (typically, one time level)
void printMatrixInExcel(const NumericMatrix<double, long>& matrix,
				 const Vector<double, long>& xarr, const Vector<double, long>& yarr, 
				 const std::string& SheetName)
{

	// PREC: Type II, III
	if (xarr.Size() != matrix.Rows() || yarr.Size() != matrix.Columns())
	{
		string tmp = "Vectors X, Y, matrix M: " + getString(xarr.Size()) + comma + getString(yarr.Size())
			+ bracketL + getString(matrix.Rows()) + comma + getString(matrix.Columns()) + bracketR;

		throw DatasimException(string("Size mismatch of vector(s) and matrix"), string("PrintMatrixInExcel"),
			tmp);
	}

	ExcelDriver& excel = ExcelDriver::Instance();
	excel.MakeVisible(true);
	// Print a matrix showing the x and y positions

	// We need to convert the double arrays to lists of strings
	cout << "Starting Excel";

	list<std::string> rowlabels = convertToString(xarr);
	list<std::string> columnlabels = convertToString(yarr);

	cout << "Staring Excel";
	
	excel.AddMatrix(SheetName, matrix, rowlabels, columnlabels);

}
// Print a matrix's rows as line graphs
void printMatrixChartsInExcel(int freq, // Selective printing
				 const NumericMatrix<double, long>& matrix,
				 const Vector<double, long>& rowArr, const Vector<double, long>& colArr,
				 const std::string& SheetName)
{
	// PREC: Type II, III
	if (rowArr.Size() != matrix.Rows() || colArr.Size() != matrix.Columns())
	{
		string tmp = string("Vectors X, Y, matrix M: ") + getString(rowArr.Size()) + comma + getString(colArr.Size())
			 + bracketL + getString(matrix.Rows()) + comma + getString(matrix.Columns()) + bracketR;

		throw DatasimException(string("Size mismatch of vector(s) and matrix"), string("PrintMatrixChartsInExcel"),
			tmp);
	}


	string title;
	Vector<double, long> tmp(matrix.Columns(), matrix.MinColumnIndex());

	for (long r = matrix.MinRowIndex(); r <= matrix.MaxRowIndex(); r++)
	{
		title = getString(r);
		tmp = createVector(matrix, r); // Can optimise (later)
		print(tmp);

		if ((r/freq)*freq == r)
		{
			printOneExcel(colArr, tmp, title); 
		}
	}

	
}

// Print the vector that is the difference of two vectors
void printDifferenceInExcel(const Vector<double, long>& x,	const Vector<double, long>& y1,					
					const Vector<double, long>& y2,
					const std::string& title, 
					const std::string& horizontal, 
					const std::string& vertical,
					const std::string& legend,
					long freq)
{

	// PREC: Type IA
	if (x.Size() != y1.Size() || x.Size() != y2.Size())
	{
		string tmp = "Sizes vectors X,Y1,Y2: " + getString(x.Size()) + comma + getString(y1.Size()) 
							+ comma + getString(y2.Size());

		throw DatasimException(string("Size mismatch of 3 vectors"), string("PrintDifferenceInExcel"),
			tmp);
	}


	Vector<double, long> diffVector = y1 - y2;

	printOneExcel(x, diffVector, title, horizontal, vertical, legend);
	

}

void printMatrixDifferenceInExcel(const NumericMatrix<double, long>& matrix1,
								  const NumericMatrix<double, long>& matrix2,
				 const Vector<double, long>& xarr, const Vector<double, long>& yarr, 
				 const std::string& SheetName)
{

	// PREC: Type IV m1, m2 have same 'shape'
	if (matrix1.Rows() != matrix2.Rows() || matrix1.Columns() != matrix2.Columns())
	{
		string tmp1 = string(", x and y arrays: ") + bracketL + getString(xarr.Size()) + comma + getString(yarr.Size()) + bracketR;

		string tmp = "Incompatible matrices: [" + getString(matrix1.Rows()) + comma + getString(matrix1.Columns()) + bracketR + 
						bracketL + getString(matrix2.Rows()) + comma + getString(matrix2.Columns()) + bracketR;

		tmp += tmp1;

		throw DatasimException(string("Size mismatch of matrices"), string("PrintMatrixDifferenceInExcel"),tmp);
	}


	NumericMatrix<double, long> m2 = matrix1 - matrix2;

	// PREC: Type II, III
	if (xarr.Size() != m2.Rows() || yarr.Size() != m2.Columns())
	{
		string tmp = "Vectors X, Y, matrix M: " + getString(xarr.Size()) + comma + getString(yarr.Size()) + 
						bracketL + getString(m2.Rows()) + comma + getString(m2.Columns()) + bracketR;

		throw DatasimException(string("Size mismatch of vector(s) and matrix"), string("PrintMatrixDifferenceInExcel"),
			tmp);
	}

	print(m2);

	printMatrixInExcel(m2, xarr, yarr, SheetName);

}

// Print an array of matrices
void printTensorInExcel(const Tensor<double, long>& tensor, long freq)
{

	// PREC: None needed, always works

	ExcelDriver& excel = ExcelDriver::Instance();
	excel.MakeVisible(true);	

	//	Use: excel.AddMatrix(sheetName, matrix, rowlabels, columnlabels);

	std::list<std::string> rowlabels(tensor.MaxFirstIndex());
	std::list<std::string> columnlabels(tensor.MaxSecondIndex());
	std::string name;

	for (long i = tensor.MinThirdIndex(); i <= tensor.MaxThirdIndex(); i++)
	{
		name = getString(i);

		if ((i/freq)*freq == i || i == tensor.MinThirdIndex())
		{
			excel.AddMatrix(name, tensor[i], rowlabels, columnlabels);
		}

	}

}
// Print an array of matrices
void printTensorInExcel(const Tensor<double, long>& tensor,
				const Vector<double, long>& xarr, const Vector<double, long>& yarr, 
				const std::string& SheetName, long freq)
{


	// PREC: Type II, III
	if (xarr.Size() != tensor.Rows() || yarr.Size() != tensor.Columns())
	{
		string tmp = string("Vectors X, Y, tensor M: ") + getString(xarr.Size()) + comma + getString(yarr.Size()) + 
						bracketL + getString(tensor.Rows()) + comma + getString(tensor.Columns()) + bracketR;

		throw DatasimException(string("Size mismatch of vector(s) and tensor"), string("PrintTensorInExcel"),
			tmp);
	}

	list<std::string> rowlabels = convertToString(xarr);
	list<std::string> columnlabels = convertToString(yarr);

	ExcelDriver& excel = ExcelDriver::Instance();
	excel.MakeVisible(true);	

	std::string tmp;

	for (long i = tensor.MinThirdIndex(); i <= tensor.MaxThirdIndex(); i++)
	{
		tmp = SheetName + getString(i);

		if ((i/freq)*freq == i || i == tensor.MinThirdIndex())
		{
			excel.AddMatrix(tmp, tensor[i], rowlabels, columnlabels);
		}

	}

}

// Print discrete values of a continuous function on interval [A,B]
void printDiscreteFunctionValues(double (*f) (double x), double A, double B, long nSteps,
					const std::string& title, 
					const std::string& horizontal, 
					const std::string& vertical,
					const std::string& legend)
{	 

	// Create discrete x and y arrays
	double h = (B - A) / double (nSteps);

	Vector<double, long> mesh(nSteps + 1, 1);

	double val = A;

	for (long i = 1; i <= nSteps + 1; i++)	
	{
		mesh[i] = val;
		val += h;
	}

	// Now array of values
	Vector<double, long> result(nSteps + 1, 1);

	for (long i2 = 1; i2 <= nSteps + 1; i2++)	
	{
		result[i2] = (*f)(mesh[i2]);
	
	}

	printOneExcel(mesh, result, title, horizontal, vertical, legend);


}



//#endif