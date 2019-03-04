// arraymechanisms.hpp
//
// Sets of functions for common vector and matrix manipulation. These
// are useful utility functions.
//
// Categories:
//
//			Sums and averages of vectors
//			Mean, median, std, variance
//			Maximum/minimum values associated with vectors
//			Inner products, norms of vectors and matrices
//			Comparing vectors
//			Converting between STL vector and (Datasim) Vector
//			Simple (but useful) print functions
//
// (C) Datasim Education BV 2003-2005

#ifndef ArrayMechanisms_hpp
#define ArrayMechanisms_hpp

#include "..\PropertySet\SimplePropertySet.cpp"
#include "..\Geometry\range.cpp"
#include "..\Geometry\tensor.cpp"

///////////////////////////////////////////////////////////////////////////////////////////////
// Sums and averages
template <class V, class I> V sum(const Vector<V,I>& x); // Sum of elements
template <class V, class I> V product(const Vector<V,I>& x); // Product of elements
template <class V, class I> V sumReciprocals(const Vector<V,I>& x); // Sum of reciprocals
template <class V, class I> V sumAbsoluteValues(const Vector<V,I>& x); // Sum of absolute values


// Mean value == sum() / N 
template <class V, class I> V mean(const Vector<V,I>& x); 

// Weighted arithmetic mean
template <class V, class I> V weightedArithMean(const Vector<V,I>& x, const Vector<V,I>& w); 

// Geometric mean or geometric average 
template <class V, class I> V geometricMean(const Vector<V,I>& x); 

// Harmonic mean
template <class V, class I> V harmonicMean(const Vector<V,I>& x); 

// Root mean square (RMS)
template <class V, class I> V quadraticMean(const Vector<V,I>& x); 

// Sum of squares
template <class V, class I> V sumSquares(const Vector<V,I>& x);

// A function returning all of the above values in one foul swoop (performance)
template <class V, class I> SimplePropertySet<string, double> allAverages(const Vector<V,I>& x);


////////////////////////////////////////////////////////////////////////////////////////////////


// Measures of Dispersion

template <class V, class I> V deviationFromMean(const Vector<V,I>& x);
template <class V, class I> V standardDeviation(const Vector<V,I>& x);
template <class V, class I> V variance(const Vector<V,I>& x);

// A function returning all of the above values in one foul swoop (performance)
template <class V, class I> SimplePropertySet<string, double> allDispersions(const Vector<V,I>& x);

////////////////////////////////////////////////////////////////////////////////////////////////


// Moments, Skewness and Kurtosis

// The rth moment
template <class V, class I> V rthMoment(const Vector<V,I>& x, const I& r);

// The rth moment about the Mean m(r)
template <class V, class I> V rthMomentMean(const Vector<V,I>& x, const I& r);
template <class V, class I> V rthMomentMean(const Vector<V,I>& x, const Vector<V,I>& freq,
											const I& r);

// The rth moment about an origin A
template <class V, class I> V rthMoment(const Vector<V,I>& x, const I& r, const V& A);

// The rth moment about an origin A and with frequencies of each element in vector
template <class V, class I> V rthMoment(const Vector<V,I>& x, const Vector<V,I>& freq, 
										const I& r, const V& A);

// Mode: either the middle element or the mean of the two middle elements 
template <class V, class I> V median(const Vector<V,I>& x);

// Number of occurrences of value d in vector x
template <class V, class I> I occurs(const Vector<V,I>& x, const V& d);

// The element in x that occurs with the greatest frequency
template <class V, class I> V mode(const Vector<V,I>& x);

template <class V, class I> V skewness(const Vector<V,I>& x);


////////////////////////////////////////////////////////////////////////////////////////////////////

// Extremum operations on vectors

template <class V, class I> V maxValue(const Vector<V,I>& x);
template <class V, class I> V minValue(const Vector<V,I>& x);

// Max and min of the absolute values
template <class V, class I> V maxAbsValue(const Vector<V,I>& x);
template <class V, class I> V minAbsValue(const Vector<V,I>& x);

