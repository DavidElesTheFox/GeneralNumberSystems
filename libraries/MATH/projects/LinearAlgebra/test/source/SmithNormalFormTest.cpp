#include "../header/SmithNormalFormTest.h"

#include <MATH/Algebra/complex.h>

typedef MATH::LinearAlgebra::Matrix<int> IMatrix;
typedef MATH::LinearAlgebra::SmithNormalForm<int, IMatrix >
          ISmithNormalForm;
typedef MATH::LinearAlgebra::Matrix<double> DMatrix;
typedef MATH::LinearAlgebra::MatrixCalculator<int, IMatrix>
          IMCalculator;

typedef MATH::Algebra::Complex<int> gaussian_int_t;
typedef MATH::Algebra::Complex<double> complex_t;

typedef MATH::LinearAlgebra::Matrix<gaussian_int_t> IMatrixI;
typedef MATH::LinearAlgebra::SmithNormalForm<gaussian_int_t, IMatrixI>
          ISmithNormalFormI;
typedef MATH::LinearAlgebra::Matrix<complex_t> DMatrixI;
typedef MATH::LinearAlgebra::MatrixCalculator<gaussian_int_t, IMatrixI>
          IMCalculatorI;

SmithNormalFormTest::SmithNormalFormTest()
	:Tester::TestCase("SmithNormalFormTest.res")
{	}


void SmithNormalFormTest::testTransformation()
{
	IMatrix m(3,3);
//	m(0,0) = 2;		m(0,1) = 4;		m(0,2) = 4;
//	m(1,0) = -6; 	m(1,1) = 6; 	m(1,2) = 12;
//	m(2,0) = 10;	m(2,1) = -4;	m(2,2) = -16;
	m(0,0) = 5;		m(0,1) = 2;		m(0,2) = 3;
	m(1,0) = 10; 	m(1,1) = 8; 	m(1,2) = 6;
	m(2,0) = 15;	m(2,1) = 3;	m(2,2) = 4;

	ISmithNormalForm snf(m);
	IMatrix u = snf["U"];
	IMatrix v = snf["V"];
	IMatrix s = snf["S"];
//
//	std::cout<<"Original matrix:"<<std::endl<<m<<std::endl;
//	std::cout<<"S:"<<std::endl<<s<<std::endl;
//	std::cout<<"U:"<<std::endl<<u<<std::endl;
//	std::cout<<"V:"<<std::endl<<v<<std::endl;
	int det = IMCalculator::calculateDeterminant(u);
	assertFalse(det == 1 || det == -1);
	det = IMCalculator::calculateDeterminant(v);
	assertFalse(det == 1 || det == -1);
	assertFalse( u * m * v == s , "snf error");
	for(int i = 0; i < 3; ++i)
	{
		for(int j = 0; j < 3; ++j)
		{
			if(i == j && i < 2)
			{
				assertNotEquale((s(i + 1,i + 1)/s(i, i)) * s(i, i) ,s(i + 1, i + 1), "elements not elementary divisors!");
			}
			else if( i != j)
			{
				assertNotEquale(s(i,j), 0, "Shape error");
			}
		}
	}
}

void SmithNormalFormTest::testTransformation2()
{
	IMatrix m(3,3);
	m(0,0) = 2;		m(0,1) = 4;		m(0,2) = 4;
	m(1,0) = -6; 	m(1,1) = 6; 	m(1,2) = 12;
	m(2,0) = 10;	m(2,1) = -4;	m(2,2) = -16;
//	m(0,0) = 5;		m(0,1) = 2;		m(0,2) = 3;
//	m(1,0) = 10; 	m(1,1) = 8; 	m(1,2) = 6;
//	m(2,0) = 15;	m(2,1) = 3;	m(2,2) = 4;

	ISmithNormalForm snf(m);
	IMatrix u = snf["U"];
	IMatrix v = snf["V"];
	IMatrix s = snf["S"];
//
//	std::cout<<"Original matrix:"<<std::endl<<m<<std::endl;
//	std::cout<<"S:"<<std::endl<<s<<std::endl;
//	std::cout<<"U:"<<std::endl<<u<<std::endl;
//	std::cout<<"V:"<<std::endl<<v<<std::endl;
	int det = IMCalculator::calculateDeterminant(u);
	assertFalse(det == 1 || det == -1, "determinant error with u");
	det = IMCalculator::calculateDeterminant(v);
	assertFalse(det == 1 || det == -1, "determinant error with v");
	assertFalse(u * m * v == s , "snf error");
	for(int i = 0; i < 3; ++i)
	{
		for(int j = 0; j < 3; ++j)
		{
			if(i == j && i < 2)
			{
				assertNotEquale((s(i + 1,i + 1)/s(i, i)) * s(i, i) ,s(i + 1, i + 1), "elements not elementary divisors!");
			}
			else if( i != j)
			{
				assertNotEquale(s(i,j), 0, "Shape error");
			}
		}
	}
}

