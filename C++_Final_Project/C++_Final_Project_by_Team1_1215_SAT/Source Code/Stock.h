#ifndef Stock_h
#define Stock_h

#include <string>
#include <vector>
#include <iostream>
#include "VecOverloading.h"


using namespace std;
class Stock
{
private:
	string StartTime;
	string EndTime;
	string Ticker;
	string Est_EPS;
	string Act_EPS;
public:
	vector<string> Date;
	vector<double> Price;
	vector<double> DailyReturn;
	vector<double> AbnormalReturn;
	Stock() :Ticker("0"), StartTime("0"), EndTime("0"), Act_EPS("0"), Est_EPS("0") {}
	Stock(string ticker, string startdate, string enddate, string act_eps, string est_eps)
		:Ticker(ticker), StartTime(startdate), EndTime(enddate), Act_EPS(act_eps), Est_EPS(est_eps) {}
    ~Stock() {}
	string GetTicker() const;
	string GetStartTime() const;
	string GetEndTime() const;
	string GetEstEps() const;
	string GetActEps() const;
	void printInfo() const;
	void GenDailyReturn();
	void GenAbnormalReturn(Stock& IWB);
};


#endif
