#ifndef MATRIXCALCULATORTEST_H
#define MATRIXCALCULATORTEST_H

#include <Tester/testcase.h>
#include <MATH/LinearAlgebra/matrix.h>
#include <MATH/LinearAlgebra/matrixcalculator.h>

class MatrixCalculatorTest: public Tester::TestCase
{
	public:
		static const double PRECISION = 0.001;
		MatrixCalculatorTest();

		void run();

		void testNorm_1();
		void testNorm_Inf();
		void testInverseExists();
		void testInverseNotExists();

		void testIsDiagonal();

		void testTransponate();
		void testDeterminantNotNull();
		void testDeterminantNull();
		void testRank();
		void testFullRank();
		void testRest();
    void testCharacteristicPolynomial();
    void testIsExpansive();
    void testIsExpansive2();
};


#endif //MATRIXCALCULATORTEST_H

