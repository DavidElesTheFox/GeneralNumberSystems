#include "../header/IntegerTest.h"


IntegerTest::IntegerTest():Tester::TestCase("IntegerTest.res")
{}

void IntegerTest::testConstructor()
{
	MATH::Algebra::Integer<5> i = 6;
	assertFalse(i==1);

}

void IntegerTest::testCopyConstrucror()
{
	MATH::Algebra::Integer<5> i = 6;
	MATH::Algebra::Integer<5> j = i;
	assertFalse(j==1);
}

void IntegerTest::testBeEq()
{
	MATH::Algebra::Integer<5> i = 6;
	MATH::Algebra::Integer<5> j;
	j = i;
	assertFalse(j==1);
}

void IntegerTest::testOpMinus()
{
	MATH::Algebra::Integer<5> i = 6;

	assertFalse(-i==-1);
}

void IntegerTest::testOpPlusEq()
{
	MATH::Algebra::Integer<5> i = 6;
	i+= 1;
	assertFalse(i==2);
}

void IntegerTest::testOpMinusEq()
{
	MATH::Algebra::Integer<5> i = 6;
	i-= 1;
	assertFalse(i==0);
}

void IntegerTest::testOpMultEq()
{
	MATH::Algebra::Integer<5> i = 6;
	i*= 3;
	assertFalse(i==3);
}

void IntegerTest::testOpDivEq()
{
	MATH::Algebra::Integer<5> i = 9;
	i/= 2;
	assertFalse(i==2);
}

void IntegerTest::testOpEq1()
{
	MATH::Algebra::Integer<5> i = 6;
	assertFalse(i==1);
}

void IntegerTest::testOpEq2()
{
	MATH::Algebra::Integer<5> i = 6;
	MATH::Algebra::Integer<5> j = 6;
	assertFalse(i==j);
}

void IntegerTest::testOpNe1()
{
	MATH::Algebra::Integer<5> i = 6;
	MATH::Algebra::Integer<5> j = 7;
	assertFalse(i!=j);
}

void IntegerTest::testOpNe2()
{
	MATH::Algebra::Integer<5> i = 6;
	assertFalse(i!=4);
}

void IntegerTest::testOplt1()
{
	MATH::Algebra::Integer<5> i = 6;
	MATH::Algebra::Integer<5> j = 4;
	assertFalse(i<j);
}

void IntegerTest::testOplt2()
{
	MATH::Algebra::Integer<5> i = 6;
	assertFalse(i<4);
}

void IntegerTest::testOpgt1()
{
	MATH::Algebra::Integer<5> i = 3;
	MATH::Algebra::Integer<5> j = 4;
	assertFalse(j>i);
}

void IntegerTest::testOpgt2()
{
	MATH::Algebra::Integer<5> i = 6;
	assertFalse(i>0);
}

void IntegerTest::testOple1()
{
	MATH::Algebra::Integer<5> i = 6;
	MATH::Algebra::Integer<5> j = 4;
	assertFalse(i<=j);
}

void IntegerTest::testOple2()
{
	MATH::Algebra::Integer<5> i = 6;
	assertFalse(i<=4);
}

void IntegerTest::testOpge1()
{
	MATH::Algebra::Integer<5> i = 3;
	MATH::Algebra::Integer<5> j = 4;
	assertFalse(j>=i);
}

void IntegerTest::testOpge2()
{
	MATH::Algebra::Integer<5> i = 6;
	assertFalse(i>=0);
}

void IntegerTest::testOpAdd1()
{
	MATH::Algebra::Integer<5> i = -1;
	MATH::Algebra::Integer<5> j = 2;
	assertFalse(i + j == 1);
}

void IntegerTest::testOpAdd2()
{
	MATH::Algebra::Integer<5> i = 3;
	assertFalse(i + 5 == 3);
}

void IntegerTest::testOpMinus1()
{
	MATH::Algebra::Integer<5> i = 3;
	MATH::Algebra::Integer<5> j = 4;
	assertFalse(i - 4 == -1);
}

void IntegerTest::testOpMinus2()
{
	MATH::Algebra::Integer<5> i = 3;
	assertFalse(i - 4 == -1);
}

void IntegerTest::testOpMult1()
{
	MATH::Algebra::Integer<5> i = 3;
	MATH::Algebra::Integer<5> j = 4;
	assertFalse(j*i == 2);
}

void IntegerTest::testOpMult2()
{
	MATH::Algebra::Integer<5> i = 3;
	assertFalse(i*-1 == -3);
}

void IntegerTest::testOpDiv1()
{
	MATH::Algebra::Integer<5> i = 14;
	MATH::Algebra::Integer<5> j = 2;
	assertFalse(i/j == 2);
}

void IntegerTest::testOpDiv2()
{
	MATH::Algebra::Integer<5> i = 3;
	assertFalse(i / -1 == -3);
}

void IntegerTest::testPressure()
{

	int limit = 100000000;
	int a = 0;
	clock_t start = clock();
	for(int i = 0; i < limit; ++i)
		a += 0;
	double time1 = (clock() - start)/(double)CLOCKS_PER_SEC;
	MATH::Algebra::Integer<5> aa;
	start = clock();
	for(int i = 0; i < limit; ++i)
		aa += 0;
	double time2 = (clock() - start)/(double)CLOCKS_PER_SEC;
	std::cout<<time1<<std::endl;
	std::cout<<time2<<std::endl;
}

void IntegerTest::testOpPp()
{
	MATH::Algebra::Integer<5> i = 4;
	assertFalse(++i == 0);
}

void IntegerTest::testOpMm()
{
	MATH::Algebra::Integer<5> i = -4;
	assertFalse(--i == 0);
}

#include "run_IntegerTest._cpp_"
