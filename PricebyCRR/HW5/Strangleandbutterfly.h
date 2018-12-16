#pragma once
#ifndef Strangleandbutterfly_h
#define Strangleandbutterfly_h
#include "Options06.h"
class Strangle : public EurOption
{
private:
	double K1; //parameter 1
	double K2; //parameter 2
public:
	int GetInputData();
	double Payoff(double z);
};
class Butterfly : public EurOption
{
private:
	double K1; //parameter 1
	double K2; //parameter 2
public:
	int GetInputData();
	double Payoff(double z);
};
#endif
