// SimplePropertySet.hpp
//
// Class that represents a list of named properties. This is simply a list of
// Property objects. Each property is a name/value pair.
// This kind of structure occurs in many applications, for example relational
// database theory.
//
// For larger lists we could consider using maps instead of lists bacause of
//
//		Performance (random access)
//		Unique keys are in map (with a list the client must do this)
//
// (C) Datasim Education BV 2002-2004

#ifndef SimplePropertySet_hpp
#define SimplePropertySet_hpp

#include "property.cpp"
#include <map>
#include <string>

#include "..\DataStructures\Set.cpp"

using namespace std;


template <class N = string, class V = double> class SimplePropertySet 
		: public PropertyThing<N, V>
{
private:

	N nam;		// The name of the set

	// The SimplePropertySet list using the STL map
	map<N, V> sl;
	Set<N> keys;


public:
	// User can use the STL iterator
	typedef typename map<N, V>::iterator iterator;
	typedef typename map<N, V>::const_iterator const_iterator;

	// Constructors and destructor
	SimplePropertySet();		// Default constructor
	SimplePropertySet(const N& name);		// Named property set
	SimplePropertySet(const SimplePropertySet<N,V>& source);	// Copy constructor
	SimplePropertySet(const N& name, const Set<N>& keySet);	// From a set

	virtual ~SimplePropertySet();	// Destructor

	// Iterator functions
    iterator Begin();			// Return iterator at begin of composite
	const_iterator Begin() const;// Return const iterator at begin of composite
	iterator End();				// Return iterator after end of composite
    const_iterator End() const;	// Return const iterator after end of composite

	// Selectors
	int Size() const;				// The number of properties in the list
	N operator ()() const;			// The name of the property set
	N name() const;			// Ditto: name of pset
	Set<N>& definingSet() const;		// Set of keys
	bool hasProperty(const N& search_name) const;	// Is the property in the list?
	V value(const N& name) const;	// Property value based on a name

	// Modifiers
	void operator () (const N& name);		// Change the name of the property set
	void value(const N& name, const V& value);	// Change value of Property, key 'name'
	void value(const Property<N, V>& prop);

	void ClearAll();						// Remove all its properties

	// Add and remove functions (sort of mixin or embedded inheritance)
	void add(const Property<N,V>& p); 
	void add(const N& key, const V& value); 
	//	void add(const SimplePropertySet<N,V>& source); 

	void remove(const N& key);		// Remove all elements with 'key' O(1)
	void remove(const Property<N, V>& prop);	// Remove the given property


	// Operators
	SimplePropertySet<N,V>& operator = (const SimplePropertySet<N,V>& source);

	// Prototype pattern
	PropertyThing<N,V>* Copy() const;

	// Delegation to Visitor pattern
//	void accept(PropertyThingVisitor<N,V>& pv);


};

#endif	// SimplePropertySet_hpp
