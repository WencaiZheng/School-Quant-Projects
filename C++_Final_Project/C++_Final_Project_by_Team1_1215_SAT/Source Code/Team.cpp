#include "Team.h"
#include <numeric>
#include <time.h>
#include <algorithm>
#include <numeric>

using namespace std;


void Team::GenAbnormalReturn(Stock& IWB)
{
	for (map<string, Stock>::iterator itr = StockList.begin(); itr != StockList.end(); itr++)
	{
		itr->second.GenDailyReturn();
		itr->second.GenAbnormalReturn(IWB);
	}

}

void Team::RandSelect()
{
	AAR.resize(240);
	Team SampleList;// use SampleList to store sample information 
	srand(time(NULL));
	for (int t = 0; t < 5; t++)
	{
		random_shuffle(Ticker.begin(), Ticker.end());
		for (unsigned int i = 0; i < 100; i++)
		{
			SampleList.StockList.insert(pair<string, Stock>(Ticker[i], StockList[Ticker[i]]));
		}
		SampleList.GenAAR();//AAR of SampleList stores the AAR of each sample, is changing after every sample
		AAR = (AAR * t) / (t + 1) + SampleList.AAR / (t + 1);//Beat/Miss/Meet.AAR stores the AAR of five samples
		SampleList.StockList.clear();//clear SampleList and get ready for the next sample
	}
	GenCAAR();
}

void Team::GenAAR()
{
	AAR.resize(240);
	for (int i = 0; i < 240; ++i)
	{
		map<string, Stock>::iterator itr = StockList.begin();
		double sum = 0;
		for (int j = 0; j <= 99; ++j)
		{
			sum = sum * j / (j + 1) + itr->second.AbnormalReturn[i] / (j + 1);
			itr++;
		}// get average of all stocks' AR in a certain day
		AAR[i] = sum;
	}


}

void Team::GenCAAR()
{
	CAAR.resize(240);
	if (AAR.empty() == 1)
	{
		cout << "Error: AAR is empty" << endl;
		return;
	}

	double sum = 0;
	for (int i = 0; i < 240; i++)
	{
		sum = sum + AAR[i];
		CAAR[i] = sum;
	}
}

void GenReturnMatrix(Team &Beat, Team &Meet, Team&Miss, ReturnMatrix &TeamReturn)
{
	TeamReturn.resize(3);
	for (int n = 0; n <= 2; n++)
	{
		TeamReturn[n].resize(2);
		for (int i = 0; i <= 1; i++)
		{
			TeamReturn[n][i].resize(240);
		}
	}//TeamReturn initialization
	Team ThreeGroup[3] = { Beat,Meet,Miss };
	
	
	for (int i = 0; i < 3; i++)
	{
		ThreeGroup[i].RandSelect();
		TeamReturn[i][0].assign(ThreeGroup[i].AAR.begin(), ThreeGroup[i].AAR.end());
		TeamReturn[i][1].assign(ThreeGroup[i].CAAR.begin(), ThreeGroup[i].CAAR.end());
	}


}
