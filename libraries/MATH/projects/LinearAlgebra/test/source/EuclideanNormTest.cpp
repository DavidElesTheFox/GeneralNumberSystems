#include "../header/EuclideanNormTest.h"

#include <MATH/LinearAlgebra/matrix.h>
#include <MATH/LinearAlgebra/vector.h>

typedef MATH::LinearAlgebra::Matrix<float> FMatrix;
typedef MATH::LinearAlgebra::Matrix<int> IMatrix;

typedef MATH::LinearAlgebra::Vector<float> FVector;
typedef MATH::LinearAlgebra::Vector<int> IVector;

typedef MATH::LinearAlgebra::EuclideanMatrixNorm<0, float, FMatrix> InftyFloatMNorm;
typedef MATH::LinearAlgebra::EuclideanMatrixNorm<0, int, IMatrix> InftyIntMNorm;

typedef MATH::LinearAlgebra::EuclideanVectorNorm<2, float, FVector> SecFloatVNorm;
typedef MATH::LinearAlgebra::EuclideanVectorNorm<1, int, IVector> FirstIntVNorm;

EuclideanNormTest::EuclideanNormTest()
	:Tester::TestCase("EuclideanNormTest.res")
{	
}

void EuclideanNormTest::testMatrixNormFloat()
{
	FMatrix mtx(3,3);
	for (int i = 0; i < 3; ++i)
		for (int j = 0; j < 3; ++j)
			mtx(i,j) = i * 3 + j;
	float f = InftyFloatMNorm::calculateNorm(mtx);
	assertDifferentHigher(21, 0.01, f);
}

void EuclideanNormTest::testMatrixNormInt()
{
	IMatrix mtx(3,3);
	for (int i = 0; i < 3; ++i)
		for (int j = 0; j < 3; ++j)
			mtx(i,j) = i * 3 + j;
	int norm = InftyIntMNorm::calculateNorm(mtx);
	assertNotEquale(21, norm);
}

void EuclideanNormTest::testVectorNormFloat()
{
	FVector v(3);
	v[0] = 10.0f;
	v[1] = 5.0f;
	v[2] = 2.0f;

	float norm = SecFloatVNorm::calculateNorm(v);
	assertDifferentHigher(11.35, 0.01, norm);
}

void EuclideanNormTest::testVectorNormInt()
{
	IVector v(3);
	v[0] = 10.0f;
	v[1] = 5.0f;
	v[2] = 2.0f;

	int norm = FirstIntVNorm::calculateNorm(v);
	assertNotEquale(17, norm);
}


#include "run_EuclideanNormTest._cpp_"
