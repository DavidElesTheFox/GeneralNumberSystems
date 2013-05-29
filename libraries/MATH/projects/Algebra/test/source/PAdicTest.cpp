#include "../header/PAdicTest.h"


PAdicTest::PAdicTest():
  Tester::TestCase("PAdicTest")
{
}

void PAdicTest::testCreateElement() 
{
  MATH::Algebra::PAdicShape<2, unsigned> a = 15;
  assertNotEquale(a.getCoeff(0), 1);
  assertNotEquale(a.getCoeff(1), 1);
  assertNotEquale(a.getCoeff(2), 1);
  assertNotEquale(a.getCoeff(3), 1);
}

void PAdicTest::testPrefixAdd() 
{
  MATH::Algebra::PAdicShape<2, unsigned> a = 23;
  assertTrue(++a != a);
  assertNotEquale(a.getCoeff(0), 0);
  assertNotEquale(a.getCoeff(1), 0);
  assertNotEquale(a.getCoeff(2), 0);
  assertNotEquale(a.getCoeff(3), 1);
  assertNotEquale(a.getCoeff(4), 1);
}

void PAdicTest::testPostfixAdd() 
{
  MATH::Algebra::PAdicShape<2, unsigned> a = 23;
  assertTrue(a++ == a);
  assertNotEquale(a.getCoeff(0), 0);
  assertNotEquale(a.getCoeff(1), 0);
  assertNotEquale(a.getCoeff(2), 0);
  assertNotEquale(a.getCoeff(3), 1);
  assertNotEquale(a.getCoeff(4), 1);
}

void PAdicTest::testPrefixMinus() 
{
  MATH::Algebra::PAdicShape<2, unsigned> a = 25;
  assertTrue(--a != a);
  assertNotEquale(a.getCoeff(0), 0);
  assertNotEquale(a.getCoeff(1), 0);
  assertNotEquale(a.getCoeff(2), 0);
  assertNotEquale(a.getCoeff(3), 1);
  assertNotEquale(a.getCoeff(4), 1);
}

void PAdicTest::testPostfixMinus() 
{
	
  MATH::Algebra::PAdicShape<2, unsigned> a = 25;
  assertTrue(a-- == a);
  assertNotEquale(a.getCoeff(0), 0);
  assertNotEquale(a.getCoeff(1), 0);
  assertNotEquale(a.getCoeff(2), 0);
  assertNotEquale(a.getCoeff(3), 1);
  assertNotEquale(a.getCoeff(4), 1);
}

void PAdicTest::testShortAdd() 
{
  MATH::Algebra::PAdicShape<2, unsigned> a = 4;
  a += 20;
  assertNotEquale(a.getCoeff(0), 0);
  assertNotEquale(a.getCoeff(1), 0);
  assertNotEquale(a.getCoeff(2), 0);
  assertNotEquale(a.getCoeff(3), 1);
  assertNotEquale(a.getCoeff(4), 1);
}

void PAdicTest::testShortMinus() 
{
  MATH::Algebra::PAdicShape<2, unsigned> a = 44;
  a -= 20;
  assertNotEquale(a.getCoeff(0), 0);
  assertNotEquale(a.getCoeff(1), 0);
  assertNotEquale(a.getCoeff(2), 0);
  assertNotEquale(a.getCoeff(3), 1);
  assertNotEquale(a.getCoeff(4), 1);
}

void PAdicTest::testShortDiv() 
{
  MATH::Algebra::PAdicShape<2, unsigned> a = 45;
  a /= 4;
  assertNotEquale(a.getCoeff(0), 1);
  assertNotEquale(a.getCoeff(1), 1);
  assertNotEquale(a.getCoeff(2), 0);
  assertNotEquale(a.getCoeff(3), 1);
}

void PAdicTest::testShortMult() 
{
  MATH::Algebra::PAdicShape<2, unsigned> a = 11;
  a *= 4;
  assertNotEquale(a.getCoeff(0), 0);
  assertNotEquale(a.getCoeff(1), 0);
  assertNotEquale(a.getCoeff(2), 1);
  assertNotEquale(a.getCoeff(3), 1);
  assertNotEquale(a.getCoeff(4), 0);
  assertNotEquale(a.getCoeff(5), 1);
}

void PAdicTest::testToString() 
{
  MATH::Algebra::PAdicShape<2, unsigned> a = 11;
  assertNotEquale(a, "1*p^(3) + 0*p^(2) + 1*p^(1) + 1");
}

void PAdicTest::testEq() 
{
  MATH::Algebra::PAdicShape<2, unsigned> a = 11;
  MATH::Algebra::PAdicShape<2, unsigned> b = 12;
  assertFalse(a != b);
}

