// TwoDimMesher.hpp
//
// A simple TwoDimMesher on a 1d domain. We divide
// an interval into J+1 mesh points, J-1 of which
// are internal mesh points.
//
// Future projects:
//
//	1. Separate space and time meshing
//  2. Meshing in hypercubes (modelling geometric aspects)
//
// (C) Datasim Education BV 2006
//

#ifndef TwoDimMesher_HPP
#define TwoDimMesher_HPP

#include "Vector.cpp"
#include "NumericMatrix.cpp"
#include "range.cpp"
using namespace std;

class TwoDimMesher
{
private:
		double a1, b1;	// In space (left, right)
		double a2, b2;
		double LT, HT;	// In time (low, high)

public:

		TwoDimMesher();

		TwoDimMesher (double A1, double B1, 
							double A2, double B2, double t, double T);

		TwoDimMesher (const Range<double>& rX, const Range<double>& rY,
							const Range<double>& rT);

		Vector<double, long> xarr(int I);	// Mesh in direction x
		Vector<double, long> yarr(int J);	// Mesh in direction y
		Vector<double, long> tarr(int N);	// Mesh in direction t

		NumericMatrix<pair<double, double>, long> fullMesh(long I, long J);

		// Step lengths
		double h1(int I) const;				// x dir
		double h2(int J) const;				// y dir

		double timeStep(int N) const;		// t dir
};

#endif
