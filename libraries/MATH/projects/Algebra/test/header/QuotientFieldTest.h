#ifndef QUOTIENTFIELD_TEST_H
#define QUOTIENTFIELD_TEST_H

#include <Tester/testcase.h>
#include <MATH/Algebra/quotientfield.h>

#include <time.h>

class QuotientFieldTest: public Tester::TestCase
{
    public:
        QuotientFieldTest();

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
        void testL();
        void testH();
        void testLE();
        void testHE();

        void testAdd();
        void testMinus();
        void testMult();
        void testDiv();

        void testPreasureAdd();
        void testPreasureMult();
};

#endif


