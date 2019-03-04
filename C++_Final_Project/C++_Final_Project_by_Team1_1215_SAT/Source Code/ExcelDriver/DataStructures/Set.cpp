// Set.cpp
//
// C++ template class that implements the concept of
// a mathematical set.
// This class is composed of an STL set and uses Information
// Hiding.
//
//	Last modification dates:
//
//	2004-5-14 DD kick-off code (spec)
//	2004-5-15 DD Code for member functions
//	2004-5-20 DD Programmed Cartesian Product
//	2004-7-4 DD Review of code
//	2004-7-4 DD Cartesian product whose domain and range
//	are in different spaces (using template member functions!)
//	2004-9-14 DD Insert another set (union)
//
// (C) Datasim Education BV 2004

#ifndef Set_CPP
#define Set_CPP

#include <algorithm>
#include "set.hpp"


// Constructors
template <class V>
Set<V>::Set()
{ // Empty set
	
	s = set<V>();
}

template <class V>
Set<V>::Set(const set<V>& stlSet)
{ // Empty set
	
	s = stlSet;
}

template <class V>
Set<V>::Set(const Set<V>& s2)
{ // Copy constructor

	s = set<V>(s2.s);
}


// Construct a set from V that has STL-compatible iterators
template <class V>
Set<V>::Set(const list<V>& con)
{ // From am STL container (list, vector)

	s = set<V>();
	
	// Create list iterator
	list<V>::const_iterator i;
	
	// Print every character in the list
	for (i = con.begin(); i != con.end(); ++i)
	{
			s.insert(*i);		// Will only be inserted once
	}
}

template <class V>
Set<V> Set<V>::operator = (const Set<V>& s2)
{

	if (this == &s2)
		return *this;

	s = s2.s;

	return *this;
}

template <class V>
Set<V>::~Set()
{

}

// Standard set operations from High School
template <class V>
Set<V> Intersection(const Set<V>& s1, const Set<V>& s2)
{
	set<V> myintersect;
	set<V>::iterator i = myintersect.begin();
	insert_iterator<set<V> > insertiter(myintersect, i);
	set_intersection(s1.s.begin(), s1.s.end(), s2.s.begin(), s2.s.end(), insertiter);

	return Set<V>(myintersect);

}

template <class V>
Set<V> Set<V>::operator ^ (const Set<V>& s2)
{ // Intersection

	return Intersection(*this, s2);
}


template <class V>
Set<V> Union(const Set<V>& s1, const Set<V>& s2)
{
	set<V> myunion;
	set<V>::iterator i = myunion.begin();
	insert_iterator<set<V> > insertiter(myunion, i);
	set_union(s1.s.begin(), s1.s.end(), s2.s.begin(), s2.s.end(), insertiter);

	return Set<V>(myunion);

}


template <class V>
Set<V> Set<V>::operator + (const Set<V>& s2)
{ // Union

	return Union(*this, s2);

}


template <class V>
Set<V> Difference(const Set<V>& s1, const Set<V>& s2)
{
	set<V> mydiff;
	set<V>::iterator i = mydiff.begin();
	insert_iterator<set<V> > insertiter(mydiff, i);
	set_difference(s1.s.begin(), s1.s.end(), s2.s.begin(), s2.s.end(), insertiter);

	return Set<V>(mydiff);

}


template <class V>
Set<V> Set<V>::operator - (const Set<V>& s2)
{ // Difference

	return Difference(*this, s2);

}


template <class V>
Set<V> SymmetricDifference(const Set<V>& s1, const Set<V>& s2)
{
	set<V> mysdiff;
	set<V>::iterator i = mysdiff.begin();
	insert_iterator<set<V> > insertiter(mysdiff, i);
	set_symmetric_difference(s1.s.begin(), s1.s.end(), s2.s.begin(), s2.s.end(), insertiter);

	return Set<V>(mysdiff);
}

template <class V>
Set<V> Set<V>::operator % (const Set<V>& s2)
{ // Symmetric Difference

	return SymmetricDifference(*this, s2);

}

template <class V> typename
Set<V>::iterator Set<V>::Begin()
{ // Return iterator at begin of set

	return s.begin();
}

template <class V> typename
Set<V>::const_iterator Set<V>::Begin() const
{ // Return const iterator at begin of set

	return s.begin();

}

template <class V> typename
Set<V>::iterator Set<V>::End()
{ // Return iterator after end of set

	return s.end();

}

template <class V> typename
Set<V>::const_iterator Set<V>::End() const
{ // Return const iterator after end of set

	return s.end();

}


// Operations on a single set
template <class V>
long Set<V>::Size() const
{ // Number of elements	

	return s.size();
}


template <class V>
void Set<V>::Insert(const V& v)
{ // Insert an element

	s.insert(v);
}

template <class V>
void Set<V>::Insert(const Set<V>& mySet)
{ // Insert another set

	// Test this
	set<V>::iterator i = s.begin();
	insert_iterator<set<V> > insertiter(s, i);
	set_union(s.begin(), s.end(), mySet.s.begin(), mySet.s.end(), insertiter);

}

template <class V>
void Set<V>::Remove(const V& v)
{ // Remove an element

	s.erase(v);
}

template <class V>
void Set<V>::Replace(const V& Old, const V& New)
{ // Replace old by new

	s.erase(Old);
	s.insert(New);
}

template <class V>
void Set<V>::Clear()
{ // Remove all elements

	s.clear();
}

template <class V>
bool Set<V>::Contains(const V& v) const
{ // Is v in set?


	const_iterator it = s.find(v);

	if (it == s.end())
		return false;

	return true;
}

template <class V>
bool Set<V>::Empty() const
{ // Contains no elements


	return s.empty();
}


// Using 'clever' operators
template <class V>
void Set<V>::operator + (const V& v)
{ // Insert an element

	s.insert(v);
}

template <class V>
void Set<V>::operator - (const V& v)
{ // Remove an element

	s.remove(v);
}


// Relations between sets (s1 == *this)
template <class V>
bool Set<V>::Subset(const Set<V>& s2) const
{ // This a subset of s2?

	return includes(s2.s.begin(), s2.s.end(), (*this).s.begin(), (*this).s.end());


}

template <class V>
bool Set<V>::Superset(const Set<V>& s2) const
{ // this a superset of s2?

	return s2.Subset(*this);

}

template <class V>
bool Set<V>::Intersects(const Set<V>& s2) const
{ // s1 and s2 have common elements?

	if (Empty() == true || s2.Empty() == true)
		return false;

	set<V>::const_iterator iter;

	for (iter = s.begin(); iter != s.end(); iter++)
	{
		if (s2.Contains((*iter)) == true)
		{
			return true;
		}
	}

	return false;
}

#endif
