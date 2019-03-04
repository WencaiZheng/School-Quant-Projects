// mesher.hpp
//
// A simple mesher on a 1d domain. We divide
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

#ifndef Mesher_HPP
#define Mesher_HPP

#include "Vector.cpp"
#include "range.cpp"

class Mesher
{
private:
		double a, b;	// In space (left, right)
		double LT, HT;	// In time (low, high)

public:

		Mesher();

		Mesher (double A, double B, double t, double T);

		Mesher (const Range<double>& rX, const Range<double>& rT);

		Vector<double, long> xarr(int J);	// Mesh in direction 1
		Vector<double, long> yarr(int N);	// Mesh in direction 2

		double timeStep(int N);

};

#endif
