// Entity.cpp
//
// Template classes for entities and their related classes
// (e.g. the categories to which they belong).
// 
// The main classes are:
//
//		0. Property classes (std::list of attribute/value pairs), used by entity classes
//		1. EntityThing (base class for all entities) 
//		2. EntityCategory (entities grouped into a certain category) 
//		3. Entity (building block class for all future products)
//
// Last modification dates:
//
//	2001-6-22 DD Kick-off code Implementation of the entity classes
//	2001-6-23 DD Fill in code for methods (got the stuff compiled)
//	2001-6-25 DD Review session
//	2001-6-26 DD Tricky pointer stuff resolved; accept() function for Visitor
//	2001-6-30 DD Possibility to add dynamic methods (Command pattern). We now have the 
//	basis for our own components, introspection, reflection etc. etc.
//	2001-7-2 DD remove main program and changed Property<Field, Value> --> Property<Name, Value>
//	2001-8-14 DD remove command pattern stuff at this level.
//	2002-12-23 DD Property sets and Commands
//	2003-6-7 DD execute() function() signature drastically changed
//	2004-4-26 DD Stripped down value for CD
//
// (C) Datasim Education BV 2001-2004
//     

#ifndef Entity_CPP
#define Entity_CPP

#include "entity.hpp"
#include <math.h>

// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// Base class for all kinds of entities. An EntityThing contains the following data:
//
//			1. The name of the entity (typically an ID) 
//			2. Its current std::list of properties (e.g. such as a description) 
//


template <class Name, class Value>	 EntityThing<Name, Value>::EntityThing() 
{

		name = Name();
		properties = SimplePropertySet<Name, Value> ();
}

template <class Name, class Value>	 EntityThing<Name, Value>::EntityThing(const Name& t) 
{ 

		name = t;
		properties = SimplePropertySet<Name, Value> ();
}

template <class Name, class Value>  EntityThing<Name, Value>::EntityThing(const EntityThing<Name, Value>& source) 
{ 

		name = source.name;
		properties = source.properties;
} 
		
template <class Name, class Value> EntityThing<Name, Value>::~EntityThing() 
{   


}
 
////////////////////////////////////////////////////////////////////////////////////




// Add property and property seet
template <class Name, class Value> void EntityThing<Name, Value>::AddProperty(const Property<Name, Value>& prop)
{

	properties.add(prop);
}


template <class Name, class Value> void EntityThing<Name, Value>::AddProperty(const SimplePropertySet<Name, Value>& prop_set)
{
	properties.add(prop_set);
}




// Assignment operator 
template <class Name, class Value> EntityThing<Name, Value>&  EntityThing<Name, Value>::operator = (const EntityThing<Name, Value>& source) 
{   

	if (this == &source)
		return *this;

	name = source.name;
	properties = source.properties;
}

// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// Class representing categories of entities. Such categories contain the following data:
//
//		1. The possible container entity category
//		2. A std::list of subcategories (as a sequential linked std::list) 
//
// The above two relationships are realisations of unary relationships in UML.
//


// Constructors and destructor
template <class Name, class Value> EntityCategory<Name, Value>::EntityCategory()  : EntityThing<Name, Value>()
{   


}

template <class Name, class Value> EntityCategory<Name, Value>::EntityCategory(const Name& ename) : EntityThing<Name, Value>(ename)
{  


}

template <class Name, class Value> EntityCategory<Name, Value>::EntityCategory(const EntityCategory<Name, Value>& source) : EntityThing<Name, Value>(source)
{   


} 
		
template <class Name, class Value>  EntityCategory<Name, Value>::~EntityCategory() 
{   

}
 	




// Copy on heap
template <class Name, class Value> EntityThing<Name, Value>*  EntityCategory<Name, Value>::Clone() const 
{   

	return new EntityCategory(*this);

}


// Assignment operator 
template <class Name, class Value> EntityCategory<Name, Value>&  EntityCategory<Name, Value>::operator = (const EntityCategory<Name, Value>& source) 
{   

	if (this == &source)
		return (*this);

	EntityThing<Name, Value>::operator = (source);


	return (*this);
}



// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// A class representing specfic entities. An entity contains the following data:
//
//			1. A pointer to its corresponding category
//


// Constructors and destructor
template <class Name, class Value> Entity<Name, Value>::Entity() : EntityThing<Name, Value> ()
{   

	cat = 0;
}

template <class Name, class Value> Entity<Name, Value>::Entity(const Name& ename) : EntityThing<Name, Value> (ename) 
{   

	cat = 0;

}

template <class Name, class Value> Entity<Name, Value>::Entity(const Entity<Name, Value>& source) : EntityThing<Name, Value> (source)
{   
	cat = source.cat;
} 
		
template <class Name, class Value> Entity<Name, Value>::~Entity()
{   

}
 
// Set and get operations
template <class Name, class Value> void Entity<Name, Value>::category(EntityCategory<Name, Value>& caty) 
{   
	cat = &caty;
}

template <class Name, class Value> EntityCategory<Name, Value>* Entity<Name, Value>::category() 
{
	return cat;
}


// Copy on heap
template <class Name, class Value> EntityThing<Name, Value>* Entity<Name, Value>::Clone() const
{   
	return new Entity(*this);
}


// Assignment operator 
template <class Name, class Value> Entity<Name, Value>& Entity<Name, Value>::operator = (const Entity<Name, Value>& source) 
{   

	if (this == &source)
		return (*this);

	EntityThing<Name, Value>::operator = (source);

	cat = source.cat;

	return (*this);
}


#endif