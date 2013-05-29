#ifndef SMITHNORMALFORM_TEST_H
#define SMITHNORMALFORM_TEST_H

#include <Tester/testcase.h>
#include <MATH/LinearAlgebra/matrix.h>
#include <MATH/LinearAlgebra/smithnormalform.h>

#include <time.h>

class SmithNormalFormTest:public Tester::TestCase
{
    public:
        SmithNormalFormTest();

        virtual void run();

        void testTransformation();
        void testTransformation2();
        void testTransformation3();
        void testTransformation4();
        void testTransformation5();
        void testTransformation6();
				void testTransformation7();
				void testTransformation8();
				void testTransformation9();

};


#endif
