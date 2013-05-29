#ifndef PNORM_TEST_H
#define PNORM_TEST_H

#include <Tester/testcase.h>
#include <MATH/LinearAlgebra/pnorm.h>

class PNormTest:public Tester::TestCase
{

  public:
    PNormTest();

    virtual void run();

    void testMatrixNormFloat();
    void testMatrixNormInt();
    void testVectorNormFloat();
    void testVectorNormInt();

};


#endif
