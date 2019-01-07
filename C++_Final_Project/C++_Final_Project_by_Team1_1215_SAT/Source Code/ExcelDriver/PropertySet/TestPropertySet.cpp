// TestpropertySet.cpp
//
// Testing properties and Sets. In this case we do the following:
//
//		1. Create properties for an European option
//		2. Create some entities in a Category 'Option'
//		3. Create a EntityThingComposite and add entities to it
//		4. Print them using a Visitor
//
// (C) Datasim Education BV 2001-2004
// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

#include "simplepropertyset.cpp"
#include <iostream>
using namespace std;

void print(const SimplePropertySet<string,double>& pset)
{

	SimplePropertySet<string,double>::const_iterator it;
	
	cout << "\nPrinting Unique option\n";

	for (it= pset.Begin(); it!=pset.End(); it++)
	{ 
	
			cout << (*it).first << ", " << (*it).second << endl;
	}
}

int main()
{
	
	// The properties
	SimplePropertySet<string,double> myDefaultSet;
	
	// My property set that is default for my European option class
	// You can customise this to suit your own needs and wants

	Property<string, double> r;		// Interest rate
	Property<string, double> sig;	// Volatility
	Property<string, double> K;		// Strike price
	Property<string, double> T;		// Expiry date
	Property<string, double> U;		// Current underlying price (e.g. stock, forward)
	Property<string, double> b;		// Cost of carry


	r = Property<string, double> ("Interest rate", 0.08);
	sig= Property<string, double> ("Volatility",0.30);
	K = Property<string, double>("Strike Price", 65.0);
	T = Property<string, double>("Expiry date", 0.25);
	U = Property<string, double>("Underlying Asset", 60.0);		
	b = Property<string, double>("Cost of carry rate", r());	

	myDefaultSet.add(r);
	myDefaultSet.add(sig);
	myDefaultSet.add(K);
	myDefaultSet.add(T);
	myDefaultSet.add(U);
	myDefaultSet.add(b);

	// Create another set
	SimplePropertySet<string,double> mySet2(myDefaultSet);
	mySet2.value("Volatility", 0.20);
	mySet2.value("Expiry date", 1.0);

	// Print these Psets
	print(myDefaultSet);
	print(mySet2);

	

	// Now create a set of property names and test if
	// the option contains these names
	set<string> controller;			

	// Only unique (new elements) added
	controller.insert("Interest rate");
	controller.insert("Volatility");
	controller.insert("Strike Price");
	controller.insert("Expiry date");
	controller.insert("Underlying Asset");		
	controller.insert("Cost of carry rate");

	set<string>::const_iterator i;

	cout << endl << "Size of set is " << controller.size() << endl;




	return 0;
	
}
