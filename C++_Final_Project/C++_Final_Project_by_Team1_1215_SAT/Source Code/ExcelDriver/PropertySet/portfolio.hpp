// portfolio.hpp
//
// 
// Simple classes to show the rationale of heterogeneous
// property sets.
// 
//
// (C) Datasim Education BV 2004-2006
//
//

#ifndef PORTFOLIO_HPP
#define PORTFOLIO_HPP

#include <iostream.h>

class Portfolio
{ // Base class for all derivative products
public:

		virtual void print() const = 0;

};

class Option: public Portfolio
{
public:

	void print() const
	{ 
		cout << "An option\n";
	}

										
};	

class Bond: public Portfolio
{
public:

	void print() const
	{ 
		cout << "A bond\n";
	}

										
};	

class Swap: public Portfolio
{
public:

	void print() const
	{ 
		cout << "A swap\n";
	}
										
};	

#endif