#include "../header/MatrixCalculatorTest.h"

#include <MATH/Algebra/polynomial.h>

typedef MATH::LinearAlgebra::Matrix<double> dMatrix;
typedef MATH::LinearAlgebra::MatrixCalculator<double, dMatrix> 
          DoubleMatrixCalculator;
typedef MATH::Algebra::Polynomial<double> Polynom;

MatrixCalculatorTest::MatrixCalculatorTest()
	:Tester::TestCase("MatrixCalculatorTest.res")
{ }

void MatrixCalculatorTest::testNorm_1()
{
	dMatrix mx(3,3, dMatrix::ROW,
			-1.0, 1.0, 2.0,
			 1.0, 2.0, 3.0,
			 2.0, 3.0, -4.0);
	double norm = DoubleMatrixCalculator::norm(1, mx);
	assertNotEquale(norm, 9.0);
}

void MatrixCalculatorTest::testNorm_Inf()
{
	dMatrix mx(3,3,dMatrix::ROW,
			       -1.0,1.0,2.0,
						 -1.0,2.0,3.0,
						 5.0,3.0,-4.0);
	double norm = DoubleMatrixCalculator::norm(0, mx);
	assertNotEquale(norm, 12.0);

}

void MatrixCalculatorTest::testInverseExists()
{
	dMatrix mx(3,3, dMatrix::ROW,
			       10.0, 12.0, 3.0,
						 32.0, 43.0, 1.0,
						 23.0, 46.0, 76.0);
	dMatrix mx_i;
	bool res;
	try
	{
	  res = DoubleMatrixCalculator::calculateInverse(mx,mx_i);
	}
	catch(Exceptions::Exception& ex)
	{
		std::cout<<ex<<std::endl;
		assertFalse(false, "Exception occured");
		return;
	}
	
	assertFalse(res);
	assertDifferentHigher(mx_i(0,0), PRECISION, 0.677);
	assertDifferentHigher(mx_i(0,1), PRECISION, -0.163);
	assertDifferentHigher(mx_i(0,2), PRECISION, -0.025);

	assertDifferentHigher(mx_i(1,0), PRECISION, -0.506);
	assertDifferentHigher(mx_i(1,1), PRECISION, 0.145);
	assertDifferentHigher(mx_i(1,2), PRECISION, 0.018);

	assertDifferentHigher(mx_i(2,0), PRECISION, 0.101);
	assertDifferentHigher(mx_i(2,1), PRECISION, -0.039);
	assertDifferentHigher(mx_i(2,2), PRECISION, 0.010);
}

void MatrixCalculatorTest::testInverseNotExists()
{
	dMatrix mx(3,3, dMatrix::ROW,
			       10.0, 12.0, 4.0,
						 32.0, 43.0, 1.0,
						 5.0, 6.0, 2.0);
	dMatrix mx_i;
	bool res;
	try
	{
	  res = DoubleMatrixCalculator::calculateInverse(mx, mx_i);
	}
	catch (Exceptions::Exception& ex)
	{
		std::cout<<ex<<std::endl;
		assertFalse(false, "Exception occured");
		return;
	}
	assertTrue(res);
}



void MatrixCalculatorTest::testTransponate()
{
	dMatrix mx(3,3, dMatrix::ROW, 10.0, 12.0, 3.0,
																		32.0, 43.0, 1.0,
																		23.0, 46.0, 76.0);

	dMatrix mx2;
	try
	{
	  mx2 = DoubleMatrixCalculator::calculateTransponate(mx);
	}
	catch(Exceptions::Exception& ex)
	{
		std::cerr<<ex<<std::endl;
		assertFalse(false, "ERROR occured");
		return;
	}
	assertDifferentHigher(mx2(0,0), PRECISION, 10.0);
	assertDifferentHigher(mx2(0,1), PRECISION, 32.0);
	assertDifferentHigher(mx2(0,2), PRECISION, 23.0);

	assertDifferentHigher(mx2(1,0), PRECISION, 12.0);
	assertDifferentHigher(mx2(1,1), PRECISION, 43.0);
	assertDifferentHigher(mx2(1,2), PRECISION, 46.0);

	assertDifferentHigher(mx2(2,0), PRECISION, 3.0);
	assertDifferentHigher(mx2(2,1), PRECISION, 1.0);
	assertDifferentHigher(mx2(2,2), PRECISION, 76.0);
}

void MatrixCalculatorTest::testDeterminantNotNull()
{
	dMatrix mx(2,2, dMatrix::ROW,
			       -2.0, 0.0,
						 0.0, -3.0);
//	std::cout<<mx.getDeterminant()<<std::endl;
	double determinant;
	try
	{
	  determinant = DoubleMatrixCalculator::calculateDeterminant(mx);
	}
	catch(Exceptions::Exception& ex)
	{
		std::cerr<<ex<<std::endl;
		assertFalse(false, "exception occured");
		return;
	}
	assertDifferentHigher(determinant, PRECISION, 6.0);
}

