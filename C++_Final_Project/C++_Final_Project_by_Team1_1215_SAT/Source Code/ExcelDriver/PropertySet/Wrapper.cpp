// Wrapper.cpp
//
// Class for use in heterogeneous data types.
// Notice that type are generic, so classes are built for you.
//
// Version 1 (i.e. minimal functionality).
//
// (C) Datasim Education BV 2006
//

#ifndef AnyType_CPP
#define AnyType_CPP

#include "SimplePropertySet.cpp"
#include <typeinfo.h>

class AnyType 
{ // Base class for all wrapped types

public:
	AnyType() {}
};

template <class T> class Wrapper : public AnyType
{ // Generic wrapper for any data type
private:
		T obj;

public:
	Wrapper() { obj = T();}

	Wrapper(T wrappedObject) { obj = wrappedObject;}

	// Need to know if current type is same as another type
	// This is a template member function
	template <class T2>
			bool sameType (const T2& t2)
	{
		
		if (typeid(Wrapper<T>) == typeid(t2))
		{
			
			return true;
		}

		return false;
	}

};


#endif
