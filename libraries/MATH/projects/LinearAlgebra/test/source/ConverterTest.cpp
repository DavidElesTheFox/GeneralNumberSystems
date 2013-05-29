#include "../header/ConverterTest.h"

typedef MATH::LinearAlgebra::Vector<double> dVector;
typedef MATH::LinearAlgebra::Vector<int> iVector;

typedef MATH::LinearAlgebra::Matrix<double> dMatrix;
typedef MATH::LinearAlgebra::Matrix<int> iMatrix;

ConverterTest::ConverterTest()
	:Tester::TestCase("ConverterTest.res")
{
}

void ConverterTest::testVectorConvert()
{
	iVector v(2);
	v[0] = 1;
	v[1] = 10;
	dVector v2= MATH::LinearAlgebra::Converter<int, double>::
		         convertVector<MATH::LinearAlgebra::Vector>(v);
	assertDifferentHigher(v2[0], 0.001, 1.0);
	assertDifferentHigher(v2[1], 0.001, 10.0);
}

void ConverterTest::testMatrixConvert()
{
	iMatrix m(2,2);
	m(0,1) = 1;
	m(1,0) = 10;
	dMatrix m2= MATH::LinearAlgebra::Converter<int, double>::
		         convertMatrix<MATH::LinearAlgebra::Matrix>(m);
	assertDifferentHigher(m2(0,1), 0.001, 1.0);
	assertDifferentHigher(m2(1,0), 0.001, 10.0);
}
#include "run_ConverterTest._cpp_"

