// Relation.cpp
//
// Generic classes that model N:N, N:1 and 1:1
// relationships. These classes have a myriad of
// applications.
//
//	Last modification dates:
//
//	DD 2004-5-8 Kick-off
//	DD 2004-5-20 Programming the methods in class
//	DD 2004-5-23 removed 2 functions (now in mechanisms)
//	DD 2004-7-4 Review + some more functions
//	DD 2004-8-19 Inverse multimap
//			- constructor changes
//			- inverse iterators
//			- use of template member functions
//			- adding and removeing elements (2 hours)
//
// (C) Datasim Education BV 2004
//

#ifndef Relation_cpp
#define Relation_cpp

#include "relation.hpp"

/*
// Private functions
template <class X, class Y> void removeElements(Relation<X,Y>& rel, const Y& y)
{
	// Remove all domain elements in X that correspond to a given range element y
	// Iterate over relation until we come to a second element named y

	// Simple but understandable solution
	multimap<X,Y>::const_iterator it;


	for (it = rel.f.begin(); it != rel.f.end(); it++)
	{

		if ((*it).second == y)
		{
			delete it;	// Good????????????????
		}
	}

}

*/

// Essential members
template <class D, class R> 
Relation<D,R>::Relation()	
{

	s1 = Set<D>();
	s2 = Set<R>();
	f = multimap<D,R>();
	finv = multimap<R, D>();

}


template <class D, class R> Relation<D,R>::Relation (const Set<D>& domainSet, const Set<R>& rangeSet)
{
	s1 = domainSet;
	s2 = rangeSet;
	f = multimap<D,R>();
	finv = multimap<R, D>();

}

template <class D, class R> 
Relation<D,R>::Relation(const Relation& r2)
{

	s1 = r2.s1;
	s2 = r2.s2;
	f = r2.f;
	finv = r2.finv;
}

template <class D, class R> 
Relation<D,R>::~Relation()
{

}

template <class D, class R> 
Relation<D,R>& Relation<D,R>::operator = (const Relation<D,R>& r2)
{
	if (this == &r2)
		return *this;

	s1 = r2.s1;
	s2 = r2.s2;
	f = r2.f;
	finv = r2.finv;


	return *this;

}


// Building and breaking the Relation
// The set element in the relations
template <class D, class R> 
void Relation<D,R>::addDomainElement(const D& d)
{

	s1.Insert(d);
}


template <class D, class R> 
void Relation<D,R>::addRangeElement(const R& r)
{

	s2.Insert(r);
}


template <class D, class R> 
void Relation<D,R>::removeDomainElement(const D& d)
{
	// Remove all references to Domain element d ??
	f.erase(d);

	// Remove all references in inverse map

	multimap<R, D>::iterator it, it2;

	it2 = finv.begin();
	it = it2;

L1:
	{
		if ((*it).second == d)
		{
			it2 = finv.erase(it);	
			it = it2;
		}
		else
		{
			it++;
		}

		if (it != finv.end())
			goto L1;

	}


	s1.Remove(d);

}

template <class D, class R> 
void Relation<D,R>::removeRangeElement(const R& r)
{
	// Remove all references to Range element r
	finv.erase(r);
	
	// Remove all references in forward map
	multimap<D,R>::iterator it, it2;

	it2 = f.begin();
	it = it2;
L1:
	{
		if ((*it).second == r)
		{
			it2 = f.erase(it);	
			it = it2;
		}
		else
		{
			it++;
		}

		if (it != f.end())
			goto L1;

	}

	s2.Remove(r);

}

// Define relationship between elements
template <class D, class R> 
void Relation<D,R>::addRelation(const D& d, const R& r)
{
	// Prec: d and r must be in the sets
	if (s1.Contains(d) == false)
		return;
	if (s2.Contains(r) == false)
		return;

	// Add a link between d and r
	pair<D, R> p;
	p.first = d;
	p.second = r;
	f.insert(p);

	// Add a link between r and d
	pair<R, D> pinv;
	pinv.first = r;
	pinv.second = d;
	finv.insert(pinv);

}

template <class D, class R> 
void Relation<D,R>::removeRelation(const D& d)
{

	// Remove link between d and ALL r ??
	f.erase(d);
}


template <class D, class R> 
void Relation<D,R>::ClearAll()
{ // Break all links and set elements

	f.erase(f.begin(), f.end());
	finv.erase(finv.begin(), finv.end());
	s1.Clear();
	s2.Clear();
}

template <class D, class R> 
void Relation<D,R>::ClearLinks()
{ // Break all links

	f.erase(f.begin(), f.end());
	finv.erase(finv.begin(), finv.end());

}

// Selectors
template <class D, class R> 
const Set<D>& Relation<D,R>::DomainSet()
{
	return s1;
}

template <class D, class R> 
const Set<R>& Relation<D,R>::RangeSet()
{
	return s2;
}

template <class D, class R> 
	Set<R> Relation<D,R>::range(const D& d)
{ // Set of r for a d

	Set<R> result;

	// Simple but understandable solution
	multimap<D,R>::const_iterator it;

	for (it = f.begin(); it != f.end(); it++)
	{
		cout << "*" << (*it).first << (*it).second;

		if ((*it).first == d)
		{
			result.Insert((*it).second);
		}
	}

	return result;
}



template <class D, class R> 
	Set<D> Relation<D,R>::domain(const R& r)
{ // Set of d for an r

	Set<D> result;

	multimap<R, D>::const_iterator it;


	for (it = finv.begin(); it != finv.end(); it++)
	{
		if ((*it).first == r)
		{
			result.Insert((*it).second);
		}
	}

	return result;
}

template <class D, class R> 
bool Relation<D,R>::inDomain(const D& d) const
{ // Is an element in domain?

	return s1.Contains(d);
}

template <class D, class R> 
bool Relation<D,R>::inRange(const D& r) const
{ // Is an element in range?

	return s2.Contains(r);

}


// Iterator functions	
template <class D, class R> typename
	Relation<D,R>::iterator Relation<D,R>::Begin()		
{ // Return iterator at begin of relation

	return f.begin();
}

template <class D, class R> typename
	Relation<D,R>::const_iterator Relation<D,R>::Begin() const	
{ // Return const iterator at begin of relation

	return f.begin();

}

template <class D, class R> typename
	Relation<D,R>::iterator Relation<D,R>::End()
{ // Return iterator after end of relation

	return f.end();

}

template <class D, class R> typename
	Relation<D,R>::const_iterator Relation<D,R>::End() const		
{ // Return const iterator after end of relation

	return f.end();

}

// Iterator functions(Inverse)
template <class D, class R> typename
	Relation<D,R>::iteratorInv Relation<D,R>::BeginInv()		
{ // Return iterator at begin of relation

	return finv.begin();
}

template <class D, class R> typename
	Relation<D,R>::const_iteratorInv Relation<D,R>::BeginInv() const	
{ // Return const iterator at begin of relation

	return finv.begin();

}

template <class D, class R> typename
	Relation<D,R>::iteratorInv Relation<D,R>::EndInv()
{ // Return iterator after end of relation

	return finv.end();

}

template <class D, class R> typename
	Relation<D,R>::const_iteratorInv Relation<D,R>::EndInv() const		
{ // Return const iterator after end of relation

	return finv.end();

}


#endif

