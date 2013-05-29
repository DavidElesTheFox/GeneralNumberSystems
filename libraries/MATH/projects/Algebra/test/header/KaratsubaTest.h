#ifndef KARATSUBA_TEST_H
#define KARATSUBA_TEST_H

#include <Tester/testcase.h>
#include <MATH/Algebra/karatsuba.h>

#include <time.h>

class KaratsubaTest: public Tester::TestCase
{
    public:
        KaratsubaTest();

        virtual void run();

				void testMult();
				void testMult2();
				void testMult3();
				void testMult4();
};


#endif

