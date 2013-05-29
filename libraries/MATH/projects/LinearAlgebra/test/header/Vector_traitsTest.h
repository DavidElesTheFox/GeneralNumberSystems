#ifndef VECTOR_TRAITS_TEST_H
#define VECTOR_TRAITS_TEST_H

#include <Tester/testcase.h>
#include <MATH/LinearAlgebra/vector_traits.h>
#include <MATH/LinearAlgebra/vector.h>
#include <iostream>

class Vector_traitsTest: public Tester::TestCase
{
	public:
		Vector_traitsTest();

		virtual void run();

		void testCreate();
		void testGetElement();
		void testRefGetElement();
		void testCopy();
		void testGetDimension();
		void testEquals();

};

#endif // VECTOR_TRAITS_TEST_H

