#include "../header/ExpansionUtilTest.h"

#include <MATH/Algebra/quotientfield.h>
#include <MATH/Algebra/polynomial.h>

#include <MATH/Algebra/expansionutil.h>
typedef MATH::Algebra::QuotientField<int> Racional_t;
typedef MATH::Algebra::Polynomial<Racional_t> Polynomial_t;

ALGEBRICAL_EXPANSION(Racional_t,Polynomial_t(3,2,0,-2), Quadratic_t, "sqrt(2)");
//NON_ALGEBRICAL_EXPANSION(Racional_t, PiRac_t, "pi");

ExpansionUtilTest::ExpansionUtilTest() 
  :Tester::TestCase("ExpansionUtilTest")
{  }


void ExpansionUtilTest::testCreateAlgebricalField() 
{
  MATH::Algebra::Quadratic_t t(2, 2, 1);
  std::cout << t << std::endl;
}

void ExpansionUtilTest::testCreateNonAlgebricalField() 
{
	
}

#include "run_ExpansionUtilTest._cpp_"

