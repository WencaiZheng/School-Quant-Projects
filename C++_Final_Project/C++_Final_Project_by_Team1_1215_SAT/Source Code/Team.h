#ifndef Team_h
#define Team_h
#include "Stock.h"
#include <map>
#include "VecOverloading.h"

typedef vector<vector<vector<double>>> ReturnMatrix;

using namespace std;
class Team
{
public:
	map<string, Stock> StockList;
	vector<string> Ticker;
	vector<double> AAR;
	vector<double> CAAR;
	Team() {}
	Team(map<string, Stock> StockList_, vector<string> Ticker_, vector<double> AAR_, vector<double> CAAR_)
		:StockList(StockList_), Ticker(Ticker), AAR(AAR_), CAAR(CAAR_) {}
	~Team() {}

	void GenAbnormalReturn(Stock& IWB);
	void GenAAR();
	void GenCAAR();
	void RandSelect();
};

void GenReturnMatrix(Team &Beat, Team &Meet, Team&Miss, ReturnMatrix &TeamReturn);

#endif

