#ifndef VECTORTEST_H
#define VECTORTEST_H

#include <Tester/testcase.h>
#include <MATH/LinearAlgebra/vector.h>


class VectorTest: public Tester::TestCase
{
		static const double PRECISION = 0.001;
		typedef MATH::LinearAlgebra::Vector<double> dVector;
    public:
        VectorTest():Tester::TestCase("VectorTest.res") {}
        virtual void run();
 /*******************Test Cases:*******************/
        void testConstructor();
        void testCopyConstructor();
        void testConstructor2();

        void testCount();

        void testOperator_BR_C();
        void testOperator_BR();

        void testOperatorBeEQ();

        void testOperatorEQ();

        void testOperatorPlus();

        void testOperatorMinus();

        void testOperatorMultV_D();
        void testOperatorMultD_V();
        void testOperatorMultV_V();

        void testXmultiply();
};



#endif
