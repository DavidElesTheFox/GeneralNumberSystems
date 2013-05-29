#ifndef IDEALADICREPRESENTATION_TEST_H
#define IDEALADICREPRESENTATION_TEST_H

#include <Tester/testcase.h>
#include <MATH/Algebra/idealadicrepresentation.h>

#include <time.h>

class IdealAdicRepresentationTest: public Tester::TestCase
{
    public:
        IdealAdicRepresentationTest();

        virtual void run();

        void testCreateElement();
				void testCreateInfinityElement();

        void testCreateWellFormattedElement();
				void testCreateWrongFormattedElement();

				void testPrefixAdd();
				void testPostfixAdd();

				void testPrefixMinus();
				void testPostfixMinus();
				void testPostfixWrongMinus();
				void testPrefixWrongMinus();

				void testShortAdd();
				void testShortMinus();
				void testShortMinusWrong();

				void testShortDiv1();
				void testShortDiv2();

				void testShortMult();

				void testShortMod1();
				void testShortMod2();

				void testToString();

				void testLcoeff();

				void testDegree();

				void testEq();

				void testNotEq();

				void testAdd();
				void testMinus();
				void testWrongMinus();
				void testMult();
				void testDiv1();
				void testDiv2();
				void testMod1();
				void testMod2();

				void testShiftLeft();
				void testShiftRight();

				void testPreasureAdd();
				void testPreasureMult();
};

#endif

