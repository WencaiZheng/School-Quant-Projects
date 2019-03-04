// testRelation.cpp
//
// Testing Relation class. This can be seen as a UNIVERSAL
// MEDIATOR.
//
// (C) Datasim Education BV 2004-2006
//

#include <iostream>
#include <string>
using namespace std;

#include "relation.cpp"

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

template <class D, class R>
	void print(const Relation<D,R>& r)
{
	Relation<D,R>::const_iterator i = r.Begin();

	while (i != r.End())
	{ 
			cout << "[" << (*i).first << "," << (*i).second << "]";
			i++;
	}
	
	cout << endl;

}

int main()
{

	Set<char> s1;
	s1.Insert('A');
	s1.Insert('B');
	s1.Insert('C');
	s1.Insert('D');
	s1.Insert('F');
	
	Set<char> s2;
	s2.Insert('X');
	s2.Insert('Y');
	s2.Insert('Z');
	s2.Insert('N');	// Prof. N

	Relation<char, char> r(s1, s2);

	r.addRelation('A', 'X');
	r.addRelation('A', 'D'); // will not be inserted
	r.addRelation('A', 'D');
	r.addRelation('A', 'Y');
	r.addRelation('B', 'X');
	r.addRelation('B', 'X');
	r.addRelation('B', 'X');
	r.addRelation('B', 'X');
	r.addRelation('B', 'X'); // Does not delete
	r.addRelation('C', 'Y');
	r.addRelation('B', 'Z');
	r.addRelation('B', 'X');
	r.addRelation('F', 'N');
	r.addRelation('A', 'N');


	print(r);

	cout << "Delete X\n";

//	r.removeRangeElement('X');
	print(r);

	cout << "Delete B\n";

//	r.removeDomainElement('B');
//	print(r);

	cout << "Delete A\n";

//	r.removeDomainElement('A');
//	print(r);

	// December 12 2005
	Set<char> answer = r.range('A');
	print(answer, string("Range Extraction"));

L1:

	cout << "1. Forward search 2. Backward Search ";
	int k; cin >> k;
	if (k == 0) return 0;

	cout << "String Name: ";
	char ch; cin >> ch;

	if (k == 1)
	{
	
		print(answer, string("Range Extraction")+ch);
		answer = r.range(ch);

	}
	else
	{
	
		print(answer, string("Range Extraction")+ch);
		answer = r.domain(ch);
	}

	goto L1;

	return 0;
}
