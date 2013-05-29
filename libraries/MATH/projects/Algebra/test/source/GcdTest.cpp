#include "../header/GcdTest.h"


GcdTest::GcdTest() :Tester::TestCase("GcdTest.res")
{	}


void GcdTest::testGcd()
{
	MATH::Algebra::Gcd<int>::EuclideanResult_t res = MATH::Algebra::Gcd<int>::EuclideanAlg(18,-24);
	assertNotEquale(res.a,1,"res.a");
	assertNotEquale(res.b,1,"res.b");
	assertNotEquale(res.gcd,-6,"res.gcd");
	assertNotEquale(res.number1,4,"res.number1");
	assertNotEquale(res.number2,3,"res.number2");
}

void GcdTest::testGcd2()
{
	MATH::Algebra::Gcd<int>::EuclideanResult_t res = MATH::Algebra::Gcd<int>::EuclideanAlg(1203320,2013234);
	assertNotEquale(res.gcd, res.a*1203320 + res.b*2013234,"Error with res.a, res.b");
	assertNotEquale(res.number1*1203320 + res.number2*2013234,0, "Error with res.number1, res.number2");
}

#include "run_GcdTest._cpp_"

