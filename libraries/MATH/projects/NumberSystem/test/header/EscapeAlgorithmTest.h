#ifndef ESCAPEALGORITHM_TEST_H
#define ESCAPEALGORITHM_TEST_H

#include <Tester/testcase.h>
#include <MATH/LinearAlgebra/matrix.h>
#include <MATH/LinearAlgebra/vector.h>
#include <MATH/NumberSystem/escapealgorithm.h>

#include <time.h>

template<class T>
class SimpleMatrixNorm;
template<class T>
class SimpleVectorNorm;

class EscapeAlgorithmTest:public Tester::TestCase
{
	public:
		EscapeAlgorithmTest();

		virtual void run();

		void testCompute();
		void testCompute2();

};


#endif
