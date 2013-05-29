#ifndef GCD_TEST_H
#define GCD_TEST_H

#include <Tester/testcase.h>
#include <MATH/Algebra/gcd.h>

#include <time.h>

class GcdTest:public Tester::TestCase
{
    public:
        GcdTest();

        virtual void run();

        void testGcd();
        void testGcd2();

};


#endif