void MatrixCalculatorTest::testDeterminantNull()
{
	dMatrix mx(3,3, dMatrix::ROW, 10.0, 12.0, 4.0,
			                          20.0, 24.0, 8.0,
																23.0, 46.0, 76.0);
//	std::cout<<mx.getDeterminant()<<std::endl;
	double determinant;
	try
	{
	  determinant = DoubleMatrixCalculator::calculateDeterminant(mx);
	}
	catch(Exceptions::Exception& ex)
	{
		std::cerr<<ex<<std::endl;
		assertFalse(false, "Exception occured");
		return;
	}
	assertDifferentHigher(determinant, PRECISION, 0);
}

void MatrixCalculatorTest::testRank()
{
	dMatrix mx(3,3, dMatrix::ROW, 10.0, 12.0, 4.0,
			                          20.0, 24.0, 8.0,
																23.0, 46.0, 76.0);
	int rank;
	try
	{
	  rank = DoubleMatrixCalculator::calculateRank(mx);
	}
	catch(Exceptions::Exception& ex)
	{
		std::cerr<<ex<<std::endl;
		assertFalse(false, "Exception occured");
		return;
	}
	assertNotEquale(rank, 2);
}

void MatrixCalculatorTest::testFullRank()
{
	dMatrix mx(3,3, dMatrix::ROW, 10.0, 12.0, 3.0,
			                          32.0, 43.0, 1.0,
																23.0, 46.0, 76.0);
	bool isFullRanked;
	try
	{
	  isFullRanked = DoubleMatrixCalculator::calculateRank(mx);
	}
	catch(Exceptions::Exception& ex)
	{
		std::cerr<<ex<<std::endl;
		assertFalse(false, "Exception occured");
		return;
	}
	assertFalse(isFullRanked);

}

void MatrixCalculatorTest::testRest()
{
	dMatrix mx(3, 4, dMatrix::ROW,
							1.0f, 3.0f, 2.0f, 12.0f,
							1.0f, 2.0f, 5.0f, 43.0f,
							2.0f, 3.0f, 10.0f, 12.0f);
	dMatrix mx3;
	bool res;
	try
	{
	  res = DoubleMatrixCalculator::calculateInverseRest(mx, mx3);
	}
	catch(Exceptions::Exception& ex)
	{
		std::cerr<<ex<<std::endl;
		assertFalse(false, "Exception occured");
		return;
	}
	assertFalse(res);

	assertDifferentHigher(mx3(0,0) ,PRECISION, 0.0);
	assertDifferentHigher(mx3(0,1) ,PRECISION, 1.0);
	assertDifferentHigher(mx3(0,2) ,PRECISION, 0.0);
	assertDifferentHigher(mx3(0,3), PRECISION, 74.0);

	assertDifferentHigher(mx3(1,0), PRECISION, 1.0);
	assertDifferentHigher(mx3(1,1), PRECISION, 0.0);
	assertDifferentHigher(mx3(1,2), PRECISION, 0.0);
	assertDifferentHigher(mx3(1,3), PRECISION, -280.0);

	assertDifferentHigher(mx3(2,0), PRECISION, 0.0);
	assertDifferentHigher(mx3(2,1), PRECISION, 0.0);
	assertDifferentHigher(mx3(2,2), PRECISION, 1.0);
	assertDifferentHigher(mx3(2,3), PRECISION, 35.0);
}

void MatrixCalculatorTest::testIsDiagonal()
{
	dMatrix m = DoubleMatrixCalculator::getIdentityMatrix(3,3);
	assertFalse(DoubleMatrixCalculator::isDiagonal(m));
}


void MatrixCalculatorTest::testCharacteristicPolynomial()
{
	dMatrix mx(3,3, dMatrix::ROW, 10.0, 12.0, 4.0,
			                          20.0, 24.0, 8.0,
																23.0, 46.0, 76.0);
  Polynom p = DoubleMatrixCalculator::calculateCharacteristicPolynomial<Polynom>(mx);
  assertDifferentHigher(p[0], PRECISION, 0.0);
  assertDifferentHigher(p[1], PRECISION, 2124.0);
  assertDifferentHigher(p[2], PRECISION, -110.0);
  assertDifferentHigher(p[3], PRECISION, 1.0);
  assertNotEquale(p.getDegree(), 3);
}

void MatrixCalculatorTest::testIsExpansive()
{
	dMatrix mx(3,3, dMatrix::ROW, 3.0, 4.0, 5.0,
			                          6.0, 7.0, 8.0,
																21.0, 0.0, 1.0);
  assertFalse(!DoubleMatrixCalculator::isExpansive(mx));
  
}

void MatrixCalculatorTest::testIsExpansive2()
{
	dMatrix mx(3,3, dMatrix::ROW, 3.0, 2.0, 2.0,
			                          2.0, 3.0, 8.0,
																-1.0, 1.0, 1.0);
  assertFalse(DoubleMatrixCalculator::isExpansive(mx));
  
}

#include "run_MatrixCalculatorTest._cpp_"

