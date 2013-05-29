#include "../header/Matrix_traitsTest.h"

typedef MATH::LinearAlgebra::Matrix<float> FloatMatrix;
typedef MATH::LinearAlgebra::Matrix_traits<float, FloatMatrix>
          FloatMatrix_traits;


Matrix_traitsTest::Matrix_traitsTest():
	Tester::TestCase("Matrix_traitsTest.res")
{
}

void Matrix_traitsTest::testCreateMatrix()
{
	FloatMatrix m = FloatMatrix_traits::createMatrix(3,3);
	assertNotEquale(m.getRowCount(), 3);
	assertNotEquale(m.getColCount(), 3);
}

void Matrix_traitsTest::testGetElement()
{
	FloatMatrix m = FloatMatrix_traits::createMatrix(3,3);
	m(1,1) = 10;
	assertNotEquale(FloatMatrix_traits::getElement(1,1,m), 10.0f);
}

void Matrix_traitsTest::testRefGetElement()
{
	FloatMatrix m = FloatMatrix_traits::createMatrix(3,3);
	float& e = FloatMatrix_traits::getElement(0,0,m);
	e = 10;
	assertNotEquale(m(0,0),10.0f);
}

void Matrix_traitsTest::testResize()
{
	FloatMatrix m = FloatMatrix_traits::createMatrix(3,3);
	FloatMatrix_traits::resize(4,4,m);
	assertNotEquale(m.getRowCount(),4);
	assertNotEquale(m.getColCount(),4);
}

void Matrix_traitsTest::testCopy()
{
	FloatMatrix m = FloatMatrix_traits::createMatrix(3,3);
	m(0,0) = 10;
	FloatMatrix m2 = FloatMatrix_traits::copy(m);
	assertNotEquale(m2(0,0),10.0f);
}

void Matrix_traitsTest::testGetDimension()
{
	FloatMatrix m = FloatMatrix_traits::createMatrix(3,3);
	int rowNum, colNum;
	FloatMatrix_traits::getDimension(rowNum, colNum, m);
	assertNotEquale(rowNum, 3);
	assertNotEquale(colNum, 3);
}

void Matrix_traitsTest::testRowNum()
{
	FloatMatrix m = FloatMatrix_traits::createMatrix(3,2);
	assertNotEquale(FloatMatrix_traits::getRowNum(m), 3);
}

void Matrix_traitsTest::testColNum()
{
	FloatMatrix m = FloatMatrix_traits::createMatrix(3,2);
	assertNotEquale(FloatMatrix_traits::getColNum(m), 2);
}

void Matrix_traitsTest::testEquals()
{
	FloatMatrix m(3,3);
	m(2, 2) = 10;
	FloatMatrix m2 = m;
	assertFalse(FloatMatrix_traits::equals(m,m2));
}

#include "run_Matrix_traitsTest._cpp_"

