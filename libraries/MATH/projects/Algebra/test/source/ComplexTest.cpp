#include "../header/ComplexTest.h"


ComplexTest::ComplexTest()
  :Tester::TestCase("ComplexTest")
{}

typedef MATH::Algebra::Complex<double> Complex;

void ComplexTest::testCreateElement() 
{
  Complex a(2.0, 3.0);
  assertNotEquale(a.getRe(), 2.0);
  assertNotEquale(a.getIm(), 3.0);
  a = Complex(2.0,3.0);
}

void ComplexTest::testPrefixAdd() 
{
  Complex a(2.0, 3.0);
  ++a;
  assertNotEquale(a.getRe(), 3.0);
  assertNotEquale(a.getIm(), 3.0);
}

void ComplexTest::testPostfixAdd() 
{
  Complex a(2.0, 3.0);
  a++;
  assertNotEquale(a.getRe(), 3.0);
  assertNotEquale(a.getIm(), 3.0);
}

void ComplexTest::testPrefixMinus() 
{
  Complex a(2.0, 3.0);
  --a;
  assertNotEquale(a.getRe(), 1.0);
  assertNotEquale(a.getIm(), 3.0);
}

void ComplexTest::testPostfixMinus() 
{
  Complex a(2.0, 3.0);
  a--;
  assertNotEquale(a.getRe(), 1.0);
  assertNotEquale(a.getIm(), 3.0);
}

void ComplexTest::testShortAdd() 
{
  Complex a(2.0, 3.0);
  a += 32;
  assertNotEquale(a.getRe(), 34.0);
  assertNotEquale(a.getIm(), 3.0);
}

void ComplexTest::testShortMinus() 
{
  Complex a(2.0, 3.0);
  a -= 32;
  assertNotEquale(a.getRe(), -30.0);
  assertNotEquale(a.getIm(), 3.0);
}

void ComplexTest::testShortDiv() 
{
  Complex a(2.0, 3.0);
  a /= 2;
  assertDifferentHigher(a.getRe(), 1.0, 0.001);
  assertDifferentHigher(a.getIm(), 1.5, 0.001);
}

void ComplexTest::testShortMult() 
{
  Complex a(2.0, 3.0);
  a *= 10;
  assertNotEquale(a.getRe(), 20.0);
  assertNotEquale(a.getIm(), 30.0);
}

void ComplexTest::testToString() 
{
	
}

void ComplexTest::testEq() 
{
  Complex a(2.0, 3.0);
  Complex b(2.0, 3.0);
  assertFalse(a == b);
}

void ComplexTest::testNotEq() 
{
  Complex a(2.0, 3.0);
  Complex b(2.0, 4.0);
  assertFalse(a != b);
}

void ComplexTest::testAdd() 
{
  Complex a(2.0, 3.0);
  Complex b(2.0, 4.0);
  Complex c = (a + b);
  assertDifferentHigher(c.getRe(), 0.001, 4.0);
  assertDifferentHigher(c.getIm(), 0.001, 7.0);
}

void ComplexTest::testMinus() 
{
  Complex a(2.0, 3.0);
  Complex b(4.0, 3.0);
  Complex c = (a - b);
  assertDifferentHigher(c.getRe(), 0.001, -2.0);
  assertDifferentHigher(c.getIm(), 0.001, 0.0);
  assertFalse(c.isReal());
}

void ComplexTest::testMult() 
{
  Complex a(2.0, 3.0);
  Complex b(4.0, 3.0);
  Complex c = (a * b);
  assertDifferentHigher(c.getRe(), 0.001, -1.0);
  assertDifferentHigher(c.getIm(), 0.001, 18.0);
}

void ComplexTest::testDiv() 
{
  Complex a(2.0, 3.0);
  Complex b(4.0, 3.0);
  Complex c = (a / b);
  assertDifferentHigher(c.getRe(), 0.001, 1.0);
  assertDifferentHigher(c.getIm(), 0.001, 0.0);
  assertFalse(c.isReal());
}

void ComplexTest::testMod() 
{
  Complex a(2.0, 3.0);
  Complex b(4.0, 3.0);
  Complex c = (a % b);
  assertDifferentHigher(c.getRe(), 0.001, -2.0);
  assertDifferentHigher(c.getIm(), 0.001, 0.0);
  assertFalse(c.isReal());
}

void ComplexTest::testPreasureAdd() 
{
	
	int limit = 10000;
	Complex a = 3;
	Complex b = 4;
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

void ComplexTest::testPreasureMult() 
{
	
	int limit = 10000;
	Complex a = 3234;
	Complex b = 4324;
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

#include "run_ComplexTest._cpp_"

