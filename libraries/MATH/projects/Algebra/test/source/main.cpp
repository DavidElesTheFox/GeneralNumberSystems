#include "../header/IntegerTest.h"
#include "../header/GcdTest.h"
#include "../header/NumberCalculatorTest.h"
#include "../header/IdealAdicRepresentationTest.h"
#include "../header/KaratsubaTest.h"
#include "../header/PolynomialTest.h"
#include "../header/PAdicTest.h"
#include "../header/RussionPeasantMethodTest.h"
#include "../header/ComplexTest.h"
#include "../header/QuotientFieldTest.h"
#include "../header/ExpansionUtilTest.h"
#include "../header/LehmerSchurTest.h"
#include <vector>
#include <stdlib.h>

int main(int argc, char* argv[])
{
	std::vector<Tester::TestCase*> tests;
	tests.push_back(new IntegerTest());
	tests.push_back(new GcdTest());
	tests.push_back(new NumberCalculatorTest());
	tests.push_back(new IdealAdicRepresentationTest());
	tests.push_back(new KaratsubaTest());
	tests.push_back(new PolynomialTest());
	tests.push_back(new PAdicTest());
	tests.push_back(new RussionPeasantMethodTest());
  tests.push_back(new ComplexTest());
  tests.push_back(new QuotientFieldTest());
  tests.push_back(new ExpansionUtilTest());
  tests.push_back(new LehmerSchurTest());
	int act = -1, i = 0;
	if (argc > 1)
	{
		act = atoi(argv[1]);
		std::cout<<"act: "<<act<<"("<<argv[1]<<")"<<std::endl;
	}

	for(std::vector<Tester::TestCase*>::iterator it =tests.begin(); it != tests.end(); ++it)
	{
		if (act < 0 
				|| act == i++)
		{
			std::cout<<(**it).getResultName()<<": "<<std::endl;
			std::cout<<"================="<<std::endl;
			(*it)->run();
		}
	}

	return 0;
}

