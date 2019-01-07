// TestWrapper.cpp
//
// Testing heterogeneous properties
//
// (C) Datasim Education BV 2006
//


#include "datasimdate.hpp" // Dates and other useful stuff
#include "datetime.hpp"
#include <string> // Standard string class in C++
#include "Wrapper.cpp"
#include "SimplePropertySet.cpp"
using namespace std;

class Person
{
public: // Everything public, for convenience only

		// Data
		Wrapper<string> nam;					// Name of person
		Wrapper<DatasimDate> dob;				// Date of birth

		Wrapper<DatasimDate> createdD;			// Internal, when object was created

		SimplePropertySet<string, AnyType*> props;

public:
		Person (const string& name, const DatasimDate& DateofBirth)
		{
			nam = name;
			dob = DateofBirth;
			createdD = DatasimDate();	// default, today REALLY!

			// Now add this stuff into the property set
			props = SimplePropertySet<string, AnyType*>();
			props.add(string("Name"), &nam);
			props.add(string("DOB"), &dob);
			props.add(string("CreatedDate"), &createdD);

		}

		void print() const
		{ // Who am I?
			
			cout << "\n** Person Data **\n";
		
			SimplePropertySet<string, AnyType*>::const_iterator it;

			for (it = props.Begin(); it != props.End(); it++)
			{

				cout << "Key " << it ->first << endl;
				
				// No value printed because we lack polymorphism in 
				// general

			}
		}

};


int main()
{

	DatasimDate myBirthday(29, 8, 1952);
	string myName ("Daniel J. Duffy");
	Person dd(myName, myBirthday);
	dd.print();

	DatasimDate bBirthday(06, 8, 1994);
	string bName ("Brendan Duffy");
	Person bd(bName, bBirthday);
	bd.print();
	

	Wrapper<string> w1;
	Wrapper<string> w2;
	if (w1.sameType(w2) == true)
	{
		cout << "Same type\n";
	}
	else
	{
		cout << "Not Same type\n";
	}

	return 0;
}
