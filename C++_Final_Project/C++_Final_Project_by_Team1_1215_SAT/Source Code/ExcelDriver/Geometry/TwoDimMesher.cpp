// TwoDimMesher.cpp
//
// A simple TwoDimMesher on a 1d domain. We divide
// an interval into J+1 mesh points, J-1 of which
// are internal mesh points.
//
// DD 2005-10-1 Mesh can be in any time interval [t1, T]
// DD 2005-12-1 hpp and cpp versions
// DD 2005-12-1 mesh in T direction
// DD 2005-12-20 Two dimensional problems
//
// (C) Datasim Education BV 2006
//

#ifndef TwoDimMesher_CPP
#define TwoDimMesher_CPP

#include "TwoDimMesher.hpp"


TwoDimMesher::TwoDimMesher()
{
			a1 =0.0; b1 = 1.0;
			a2 =0.0; b2 = 1.0;
			LT = 0.0; HT = 1.0;
}

TwoDimMesher::TwoDimMesher(double A1, double B1, double A2, double B2, 
						   double t, double T)
{ // Describe the domain of integration

			a1 = A1; b1 = B1;
			a2 = A2; b2 = B2;

			LT = t; HT = T;
}

TwoDimMesher::TwoDimMesher(const Range<double>& rX, const Range<double>& rY, 
						   const Range<double>& rT)
{ // Describe the domain of integration

			a1 = rX.low(); b1 = rX.high();
			a2 = rX.low(); b2 = rX.high();

			LT = rT.low(); HT = rT.high();
}


Vector<double, long> TwoDimMesher::xarr(int I)
{
			// NB Full array (includes end points)

			double h = (b1 - a1) / double (I);
			
			int size = I+1;
			int start = 1;

			Vector<double, long> result(size, start);
			result[result.MinIndex()] = a1;

			for (int j = result.MinIndex()+1; j <= result.MaxIndex(); j++)
			{
				result[j] = result[j-1] + h1;
			}

			return result;
}

Vector<double, long> TwoDimMesher::yarr(int J)
{
			// NB Full array (includes end points)

			double h2 = (b2 - a2) / double (J);
			
			int size = J+1;
			int start = 1;

			Vector<double, long> result(size, start);
			result[result.MinIndex()] = a2;

			for (int j = result.MinIndex()+1; j <= result.MaxIndex(); j++)
			{
				result[j] = result[j-1] + h2;
			}

			return result;
}

Vector<double, long> TwoDimMesher::tarr(int N)
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

NumericMatrix<pair<double, double>, long> TwoDimMesher::fullMesh(long I, long J)
{

	Vector<double, long> x = xarr(I);
	Vector<double, long> y = yarr(J);

	NumericMatrix<pair<double, double>, long> result(x.Size(), y.Size());

	for (long i = x.MinIndex(); i <= x.MaxIndex(); i++)
	{
		for (long j = y.MinIndex(); j <= x.MaxIndex(); j++)
		{
			result(i,j) = pair<double, double>(x[i], y[j]);
		}
	}

	return result;

}

double TwoDimMesher::h1(int I)
{
			return (B1 - A1)/double (I);
}

double TwoDimMesher::h2(int J)
{
			return (B2 - A2)/double (J);
}

double TwoDimMesher::timeStep(int N)
{
			return (HT - LT)/double (N);
}


#endif