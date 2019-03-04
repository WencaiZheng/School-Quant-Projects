// Instrument.hpp
//
// 
// Simple classes to show the rationale of heterogeneous
// property sets.
// 
//
// (C) Datasim Education BV 2004-2006
//
//

#ifndef Instrument_HPP
#define Instrument_HPP

#include <iostream>
using namespace std;

class Instrument
{ // Base class for all derivative products
public:

		virtual void print() const = 0;

};

class Option: public Instrument
{
public:

	void print() const
	{ 
		cout << "An option\n";
	}

										
};	

class Bond: public Instrument
{
public:

	void print() const
	{ 
		cout << "A bond\n";
	}

										
};	

class Swap: public Instrument
{
public:

	void print() const
	{ 
		cout << "A swap\n";
	}
										
};	

#endif