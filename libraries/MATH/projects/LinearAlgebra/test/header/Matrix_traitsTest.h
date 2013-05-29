#ifndef MATRIX_TRAITS_TEST_H
#define MATRIX_TRAITS_TEST_H


#include <Tester/testcase.h>
#include <MATH/LinearAlgebra/matrix_traits.h>
#include <MATH/LinearAlgebra/matrix.h>
#include <iostream>

class Matrix_traitsTest: public Tester::TestCase
{
	public:
		Matrix_traitsTest();

		virtual void run();

		void testCreateMatrix();
		void testGetElement();
		void testRefGetElement();
		void testResize();
		void testCopy();
		void testGetDimension();
		void testRowNum();
		void testColNum();
		void testEquals();

};

#endif // MATRIX_TRAITS_TEST_H

