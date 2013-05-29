#include "../header/ReverseTreeTest.h"
#include "../header/ForestTest.h"
#include "../header/LinkedGraphTest.h"
#include <vector>
#include <Logger/logger.h>

int main()
{
	std::vector<Tester::TestCase*> tests;
	tests.push_back(new ReverseTreeTest());
	tests.push_back(new ForestTest());
	tests.push_back(new LinkedGraphTest());
	Logger::Logger::initLog("test.log");
	for(std::vector<Tester::TestCase*>::iterator it =tests.begin(); it != tests.end(); ++it)
	{
		std::cout<<(**it).getResultName()<<": "<<std::endl;
		std::cout<<"================="<<std::endl;
		(*it)->run();
	}
	Logger::Logger::closeLog();
	return 0;
}

