#include "menu.h"
using namespace std;

int BackMenu()
{
	int d;
	cout << "-----------------------------------------------" << endl
		 << "Continue current menu or back to the main menu?" << endl
		 << "Please enter 1-(continue) or 0-(back to main menu): "; cin >> d;
	if (d != 1 && d != 0)
	{
		cout << "Please enter 1 or 0: " << BackMenu();
	}
	return d;
}


void function1()
{
	cout << "Data Retrived" << endl;
}

int function2(const Team& Beat, const Team &Meet, const Team& Miss)
{
	ShowStockInfo(Beat, Meet, Miss);
	if (BackMenu() == 1) function2(Beat, Meet, Miss);
	else return 0;
}



int function3(const ReturnMatrix &TeamReturn)
{
	
	int b;
	cout << endl
		 << "Please choose a group" <<endl
		 << "1-Beat 2-Meet 3-Miss : "; cin >> b;
	if (b != 1 && b != 2 && b != 3)
	{
		cout << "WARNING: Please enter right number" << endl<<endl;
		function3(TeamReturn);
	}
	else 
	{
		int c;
		if (b == 1)
		{
			cout << "Please choose AAR or CAAR" << endl
				<< "1-AAR 2-CAAR : "; cin >> c;
			if (c != 1 && c != 2)
			{
				cout << "WARNING: Please enter right number" << endl << endl;
				function3(TeamReturn);
			}
			else 
			{
				if (c == 1) cout << TeamReturn[0][0];
				if (c == 2) cout << TeamReturn[0][1];
				if (BackMenu() == 1) function3(TeamReturn);
				else return 0;
			}
		}
		if (b == 2)
		{
			cout << "Please choose AAR or CAAR" << endl
				<< "1-AAR 2-CAAR : "; cin >> c;
			if (c != 1 && c != 2)
			{
				cout << "WARNING: Please enter right number" << endl << endl;
				function3(TeamReturn);
			}
			else
			{
				if (c == 1) cout << TeamReturn[1][0];
				if (c == 2) cout << TeamReturn[1][1];
				if (BackMenu() == 1) function3(TeamReturn);
				else return 0;
			}
		}
		if (b == 3)
		{
			cout << "Please choose AAR or CAAR" << endl
				<< "1-AAR 2-CAAR : "; cin >> c;
			if (c != 1 && c != 2)
			{
				cout << "WARNING: Please enter right number" << endl << endl;
				function3(TeamReturn);
			}
			else
			{
				if (c == 1) cout << TeamReturn[2][0];
				if (c == 2) cout << TeamReturn[2][1];
				if (BackMenu() == 1) function3(TeamReturn);
				else return 0;
			}
		}
	}
}

void function4(const ReturnMatrix &TeamReturn)
{
	ShowGraph(TeamReturn);
}

int menu(Team& Beat, Team& Meet, Team& Miss, Stock& IWB)
{
	cout <<"--------------------------------------------------" << endl
		<< "This menu contains following 5 functions:" << endl
		<< "1-Retrieve historical price data for all stocks" << endl
		<< "2-Pull information for one stock from one group" << endl
		<< "3-Show AAR or CAAR for one group" << endl
		<< "4-Show the Excel graph with CAAR for all 3 groups" << endl
		<< "5-Exit your program" << endl
		<< "--------------------------------------------------" << endl;

	GetIWBPrice(IWB);
	IWB.GenDailyReturn();
	Beat.GenAbnormalReturn(IWB);
	Meet.GenAbnormalReturn(IWB);
	Miss.GenAbnormalReturn(IWB);
	ReturnMatrix TeamReturn;
	GenReturnMatrix(Beat, Meet, Miss, TeamReturn);

	int a;
	cout << "Choose a function:"; cin >> a;
	while (a != 5)
	{
		if (a == 1) function1();
		if (a == 2) function2(Beat, Meet, Miss);
		if (a == 3) function3(TeamReturn);
		if (a == 4) function4(TeamReturn);
		if (a!=1 && a!=2 && a!=3 && a!=4) cout << "WARNING: Please enter a right number" << endl;
		cout << "Choose a function:"; cin >> a;
	}
	cout << "Exit program" << endl;
	return 0;
}