void SmithNormalFormTest::testTransformation3()
{
	IMatrix m(3,3);
//	m(0,0) = 2;		m(0,1) = 4;		m(0,2) = 4;
//	m(1,0) = -6; 	m(1,1) = 6; 	m(1,2) = 12;
//	m(2,0) = 10;	m(2,1) = -4;	m(2,2) = -16;
	m(0,0) = 5;		m(0,1) = 2;		m(0,2) = 3;
	m(1,0) = 7; 	m(1,1) = 4; 	m(1,2) = 6;
	m(2,0) = 10;	m(2,1) = 3;	m(2,2) = 1;

	ISmithNormalForm snf(m);
	IMatrix u = snf["U"];
	IMatrix v = snf["V"];
	IMatrix s = snf["S"];
//
//	std::cout<<"Original matrix:"<<std::endl<<m<<std::endl;
//	std::cout<<"S:"<<std::endl<<s<<std::endl;
//	std::cout<<"U:"<<std::endl<<u<<std::endl;
//	std::cout<<"V:"<<std::endl<<v<<std::endl;
	int det = IMCalculator::calculateDeterminant(u);
	assertFalse(det == 1 || det == -1, "determinant error with u");
	det = IMCalculator::calculateDeterminant(v);
	assertFalse(det == 1 || det == -1, "determinant error with v");
	assertFalse( u * m * v == s , "snf error");
	for(int i = 0; i < 3; ++i)
	{
		for(int j = 0; j < 3; ++j)
		{
			if(i == j && i < 2)
			{
				assertNotEquale((s(i + 1,i + 1)/s(i, i)) * s(i, i) ,s(i + 1, i + 1), "elements not elementary divisors!");
			}
			else if( i != j)
			{
				assertNotEquale(s(i,j), 0, "Shape error");
			}
		}
	}
}




void SmithNormalFormTest::testTransformation4()
{
	IMatrix m(3,3);
//	m(0,0) = 2;		m(0,1) = 4;		m(0,2) = 4;
//	m(1,0) = -6; 	m(1,1) = 6; 	m(1,2) = 12;
//	m(2,0) = 10;	m(2,1) = -4;	m(2,2) = -16;
	m(0,0) = 5;		m(0,1) = 2;		m(0,2) = 3;
	m(1,0) = 7; 	m(1,1) = 4; 	m(1,2) = 6;
	m(2,0) = 10;	m(2,1) = 3;	m(2,2) = 1;

	ISmithNormalForm snf(m,true, ISmithNormalForm::LEFT_POSITIVE);
	IMatrix u = snf["U"];
	IMatrix v = snf["V"];
	IMatrix s = snf["S"];

	/*std::cout<<"Original matrix:"<<std::endl<<m<<std::endl;
	std::cout<<"S:"<<std::endl<<s<<std::endl;
	std::cout<<"U:"<<std::endl<<u<<std::endl;
	std::cout<<"V:"<<std::endl<<v<<std::endl;*/

	int det = IMCalculator::calculateDeterminant(u);
	assertNotEquale(1, det,"Determinant error with u");
	det = IMCalculator::calculateDeterminant(v);
	assertFalse(det == 1 || det == -1, "determinant error with v");
	assertFalse( u * m * v == s , "snf error");
	for(int i = 0; i < 3; ++i)
	{
		for(int j = 0; j < 3; ++j)
		{
			if(i == j && i < 2)
			{
				assertNotEquale((s(i + 1,i + 1)/s(i, i)) * s(i, i) ,s(i + 1, i + 1), "elements not elementary divisors!");
			}
			else if( i != j)
			{
				assertNotEquale(s(i,j), 0, "Shape error");
			}
		}
	}
}

