// testTensor.cpp
//
// Simple program to test tensors.
//
// (C) Datasim Education BV 2004

#include "tensor.cpp"
#include "matrixmechanisms.cpp"

template <class V, class I> void print (Tensor<V, I>& tensor)
{
	cout << "Tensor, Rows " << tensor.Rows() << ", Columns " << tensor.Columns() << 
			", Third Dimension " << tensor.sizeThird() << endl;

	for (long k = tensor.MinThirdIndex(); k<= tensor.MaxThirdIndex(); k++)
	{
		print (tensor[k]);
	}
}

int main()
{

	Tensor<double, int> t0;
	print(t0);

	Tensor<double, int> t1(2, 3, 2);
	print(t1);

	NumericMatrix<double, int> m(2, 3); // Rows and columns
	m(1,1) = 2.0;
	m(1,2) = 3.0;

	t1[1] = m;
	t1[2] = m;

	print(t1);

	Tensor<double, int> t2(t1);
	print(t2);

	Tensor<double, int> t3 = t1;
	print(t3);

	// Stress test
	Tensor<double, int> t4(200, 300, 200);
	print(t4[50]);

	return 0;
}
