#ifndef INTEGER_TEST_H
#define INTEGER_TEST_H

#include <Tester/testcase.h>
#include <MATH/Algebra/integer.h>

#include <time.h>

class IntegerTest:public Tester::TestCase
{
    public:
        IntegerTest();

        virtual void run();

        void testConstructor();
        void testCopyConstrucror();
        void testBeEq();

        void testOpMinus();
        void testOpPlusEq();
        void testOpMinusEq();
        void testOpMultEq();
        void testOpDivEq();


        void testOpEq1();
        void testOpEq2();

        void testOpNe1();
        void testOpNe2();

        void testOplt1();
        void testOplt2();

        void testOpgt1();
        void testOpgt2();

        void testOple1();
        void testOple2();

        void testOpge1();
        void testOpge2();

        void testOpAdd1();
        void testOpAdd2();

        void testOpMinus1();
        void testOpMinus2();

        void testOpMult1();
        void testOpMult2();

        void testOpDiv1();
        void testOpDiv2();

		void testPressure();

		void testOpPp();

		void testOpMm();

};


#endif
