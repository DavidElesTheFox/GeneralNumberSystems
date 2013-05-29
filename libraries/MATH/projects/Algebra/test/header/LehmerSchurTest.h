#ifndef LEHMERSCHUR_TEST_H
#define LEHMERSCHUR_TEST_H


#include <Tester/testcase.h>
#include <MATH/Algebra/lehmerschur.h>

#include <time.h>

class LehmerSchurTest: public Tester::TestCase
{
    public:
        LehmerSchurTest();

        virtual void run();

        void testExpansive();

				void testNonExpansive();
};


#endif

