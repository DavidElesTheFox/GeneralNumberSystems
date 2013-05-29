#include "../header/RussionPeasantMethodTest.h"


RussionPeasantMethodTest::RussionPeasantMethodTest() 
  :Tester::TestCase("RussionPeasantMethod")
{
	
}

void RussionPeasantMethodTest::testPow() 
{
  unsigned a = 3;
  unsigned b = MATH::Algebra::RussionPeasantMethod<unsigned>::pow(a, 8);
  assertNotEquale(b, 6561);
}
#include "run_RussionPeasantMethod._cpp_"

