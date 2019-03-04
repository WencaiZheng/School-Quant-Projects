// PropertyThing.cpp
//
// Base class for Property. This is an abstract class.
//
// Last modification dates:
//
//	2004-8-9 DD Initial code here (minimal at moment)
//  2006-8-8 DD clean up 
//
// (C) Datasim Education BV 2001-2006
//     

#ifndef PROPERTYTHING_CPP
#define PROPERTYTHING_CPP

#include "PropertyThing.hpp"

template <class Name, class Value>
PropertyThing<Name, Value>::PropertyThing()
{

}

template <class Name, class Value>
PropertyThing<Name, Value>& PropertyThing<Name, Value>::operator = (const PropertyThing<Name, Value>& source)
{

}


template <class Name, class Value>
PropertyThing<Name, Value>::~PropertyThing()
{

}


#endif