#include "../header/testcase.h"

#include <stdio.h>
#include <string.h>
#include <fstream>

using std::string;

Tester::TestCase::TestCase()
{
	resultName="result";
	ok = true;
	result=new std::ofstream(resultName.c_str());
}

Tester::TestCase::TestCase(string result_name)
{
	this->resultName=result_name;
	ok = true;
	result=new std::ofstream(resultName.c_str());
}

Tester::TestCase::~TestCase()
{
	result->close();
	delete result;
}

bool Tester::TestCase::isOk() const
{
    return ok;
}

std::string Tester::TestCase::getResultName() const
{
	return resultName;
}

void Tester::TestCase::setResultFile(string fileName)
{
	if(result != NULL)
		delete result;
	result=new std::ofstream(fileName.c_str());
	resultName=fileName;
}

void Tester::TestCase::assertFalse(const bool value, const string comment) const
{
    if(!value)
	{
		*(const_cast<bool*>(&ok)) = false;
		(*result)<<"FAIL: \tthe expect value: true, but I get: "<<value<<"\n\t"<<comment<<endl;

	}
}

void Tester::TestCase::assertTrue(const bool value, const string comment) const
{
    if(value)
	{
		*(const_cast<bool*>(&ok)) = false;
		(*result)<<"FAIL: \tthe expect value: false, but I get: "<<value<<"\n\t"<<comment<<endl;
	}
}

void Tester::TestCase::assertNotEquale(const string expect, const string value, const string comment) const
{
    int len_1=strlen(expect.c_str());
    int len_2=strlen(value.c_str());
    bool equle=len_1==len_2;
    for(unsigned int i=0;i<strlen(expect.c_str()) && equle;++i)
	equle=expect[i]==value[i];
    if(!equle)
	{
		*(const_cast<bool*>(&ok)) = false;
        (*result)<<"FAIL: \tthe expect value: "<<expect<<"\n\tbut I get: "<<value<<"\n\t"<<comment<<endl;
	}
}

void Tester::TestCase::assertNotEquale(const double expect, const double value, const string comment) const
{
	if(expect!=value)
	{
		*(const_cast<bool*>(&ok)) = false;
		(*result)<<"FAIL: \tthe expect value: "<<expect<<"\n\tbut I get: "<<value<<"\n\t"<<comment<<endl;
	}
}

void Tester::TestCase::assertNotEquale(const int expect, const int value, const string comment) const
{
	if(expect != value)
	{
		*(const_cast<bool*>(&ok)) = false;
		(*result)<<"FAIL: \tthe expect value: "<<expect<<"\n\tbut I get: "<<value<<"\n\t"<<comment<<endl;
	}
}

void Tester::TestCase::assertEquale(const int expect, const int value, const string comment) const
{
	if(expect == value)
	{
		*(const_cast<bool*>(&ok)) = false;
		(*result)<<"FAIL: \tthe expect value: "<<expect<<"\n\tbut I get: "<<value<<"\n\t"<<comment<<endl;
	}
}

void Tester::TestCase::assertEquale(const string expect, const string value, const string comment) const
{
    bool equle=strlen(expect.c_str())==strlen(value.c_str());
    for(unsigned int i=0;i<strlen(expect.c_str()) && equle;++i)
		equle=expect[i]==value[i];
    if(equle)
	{
		*(const_cast<bool*>(&ok)) = false;
		(*result)<<"FAIL: \tthe expect value is not: "<<expect<<"\n\tbut I get: "<<value<<"\n\t"<<comment<<endl;
	}
}

void Tester::TestCase::assertEquale(const double expect, const double value, const string comment) const
{
    if(expect==value)
	{
		*(const_cast<bool*>(&ok)) = false;
        (*result)<<"FAIL:\t the expect value is not: "<<expect<<"\n\tbut I get: "<<value<<"\n\t"<<comment<<endl;
	}
}


void Tester::TestCase::assertLowerEquale(const double expect, const double value, const string comment) const
{
	if(expect<=value)
	{
		*(const_cast<bool*>(&ok)) = false;
		(*result)<<"FAIL: the expect value: "<<expect<<" is not heigher then: "<<value<<"\n\t"<<comment<<endl;
	}
}

void Tester::TestCase::assertLower(const double expect, const double value, const string comment) const
{
	if(expect<value)
	{
		*(const_cast<bool*>(&ok)) = false;
		(*result)<<"FAIL: the expect value: "<<expect<<" is not heigher-equale then: "<<value<<"\n\t"<<comment<<endl;
	}
}

void Tester::TestCase::assertHigherEquale(const double expect, const double value, const string comment) const
{
	if(expect>=value)
	{
		*(const_cast<bool*>(&ok)) = false;
		(*result)<<"FAIL: the expect value: "<<expect<<" is not lower then: "<<value<<"\n\t"<<comment<<endl;
	}
}

void Tester::TestCase::assertHigher(const double expect, const double value, const string comment) const
{
	if(expect>value)
	{
		*(const_cast<bool*>(&ok)) = false;
		(*result)<<"FAIL: the expect value: "<<expect<<" is not lower-equale then: "<<value<<"\n\t"<<comment<<endl;
	}
}

void Tester::TestCase::assertNotBetween(const double low, const double high, const double value, const string comment) const
{
	if(!(value<=high && value>=low))
	{
		*(const_cast<bool*>(&ok)) = false;
		(*result)<<"FAIL: the value: "<<value<<" isn't in the next interval:["<<low<<","<<high<<"]"<<"\n\t"<<comment<<endl;
	}
}

void Tester::TestCase::assertDifferentHigher(const double expect, const double different, const double value, const string comment) const
{
	double dif = different;

	if(!(value<=expect+dif && value>=expect-dif))
	{
		*(const_cast<bool*>(&ok)) = false;
		(*result)<<"FAIL: the value: "<<value<<" isn't in the next interval:["<<expect-dif<<","<<expect+dif<<"]"<<"\n\t"<<comment<<endl;
	}
}

