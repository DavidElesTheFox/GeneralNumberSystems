#ifndef NUMBERCALCULAOTRTEST_H
#define NUMBERCALCULATORTEST_H

#include <MATH/Algebra/numbercalculator.h>

#include <Tester/testcase.h>

#include <Exceptions/exception.h>

class NumberCalculatorTest:
	public Tester::TestCase
{
	public:
		NumberCalculatorTest();

		void run();

		void testAbs();
		void testAbsFloat();
		void testEquals();
		void testEqualsDouble();
		void testEqualsFloat();
		void testNonNegative();
		void testIsPositive();
		void testFloor();
		void testCeil();
		void testPow();
		void testRoot();
};


#endif //NUMBERCALCULATORTEST_H

