#include "../header/SmithNormalFormTest.h"
#include "../header/AdjointMatrixTest.h"
#include "../header/Matrix_traitsTest.h"
#include "../header/MatrixCalculatorTest.h"
#include "../header/Vector_traitsTest.h"
#include "../header/ConverterTest.h"
#include "../header/MatrixTest.h"
#include "../header/VectorTest.h"
#include "../header/EuclideanNormTest.h"
#include "../header/PNormTest.h"
#include <vector>
#include <stdlib.h>

int main(int argc, char* argv[])
{
	std::vector<Tester::TestCase*> tests;
	tests.push_back(new SmithNormalFormTest());
	tests.push_back(new AdjointMatrixTest());
	tests.push_back(new Matrix_traitsTest());
	tests.push_back(new MatrixCalculatorTest());
	tests.push_back(new Vector_traitsTest());
	tests.push_back(new ConverterTest());
	tests.push_back(new MatrixTest());
	tests.push_back(new VectorTest());
	tests.push_back(new EuclideanNormTest());
	tests.push_back(new PNormTest());
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

	return 0;
}