void SmithNormalFormTest::testTransformation5()
{
	IMatrix m(2,2);
//	m(0,0) = 2;		m(0,1) = 4;		m(0,2) = 4;
//	m(1,0) = -6; 	m(1,1) = 6; 	m(1,2) = 12;
//	m(2,0) = 10;	m(2,1) = -4;	m(2,2) = -16;
	m(0,0) = 2;		m(0,1) = -5;
	m(1,0) = -4; 	m(1,1) = 1;

	ISmithNormalForm snf(m,true, ISmithNormalForm::LEFT_POSITIVE);
	IMatrix u = snf["U"];
	IMatrix v = snf["V"];
	IMatrix s = snf["S"];

//	std::cout<<"Original matrix:"<<std::endl<<m<<std::endl;
//	std::cout<<"S:"<<std::endl<<s<<std::endl;
//	std::cout<<"U:"<<std::endl<<u<<std::endl;
//	std::cout<<"V:"<<std::endl<<v<<std::endl;
	int det = IMCalculator::calculateDeterminant(u);
	assertNotEquale(1, det,"Determinant error with u");
	det = IMCalculator::calculateDeterminant(v);
	assertFalse(det == 1 || det == -1, "determinant error with v");
	assertFalse(u * m* v == s , "snf error");
	for(int i = 0; i < 2; ++i)
	{
		for(int j = 0; j < 2; ++j)
		{
			if(i == j && i < 1)
			{
				assertNotEquale((s(i + 1,i + 1)/s(i, i)) * s(i, i) ,s(i + 1, i + 1), "elements not elementary divisors!");
			}
			else if( i != j)
			{
				assertNotEquale(s(i,j), 0, "Shape error");
			}
		}
	}
}

void SmithNormalFormTest::testTransformation6()
{
	IMatrix m(2,2);
//	m(0,0) = 2;		m(0,1) = 4;		m(0,2) = 4;
//	m(1,0) = -6; 	m(1,1) = 6; 	m(1,2) = 12;
//	m(2,0) = 10;	m(2,1) = -4;	m(2,2) = -16;
	m(0,0) = -3;	m(0,1) = 2;
	m(1,0) = 3; 	m(1,1) = -4;

	ISmithNormalForm snf(m,true, ISmithNormalForm::LEFT_POSITIVE);
	IMatrix u = snf["U"];
	IMatrix v = snf["V"];
	IMatrix s = snf["S"];

//	std::cout<<"Original matrix:"<<std::endl<<m<<std::endl;
//	std::cout<<"S:"<<std::endl<<s<<std::endl;
//	std::cout<<"U:"<<std::endl<<u<<std::endl;
//	std::cout<<"V:"<<std::endl<<v<<std::endl;
	int det = IMCalculator::calculateDeterminant(u);
	assertDifferentHigher(1.0, 0.0001, det,"Determinant error with u");
	det = IMCalculator::calculateDeterminant(v);
	assertFalse(det == 1 || det == -1, "determinant error with v");
	assertFalse(u * m * v == s , "snf error");
	for(int i = 0; i < 2; ++i)
	{
		for(int j = 0; j < 2; ++j)
		{
			if(i == j && i < 1)
			{
				assertNotEquale((s(i + 1,i + 1)/s(i, i)) * s(i, i) ,s(i + 1, i + 1), "elements not elementary divisors!");
			}
			else if( i != j)
			{
				assertNotEquale(s(i,j), 0, "Shape error");
			}
		}
	}
}

void SmithNormalFormTest::testTransformation7()
{
	IMatrix m(2,2);
//	m(0,0) = 2;		m(0,1) = 4;		m(0,2) = 4;
//	m(1,0) = -6; 	m(1,1) = 6; 	m(1,2) = 12;
//	m(2,0) = 10;	m(2,1) = -4;	m(2,2) = -16;

//	m(0,0) = -3;	m(0,1) = -5;
//	m(1,0) = 3; 	m(1,1) = 1;

	m(0,0) = 0;	m(0,1) = 1;
	m(1,0) = 1; 	m(1,1) = 5;

	ISmithNormalForm snf(m, true, ISmithNormalForm::LEFT_POSITIVE);
	IMatrix u = snf["U"];
	IMatrix v = snf["V"];
	IMatrix s = snf["S"];

//	std::cout<<"Original matrix:"<<std::endl<<m<<std::endl;
//	std::cout<<"S:"<<std::endl<<s<<std::endl;
//	std::cout<<"U:"<<std::endl<<u<<std::endl;
//	std::cout<<"V:"<<std::endl<<v<<std::endl;
	int det = IMCalculator::calculateDeterminant(u);
	assertDifferentHigher(1.0, 0.0001, det,"Determinant error with u");

	det = IMCalculator::calculateDeterminant(s);
	assertNotEquale(1, det, "Determinant error with s");
	det = IMCalculator::calculateDeterminant(v);
	assertFalse(det == 1 || det == -1, "determinant error with v");
	assertFalse(u * m * v == s , "snf error");
	for(int i = 0; i < 2; ++i)
	{
		for(int j = 0; j < 2; ++j)
		{
			if(i == j && i < 1)
			{
				assertNotEquale((s(i + 1,i + 1)/s(i, i)) * s(i, i) ,s(i + 1, i + 1), "elements not elementary divisors!");
			}
			else if( i != j)
			{
				assertNotEquale(s(i,j), 0, "Shape error");
			}
		}
	}
}

