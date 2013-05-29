#include "../header/ExpansionUtilTest.h"

#include <MATH/Algebra/quotientfield.h>
#include <MATH/Algebra/polynomial.h>

#include <MATH/Algebra/expansionutil.h>
#include <MATH/Algebra/fieldexpansion.h>
typedef MATH::Algebra::QuotientField<int> Racional_t;
typedef MATH::Algebra::Polynomial<Racional_t> Polynomial_t;

ALGEBRICAL_EXPANSION(Racional_t,Polynomial_t(3,-2,0,1), Quadratic_t, "sqrt(2)");
NON_ALGEBRICAL_EXPANSION(Racional_t, PiRac_t, "pi");

ExpansionUtilTest::ExpansionUtilTest() 
  :Tester::TestCase("ExpansionUtilTest")
{  }


void ExpansionUtilTest::testCreateAlgebricalField() 
{
  MATH::Algebra::Quadratic_t t(2, 2, 1);
  MATH::Algebra::Quadratic_t t2(2, 2, 3);
  MATH::Algebra::Quadratic_t t3 = t * t2;

  assertNotEquale(t.getCoeff(0).getCounter(), 2);
  assertNotEquale(t.getCoeff(0).getNominator(), 1);
  assertNotEquale(t.getCoeff(1).getCounter(), 1);
  assertNotEquale(t.getCoeff(1).getNominator(), 1);

  assertNotEquale(t2.getCoeff(0).getCounter(), 2);
  assertNotEquale(t2.getCoeff(0).getNominator(), 1);
  assertNotEquale(t2.getCoeff(1).getCounter(), 3);
  assertNotEquale(t2.getCoeff(1).getNominator(), 1);

  assertNotEquale(t3.getCoeff(0).getCounter(), 10);
  assertNotEquale(t3.getCoeff(0).getNominator(), 1);
  assertNotEquale(t3.getCoeff(1).getCounter(), 8);
  assertNotEquale(t3.getCoeff(1).getNominator(), 1);
  assertNotEquale(t3.getOrder(), 1);
}

void ExpansionUtilTest::testCreateNonAlgebricalField() 
{
	
  MATH::Algebra::PiRac_t t(2, 2, 1);
  MATH::Algebra::PiRac_t t2(2, 2, 3);
  MATH::Algebra::PiRac_t t3 = t * t2;

  assertNotEquale(t.getCoeff(0).getCounter(), 2);
  assertNotEquale(t.getCoeff(0).getNominator(), 1);
  assertNotEquale(t.getCoeff(1).getCounter(), 1);
  assertNotEquale(t.getCoeff(1).getNominator(), 1);

  assertNotEquale(t2.getCoeff(0).getCounter(), 2);
  assertNotEquale(t2.getCoeff(0).getNominator(), 1);
  assertNotEquale(t2.getCoeff(1).getCounter(), 3);
  assertNotEquale(t2.getCoeff(1).getNominator(), 1);

  assertNotEquale(t3.getCoeff(0).getCounter(), 4);
  assertNotEquale(t3.getCoeff(0).getNominator(), 1);
  assertNotEquale(t3.getCoeff(1).getCounter(), 8);
  assertNotEquale(t3.getCoeff(1).getNominator(), 1);
  assertNotEquale(t3.getCoeff(2).getCounter(), 3);
  assertNotEquale(t3.getCoeff(2).getNominator(), 1);
  assertNotEquale(t3.getOrder(), 2);

}

#include "run_ExpansionUtilTest._cpp_"

