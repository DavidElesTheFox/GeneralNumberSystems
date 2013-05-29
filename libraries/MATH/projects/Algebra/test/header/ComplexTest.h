#ifndef COMPLEX_TEST_H
#define COMPLEX_TEST_H

#include <Tester/testcase.h>
#include <MATH/Algebra/complex.h>

#include <time.h>

class ComplexTest: public Tester::TestCase
{
    public:
        ComplexTest();

        virtual void run();

        void testCreateElement();

				void testPrefixAdd();
				void testPostfixAdd();

				void testPrefixMinus();
				void testPostfixMinus();

				void testShortAdd();
				void testShortMinus();

				void testShortDiv();

				void testShortMult();

				void testToString();

				void testEq();

				void testNotEq();

				void testAdd();
				void testMinus();
				void testMult();
				void testDiv();
				void testMod();

				void testPreasureAdd();
				void testPreasureMult();
};

#endif

