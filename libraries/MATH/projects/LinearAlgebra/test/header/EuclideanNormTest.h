#ifndef EUCLIDEANNORM_TEST_H
#define EUCLIDEANNORM_TEST_H

#include <Tester/testcase.h>
#include <MATH/LinearAlgebra/euclideannorm.h>

class EuclideanNormTest:public Tester::TestCase
{

  public:
    EuclideanNormTest();

    virtual void run();

    void testMatrixNormFloat();
    void testMatrixNormInt();
    void testVectorNormFloat();
    void testVectorNormInt();

};


#endif
