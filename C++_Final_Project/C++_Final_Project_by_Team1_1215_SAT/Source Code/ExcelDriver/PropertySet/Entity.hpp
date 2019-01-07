// Entity.hpp
//
// Template classes for entities and their related classes
// (e.g. the categories to which they belong).
// 
// The main classes are:
//
//		0. Property classes (list of attribute/value pairs)
//		0. Function classes (encapsulation of C functions)
//		1. EntityThing (base class fo all entities)
//		2. EntityCategory (entities grouped into a certain category)
//		3. Entity (building block class for all future products)
//
// An entity is a set of attribute properties than can be modified and queried.
// Furthermore, it it possible to execute 'dynamic' commands on the entities.
//
// (C) Datasim Education BV 2001-2004
//     

#ifndef Entity_HPP
#define Entity_HPP


// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// Base class for all kinds of entities. An EntityThing contains the following data:
//
//			1. The name of the entity (typically an ID)
//			2. Its current list of properties (e.g. such as a description)
//

template <class Name, class Value> class EntityThing
{
private:


public:
	EntityThing();
	EntityThing(const Name& t);
	EntityThing(const EntityThing<Name,Value>& source); 
		
	virtual ~EntityThing();
 
	// The defining structure and behaviour of entites. Notice
	// that these are public 'objects' and that we can use the 
	// member functions of the corresponding template classes.
	// Thus, there is no need to reproduce member functions.

	Property<Name, Value> name;					// The ID of the entity
	SimplePropertySet<Name, Value> properties;	// The properties in the Entity


	////////////////////////////////////////////////////////////////////////////////////


	// Add property and property seet
	virtual void AddProperty(const Property<Name, Value>& prop);
	virtual void AddProperty(const SimplePropertySet<Name, Value>& prop_set);


	/////////////////////////////////////////////////////////////////////////////////////

	// Copy on heap (Prototype) 
	virtual EntityThing<Name,Value>* Clone() const = 0;

	// Assignment operator 
	EntityThing<Name,Value>& operator = (const EntityThing<Name,Value>& source);


};


// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// Class representing categories of entities. Such categories contain the following data:
//
//		1. The possible container entity category
//		2. A list of subcategories (as a sequential linked list)
//
// The above two relationships are realisations of unary relationships in UML.
//

template <class Name, class  class Value> class EntityCategory : public EntityThing<Name,Value>
{ 
private:


public:
	// Constructors and destructor
	EntityCategory();
	EntityCategory(const Name& ename);
	EntityCategory(const EntityCategory<Name,Value>& source); 
		
	virtual ~EntityCategory();
 	

	// Copy on heap
	virtual EntityThing<Name,Value>* Clone() const;

	// Assignment operator 
	EntityCategory<Name,Value>& operator = (const EntityCategory<Name,Value>& source);


};


// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// A class representing specfic entities. An entity contains the following data:
//
//			1. A pointer to its corresponding category
//

template <class Name, class  class Value> class Entity : public EntityThing<Name,Value>
{
private:

	EntityCategory<Name,Value>* cat;		// The category to which the Entity belongs

public:
	// Constructors and destructor
	Entity();
	Entity(const Name& ename);
	Entity(const Entity<Name,Value>& source); 
		
	virtual ~Entity();
 
	// Set and get operations
	void category(EntityCategory<Name,Value>& caty);
	EntityCategory<Name,Value>* category();

	// Copy on heap
	virtual EntityThing<Name,Value>* Clone() const;


	// Assignment operator 
	Entity<Name,Value>& operator = (const Entity<Name,Value>& source);


};



#endif // Entity_HPP