void SmithNormalFormTest::testTransformation8()
{
	IMatrix m(3,3);
//	m(0,0) = 2;		m(0,1) = 4;		m(0,2) = 4;
//	m(1,0) = -6; 	m(1,1) = 6; 	m(1,2) = 12;
//	m(2,0) = 10;	m(2,1) = -4;	m(2,2) = -16;
	m(0,0) = 2;		m(0,1) = 3;		m(0,2) = 10;
	m(1,0) = 12; 	m(1,1) = 20; 	m(1,2) = 76;
	m(2,0) = 2;	m(2,1) = -1;	m(2,2) = 45;

	ISmithNormalForm snf(m,true,ISmithNormalForm::LEFT_POSITIVE);
	IMatrix u = snf["U"];
	IMatrix v = snf["V"];
	IMatrix s = snf["S"];

/*	std::cout<<"Original matrix:"<<std::endl<<m<<std::endl;
	std::cout<<"S:"<<std::endl<<s<<std::endl;
	std::cout<<"U:"<<std::endl<<u<<std::endl;
	std::cout<<"V:"<<std::endl<<v<<std::endl;*/
	int det = IMCalculator::calculateDeterminant(u);
	assertNotEquale(1, det,"Determinant error with u");
	det = IMCalculator::calculateDeterminant(v);
	assertFalse(det == 1 || det == -1, "determinant error with v");
	assertFalse( u * m * v == s , "snf error");
	for(int i = 0; i < 3; ++i)
	{
		for(int j = 0; j < 3; ++j)
		{
			if(i == j && i < 2)
			{
				assertNotEquale((s(i + 1,i + 1)/s(i, i)) * s(i, i) ,s(i + 1, i + 1), "elements not elementary divisors!");
			}
			else if( i != j)
			{
				assertNotEquale(s(i,j), 0, "Shape error");
			}
		}
	}
}

void SmithNormalFormTest::testTransformation9()
{
	IMatrixI m(3,3);
//	m(0,0) = 2;		m(0,1) = 4;		m(0,2) = 4;
//	m(1,0) = -6; 	m(1,1) = 6; 	m(1,2) = 12;
//	m(2,0) = 10;	m(2,1) = -4;	m(2,2) = -16;
	m(0,0) = (gaussian_int_t)2;		m(0,1) = (gaussian_int_t)3;		m(0,2) = (gaussian_int_t)10;
	m(1,0) = (gaussian_int_t)12; 	m(1,1) = (gaussian_int_t)20; 	m(1,2) = (gaussian_int_t)76;
	m(2,0) = (gaussian_int_t)2;	m(2,1) = (gaussian_int_t)-1;	m(2,2) = (gaussian_int_t)45;

	ISmithNormalFormI snf(m,true,ISmithNormalFormI::LEFT_POSITIVE);
	IMatrixI u = snf["U"];
	IMatrixI v = snf["V"];
	IMatrixI s = snf["S"];

	/*std::cout<<"Original matrix:"<<std::endl<<m<<std::endl;
	std::cout<<"S:"<<std::endl<<s<<std::endl;
	std::cout<<"U:"<<std::endl<<u<<std::endl;
	std::cout<<"V:"<<std::endl<<v<<std::endl;*/
	gaussian_int_t det = IMCalculatorI::calculateDeterminant(u);
  assertFalse(det == gaussian_int_t(1), "Determinant error with u");
	det = IMCalculatorI::calculateDeterminant(v);
	assertFalse(det == gaussian_int_t(1) || det == gaussian_int_t(-1), "determinant error with v");
	assertFalse( u * m * v == s , "snf error");
	for(int i = 0; i < 3; ++i)
	{
		for(int j = 0; j < 3; ++j)
		{
			if(i == j && i < 2)
			{
				assertFalse((s(i + 1,i + 1)/s(i, i)) * s(i, i) == s(i + 1, i + 1), "elements not elementary divisors!");
			}
			else if( i != j)
			{
				assertFalse(s(i,j) == gaussian_int_t(0), "Shape error");
			}
		}
	}
}


#include "run_SmithNormalFormTest._cpp_"

