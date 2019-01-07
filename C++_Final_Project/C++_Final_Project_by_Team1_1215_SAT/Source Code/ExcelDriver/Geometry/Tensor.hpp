// Tensor.hpp
//
// Tensor class. This is a simple class to model 3-d
// matrices. These are numeric matrices so you can carry
// out math operations.
//
// Note: We model this class as an array of Numeric matrices.
//
// (C) Datasim Component Technology 1999-2004

#ifndef TENSOR_HPP
#define TENSOR_HPP

#include "VectorsAndMatrices\NumericMatrix.cpp"
#include "VectorsAndMatrices\Array.cpp"

// N.B. tensors always use Full Matrices
template <class V, class I>
class Tensor
{
private:

	Array<NumericMatrix <V, I>, I > tensor;

	// Redundant data 
	size_t nr, nc, nt;			// First, second and 3rd dimensions

public:
	// Constructors & destructor
	Tensor();												
	Tensor(size_t rows, size_t columns, size_t third);	// Constructor with size. Start index
	Tensor(size_t rows, size_t columns,size_t third,
		I rowStart, I columnStart, I thirdStart);		
	Tensor(const Tensor<V, I>& source);					// Copy constructor
	virtual ~Tensor();									// Destructor

	// Selectors. Return type should really be I!
	long MinFirstIndex() const;			// Return the minimum index
	long MaxFirstIndex() const;			// Return the maximum index
	long MinSecondIndex() const;			// Return the minimum index
	long MaxSecondIndex() const;			// Return the maximum index
	long MinThirdIndex() const;			// Return the minimum index
	long MaxThirdIndex() const;			// Return the maximum index

	size_t Rows() const;				// The number of rows
	size_t Columns() const;				// The number of columns
	size_t sizeThird() const;			// The number of element in 3rd dim


	// Operators
	NumericMatrix<V,I>& operator [] (I k);		// Get matrix at position k
	const NumericMatrix<V,I>& operator [] (I k) const;		// Get matrix at position k

	V& operator () (I i, I j, I k);				// Get the element at position

	Tensor<V, I>& operator = (const Tensor<V, I>& source);
};


#endif	// Tensor_hpp

