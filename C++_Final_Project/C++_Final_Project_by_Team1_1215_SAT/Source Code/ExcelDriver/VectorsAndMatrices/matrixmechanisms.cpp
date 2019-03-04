// matrixmechanisms.cpp
//
// Mechanism functions for matrices. 
//
//	Modification dates
//	
//	DD 2004-4-3 Kick off
//	DD 2004-4-9 Power method, code review and round-off
//  DD 2005-12-1 Extracting a row fom a Matrix (can be optmised)
//	DD 2006-8-6 set_diagomnal() commented out
//
// (C) Datasim Education BV 2004-2006
//

#ifndef MatrixMechanisms_cpp
#define MatrixMechanisms_cpp


#include "matrixmechanisms.hpp"
#include "PropertySet\simplepropertyset.cpp"

// Properties

// Sum of absolute values of row and column
template <class V, class I> V sumAbsRow(const NumericMatrix<V,I>& m, const I& i)
{ // Add up for a given row i

	V result = fabs(m(i, m.MinColumnIndex()));

	for (I j = m.MinColumnIndex() + 1; j <= m.MaxColumnIndex(); j++)
	{
		result += fabs(m(i,j));
	}

	return result;

}

template <class V, class I> V sumAbsColumn(const NumericMatrix<V,I>& m, const I& j)
{ // Add up for a given column j

	V result = fabs(m(m.MinRowIndex(), j));

	for (I i = m.MinRowIndex() + 1; i <= m.MaxRowIndex(); i++)
	{

		result += fabs(m(i,j));
	}

	return result;

}

// Now Abs sume of rows and columns for all indices
template <class V, class I> Vector<V,I> sumAbsRow(const NumericMatrix<V,I>& m)
{

	Vector<V,I> result (m.Rows(), m.MinRowIndex());

	// Do for all rows
	for (I i = m.MinRowIndex(); i <= m.MaxRowIndex(); i++)
	{
		result[i] = sumAbsRow(m, i);
	}

	return result;

}


template <class V, class I> Vector<V,I> sumAbsColumn(const NumericMatrix<V,I>& m)
{

	Vector<V,I> result (m.Columns(), m.MinColumnIndex());

	// Do for all columns
	for (I j = m.MinColumnIndex(); j <= m.MaxColumnIndex(); j++)
	{
		result[j] = sumAbsColumn(m, j);
	}

	return result;
}


template <class V, class I> V l1Norm(const NumericMatrix<V,I>& matrix)
{ // Largest coulmn 

		V ans = V(0.0);
		V tmp(ans);

		for (I j = matrix.MinColumnIndex(); j <= matrix.MaxColumnIndex(); j++)
		{
			for (I i = matrix.MinRowIndex(); i <= matrix.MaxRowIndex(); i++)
			{
				tmp = sumAbsColumn(matrix, i);
			}

			if (tmp > ans)
					ans = tmp;
		}

		return ans;

}

template <class V, class I> V FrobeniusNorm(const NumericMatrix<V,I>& matrix)
{      
		V ans(0.0);
		V tmp(0.0);

		for (I i = matrix.MinRowIndex(); i <= matrix.MaxRowIndex(); i++)
		{

			for (I j = matrix.MinColumnIndex(); j<= matrix.MaxColumnIndex(); j++)
			{
				tmp = matrix(i, j);
				ans += (tmp * tmp);
			}

		}

		return sqrt(ans);
} 

template <class V, class I> V lInfinityNorm(const NumericMatrix<V,I>& matrix)
{ // Largest row

		V ans = V(0.0);
		V tmp(ans);

		for (I i = matrix.MinRowIndex(); i <= matrix.MaxRowIndex(); i++)
		{

			for (I j = matrix.MinRowIndex(); j <= matrix.MaxRowIndex(); j++)
			{
				tmp = sumAbsRow(matrix, j);

			}
		
			if (tmp > ans)
					ans = tmp;

		}


		return ans;

}

