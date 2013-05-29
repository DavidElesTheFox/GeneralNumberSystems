#ifndef PADIC_TEST_H
#define PADIC_TEST_H

#include <Tester/testcase.h>
#include <MATH/Algebra/padicshape.h>

#include <time.h>

class PAdicTest: public Tester::TestCase
{
    public:
        PAdicTest();

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

