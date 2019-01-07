#ifndef ShowData_HPP
#define ShowData_HPP
#include "ExcelDriver\excelmechanisms.hpp"
#include "ExcelDriver\VectorsAndMatrices\arraymechanisms.hpp"
#include "ExcelDriver\VectorsAndMatrices\vector.cpp"
#include "ExcelDriver\Geometry\range.cpp"
#include <iostream>
#include "Team.h"
using namespace std;

int ShowStockInfo(const Team& Beat, const Team& Meet, const Team& Miss);
void ShowGraph(const ReturnMatrix &TeamReturn);

#endif