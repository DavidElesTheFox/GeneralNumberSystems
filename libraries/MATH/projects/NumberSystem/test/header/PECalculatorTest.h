#ifndef PECALCULATOR_TEST_H
#define PECALCULATOR_TEST_H

#include <Tester/testcase.h>
#include <MATH/LinearAlgebra/matrix.h>
#include <MATH/LinearAlgebra/vector.h>
#include <MATH/NumberSystem/numbersystem.h>
#include <MATH/NumberSystem/abstractperiodicelementcalculator.h>

template<class PE_CALC,
	       bool canDetermineNumberSystem>
class PECalculatorTest:public Tester::TestCase
{
	public:
		PECalculatorTest():
			Tester::TestCase("PECalculatorTest.res")
		{}

		void run();

		void testCalculatePeriodicElements();
		void testIsNumberSystem();
	private:

		template<class T>
		class SimpleMatrixNorm;
		template<class T>
		class SimpleVectorNorm;
};

#include "PECalculatorTest.hpp"

#endif