void PAdicTest::testNotEq() 
{
  MATH::Algebra::PAdicShape<2, unsigned> a = 11;
  MATH::Algebra::PAdicShape<2, unsigned> b = 11;
  assertFalse(a == b);
}

void PAdicTest::testAdd() 
{
  MATH::Algebra::PAdicShape<2, unsigned> a = 4;
  MATH::Algebra::PAdicShape<2, unsigned> b = 20;
  MATH::Algebra::PAdicShape<2, unsigned> c = a + b;
  assertNotEquale(c.getCoeff(0), 0);
  assertNotEquale(c.getCoeff(1), 0);
  assertNotEquale(c.getCoeff(2), 0);
  assertNotEquale(c.getCoeff(3), 1);
  assertNotEquale(c.getCoeff(4), 1);
}

void PAdicTest::testMinus() 
{
  MATH::Algebra::PAdicShape<2, unsigned> a = 44;
  MATH::Algebra::PAdicShape<2, unsigned> b = 20;
  MATH::Algebra::PAdicShape<2, unsigned> c = a - b;
  assertNotEquale(c.getCoeff(0), 0);
  assertNotEquale(c.getCoeff(1), 0);
  assertNotEquale(c.getCoeff(2), 0);
  assertNotEquale(c.getCoeff(3), 1);
  assertNotEquale(c.getCoeff(4), 1);
}

void PAdicTest::testMult() 
{
  MATH::Algebra::PAdicShape<2, unsigned> a = 11;
  MATH::Algebra::PAdicShape<2, unsigned> b = 4;
  MATH::Algebra::PAdicShape<2, unsigned> c = a * b;
  assertNotEquale(c.getCoeff(0), 0);
  assertNotEquale(c.getCoeff(1), 0);
  assertNotEquale(c.getCoeff(2), 1);
  assertNotEquale(c.getCoeff(3), 1);
  assertNotEquale(c.getCoeff(4), 0);
  assertNotEquale(c.getCoeff(5), 1);
}

void PAdicTest::testDiv() 
{
  MATH::Algebra::PAdicShape<2, unsigned> a = 45;
  MATH::Algebra::PAdicShape<2, unsigned> b = 4;
  MATH::Algebra::PAdicShape<2, unsigned> c = a / b;
  assertNotEquale(c.getCoeff(0), 1);
  assertNotEquale(c.getCoeff(1), 1);
  assertNotEquale(c.getCoeff(2), 0);
  assertNotEquale(c.getCoeff(3), 1);
}

void PAdicTest::testMod() 
{
  MATH::Algebra::PAdicShape<2, unsigned> a = 45;
  MATH::Algebra::PAdicShape<2, unsigned> b = 10;
  MATH::Algebra::PAdicShape<2, unsigned> c = a % b;
  assertNotEquale(c.getCoeff(0), 1);
  assertNotEquale(c.getCoeff(1), 0);
  assertNotEquale(c.getCoeff(2), 1);
}

void PAdicTest::testPreasureAdd() 
{
	int limit = 10000;
	MATH::Algebra::PAdicShape<2, unsigned> a = 3;
	MATH::Algebra::PAdicShape<2, unsigned> b = 4;
	clock_t start = clock();
	for (int i = 0; i < limit; ++i)
	{
		a + b;
	}
	double time1 = (clock() - start)/(double)CLOCKS_PER_SEC;
	int aa = 3;
	int bb = 4;
	start = clock();
	for (int i = 0; i < limit * 1000; ++i)
	{
		aa + bb;
	}
	double time2 = (clock() - start)/(double)CLOCKS_PER_SEC;
	std::cout<<time1<<std::endl;
	std::cout<<time2<<std::endl;
}

void PAdicTest::testPreasureMult() 
{
	int limit = 10000;
	MATH::Algebra::PAdicShape<2, unsigned> a = 3234;
	MATH::Algebra::PAdicShape<2, unsigned> b = 4324;

	clock_t start = clock();
	for (int i = 0; i < limit; ++i)
	{
		a * b;
	}
	double time1 = (clock() - start)/(double)CLOCKS_PER_SEC;
	int aa = 3234;
	int bb = 4324;

	start = clock();
	for (int i = 0; i < limit; ++i)
	{
		aa * bb;
	}
	double time2 = (clock() - start)/(double)CLOCKS_PER_SEC;
	std::cout<<time1<<std::endl;
	std::cout<<time2<<std::endl;
}

#include "run_PAdicTest._cpp_"

