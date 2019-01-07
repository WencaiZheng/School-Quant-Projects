// testLatticeNamespace.cpp
//
// Using namespaces to create different kinds of 
// BINOMIAL lattices.
//
//	2005-1-4 DD Kick-off code
//	2006-3-10 DD simplified (no global data, just functions)
//
// (C) Datasim Education BV 2005-2006

#include "lattice.cpp"
#include <math.h>

namespace StandardLattice
{
	

			
		// Code here corresponds to forward induction
		Lattice<double, int, 2> createLattice (int N, double rootValue, double up, 
										double down)
		{ // Note that the above parameters are accessible in this function

			// This is for the binomial method only!!!

			Lattice<double, int, 2> source(N + 1, 0.0);
	
			int si = source.MinIndex();
			source[si][source[si].MinIndex()] = rootValue;

			// Loop from the min index to the end index
			for (int j = source.MinIndex() + 1; j <= source.MaxIndex(); j++)
			{
				for (int i = source[j].MinIndex(); i < source[j].MaxIndex(); i++)
				{
					source[j][i] = down * source[j-1][i];
					source[j][i+1] = up * source[j-1][i];
				}

			}

			return source;

		}

	
		// Code here corresponds to backward induction
		double traverse(Lattice<double, int, 2>& lattice, 
						Vector<double, int>& Payoff, double p,double discounting)
		{

				int ei = lattice.MaxIndex();
				lattice[ei] = Payoff;

				// Loop from the max index to the start (min) index
				for (int n = lattice.MaxIndex() - 1; n >= lattice.MinIndex(); n--)
				{

					for (int i = lattice[n].MinIndex(); i <= lattice[n].MaxIndex(); i++)
					{
			
						lattice[n][i] = discounting * (p * lattice[n+1][i+1] + (1.0-p) * lattice[n+1][i]);
				//		lattice[n][i] = BackTrace(lattice[n+1][i+1], lattice[n+1][i]);

					}
				}

				int si = lattice.MinIndex();
				return lattice[si][lattice[si].MinIndex()];

			
		}

}

