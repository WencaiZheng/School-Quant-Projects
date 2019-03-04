#pragma once
#ifndef menu_h
#define menu_h

#include <iostream>
#include <fstream>
#include <string>
#include "GetData.h"
#include "Team.h"
#include "ShowData.hpp"
#include "VecOverloading.h"

using namespace std;

void function1();
int function2(const Team& Beat, const Team& Meet, const Team& Miss);
int function3(const ReturnMatrix &TeamReturn);
void function4(const ReturnMatrix &TeamReturn);
int menu(Team& Beat,  Team& Meet,  Team& Miss, Stock& IWB);

#endif
