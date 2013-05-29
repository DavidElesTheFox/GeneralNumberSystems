#ifndef MATRIXTEST_H
#define MATRIXTEST_H

#include <Tester/testcase.h>
#include <MATH/LinearAlgebra/matrix.h>

class MatrixTest: public Tester::TestCase
{
	typedef MATH::LinearAlgebra::Matrix<double> dMatrix;
	typedef MATH::LinearAlgebra::Matrix<int> iMatrix;
	typedef MATH::LinearAlgebra::Vector<double> dVector;
	static const double PRECISION = 0.001;
	public:
		MatrixTest():Tester::TestCase("MatrixTest.res") {}
		virtual void run();
 /*******************Test Cases:*******************/
		void testConstructor();
		void testCopyConstructor();
		void testConstructor2();

		void testOperatorBeEq();

		void testOperatorResize();

		void testOperatorEq();
		void testOperatorNotEq();
		void testOperatorAdd();
		void testOperatorMinus();
		void testOperatorMultScalar();
		void testOperatorMult();
		void testOperatorMultVM();
		void testOperatorMultMV();
		void testFill();
		void testPressure();
};



#endif
