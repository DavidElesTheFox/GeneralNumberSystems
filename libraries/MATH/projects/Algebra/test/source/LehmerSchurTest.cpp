#include "../header/LehmerSchurTest.h"

#include <MATH/Algebra/polynomial.h>

typedef MATH::Algebra::Polynomial<double> Poly;
typedef MATH::Algebra::LehmerSchur<double, Poly> LS;

LehmerSchurTest::LehmerSchurTest() 
  :Tester::TestCase("LehmerSchurTest")
{
	
}


void LehmerSchurTest::testExpansive() 
{
	Poly a(2, 1.5, 1.);
	Poly b(2, 3.5, 1.);
	Poly c(2, 2.1, 1.);
	Poly d(2, -5.2, 1.);
  Poly e = a * b * c * d;
  bool ret = LS::doAlgorithm(e);
  assertFalse(ret);
}

void LehmerSchurTest::testNonExpansive() 
{
	
	Poly a(2, 1.5, 1.);
	Poly b(2, 3.5, 1.);
	Poly c(2, 0.1, 1.);
	Poly d(2, -5.2, 1.);
  Poly e = a * b * c * d;
  bool ret = LS::doAlgorithm(e);
  assertFalse(!ret);
}

#include "run_LehmerSchurTest._cpp_"

