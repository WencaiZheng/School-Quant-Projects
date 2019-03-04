// testTelephoneBook.cpp
//
// Testing Relation class. This is an extensive test
// and it builds up a telephone book of names (string)
// and numbers (int).
//
// (C) Datasim Education BV 2004
//

#include <iostream>
#include <string>
using namespace std;

#include "relation.cpp"

template <class D, class R>
	void print(const Relation<D,R>& r)
{
	cout << "Display of the relation \n";
	Relation<D,R>::const_iterator i = r.Begin();

	while (i != r.End())
	{ 
			cout << "Element pair [" << (*i).first << "," << (*i).second << "]\n";
			i++;
	}
}

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
int main()
{

	// Set of People
	Set<string> people;
	people.Insert("Daniel");
	people.Insert("Ilona");
	people.Insert("Brendan");
	people.Insert("Mieke");
	people.Insert("Boris");
	
	// Set of telephone numbers
	Set<int> numbers;
	numbers.Insert(6240055);
	numbers.Insert(5669667);
	numbers.Insert(4200075);
		
	Relation<string, int> r(people, numbers);
	print(r);

	r.addRelation("Daniel", 5669667);
	r.addRelation("Daniel", 6240055);
	r.addRelation("Daniel", 4200075);
	r.addRelation("Ilona", 5669667);
	r.addRelation("Ilona", 6240055);
	r.addRelation("Brendan", 5669667);

	// Non-existing
	r.addRelation("Santa Claus", 5669667);
	r.addRelation("Daniel", 11111111);

	print(r);

	r.addDomainElement("Santa Claus");
	r.addRangeElement(11111111);

	r.addRelation("Santa Claus", 5669667);
	r.addRelation("Daniel", 11111111);

	print(r);

//	r.removeDomainElement("Daniel");
//	r.removeRangeElement(5669667);
	print(r);

//	r.removeRelation("Santa Claus", 5669667);
//	r.removeRelation("Daniel", 11111111);

//	r.removeRelation("Daniel");
//	r.removeRelation("Ilona");

	print(r);

	r.ClearLinks();
	cout << "Links now cleared\n";
	print(r);
	r.ClearAll();
	print (r.DomainSet(), "Domain Set");
	print (r.RangeSet(), "Range Set");

	r.addRelation("Daniel", 5669667);
	r.addRelation("Daniel", 6240055);
	r.addRelation("Daniel", 4200075);
	r.addRelation("Ilona", 5669667);
	r.addRelation("Ilona", 6240055);
	r.addRelation("Brendan", 5669667);

	cout << "Next set of tests\n";

	print(r);

	Set<int> s1 = r.range("Ilona");
	print(s1, "telehphone numbers");

	Set<string> s2 = r.domain(5669667);
	print(s2, "names");


	return 0;
}