template <class V, class I> SimplePropertySet<string, double> allNorms(const NumericMatrix<V,I>& m)
{

	SimplePropertySet<string, double> result;	// Empty list

	result.add(Property<string, double> ("l1", l1Norm(m)));
	result.add(Property<string, double> ("l2", FrobeniusNorm(m)));
	result.add(Property<string, double> ("linf", lInfinityNorm(m)));

	return result;

}
/*
template <class V, class I> setDiagonal(Matrix<V,I>& m, const V& v)
{ // All diagonal elements get the value v

		// Matrix must be square, otherwise ...

		for (I j = m.MinRowIndex(); j <= m.MaxRowIndex(); j++)
		{
			m(j,j) = v;
		}
}
*/
template <class V, class I> void initMatrix(Matrix<V,I>& m, const V& v)
{ // All elements get the value v


		for (I i = m.MinRowIndex(); i <= m.MaxRowIndex(); i++)
		{
			for (I j = m.MinColumnIndex(); j <= m.MaxColumnIndex(); j++)
			{
				m(i,j) = v;
			}
		}
}



template <class V, class I> NumericMatrix<V,I> createMatrix(
	const Vector<V,I>& lower, const Vector<V,I>& diagonal, const Vector<V,I>& upper)
{ // Create a matrix based on the diagonal elements of a tridiagonal matrix; bit wasteful of
  // space but who cares! I've got a Pentium with a giga of memory


	// We use the indexing as with LU decomposition routines, i.e.
	//
	//	lower [2, J]
	//	diagonal [1, J]
	//	upper [1, J-1]
	//

	NumericMatrix<V, I> result(diagonal.Size(), diagonal.Size(), 1, 1);

	// All values set to 0
	initMatrix(result, V(0.0));

	// Initialise the 'extremities' of the matrix
	result(result.MaxRowIndex(), result.MaxColumnIndex()) = diagonal[diagonal.MaxIndex()];
	result(result.MaxRowIndex(), result.MaxColumnIndex() -1) = lower[lower.MaxIndex()];

	result(1, 1) = diagonal[diagonal.MinIndex()];
	result(1, 2) = upper[upper.MinIndex()];

	// Now the 'uniform' part of the matrix
	for (I i = result.MinRowIndex() + 1; i <= result.MaxRowIndex() - 1; i++)
	{

		// Create the diagonal element	
		result(i, i-1)	= lower[i];
		result(i, i)	= diagonal[i];
		result(i, i+1)	= upper[i];
	}

	return result;
}
// Other results for vectors and matrces
template <class V, class I> V quadraticForm(const NumericMatrix<V,I>& matrix, const Vector<V,I>& x)
{    

		V ans = V(0.0);

		for (I i = matrix.MinRowIndex(); i <= matrix.MaxRowIndex(); i++)
		{

			for (I j = matrix.MinColumnIndex(); j<= matrix.MaxColumnIndex(); j++)
			{
				ans += matrix(i,j) * x[i] * x[j];
			}

		}

		return ans;
}

template <class V, class I> V RayleighQuotient(const NumericMatrix<V,I>& A, const Vector<V,I>& x)
{    

	// PREC: Compatibiity, number of columns of A == number of rows of x
	// PREC: inner product does not evaluate to 0.0


	return quadraticForm(A, x) / innerProduct (x,x);

}
template <class V, class I> bool operator < (const NumericMatrix<V,I>& m1, const NumericMatrix<V,I>& m2)
{

		for (I i = m1.MinRowIndex(); i <= m1.MaxRowIndex(); i++)
		{

			for (I j = m1.MinColumnIndex(); j<= m1.MaxColumnIndex(); j++)
			{
				if (m1(i,j) >= m2(i,j))
					return false;
			}

		}


		return true;
}

template <class V, class I> bool operator <= (const NumericMatrix<V,I>& m1, const NumericMatrix<V,I>& m2)
{

		for (I i = m1.MinRowIndex(); i <= m1.MaxRowIndex(); i++)
		{

			for (I j = m1.MinColumnIndex(); j<= m1.MaxColumnIndex(); j++)
			{
				if (m1(i,j) > m2(i,j))
					return false;
			}

		}


		return true;
}


