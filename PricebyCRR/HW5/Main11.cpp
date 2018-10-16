#include "BinModel02.h"
#include "Options06.h"
#include "DoubDigitOpt.h"
#include"Strangleandbutterfly.h"
#include <iostream>
#include <cmath>
using namespace std;
int main()
{
	BinModel Model;
	if (Model.GetInputData() == 1)
		return 1;
	Call Option1;
	Option1.GetInputData();
	cout << "European call option price = " << Option1.PriceByCRR(Model) << endl << endl;

	Put Option2;
	Option2.GetInputData();
	cout << "European put option price = " << Option2.PriceByCRR(Model) << endl << endl;
	DoubDigitOpt Option3;
	Option3.GetInputData();
	cout << "European double-digital option price = " << Option3.PriceByCRR(Model) << endl << endl;
	Strangle Option4;
	Option4.GetInputData();
	cout << "European Strangle option price = " << Option4.PriceByCRR(Model) << endl << endl;
	Butterfly Option5;
	Option5.GetInputData();
	cout << "European Butterfly option price = " << Option5.PriceByCRR(Model) << endl << endl;
	system("PAUSE");
	return 0;
}
/*Result
Enter S0: 106
Enter U:  0.1525
Enter D:  -0.13138
Enter R:   0.00545

Input data checked
There is no arbitrage

Enter call option data:
Enter steps to expiry N: 8
Enter strike price K:    100

European call option price = 21.7726

Enter put option data:
Enter steps to expiry N: 8
Enter strike price K:    100

European put option price = 11.5176

Enter double-digital option data:
Enter steps to expiry N: 8
Enter parameter K1:      100
Enter parameter K2:      110

European double-digital option price = 0.260448

Enter Strangle data:
Enter steps to expiry N: 8
Enter parameter K1:      100
Enter parameter K2:      110

European Strangle option price = 28.4991

Enter Butterfly option data:
Enter steps to expiry N: 8
Enter parameter K1:      100
Enter parameter K2:      110

European Butterfly option price = 0.921831

Press any key to continue . . .
*/