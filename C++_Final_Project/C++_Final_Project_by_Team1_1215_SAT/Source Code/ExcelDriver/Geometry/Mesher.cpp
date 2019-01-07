// mesher.cpp
//
// A simple mesher on a 1d domain. We divide
// an interval into J+1 mesh points, J-1 of which
// are internal mesh points.
//
// DD 2005-10-1 Mesh can be in any time interval [t1, T]
// DD 2005-12-1 hpp and cpp versions
// DD 2005-12-1 mesh in T direction
//
// (C) Datasim Education BV 2006
//

#ifndef Mesher_CPP
#define Mesher_CPP

#include "mesher.hpp"


Mesher::Mesher()
{
			a =0.0; b = 1.0;
			LT = 0.0; HT = 1.0;
}

Mesher::Mesher(double A, double B, double t, double T)
{ // Describe the domain of integration

			a = A; b = B;
			LT = t; HT = T;
}

Mesher::Mesher(const Range<double>& rX, const Range<double>& rT)
{ // Describe the domain of integration

			a = rX.low(); b = rX.high();
			LT = rT.low(); HT = rT.high();
}


Vector<double, long> Mesher::xarr(int J)
{
			// NB Full array (includes end points)

			double h = (b - a) / double (J);
			
			int size = J+1;
			int start = 1;

			Vector<double, long> result(size, start);
			result[result.MinIndex()] = a;

			for (int j = result.MinIndex()+1; j <= result.MaxIndex(); j++)
			{
				result[j] = result[j-1] + h;
			}

			return result;
}

Vector<double, long> Mesher::yarr(int N)
{
			// NB Full array (includes end points)

			double k = (HT - LT) / double (N);
			
			int size = N+1;
			int start = 1;

			Vector<double, long> result(size, start);
			result[result.MinIndex()] = LT;

			for (int j = result.MinIndex()+1; j <= result.MaxIndex(); j++)
			{
				result[j] = result[j-1] + k;
			}

			return result;
}

double Mesher::timeStep(int N)
{
			return (HT - LT)/double (N);
}


#endif