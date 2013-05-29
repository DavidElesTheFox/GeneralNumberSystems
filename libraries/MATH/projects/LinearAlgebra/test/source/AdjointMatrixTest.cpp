#include "../header/AdjointMatrixTest.h"

typedef MATH::LinearAlgebra::Matrix<double> DMatrix;
typedef MATH::LinearAlgebra::AdjointMatrix<double, DMatrix >
          DAdjMatrix;
typedef MATH::LinearAlgebra::MatrixCalculator<double, DMatrix >
          DMCalculator;

typedef MATH::LinearAlgebra::Matrix<int> IMatrix;
typedef MATH::LinearAlgebra::AdjointMatrix<int, IMatrix>  IAdjMatrix;
typedef MATH::LinearAlgebra::MatrixCalculator<int, IMatrix>
          IMCalculator;

AdjointMatrixTest::AdjointMatrixTest() 
	:Tester::TestCase("AdjointMatrixTest.res")
{	}

void AdjointMatrixTest::testTransformation()
{
	DMatrix m(3,3);
	m(0,0) = 1;		m(0,1) = -2;	m(0,2) = 0;
	m(1,0) = 2; 	m(1,1) = -1; 	m(1,2) = 1;
	m(2,0) = -1;	m(2,1) = 0;		m(2,2) = -3;

	DAdjMatrix adj(m);
	DMatrix adjMtx = adj["ADJOINT"];
	assertDifferentHigher(3.0,0.0001,adjMtx(0,0), "Error with adjointMatrix element");
	assertDifferentHigher(-6.0,0.0001,adjMtx(0,1), "Error with adjointMatrix element");
	assertDifferentHigher(-2.0,0.0001,adjMtx(0,2), "Error with adjointMatrix element");

	assertDifferentHigher(5.0,0.0001,adjMtx(1,0), "Error with adjointMatrix element");
	assertDifferentHigher(-3.0,0.0001,adjMtx(1,1), "Error with adjointMatrix element");
	assertDifferentHigher(-1.0,0.0001,adjMtx(1,2), "Error with adjointMatrix element");

	assertDifferentHigher(-1.0,0.0001,adjMtx(2,0), "Error with adjointMatrix element");
	assertDifferentHigher(2.0,0.0001,adjMtx(2,1), "Error with adjointMatrix element");
	assertDifferentHigher(3.0,0.0001,adjMtx(2,2), "Error with adjointMatrix element");

	double det = DMCalculator::calculateDeterminant(m);
	DMatrix detI = m*adj["ADJOINT"];
	for(int i = 0; i < m.getRowCount(); ++i)
	{
		for(int j = 0; j < m.getColCount(); ++j)
		{
			if(i == j)
			{
				assertDifferentHigher(det, 0.0001, detI(i,j), "Error with properte");
			}
			else
			{
				assertDifferentHigher(0, 0.0001, detI(i,j), "Error with properte");
			}
		}
	}
}

void AdjointMatrixTest::testTransformation2()
{
	DMatrix m(3,3);
	m(0,0) = -3;	m(0,1) = 2;		m(0,2) = -5;
	m(1,0) = -1; 	m(1,1) = 0; 	m(1,2) = -2;
	m(2,0) = 3;		m(2,1) = -4;	m(2,2) = 1;

	DAdjMatrix adj(m);
	DMatrix adjMtx = adj["ADJOINT"];
	assertDifferentHigher(-8.0,0.0001,adjMtx(0,0), "Error with adjointMatrix element");
	assertDifferentHigher(18.0,0.0001,adjMtx(0,1), "Error with adjointMatrix element");
	assertDifferentHigher(-4.0,0.0001,adjMtx(0,2), "Error with adjointMatrix element");

	assertDifferentHigher(-5.0,0.0001,adjMtx(1,0), "Error with adjointMatrix element");
	assertDifferentHigher(12.0,0.0001,adjMtx(1,1), "Error with adjointMatrix element");
	assertDifferentHigher(-1.0,0.0001,adjMtx(1,2), "Error with adjointMatrix element");

	assertDifferentHigher(4.0,0.0001,adjMtx(2,0), "Error with adjointMatrix element");
	assertDifferentHigher(-6.0,0.0001,adjMtx(2,1), "Error with adjointMatrix element");
	assertDifferentHigher(2.0,0.0001,adjMtx(2,2), "Error with adjointMatrix element");

	double det = DMCalculator::calculateDeterminant(m);
	DMatrix detI = m*adj["ADJOINT"];
//	std::cout<<m*adj()<<std::endl;
	for(int i = 0; i < m.getRowCount(); ++i)
	{
		for(int j = 0; j < m.getColCount(); ++j)
		{
			if(i == j)
			{
				assertDifferentHigher(det, 0.0001, detI(i,j), "Error with properties");
			}
			else
			{
				assertDifferentHigher(0.0, 0.1, detI(i,j), "Error with 0 properte");
			}
		}
	}
}

void AdjointMatrixTest::testTransformation3()
{
	IMatrix m(3,3);
	m(0,0) = -3;	m(0,1) = 2;		m(0,2) = -5;
	m(1,0) = -1; 	m(1,1) = 0; 	m(1,2) = -2;
	m(2,0) = 3;		m(2,1) = -4;	m(2,2) = 1;

	IAdjMatrix adj(m);
	IMatrix adjMtx = adj["ADJOINT"];
//	std::cout<<"ADJ:\n"<<adjMtx<<std::endl;
	assertNotEquale(-8,adjMtx(0,0), "Error with adjointMatrix element");
	assertNotEquale(18,adjMtx(0,1), "Error with adjointMatrix element");
	assertNotEquale(-4,adjMtx(0,2), "Error with adjointMatrix element");

	assertNotEquale(-5,adjMtx(1,0), "Error with adjointMatrix element");
	assertNotEquale(12,adjMtx(1,1), "Error with adjointMatrix element");
	assertNotEquale(-1,adjMtx(1,2), "Error with adjointMatrix element");

	assertNotEquale(4,adjMtx(2,0), "Error with adjointMatrix element");
	assertNotEquale(-6,adjMtx(2,1), "Error with adjointMatrix element");
	assertNotEquale(2,adjMtx(2,2), "Error with adjointMatrix element");

	IMatrix detI = m*adj["ADJOINT"];
	int det = -6;
	for(int i = 0; i < m.getRowCount(); ++i)
	{
		for(int j = 0; j < m.getColCount(); ++j)
		{
			if(i == j)
			{
				assertNotEquale(det, detI(i,j), "Error with properties");
			}
			else
			{
				assertNotEquale(0, detI(i,j), "Error with 0 properte");
			}
		}
	}
}


#include "run_AdjointMatrixTest._cpp_"
