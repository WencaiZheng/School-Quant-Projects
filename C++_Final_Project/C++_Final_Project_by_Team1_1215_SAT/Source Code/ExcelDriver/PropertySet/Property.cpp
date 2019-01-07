// property.cpp
//
// Base class for Properties
//
// Last modification dates:
//
//	2001-6-18 DD Modifications to previously defined classes
//	2001-7-2 DD Compiler directives
//	2002-12-7 DD bug fix
//	2003-8-1 DD new constructor with just a Value
//	2004-4-26 DD l'ultima modificazione, last checks
//	2004-7-20 DD optimisations and operators !=
//	2004-7-23 DD Prototype and Visitor
//	2004-8-4 DD Minor changes
//	2004-8-7 DD operators +=, -= and *= for numeric V
//  2006-8-8 DD numeric operators removed
//
// (C) Datasim Education BV 2001-2006


#ifndef PROPERTY_CPP
#define PROPERTY_CPP

#include "property.hpp"

// Constructors and destructor
template <class Name, class Value> 
Property< Name,  Value>::Property()
{// Default constructor

	nam = Name();
	con = Value();
}

template <class Name, class Value> 
Property< Name,  Value>::Property(const Name& name)
{// Constructor  

	nam = name;
	con = Value();
}


template <class Name, class Value> 
Property< Name,  Value>::Property(const Name& name, const Value& t)
{// Constructor  

	nam = name;
	con = t;
}

template <class Name, class Value> 
Property< Name,  Value>::Property(const Property<Name, Value>& source) 
{// Copy-constructor

	nam = source.nam;
	con = source.con;
}

template <class Name, class Value> 
Property< Name,  Value>::~Property()
{// Destructor

}

template <class Name, class Value>  
Property< Name,  Value>& Property<Name, Value>::operator = (const Property<Name, Value>& source)
{// Assignment operator 

	if (this == &source)
		return *this;

	nam = source.nam;
	con = source.con;

	return *this;
}
/*
// Arithmetic operations on properties (shortcuts). Mostly on
// properties that already exist
template <class Name, class Value>  
	Property<Name, Value>& Property<Name, Value>::operator += (const Value& value)
{

	con = con + value;

	return *this;
}

template <class Name, class Value>  
	Property<Name, Value>& Property<Name, Value>::operator *= (const Value& value)
{

	con = con * value;

	return *this;
}

template <class Name, class Value>  
	Property<Name, Value>& Property<Name, Value>::operator -= (const Value& value)
{

	con = con - value;

	return *this;
}
*/
template <class Name, class Value>  
PropertyThing<Name, Value>* Property<Name, Value>::Copy() const 
{

	return new Property(*this);
}
/*
template <class Name, class Value>  
void Property<Name, Value>::accept(PropertyThingVisitor<Name, Value>& pv) 
{

	pv.Visit(*this);
}
*/

		
// Accessing function operators
template <class Name, class Value> Value Property<Name, Value>::operator()() const
{

		return con;

}

template <class Name, class Value> void Property<Name, Value>::operator()(const Value& t)
{

		con = t;

}

template <class Name, class Value> Name Property<Name, Value>::name() const
{

	return nam;
}



template <class Name, class Value> bool Property<Name, Value>:: operator == (const Property<Name, Value>& prop2)
{

		if (nam == prop2.name())
			return true;

		return false;

}

template <class Name, class Value> bool Property<Name, Value>:: operator != (const Property<Name, Value>& prop2)
{

		if (*this == source)
			return false;

		retun true;

}

#endif // PROPERTY_CPP




