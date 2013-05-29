#include "../header/NumberSystemTest.h"
#include "../header/EscapeAlgorithmTest.h"
#include "../header/PECalculatorTest.h"
#include <vector>
#include <Logger/logger.h>
#include <MATH/LinearAlgebra/matrix.h>
#include <MATH/LinearAlgebra/vector.h>
#include <MATH/NumberSystem/pecalculators.h>

typedef MATH::NumberSystem::GraphPECalculator<int, float,
				                                      MATH::LinearAlgebra::Matrix,
																							MATH::LinearAlgebra::Vector,
																						  SimpleMatrixNorm,
																							SimpleVectorNorm>
																							  GraphCalc;

int main(int argc, char* argv[])
{
	std::vector<Tester::TestCase*> tests;
	tests.push_back(new NumberSystemTest());
	tests.push_back(new EscapeAlgorithmTest());
	tests.push_back(new PECalculatorTest<GraphCalc, false>());
	Logger::Logger::initLog("test.log");
	int id = -1;
	if (argc>1)
	{
		id = atoi(argv[1]);
	}
	int counter = 0;
	for(std::vector<Tester::TestCase*>::iterator it =tests.begin(); it != tests.end(); ++it)
	{
		if (id < 0 
				|| id == counter++)
		{
			std::cout<<(**it).getResultName()<<": "<<std::endl;
			std::cout<<"================="<<std::endl;
			try
			{
				(*it)->run();
			}
			catch(Exceptions::Exception& ex)
			{
				std::cout<<"Exception occured: "<<ex<<std::endl;
			}
			catch(...)
			{
				std::cout<<"Unknown error!"<<std::endl;
			}
		}
	}
	Logger::Logger::closeLog();
	return 0;
}

