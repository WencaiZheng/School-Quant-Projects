#include <iostream>
#include <string>
#include "Stock.h"

void Stock::GenDailyReturn()
{
	int len = Price.size();//241
	DailyReturn.resize(len - 1);
	for (int i = 0; i < len - 1; i++)
	{
		DailyReturn[i] = (Price[i + 1] - Price[i]) / Price[i];
	}
}

void Stock::GenAbnormalReturn(Stock& IWB)
{
	vector<double>IWBDailyReturnCut;
	for (int i = 0; i < IWB.Date.size(); i++)
	{
		if (StartTime.compare(IWB.Date[i]) == 0)
		{
			for (int j = 0; j < 240; j++)
			{
				IWBDailyReturnCut.push_back(IWB.DailyReturn[i + j]);
			}
			break;
		}
	}
	// calculate abnormal return 
	AbnormalReturn = DailyReturn - IWBDailyReturnCut;
}

string Stock::GetTicker() const
{
	return Ticker;
}

string Stock::GetStartTime() const
{
	return StartTime;
}

string Stock::GetEndTime() const
{
	return EndTime;
}

string Stock::GetEstEps() const
{
	return Est_EPS;
}

string Stock::GetActEps() const
{
	return Act_EPS;
}

void Stock::printInfo() const
{
	for (int i = 0; i < Price.size(); i++)
	{
		cout << Date[i] << '\t' << Price[i] << '\n';
	}

}