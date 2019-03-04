// Clock.hpp
// 
// Simple class for timing processes, loops
// and general performance tests.
//
// (C) Datasim Education BV 2006
//

#ifndef DatasimClock_HPP
#define DatasimClock_HPP

#include <time.h>
#include <iostream>
using namespace std;

class DatasimClock
{
private:
		clock_t st;	// Start tick
		clock_t fi;	// Finish tick

public:
	DatasimClock() { }

	void start() { st = clock(); }

	void stop() { fi = clock(); }

	double duration() const { return double (fi - st)/CLOCKS_PER_SEC; }

	void print() const
	{
		cout << "Processing time was: ";
		cout << duration() << endl; 
	}

};


#endif