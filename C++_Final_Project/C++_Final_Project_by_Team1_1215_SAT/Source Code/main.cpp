#include "ShowData.hpp"
#include <iostream>
#include <iostream>
#include <fstream>
#include <string>
#include "GetData.h"
#include "Team.h"
#include "ShowData.h"
#include <thread>
#include "menu.h"

int main()
{
	double starttime, endtime;
	// Generate the Team object
	Team Beat, Meet, Miss;

	// Read Information from txt
	GetTxt(Beat, "Beat.txt");
	GetTxt(Meet, "Meet.txt");
	GetTxt(Miss, "Miss.txt");
	curl_global_init(CURL_GLOBAL_ALL);

	// Get IWB Price data
	Stock IWB("IWB", "2016-02-23", "2018-02-07", "0", "0");
	
	// Get Team Object price
	starttime = clock();
	thread t1{ GetStockPrice, ref(Beat) };
	thread t2{ GetStockPrice, ref(Meet) };
	thread t3{ GetStockPrice, ref(Miss) };
	t1.join(); t2.join(); t3.join();
	endtime = clock();
	cout << "The retrive time is " << (endtime - starttime) / 1000 << " s" << endl;

	menu(Beat, Meet, Miss,IWB);
	system("pause");
	return 0;
}

