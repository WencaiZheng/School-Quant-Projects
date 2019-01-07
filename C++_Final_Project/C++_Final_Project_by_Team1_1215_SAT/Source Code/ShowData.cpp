#include"ShowData.hpp"

using namespace std;
int ShowStockInfo(const Team& Beat, const Team& Meet, const Team& Miss)
{
	string sticker;
	cout << "Enter the ticker: "; cin >> sticker;

	map<string, Stock>::const_iterator itr1 = Beat.StockList.find(sticker);
	if (itr1 != Beat.StockList.end())
	{
		cout << "The basic information of Stock " << itr1->second.GetTicker() << " is: " << endl;
		cout << "Est EPS: " << itr1->second.GetEstEps() << endl;
		cout << "Act EPS: " << itr1->second.GetActEps() << endl;
		cout << "The stock you chose belongs to group Beat" << endl;
		cout << "Start Time: " << itr1->second.GetStartTime() << endl;
		cout << "End Time: " << itr1->second.GetEndTime() << endl;
		system("pause");
		itr1->second.printInfo();
		return 0;
	}

	map<string, Stock>::const_iterator itr2 = Meet.StockList.find(sticker);
	if (itr2 != Meet.StockList.end())
	{
		cout << "The basic information of Stock " << itr2->second.GetTicker() << " is: " << endl;
		cout << "Est EPS: " << itr2->second.GetEstEps() << endl;
		cout << "Act EPS: " << itr2->second.GetActEps() << endl;
		cout << "The stock you chose belongs to group Meet" << endl;
		cout << "Start Time: " << itr2->second.GetStartTime() << endl;
		cout << "End Time: " << itr2->second.GetEndTime() << endl;
		system("pause");
		itr2->second.printInfo();
		return 0;
	}

	map<string, Stock>::const_iterator itr3 = Miss.StockList.find(sticker);
	if (itr3 != Miss.StockList.end())
	{
		cout << "The basic information of Stock " << itr3->second.GetTicker() << " is: " << endl;
		cout << "Est EPS: " << itr3->second.GetEstEps() << endl;
		cout << "Act EPS: " << itr3->second.GetActEps() << endl;
		cout << "The stock you chose belongs to group Miss" << endl;
		cout << "Start Time: " << itr3->second.GetStartTime() << endl;
		cout << "End Time: " << itr3->second.GetEndTime() << endl;
		system("pause");
		itr3->second.printInfo();
		return 0;

	}

	cout << "WARNING:It is an invalid ticker.Please enter a valid ticker." << endl;
	return 0;


}
void ShowGraph(const ReturnMatrix &TeamReturn)
{
	Vector<double, long>x1(240);
	Vector<double, long>y1(240);
	Vector<double, long>y2(240);
	Vector<double, long>y3(240);
	x1[x1.MinIndex()] = -120.0;

	for (long i = x1.MinIndex() + 1; i <= x1.MaxIndex(); i++)
	{
		x1[i] = x1[i - 1] + 1;
	}

	for (long i = y1.MinIndex(); i <= y1.MaxIndex(); i++)
	{
		y1[i] = TeamReturn[0][1][i-1];
		y2[i] = TeamReturn[1][1][i-1];
		y3[i] = TeamReturn[2][1][i-1];
	}

	list<string> labels;
	list<Vector<double, long>> y;
	labels.push_back("Beat");
	labels.push_back("Meet");
	labels.push_back("Miss");

	y.push_back(y1);
	y.push_back(y2);
	y.push_back(y3);
	printInExcel(x1, labels, y, "CAAR", "T", "CAAR");
}