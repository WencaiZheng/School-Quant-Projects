#include"VecOverloading.h"

using namespace std;

ostream &operator<<(ostream &out, const vector<double> &T)
{
	for (int i = 0; i < T.size(); i++)
	{
		out << i - 119 << "  " << T[i] << endl;
	}
	return out;
}

vector<double> operator-(const vector<double> &v1, const vector<double> &v2)
{
	vector<double>DiffReturn;
	int len = v1.size();
	DiffReturn.resize(len);
	if (len == v2.size())
	{
		for (int i = 0; i < len; i++)
		{
			DiffReturn[i] = v1[i] - v2[i];
		}
	}
	return DiffReturn;
}

vector<double> operator+(vector<double>& v1, vector<double>& v2)
{
	vector<double> SumV;
	if (v1.size() == v2.size())
	{
		for (int i = 0; i < v1.size(); i++)
		{
			SumV.push_back(v1[i] + v2[i]);
		}	
	}
	return SumV;
}

vector<double> operator/(vector<double>& v1, int n)
{
	for (int i = 0; i < v1.size(); i++)
		v1[i] /= n;
	return v1;
}

vector<double> &operator*(vector<double>& v1, int n)
{
	for (int i = 0; i < v1.size(); i++)
		v1[i] *= n;
	return v1;
}