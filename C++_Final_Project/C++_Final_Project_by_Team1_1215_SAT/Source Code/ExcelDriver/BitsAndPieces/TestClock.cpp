// TestClock.cpp
//
// (C) Datasim Education BV 2006
//

#include "clock.hpp"
#include <iostream>
using namespace std;

int main()
{

	DatasimClock myClock;

	myClock.start();

	for (int i = 1; i <= 10000077700; i++) { ;}

	myClock.stop();

	cout << myClock.duration() << endl;

	return 0;
}
