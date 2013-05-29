#include "../header/PolynomialTest.h"

typedef MATH::Algebra::Polynomial<int> Poly;


PolynomialTest::PolynomialTest() 
	:Tester::TestCase("PolynomialTest")
{
	
}

void PolynomialTest::testCreateElement() 
{
	Poly p;
	assertNotEquale(p[0],0);
	assertNotEquale(p.getDegree(), 0);
}

void PolynomialTest::testCreateElement2() 
{
	Poly p = -MATH::Algebra::Number_traits<Poly>::multiplicativeUnit;
	assertNotEquale(p[0],-1);
	assertNotEquale(p.getDegree(), 0);
}

void PolynomialTest::testCreateFormattedElement() 
{
	Poly p(4, 1, 2, 4, 64);
	assertNotEquale(p[0], 1);
	assertNotEquale(p[1], 2);
	assertNotEquale(p[2], 4);
	assertNotEquale(p[3], 64);
	assertNotEquale(p.getDegree(), 3);
}

void PolynomialTest::testAdd() 
{
	Poly a(4, 1, 2, 4, 64);
	Poly b(4, 133, 22, 421, 4);
	Poly c = a + b;
	assertNotEquale(c[0], 134);
	assertNotEquale(c[1], 24);
	assertNotEquale(c[2], 425);
	assertNotEquale(c[3], 68);
	assertNotEquale(c.getDegree(), 3);
}

void PolynomialTest::testSubstract() 
{
	Poly a(4, 1, 2, 4, 64);
	Poly b(4, 133, 22, 421, 4);
	Poly c = a - b;
	assertNotEquale(c[0], -132);
	assertNotEquale(c[1], -20);
	assertNotEquale(c[2], -417);
	assertNotEquale(c[3], 60);
	assertNotEquale(c.getDegree(), 3);
}

void PolynomialTest::testMult() 
{
	Poly a(4, 1, 2, 4, 64);
	Poly b(4, 133, 22, 421, 4);
	Poly c = a * b;
	assertNotEquale(c[0], 133);
	assertNotEquale(c[1], 288);
	assertNotEquale(c[2], 997);
	assertNotEquale(c[3], 9446);
	assertNotEquale(c[4], 3100);
	assertNotEquale(c[5], 26960);
	assertNotEquale(c[6], 256);
	assertNotEquale(c.getDegree(), 6);
}

void PolynomialTest::testInterp() 
{
	Poly a(4, 1, 4, 5, 34);
	assertNotEquale(a(4), 2273);
}

#include "run_PolynomialTest._cpp_"

