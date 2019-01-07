// tesSet1.cpp
//
// Testing Set class.
//
// (C) Datasim Education BV 2004
//

#include <iostream>
#include <string>
using namespace std;

#include "Set.cpp"


template <class T> void print(const Set<T>& l, const string& name)
{  // Print the contents of a Set. Notice the presence of a constant iterator.
	
	cout << endl << name << ", size of set is " << l.Size() << "\n[ ";

	set<T>::const_iterator i;

	for (i = l.Begin(); i != l.End(); ++i)
	{
			cout << *i << " ";

	}

	cout << "]\n";
}

template <class T> void printSet(const Set<pair<T, T> >& l, const string& name)
{  // Print the contents of a Set. Notice the presence of a constant iterator.
	
	cout << endl << name << ", size of set is " << l.Size() << "\n[ ";

	set<pair<T, T> >::const_iterator i;

	for (i = l.Begin(); i != l.End(); ++i)
	{
			cout << (*i).first << ", " << (*i).second << endl;

	}

	cout << "]\n";
}

int main()
{
	Set<int> first;				// Default constructor

	// Only unique (new elements) added
	first.Insert(1);
	first.Insert(2);
	first.Insert(3);
	print (first, "First set");

	Set<char> s1;
	s1.Insert('A');
	s1.Insert('B');
	s1.Insert('C');
	s1.Insert('D');
	s1.Insert('F');
	print (s1, "s1");

	Set<char> s2;
	s2.Insert('0');
	s2.Insert('A');
	s2.Insert('B');
	s2.Insert('C');
	s2.Insert('D');
	//s2.Insert('E');
	s2+'E';
	s2.Insert('H');
	s2.Replace('H', 'G');
	print (s2, "s2");
	s2.Remove('G');
	print (s2, "s2");

	Set<char> ws;		// Work space

	ws = s1 + s2;
	print(ws, "Union");

	ws = s1 ^ s2;
	print(ws, "Intersection");

	ws = s1 - s2;
	print(ws, "Difference s1 - s2");

	ws = s2 - s1;
	print(ws, "Difference s2 - s1");


	ws = s1 % s2;
	print(ws, "Symmetric Difference");

	// Subset/superset stuff
	Set<char> s3;
	s3.Insert('A');
	s3.Insert('B');
	s3.Insert('C');
	s3.Insert('D');

	if (s3.Subset(s1) == true)
		cout << "Yes, is subset OK\n";
	else
		cout << "Bah1\n";

	if (s1.Superset(s3) == true)
		cout << "Yes, is superset OK\n";
	else
		cout << "Bah1\n";

	if (s1.Intersects(s3) == true)
		cout << "Yes, we have intersection OK\n";
	else
		cout << "Bah1\n";

	Set<char> s4;
	if (s1.Intersects(s4) == false)
		cout << "Yes, we have NO intersection OK\n";
	else
		cout << "Bah1\n";

	s4.Insert('A');
	if (s1.Intersects(s4) == true)
		cout << "Yes, we have intersection OK\n";
	else
		cout << "Bah1\n";

	// Sets from lists
	list<char> myList;
	myList.push_back('A');
	myList.push_back('B');
	myList.push_back('C');
	myList.push_back('C');
	myList.push_back('C');
	myList.push_back('D');
	myList.push_back('D');
	myList.push_back('D');
	myList.push_back('D');
	myList.push_back('A');
	myList.push_back('A');
	myList.push_back('A');
	myList.push_back('A');
	myList.push_back('A');

	Set<char> s5(myList);
	print(s5, "Filtered set");


	if (s5.Contains('A') == true)
		cout << "OK, contains A\n";
	else 
		cout << "Bah\n";

	if (s5.Contains('Z') == false)
		cout << "OK, contains NOT Z\n";
	else 
		cout << "Bah\n";

	// Cartesian product
	Set<int> s11;
	s11.Insert(2);
	s11.Insert(3);

	Set<int> s12;
	s12.Insert(8);
	s12.Insert(9);

	Set<pair <int, int> > S = s11.CartesianProduct(s12);
	printSet(S, "Pr");

	Set<pair <int, int> > S2 = s12.CartesianProduct(s11);
	printSet(S2, "Pr");

	return 0;
}
