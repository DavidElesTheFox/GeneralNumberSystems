#ifndef ADJOINTMATRIX_TEST_H
#define ADJOINTMATRIX_TEST_H

#include <Tester/testcase.h>
#include <MATH/Algebra/number_traits.h>
#include <MATH/LinearAlgebra/matrix.h>
#include <MATH/LinearAlgebra/adjointmatrix.h>
#include <MATH/LinearAlgebra/matrixcalculator.h>
#include <time.h>

class AdjointMatrixTest:public Tester::TestCase
{

  public:
    AdjointMatrixTest();

    virtual void run();

    void testTransformation();
    void testTransformation2();
    void testTransformation3();

};


#endif
