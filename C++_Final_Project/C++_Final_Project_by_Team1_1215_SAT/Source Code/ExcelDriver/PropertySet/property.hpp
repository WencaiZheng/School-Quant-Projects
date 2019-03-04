// property.hpp
//
// Class for Properties == name/value pairs. This is a concrete class.
// A property is a name-value pair and it can be used in 
// many kinds of applications.
//
// The default Value for the name is 'string' and the default
// value Value is 'double'. You use it in the following way:
//
//		Property<> myDefaultProperty
//
// (C) Datasim Education BV 2001-2004
//     

#ifndef PROPERTY_HPP
#define PROPERTY_HPP

#include "propertything.hpp"

#include <string>

template <class Name = string, class Value = double> class Property : public PropertyThing<Name, Value>
{
private:

	Name nam;
	Value con;

public:
	// Constructors and destructor
	Property();
	Property(const Name& name);
	Property(const Name& name, const Value& t);
	Property(const Property<Name, Value>& source); 
		
	virtual ~Property();
 	
	
	// Accessing function operators
	// Get and set the value of the Property
	virtual Value operator()() const;
	virtual void operator()(const Value& t);

	// Get the name of the property
	virtual Name name() const;

	Property<Name, Value>& operator = (const Property<Name, Value>& source);
	PropertyThing<Name, Value>* Copy() const;

	
	// True if names are the same
	bool operator == (const Property<Name, Value>& prop2); //Iff keys are the same
	bool operator != (const Property<Name, Value>& source);

	//void accept(PropertyThingVisitor<Name, Value>& pv);

};

#endif // PROPERTY_HPP


