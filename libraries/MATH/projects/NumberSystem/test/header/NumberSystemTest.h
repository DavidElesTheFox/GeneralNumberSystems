#ifndef NUMBERSYSTEM_TEST_H
#define NUMBERSYSTEM_TEST_H

#include <Tester/testcase.h>
#include <MATH/NumberSystem/numbersystem.h>
#include <MATH/LinearAlgebra/matrix.h>
#include <MATH/LinearAlgebra/vector.h>

#include <time.h>
#include <fstream>

class NumberSystemTest:public Tester::TestCase
{
    public:
        NumberSystemTest();

        virtual void run();

        void testChop();
        void testChop2();
        void testChop3();
        void testChopPressure();

};


#endif