template <class V, class I> bool operator > (const NumericMatrix<V,I>& m1, const NumericMatrix<V,I>& m2)
{

	if (m2 < m1)
		return true;

	return false;
}


template <class V, class I> bool operator >= (const NumericMatrix<V,I>& m1, const NumericMatrix<V,I>& m2)
{

		if (m2 <= m1)
			return true;

		return false;

}


template <class V, class I> bool operator == (const NumericMatrix<V,I>& m1, const NumericMatrix<V,I>& m2)
{

		for (I i = m1.MinRowIndex(); i <= m1.MaxRowIndex(); i++)
		{

			for (I j = m1.MinColumnIndex(); j<= m1.MaxColumnIndex(); j++)
			{
				if (m1(i,j) != m2(i,j))
					return false;
			}

		}


		return true;
}


template <class V, class I> bool operator != (const NumericMatrix<V,I>& m1, const NumericMatrix<V,I>& m2)
{

	if (m1 == m2)
		return false;

	return true;
}

// Are all elements of a matrix positive?
template <class V, class I> bool positive(const NumericMatrix<V,I>& matrix)
{

		V zero = V(0.0);

		for (I i = matrix.MinRowIndex(); i <= matrix.MaxRowIndex(); i++)
		{

			for (I j = matrix.MinColumnIndex(); j<= matrix.MaxColumnIndex(); j++)
			{
				if (matrix(i,j) <= zero)
					return false;
			}

		}


		return true;
}


template <class V, class I> bool negative(const NumericMatrix<V,I>& matrix)
{

		V zero = V(0.0);

		for (I i = matrix.MinRowIndex(); i <= matrix.MaxRowIndex(); i++)
		{

			for (I j = matrix.MinColumnIndex(); j<= matrix.MaxColumnIndex(); j++)
			{
				if (matrix(i,j) >= zero)
					return false;
			}

		}


		return true;
	
}


// Special functions for Numerical Linear Algebra
template <class V, class I> bool diagonallyDominant(const NumericMatrix<V,I>& m)
{

	for (I i = m.MinRowIndex(); i <= m.MaxRowIndex(); i++)
	{
		V tmp = fabs(m(i,i));
		if (tmp < sumAbsRow(m, i) - tmp)
			return false;
	}

	return true;

}


// Gerschgorin's circle theorem: n eigenvalues of a matrix in a nX2 matrix of
// lower and upper bounds
template <class V, class I> NumericMatrix<V,I> eigenvalueBounds(const NumericMatrix<V,I>& m)
{

	NumericMatrix<V, I> mat(m.Rows(), 2, 1, 1);	// 2 columns
	for (I i = m.MinRowIndex(); i <= m.MaxRowIndex(); i++)
	{
		V tmp = fabs(m(i,i));
		V rsum = sumAbsRow(m, i);

		mat(i, 2) = tmp - rsum;	// Lower limit
		mat(i, 1) = rsum;
	}

	return mat;
}

// Calculate largest eigenvalue by Power method
template <class V, class I> V dominantEigenvalue(const NumericMatrix<V,I>& A, const Vector<V,I>& svec,
												 const V& tolerance)
{

	Vector<V,I> startV = svec;
	Vector<V,I> currVector = (A * svec);
	V tmp(0.0);
	V nextValue (tmp);

	L1:
		tmp = RayleighQuotient(A, currVector);

		if (fabs(tmp-nextValue) > tolerance)
		{
			nextValue = tmp;
			startV = currVector;
			currVector = A * startV;
			goto L1;
		}

	return nextValue;

}

////////////// Useful and Basic Print Functions ////////////////////////////////////////////////////
template <class V, class I> void print(const Matrix<V,I>& mat)
{


	for (int i = mat.MinRowIndex(); i <= mat.MaxRowIndex(); i++)
	{
	
		cout << "\n[";
		for (I j = mat.MinColumnIndex(); j <= mat.MaxColumnIndex()-1; j++)
		{
			cout << mat(i,j) << ", ";
		}
		cout << mat(i, mat.MaxColumnIndex());
		cout << "]" << endl;
	
	}
	cout << endl;
}

#endif