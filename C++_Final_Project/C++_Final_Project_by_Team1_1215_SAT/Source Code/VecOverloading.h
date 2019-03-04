#pragma once
#ifndef VecOverloading_h
#define VecOverloading_h
#include <vector>
#include <fstream>
#include <iostream>
#include <map>
#include "Stock.h"
using namespace std;
ostream &operator<<(ostream &out, const vector<double> &T);
vector<double> operator-(const vector<double> &v1, const vector<double> &v2);
vector<double> operator+(vector<double>& v1, vector<double>& v2);
vector<double> operator/(vector<double>& v1, int n);
vector<double> &operator*(vector<double>& v1, int n);
#endif // VecOverloading_h