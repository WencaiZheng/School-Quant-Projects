// SimplePropertySet.cpp
//
// Composite function class
//
//	7 November 2002 DD Kick-of
//	8 December New class
//	10 December 2002 remove() and other list-based functions
//	2002-12-26 DD Set has a name
//	2004-4-26 DD last check
//	2004-6-8 DD implement as a map now
//	2004-7-20 DD optimisitions. more on maps
//	2004-7-21 DD bugs!!
//	2004-7-23 DD Prototype and Visitor
//	2004-8-4 DD rounding off; code review
//	2004-9-7 DD value function (modifier)
//	2004-9-19 DD add(key + value)
//	2004-9-22 DD some methods, return by reference
//  2005-3-27 DD bug soled value()
//
// (C) Datasim Education BV 2002-2004

#ifndef SimplePropertySet_CPP
#define SimplePropertySet_CPP

#include "SimplePropertySet.hpp"

template <class N, class V>
SimplePropertySet<N,V>::SimplePropertySet()
{ // Default constructor

	nam = N();
	sl=map<N,V>();
	keys = Set<N>();
}

template <class N, class V>
SimplePropertySet<N,V>::SimplePropertySet(const N& name)
{ // Named property set

	nam = name;
	sl=map<N,V>();
	keys = Set<N>();
	keys.Insert(name);
}


template <class N, class V>
SimplePropertySet<N,V>::SimplePropertySet(const SimplePropertySet<N,V>& source)
{ // Copy constructor
	
	nam = source.nam;
	sl = source.sl;
	keys = source.keys;
}

template <class N, class V>
SimplePropertySet<N,V>::SimplePropertySet(const N& name, const Set<N>& keySet)
{ // Create a property set from a set of attribute defs
	
	nam = name;
	keys = keySet;

	// Now iterate in the keys and do default constructor
	Set<N>::iterator it;

	for (it = keys.Begin(); it != keys.End(); it++)
	{ 

		add(Property<N,V>(*it, V()));
	}	
}

template <class N, class V>
SimplePropertySet<N,V>::~SimplePropertySet()
{ // Destructor


}

// Iterator functions
template <class N, class V> typename
SimplePropertySet<N,V>::iterator SimplePropertySet<N,V>::Begin()
{ // Return iterator at begin of composite

	return sl.begin();
}

template <class N, class V> typename
SimplePropertySet<N,V>::const_iterator SimplePropertySet<N,V>::Begin() const
{ // Return const iterator at begin of composite

	return sl.begin();
}

template <class N, class V> typename
SimplePropertySet<N,V>::iterator SimplePropertySet<N,V>::End()
{ // Return iterator after end of composite

	return sl.end();
}

template <class N, class V> typename
SimplePropertySet<N,V>::const_iterator SimplePropertySet<N,V>::End() const
{ // Return const iterator after end of composite

	return sl.end();
}

// Selectors
template <class N, class V>
int SimplePropertySet<N,V>::Size() const
{ // Return the number of functions in the composite

	return keys.Size();
}

template <class N, class V>
	N SimplePropertySet<N,V>::operator ()() const
{ // The name of the property set

		return nam;
}

template <class N, class V>
	N SimplePropertySet<N,V>::name() const
{ // The name of the property set

		return nam;
}

template <class N, class V>
Set<N>& SimplePropertySet<N,V>::definingSet() const
{ // Set of keys

	return keys;
}


template <class N, class V>
	bool SimplePropertySet<N,V>::hasProperty(const N& n) const
{ // Is the property in the list?


	return keys.Contains(n);

}


// Modifiers
template <class N, class V>
	void SimplePropertySet<N,V>::operator () (const N& name)
{

		nam = name;
}

template <class N, class V>
void SimplePropertySet<N,V>::ClearAll()
{	// Remove all its properties

	sl = map<N,V>();
}

template <class N, class V>
	V SimplePropertySet<N,V>::value(const N& name) const
{

	// NO exception handling
	// if (hasProperty(name) == false)
		//return V();

	// ;( Sledgehammer, use find!!
	// We iterate over the list until we find the value
	map<N,V>::const_iterator it;

	for (it=sl.begin(); it!=sl.end(); it++)
	{ 

		if ((*it).first == name)
		{
			return (*it).second;
		}
	} 

//	return sl[name];

}

template <class N, class V>
void SimplePropertySet<N,V>::value(const N& name, const V& value) 
{	// Change value of Property, key 'name'
	
	// NO exception handling
	if (hasProperty(name) == false)
		return;

	// ;( Sledgehammer
	// We iterate over the list until we find the value
	map<N,V>::iterator it;

	for (it=sl.begin(); it!=sl.end(); it++)
	{ 

		if ((*it).first == name)
		{
			(*it).second = value;
		}
	}
}

template <class N, class V>
void SimplePropertySet<N,V>::value(const Property<N,V>& scf)
{

	value(scf.name(), scf());
}



// Add functions
template <class N, class V>
void SimplePropertySet<N,V>::add(const N& key, const V& value)
{ // Add a key+value pair to the list


	pair<N,V> tmp;
	tmp.first = key;
	tmp.second = value;

	sl.insert(tmp);	// Add el. with name + value

	// Update the key set
	keys.Insert(key);
}

template <class N, class V>
void SimplePropertySet<N,V>::add(const Property<N, V>& pr)
{ // Add a key+value pair to the list


	pair<N,V> tmp;
	tmp.first = pr.name();
	tmp.second = pr();

	sl.insert(tmp);	// Add el. with name + value

	// Update the key set
	keys.Insert(tmp.first);
}

template <class N, class V>
	void SimplePropertySet<N,V>::remove(const N& key)
{ // Remove all elements with 'key' O(1)


	sl.erase(key);
}

	
template <class N, class V>
	void SimplePropertySet<N,V>::remove(const Property<N, V>& prop)
{ // Remove the given property

	remove(prop.name());
}

		
// Operators
template <class N, class V>
	SimplePropertySet<N,V>& SimplePropertySet<N,V>::operator = (const SimplePropertySet<N,V>& source)
{ // Assignment

	// Exit if same object
	if (this==&source) return *this;


	nam = source.nam;
	sl = source.sl;
	keys = source.keys;

	return *this;
}

template <class N, class V>  
PropertyThing<N,V>* SimplePropertySet<N, V>::Copy() const 
{

	return new SimplePropertySet(*this);
}

/*
template <class N, class V>  
void SimplePropertySet<N,V>::accept(PropertyThingVisitor<N,V>& pv) 
{

	pv.Visit(*this);
}

*/

#endif