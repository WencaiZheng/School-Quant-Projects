// TestHeteroProperty.cpp
//
// Testing heterogeneous properties
//
// (C) Datasim Education BV 2006
//
//

#include <string> // Standard string class in C++
#include "Instrument.hpp" 
#include "SimplePropertySet.cpp"
using namespace std;

int main()
{
	SimplePropertySet<string, Instrument*> myPortfolio;

	// Create a number of specific instruments and add to portfolio
	Option myOpt;
	Bond myBond;
	Swap mySwap;

	// Now add components to PSet
	myPortfolio.add(string("O"), &myOpt);
	myPortfolio.add(string("B"), &myBond);
	myPortfolio.add(string("S"), &mySwap);

	
	// Print out the PSet
	SimplePropertySet<string, Instrument*>::const_iterator it;

	for (it = myPortfolio.Begin(); it != myPortfolio.End(); it++)
	{
		std::string tmp = it->first;
		cout << tmp.c_str() << ", ";
		(it->second)->print(); cout << endl;
	}

	return 0;
}
