#ifndef GetData_h
#define GetData_h

#include <map>
#include <stdio.h>
#include <string> 
#include <iostream>
#include <sstream>  
#include <vector>
#include <iomanip>
#include <fstream>
#include <locale>
#include "Team.h"
#include "curl.h"

using namespace std;

void GetTxt(Team& Category, string file);
int GetStockPrice(Team& Group);
int GetIWBPrice(Stock& IWB);

#endif 
