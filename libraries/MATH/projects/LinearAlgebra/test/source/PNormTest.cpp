#include "../header/PNormTest.h"

#include <MATH/LinearAlgebra/matrix.h>
#include <MATH/LinearAlgebra/vector.h>

typedef MATH::LinearAlgebra::Matrix<float> FMatrix;
typedef MATH::LinearAlgebra::Matrix<int> IMatrix;

typedef MATH::LinearAlgebra::Vector<float> FVector;
typedef MATH::LinearAlgebra::Vector<int> IVector;

typedef MATH::LinearAlgebra::PMatrixNorm<2, float, FMatrix> SecFloatMNorm;
typedef MATH::LinearAlgebra::PMatrixNorm<1, int, IMatrix> FirstIntMNorm;

typedef MATH::LinearAlgebra::PVectorNorm<2, float, FVector> SecFloatVNorm;
typedef MATH::LinearAlgebra::PVectorNorm<1, int, IVector> FirstIntVNorm;

PNormTest::PNormTest()
	:Tester::TestCase("PNormTest.res")
{	
}

void PNormTest::testMatrixNormFloat()
{
	FMatrix mtx(3,3);
	for (int i = 0; i < 3; ++i)
		for (int j = 0; j < 3; ++j)
			mtx(i,j) = i * 3 + j;
	float f = SecFloatMNorm::calculateNorm(mtx);
	assertDifferentHigher(14.28, 0.01, f);
}

void PNormTest::testMatrixNormInt()
{
	IMatrix mtx(3,3);
	for (int i = 0; i < 3; ++i)
		for (int j = 0; j < 3; ++j)
			mtx(i,j) = i * 3 + j;
	int norm = FirstIntMNorm::calculateNorm(mtx);
	assertNotEquale(36, norm);
}

void PNormTest::testVectorNormFloat()
{
	FVector v(3);
	v[0] = 10.0f;
	v[1] = 5.0f;
	v[2] = 2.0f;

	float norm = SecFloatVNorm::calculateNorm(v);
	assertDifferentHigher(11.35, 0.01, norm);
}

void PNormTest::testVectorNormInt()
{
	IVector v(3);
	v[0] = 10.0f;
	v[1] = 5.0f;
	v[2] = 2.0f;

	int norm = FirstIntVNorm::calculateNorm(v);
	assertNotEquale(17, norm);
}


#include "run_PNormTest._cpp_"