// Index of max and min values 
template <class V, class I> I indexMaxValue(const Vector<V,I>& x);
template <class V, class I> V indexMinValue(const Vector<V,I>& x);

template <class V, class I> I indexMaxAbsValue(const Vector<V,I>& x);
template <class V, class I> V indexMinAbsValue(const Vector<V,I>& x);

// Vector-vector extremum (difference of two vectors)
template <class V, class I> V maxValue(const Vector<V,I>& vectorA, const Vector<V,I>& vectorB);
template <class V, class I> V minValue(const Vector<V,I>& vectorA, const Vector<V,I>& vectorB);

template <class V, class I> V maxAbsValue(const Vector<V,I>& vectorA, const Vector<V,I>& vectorB);
template <class V, class I> V minAbsValue(const Vector<V,I>& vectorA, const Vector<V,I>& vectorB);

///////////////////////////////////////////////////////////////////////////////////////////////////////

// Vector and matrix norms

template <class V, class I> V innerProduct(const Vector<V,I>& vectorA, const Vector<V,I>& vectorB);
template <class V, class I> V l1Norm(const Vector<V,I>& x);
template <class V, class I> V l2Norm(const Vector<V,I>& x);		// Euclidean norm
template <class V, class I> V lpNorm(const Vector<V,I>& x, const I& p);		
template <class V, class I> V lInfinityNorm(const Vector<V,I>& x);	// L infinity norm

template <class V, class I> SimplePropertySet<string, double> allNorms(const Vector<V,I>& x);

// Same vector morms as above except for the difference of two vectors
template <class V, class I> V l1Norm(const Vector<V,I>& vectorA, const Vector<V,I>& vectorB);
template <class V, class I> V l2Norm(const Vector<V,I>& vectorA, const Vector<V,I>& vectorB);		// Euclidean norm
template <class V, class I> V lpNorm(const Vector<V,I>& vectorA, const Vector<V,I>& vectorB, const I& p);		
template <class V, class I> V lInfinityNorm(const Vector<V,I>& vectorA, const Vector<V,I>& vectorB);	// L infinity norm

template <class V, class I> SimplePropertySet<string, double> allNorms(const Vector<V,I>& vectorA, const Vector<V,I>& vectorB);


////////////////////////////////////////////////////////////////////////////////////////////////////////



///////////////////////////////////////////////////////////////////////////////////////////////////
// Functions for Operations Research and Numerical Linear Algebra

// Comparing vectors with each other

// Are all elements of a vector positive?
template <class V, class I> bool positive(const Vector<V,I>& x);
template <class V, class I> bool negative(const Vector<V,I>& x);


// Is v1 < v2? etc. 
template <class V, class I> bool operator < (const Vector<V,I>& v1, const Vector<V,I>& v2);
template <class V, class I> bool operator <= (const Vector<V,I>& v1, const Vector<V,I>& v2);
template <class V, class I> bool operator > (const Vector<V,I>& v1, const Vector<V,I>& v2);
template <class V, class I> bool operator >= (const Vector<V,I>& v1, const Vector<V,I>& v2);
template <class V, class I> bool operator == (const Vector<V,I>& v1, const Vector<V,I>& v2);
template <class V, class I> bool operator != (const Vector<V,I>& v1, const Vector<V,I>& v2);




// Utility functions

// Create an STL vector from a general Vector
template <class V> vector<V> createSTLvector (const Vector<V,int>& myVector);
// Create a general Vector from an STL vector
template <class V> Vector<V, int> createDatasimVector (const vector<V>& mySTLvector);

// Cumulative vector c[j] = c[j-1] + x[j]
template <class V, class I> Vector<V, I> cumulativeVector (const vector<V>& x);

// First shall be last
template <class V, class I> Vector<V, I> reverse (const Vector<V,I>& x);


////////////// Useful and Basic Print Functions ////////////////////////////////////////////////////
template <class V, class I> void print(const Array<V,I>& v);
template <class V, class I> void print(const Vector<V,I>& v);
template <class V, class I> void print (Tensor<V, I>& tensor);

#endif