#ifndef CONVERTER_TEST_H
#define CONVERTER_TEST_H

#include <Tester/testcase.h>
#include <MATH/LinearAlgebra/converter.h>
#include <MATH/LinearAlgebra/vector.h>
#include <MATH/LinearAlgebra/matrix.h>
#include <iostream>

class ConverterTest: public Tester::TestCase
{
	public:
		ConverterTest();

		virtual void run();

		void testVectorConvert();
		void testMatrixConvert();

};

#endif // CONVERTER_TEST_H
