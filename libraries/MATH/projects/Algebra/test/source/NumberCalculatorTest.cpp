#include "../header/NumberCalculatorTest.h"

typedef MATH::Algebra::NumberCalculator<int> int_calc;
typedef MATH::Algebra::NumberCalculator<float> float_calc;
typedef MATH::Algebra::NumberCalculator<double> double_calc;

NumberCalculatorTest::NumberCalculatorTest():
	Tester::TestCase("NumberCalculatorTest.res")
{}


void NumberCalculatorTest::testAbs()
{
	int b = -10;
	int a = int_calc::abs(b);
	int c = int_calc::abs(a);
	assertNotEquale(a, 10);
	assertNotEquale(b, -10);
	assertNotEquale(c, 10);
}

void NumberCalculatorTest::testAbsFloat()
{
	float b = -10;
	float a = float_calc::abs(b);
	float c = float_calc::abs(a);
	assertNotEquale(a, 10.0f);
	assertNotEquale(b, -10.0f);
	assertNotEquale(c, 10.0f);
}

void NumberCalculatorTest::testEquals()
{
	int a = 2;
	int b = 2;
	assertFalse(int_calc::equals(a,b));
}

void NumberCalculatorTest::testEqualsDouble()
{
  double a = 0.11;
	double b = 0.011;
	double c = 0.1;
	assertFalse(double_calc::equals(a*c,b));
	assertEquale(a*c,b);
}

void NumberCalculatorTest::testEqualsFloat()
{
  float a = 0.11;
	float c = 0.011;
	float b = 0.1;
	assertFalse(float_calc::equals(a*b,c));
	assertEquale(a*b,c);
}

void NumberCalculatorTest::testNonNegative()
{
	float a = 0;
	assertFalse(float_calc::isNonNegative(a));
}

void NumberCalculatorTest::testIsPositive()
{
	float a = -0.1;
	assertTrue(float_calc::isPositive(a));
}

void NumberCalculatorTest::testFloor()
{
	float a = 3.42;
	assertNotEquale(float_calc::floor(a), 3.0f);
}

void NumberCalculatorTest::testCeil()
{
	float a = 3.001;
	assertNotEquale(float_calc::ceil(a), 4.0f);
}

void NumberCalculatorTest::testPow()
{
	int a = 4;
	assertNotEquale(int_calc::pow(4, 2), 16);
}

void NumberCalculatorTest::testRoot()
{
	int a = 16;
	assertNotEquale(int_calc::root(16,2), 4);

}

#include "run_NumberCalculatorTest._cpp_"

