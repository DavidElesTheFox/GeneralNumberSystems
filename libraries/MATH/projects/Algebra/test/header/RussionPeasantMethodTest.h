#ifndef RUSSIONPEASANTMETHOD_TEST_H
#define RUSSIONPEASANTMETHOD_TEST_H

#include <Tester/testcase.h>
#include <MATH/Algebra/russionpeasantmethod.h>
#include <Exceptions/exception.h>

#include <time.h>

class RussionPeasantMethodTest: public Tester::TestCase
{
    public:
        RussionPeasantMethodTest();

        virtual void run();

        void testPow();
};

#endif


