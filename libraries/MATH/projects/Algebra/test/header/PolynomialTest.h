#ifndef POLYNOMIAL_TEST_H
#define POLYNOMIAL_TEST_H

#include <Tester/testcase.h>
#include <MATH/Algebra/polynomial.h>


class PolynomialTest: public Tester::TestCase
{
	public:
		PolynomialTest();

		virtual void run();

		void testCreateElement();
		void testCreateElement2();
		void testCreateFormattedElement();

		void testAdd();
		void testSubstract();
		void testMult();

		void testInterp();

};


#endif

