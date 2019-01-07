// PropertyThing.hpp
//
// Base class for Property. This is an abstract class.
//
// (C) Datasim Education BV 2001-2006
//     

#ifndef PROPERTYTHING_HPP
#define PROPERTYTHING_HPP

#include <string>


template <class Name, class Value>
	class PropertyThing
{

public:
	PropertyThing() {}
	virtual ~PropertyThing() {}
	virtual PropertyThing* Copy() const = 0;

	PropertyThing<Name, Value>& operator = (const PropertyThing<Name, Value>& source) {}

};

#endif