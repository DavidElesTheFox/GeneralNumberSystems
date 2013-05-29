#include "../header/QuotientFieldTest.h"

typedef MATH::Algebra::QuotientField<int> Fraction;

QuotientFieldTest::QuotientFieldTest() 
  :Tester::TestCase("QuotientFieldTest")
{
}


void QuotientFieldTest::testCreateElement() 
{
  Fraction a(15,5);
  assertNotEquale(a.getNominator(), 1);
  assertNotEquale(a.getCounter(), 3);
}

void QuotientFieldTest::testPrefixAdd() 
{
  Fraction a(17,5);
  assertNotEquale((++a).getCounter(), 22);
  assertNotEquale(a.getNominator(), 5);
}

void QuotientFieldTest::testPostfixAdd() 
{
  Fraction a(17,5);
  assertNotEquale((a++).getCounter(), 17);
  assertNotEquale(a.getNominator(), 5);
}

void QuotientFieldTest::testPrefixMinus() 
{
  Fraction a(17,5);
  assertNotEquale((--a).getCounter(), 12);
  assertNotEquale(a.getNominator(), 5);
}

void QuotientFieldTest::testPostfixMinus() 
{
  Fraction a(17,5);
  assertNotEquale((a--).getCounter(), 17);
  assertNotEquale(a.getNominator(), 5);
}

void QuotientFieldTest::testShortAdd() 
{
  Fraction a(6,5);
  Fraction b(2,3);
  a += b;
  assertNotEquale(a.getNominator(), 15);
  assertNotEquale(a.getCounter(), 28);
}

void QuotientFieldTest::testShortMinus() 
{
  Fraction a(3,5);
  Fraction b(2,3);
  a -= b;
  assertNotEquale(a.getNominator(), 15);
  assertNotEquale(a.getCounter(), -1);
}

void QuotientFieldTest::testShortDiv() 
{
  Fraction a(3,5);
  Fraction b(2,3);
  a /= b;
  assertNotEquale(a.getNominator(), 10);
  assertNotEquale(a.getCounter(), 9);
}

void QuotientFieldTest::testShortMult() 
{
  Fraction a(3,5);
  Fraction b(2,3);
  a *= b;
  assertNotEquale(a.getNominator(), 5);
  assertNotEquale(a.getCounter(), 2);
}

void QuotientFieldTest::testToString() 
{
	
}

void QuotientFieldTest::testEq() 
{
  Fraction a(3,5);
  Fraction b(3,5);
  assertFalse(a == b);
}

void QuotientFieldTest::testNotEq() 
{
  Fraction a(3,5);
  Fraction b(3,6);
  assertFalse(a != b);
}

void QuotientFieldTest::testL()
{
  Fraction a(23,2);
  Fraction b(43,12);
  assertFalse(b < a);
}

void QuotientFieldTest::testH()
{
  Fraction a(23,2);
  Fraction b(43,12);
  assertFalse(a > b);
}

void QuotientFieldTest::testLE()
{
  Fraction a(43,12);
  Fraction b(43,12);
  assertFalse(b <= a);
}

void QuotientFieldTest::testHE()
{
  Fraction a(43,12);
  Fraction b(43,12);
  assertFalse(a >= b);
}

void QuotientFieldTest::testAdd() 
{
  Fraction a(3,2);
  Fraction b(14,4);
  Fraction c = a + b;
  assertNotEquale(c.getCounter(), 5);
  assertNotEquale(c.getNominator(), 1);
}

void QuotientFieldTest::testMinus() 
{
  Fraction a(3,2);
  Fraction b(14,4);
  Fraction c = a - b;
  assertNotEquale(c.getCounter(), -2);
  assertNotEquale(c.getNominator(), 1);
}

void QuotientFieldTest::testMult() 
{
  Fraction a(3,2);
  Fraction b(10,4);
  Fraction c = a * b;
  assertNotEquale(c.getCounter(), 15);
  assertNotEquale(c.getNominator(), 4);
}

void QuotientFieldTest::testDiv() 
{
  Fraction a(3,2);
  Fraction b(10,4);
  Fraction c = a / b;
  assertNotEquale(c.getCounter(), 3);
  assertNotEquale(c.getNominator(), 5);
}

void QuotientFieldTest::testPreasureAdd() 
{
	int limit = 10000;
	Fraction a = 3;
	Fraction b = 4;
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
	std::cout<<"1 000 times different"<<std::endl;
}

void QuotientFieldTest::testPreasureMult() 
{
	int limit = 10000;
	Fraction a = 3234;
	Fraction b = 4324;
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

#include "run_QuotientFieldTest._cpp_"

