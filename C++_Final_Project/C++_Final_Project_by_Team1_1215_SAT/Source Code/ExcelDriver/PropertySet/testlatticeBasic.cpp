// testlattice.cpp
//
// Testing the Latice class (basis for binomial and trinomial
// trees)
//
// In this version we have one class for both binomial and trinomial
// trees.
//
//	2006-3-9 DD some simple examples to show essentials
//
// (C) Datasim Education BV 2003-2006
//

#include "lattice.cpp"
#include "latticemechanisms.cpp"

#include <iostream>
using namespace std;


int main()
{
	const int typeB = 2;	// BinomialLatticeType;
	const int typeT = 3;	// Trinomial Type
	const int typeP = 5;	// Pentagonal Type

	int depth = 4;

	// Create objects of various 
	Lattice<double, int, typeB> lattice1(depth, 3.14);
	Lattice<double, long, typeT> lattice2(depth, 4.6);
	Lattice<double, long, typeP> lattice3(depth, 2.0);

	print(lattice1); 
	cout << endl << endl;
	print(lattice2);
	cout << endl << endl;
	print(lattice3);
	
	cout << endl;

	depth = 200;

	cout << "Consistent trinomial tree for short rate\n";
	cout << "How many time divisions: " << endl;
	cin >> depth;
	if (depth <= 0) return 0;


	// Trinomial lattice with matrix entries
	Matrix<double, int> prototype(4,4,1,1);
	Lattice<Matrix<double, int>, int, 3> lattice4(depth, prototype);
	cout << "Number of discrete points at end: " << lattice4.BasePyramidSize() << endl;
	cout << "Total number of nodes: " << lattice4.numberNodes() << endl;

	// Now iterate over the lattice and print the matrix elements
	for (int j = lattice4.MinIndex(); j <= lattice4.MaxIndex(); j++)
	{ // Each indexed j is a vector of matrices

		cout << "Start Level " << j << endl;

		for (int i = lattice4[j].MinIndex(); i <= lattice4[j].MaxIndex(); i++)
		{
			print(lattice4[j][i]);	// This is a matrix
	
		}
		
		cout << "End Level " << j << endl;

			
	}

	return 0;
}
