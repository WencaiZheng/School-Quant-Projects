// matrixmechanisms.hpp
//
// Mechanism functions for matrices. We do everthing inline
// for convenience and pressure of time.
//
// Functionality:
//
//		Norms of matrices
//		Some initialisation functions
//		Comparing matrices
//		Intrinsic properties of matrices (positive, negative)
//		Simple eigenvalue analysis (Rayleigh quotient, Gerschgorin)
//		Power method (find dominant eigenvalue of a matrix)
//
// (C) Datasim Education BV 2004
//

#ifndef MatrixMechanisms_hpp
#define MatrixMechanisms_hpp


#include "numericmatrix.cpp"
#include "arraymechanisms.cpp"

// Properties

// Sum of absolute values of row and column
template <class V, class I> V sumAbsRow(const NumericMatrix<V,I>& m, const I& i);
template <class V, class I> V sumAbsColumn(const NumericMatrix<V,I>& m, const I& j);

// Now Abs sume of rows and columns for all indices
template <class V, class I> Vector<V,I> sumAbsRow(const NumericMatrix<V,I>& m);
template <class V, class I> Vector<V,I> sumAbsColumn(const NumericMatrix<V,I>& m);

// Norms
template <class V, class I> V llNorm(const NumericMatrix<V,I>& matrix);
template <class V, class I> V FrobeniusNorm(const NumericMatrix<V,I>& matrix); // Euclidean norm
template <class V, class I> V lInfinityNorm(const NumericMatrix<V,I>& matrix);

template <class V, class I> SimplePropertySet<string, double> allNorms(const NumericMatrix<V,I>& x);

// All diagonal elements get the value v
//template <class V, class I> setDiagonal(Matrix<V,I>& m, const V& v);

// All elements get the value v
template <class V, class I> void initMatrix(Matrix<V,I>& m, const V& v);


// Create a matrix based on the diagonal elements of a tridiagonal matrix; bit wasteful of
// space but who cares! I've got a Pentium with a giga of memory
template <class V, class I> NumericMatrix<V,I> createMatrix(const Vector<V,I>& lower, const Vector<V,I>& diagonal, const Vector<V,I>& upper);


// Comparison operatins with matrices
template <class V, class I> bool operator < (const NumericMatrix<V,I>& v1, const NumericMatrix<V,I>& v2);
template <class V, class I> bool operator <= (const NumericMatrix<V,I>& v1, const NumericMatrix<V,I>& v2);
template <class V, class I> bool operator > (const NumericMatrix<V,I>& v1, const NumericMatrix<V,I>& v2);
template <class V, class I> bool operator >= (const NumericMatrix<V,I>& v1, const NumericMatrix<V,I>& v2);
template <class V, class I> bool operator == (const NumericMatrix<V,I>& v1, const NumericMatrix<V,I>& v2);
template <class V, class I> bool operator != (const NumericMatrix<V,I>& v1, const NumericMatrix<V,I>& v2);

// Are all elements of a matrix positive?
template <class V, class I> bool positive(const NumericMatrix<V,I>& x);
template <class V, class I> bool negative(const NumericMatrix<V,I>& x);


// Special functions for Numerical Linear Algebra
template <class V, class I> bool diagonallyDominant(const NumericMatrix<V,I>& x);

// Gerschgorin's circle theorem: n eigenvalues of a matrix in a nX2 matrix of
// lower and upper bounds
template <class V, class I> NumericMatrix<V,I> eigenvalueBounds(const NumericMatrix<V,I>& x);

// Other results for vectors and matrces
template <class V, class I> V quadraticForm(const NumericMatrix<V,I>& A, const Vector<V,I>& x);
template <class V, class I> V RayleighQuotient(const NumericMatrix<V,I>& A, const Vector<V,I>& x);
// Calculate largest eigenvalue by Power method
template <class V, class I> V dominantEigenvalue(const NumericMatrix<V,I>& A, const Vector<V,I>& startVec,
												 const V& tolerance);


////////////// Useful and Basic Print Functions ////////////////////////////////////////////////////
template <class V, class I> void print(const Matrix<V,I>& v);

#endif