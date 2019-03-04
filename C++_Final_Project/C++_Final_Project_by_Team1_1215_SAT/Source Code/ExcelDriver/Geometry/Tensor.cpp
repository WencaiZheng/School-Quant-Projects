// Tensor.cpp
//
// Tensor class. It uses an TensorStructure for the actual storage.
// This class acts like a kind of adapter class since it defines a common interface
// for different Tensor structures like normal matrices and sparse matrices.
// The Tensor structure to use is given as template argument.
//
// 1 februari 1999	RD	Started
// 2002-4-9 DD small changes
//
// 2004-3-12 DD Metamorphosis, a matrix becomes a tensor
// 2004-4-8 DD Code review, look for nasty little errors that make us so
// unhappy
//
// (C) Datasim Component Technology 1999-2004

#ifndef TENSOR_CPP
#define TENSOR_CPP

#include "Tensor.hpp"


// Constructors & destructor
template <class V, class I>
Tensor<V, I>::Tensor()
{ // Default constructor

	tensor = Array<NumericMatrix <V, I>, I > (1, 1);	// Size 1, start index 1
	tensor[1] = NumericMatrix<V, I> (1, 1, 1, 1);	// EVERYTHING starts at 1


	nr = nc = nt = 1;
}

template <class V, class I>
Tensor<V, I>::Tensor(size_t row, size_t column, size_t nthird)
{ // Constructor with size. Start index=1.

	tensor = Array<NumericMatrix <V, I>, I > (nthird, 1);	// Size nthird, start index 1

	for (I k = tensor.MinIndex(); k <= tensor.MaxIndex(); k++)
	{
		tensor[k] = NumericMatrix<V, I> (row, column, 1, 1);	
	}


	nr = row; nc = column; nt = nthird;
}

template <class V, class I>
Tensor<V, I>::Tensor(size_t row, size_t column, size_t nthird,
							I rowStart, I columnStart, I thirdStart)
{ // Constructor with size & start index

	tensor = Array<NumericMatrix <V, I>, I > (nthird, thirdStart);	// Size nthird, start index 

	for (I k = tensor.MinIndex(); k <= tensor.MaxIndex(); k++)
	{
		tensor[k] = NumericMatrix<V, I> (row, column, rowStart, columnStart);	
	}


	nr = row; nc = column; nt = nthird;
}

template <class V, class I>
Tensor<V, I>::Tensor(const Tensor<V, I>& source)
{ // Copy constructor

	tensor = source.tensor;

	nr = source.nr; nc = source.nc; nt = source.nt;
}

template <class V, class I>
Tensor<V, I>::~Tensor()
{ // Destructor
}

template <class V, class I>
long Tensor<V, I>::MinFirstIndex() const
{ 

	return tensor[tensor.MinIndex()].MinRowIndex();

}

template <class V, class I>
long Tensor<V, I>::MaxFirstIndex() const
{ 

	return tensor[tensor.MinIndex()].MaxRowIndex();

}
template <class V, class I>
long Tensor<V, I>::MinSecondIndex() const
{ 

	return tensor[tensor.MinIndex()].MinColumnIndex();

}

template <class V, class I>
long Tensor<V, I>::MaxSecondIndex() const
{ 

	return tensor[tensor.MinIndex()].MaxColumnIndex();

}
template <class V, class I>
long Tensor<V, I>::MinThirdIndex() const
{ // The number of rows

	return tensor.MinIndex();

}

template <class V, class I>
long Tensor<V, I>::MaxThirdIndex() const
{ // Return the maximum index

	return tensor.MaxIndex();

}

template <class V, class I>
size_t Tensor<V, I>::Rows() const
{ // The number of rows

	return nr;
}

template <class V, class I>
size_t Tensor<V, I>::Columns() const
{ // The number of columns

	return nc;
}

template <class V, class I>
size_t Tensor<V, I>::sizeThird() const
{ // The number of columns

	return nt;
}

template <class V, class I>
NumericMatrix<V,I>& Tensor<V, I>::operator [] (I k) 
{ // Get matrix at position k

	return tensor[k];

}



template <class V, class I>
const NumericMatrix<V,I>& Tensor<V, I>::operator [] (I k) const
{ // Get matrix at position k

	return tensor[k];

}

// Operators

template <class V, class I>
	V& Tensor<V, I>::operator () (I i, I j, I k) 
{ // Get the element at position

	
	return tensor[k] (i, j);
}



template <class V, class I>
Tensor<V, I>& Tensor<V, I>::operator = (const Tensor<V, I>& source)
{ // Assignment operator

	// Exit if same object
	if (this==&source) return *this;

	tensor = source.tensor;

	nr = source.nr; nc = source.nc; nt = source.nt;


	return *this;
}


#endif	// Tensor_cpp
