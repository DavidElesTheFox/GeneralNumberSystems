#include "../header/NumberSystemTest.h"

#include <MATH/Algebra/complex.h>

typedef MATH::NumberSystem::NumberSystem<int, float,
				                                 MATH::LinearAlgebra::Matrix,
																				 MATH::LinearAlgebra::Vector> NumSys;
typedef NumSys::DigitSet NSDigitSet;

typedef MATH::LinearAlgebra::Vector<int> iVector;
typedef MATH::LinearAlgebra::Vector<float> fVector;
typedef MATH::LinearAlgebra::Matrix<int> iMatrix;
typedef MATH::LinearAlgebra::Matrix<float> fMatrix;

typedef MATH::Algebra::Complex<float> complex_t;
typedef MATH::Algebra::Complex<int> gaussian_int_t;

typedef MATH::NumberSystem::NumberSystem<gaussian_int_t, complex_t,
				                                 MATH::LinearAlgebra::Matrix,
																				 MATH::LinearAlgebra::Vector> NumSysI;
typedef NumSysI::DigitSet NSDigitSetI;

typedef MATH::LinearAlgebra::Vector<gaussian_int_t> iVectorI;
typedef MATH::LinearAlgebra::Vector<complex_t> fVectorI;
typedef MATH::LinearAlgebra::Matrix<gaussian_int_t> iMatrixI;
typedef MATH::LinearAlgebra::Matrix<complex_t> fMatrixI;

NumberSystemTest::NumberSystemTest() :Tester::TestCase("NumberSystemTest.res")
{	}


void NumberSystemTest::testChop()
{
	NSDigitSet digits;
	iVector d(2, 0);
	digits.push_back(d);
	d[0] = 1;
	digits.push_back(d);
	d[0] = -1;
	d[1] = 1;
	digits.push_back(d);

	iMatrix base(2,2);
	base(0,0) = 0;	base(0,1)= -3;
	base(1,0) = 1; base(1,1) = 0;

	NumSys ns(base, digits);

	iVector number(2, 0);
	number[0] = -1;
	iVector ret1 = ns.chop(number);
	assertFalse(ret1[0] == number[0]);
	assertFalse(ret1[1] == number[1]);
	number[0] = 0;
	ret1 = ns.chop(number);
	assertFalse(ret1[0] == number[0]);
	assertFalse(ret1[1] == number[1]);
}

void NumberSystemTest::testChop2()
{
	NSDigitSet digits;
	iVector d(2, 0);
	digits.push_back(d);
	d[0] = 1;
	digits.push_back(d);
	d[0] = 0;
	d[1] = 1;
	digits.push_back(d);
	d[0] = 0;
	d[1] = -1;
	digits.push_back(d);
	d[0] = -6;
	d[1] = -5;
	digits.push_back(d);


	iMatrix base(2,2);
	base(0,0) = 2;	base(0,1)= -1;
	base(1,0) = 1; base(1,1) = 2;

	NumSys ns(base, digits);
	iVector number(2, 0);
	number[0] = 5;
	number[1] = 0;
	try
	{
		for(int i = 0; i < 10; ++i)
		{
			number = ns.chop(number);
			//std::cout<<"i: "<<i<<std::endl<<number<<"->\n"<<number2<<std::endl;
		}
	}catch(Exceptions::RuntimeException& ex)
	{
		std::cout<<ex<<std::endl;
		assertTrue(true);
	}
	assertNotEquale(number[0],2);
	assertNotEquale(number[1],-1);
}

void NumberSystemTest::testChop3()
{
	NSDigitSetI digits;
	iVectorI d(2, 0);
	digits.push_back(d);
	d[0] = (gaussian_int_t)1;
	digits.push_back(d);
	d[0] = (gaussian_int_t)0;
	d[1] = (gaussian_int_t)1;
	digits.push_back(d);
	d[0] = (gaussian_int_t)0;
	d[1] = (gaussian_int_t)-1;
	digits.push_back(d);
	d[0] = (gaussian_int_t)-6;
	d[1] = (gaussian_int_t)-5;
	digits.push_back(d);

	iMatrixI base(2,2);
	base(0,0) = (gaussian_int_t)2;	base(0,1)= (gaussian_int_t)-1;
	base(1,0) = (gaussian_int_t)1; base(1,1) = (gaussian_int_t)2;
	NumSysI ns(base, digits);
	iVectorI number(2, 0);
	number[0] = (gaussian_int_t)5;
	number[1] = (gaussian_int_t)0;
	try
	{
		for(int i = 0; i < 10; ++i)
		{
			number = ns.chop(number);
	//		std::cout<<"i: "<<i<<std::endl<<number<<std::endl;
		}
	}catch(Exceptions::RuntimeException& ex)
	{
		std::cout<<ex<<std::endl;
		assertTrue(true);
	}
	assertFalse(number[0] == (gaussian_int_t)2);
	assertFalse(number[1] == (gaussian_int_t)-1);
}

void NumberSystemTest::testChopPressure()
{
	NSDigitSet digits;
	iVector d(2, 0);
	digits.push_back(d);
	d[0] = 1;
	digits.push_back(d);
	d[0] = 0;
	d[1] = 1;
	digits.push_back(d);
	d[0] = 0;
	d[1] = -1;
	digits.push_back(d);
	d[0] = -6;
	d[1] = -5;
	digits.push_back(d);


	iMatrix base(2,2);
	base(0,0) = 2;	base(0,1)= -1;
	base(1,0) = 1; base(1,1) = 2;

	NumSys ns(base, digits);
	iVector number(2, 0);
	number[0] = 10123124;
	number[1] = 1023120;
	clock_t start = clock();
	try
	{
		for(int i = 0; i < 300000; ++i)
		{
			number = ns.chop(number);
			//std::cout<<"i: "<<i<<std::endl<<number<<"->\n"<<number2<<std::endl;
		}
	}catch(Exceptions::RuntimeException& ex)
	{
		std::cout<<ex<<std::endl;
		assertTrue(true);
	}
	assertHigher(((double)clock() - start)/CLOCKS_PER_SEC, 0.5);
	assertFalse(number[0] == 0);
	assertFalse(number[1] == 0);

}

#include "run_NumberSystemTest._cpp_"
