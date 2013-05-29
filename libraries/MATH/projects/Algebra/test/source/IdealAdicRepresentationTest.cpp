#include "../header/IdealAdicRepresentationTest.h"

#include <string>

#include <Exceptions/exception.h>

struct TestUnsignedIdeal
{
	static std::string strShape;
	static unsigned baseNumber;
	static bool isCongruentElement(const unsigned& element)
	{
		return element < baseNumber;
	}

	static void division(const unsigned& a, unsigned& q, unsigned& r)
	{
		q = a / baseNumber;
		r = a % baseNumber;
	}
};

std::string TestUnsignedIdeal::strShape = "3";
unsigned TestUnsignedIdeal::baseNumber = 3;

typedef MATH::Algebra::IdealAdicRepresentation<unsigned, TestUnsignedIdeal>
  UnsignedRep;

struct TestSignedIdeal
{
	static std::string strShape;
	static int baseNumber;
	static bool isCongruentElement(const int& element)
	{
		return element >= 0 && element < baseNumber;
	}

	static void division(const int& a, int& q, int& r)
	{
		q = a / baseNumber;
		r = a % baseNumber;
		if (r < 0)
		{
			r += 3;
			q -= 1;
		}
	}
};

std::string TestSignedIdeal::strShape = "3";
int TestSignedIdeal::baseNumber = 3;

typedef MATH::Algebra::IdealAdicRepresentation<int, TestSignedIdeal>
	SignedRep;


struct TestSignedCanonicalIdeal
{
	static std::string strShape;
	static int baseNumber;
	static bool isCongruentElement(const int& element)
	{
		return element > -baseNumber && element < baseNumber;
	}

	static void division(const int& a, int& q, int& r)
	{
		q = a / baseNumber;
		r = a % baseNumber;
		if (r == 2)
		{
			r -= 3;
			q += 1;
		}
		else if(r == -2)
		{
			r += 3;
			q -= 1;
		}
	}
};

std::string TestSignedCanonicalIdeal::strShape = "3";
int TestSignedCanonicalIdeal::baseNumber = 3;

typedef MATH::Algebra::IdealAdicRepresentation<int, TestSignedCanonicalIdeal>
  SignedCanonicalRep;


IdealAdicRepresentationTest::IdealAdicRepresentationTest() 
	:Tester::TestCase("IdealAdicRepresentation")
{  }

void IdealAdicRepresentationTest::testCreateElement() 
{
	UnsignedRep a = 14;
	assertNotEquale(a.getCoeff(2), 1);
	assertNotEquale(a.getCoeff(1), 1);
	assertNotEquale(a.getCoeff(0), 2);
	a = 2;

	assertNotEquale(a.getCoeff(2), 0);
	assertNotEquale(a.getCoeff(1), 0);
	assertNotEquale(a.getCoeff(0), 2);
}

void IdealAdicRepresentationTest::testCreateInfinityElement() 
{
	try
	{
	  SignedRep a = -1;
		assertTrue(true);
	}
	catch(Exceptions::ParameterException& ex)
	{
	}
}

void IdealAdicRepresentationTest::testCreateWellFormattedElement() 
{
	UnsignedRep a(3, 1, 2, 1);
	assertNotEquale(a.getCoeff(0), 1);
	assertNotEquale(a.getCoeff(1), 2);
	assertNotEquale(a.getCoeff(2), 1);
}

void IdealAdicRepresentationTest::testCreateWrongFormattedElement() 
{
	try
	{
		UnsignedRep a(3, 1, 2, 3);
		assertTrue(true);
	}
	catch (Exceptions::ParameterException& ex)
	{

	}
}

void IdealAdicRepresentationTest::testPrefixAdd() 
{
	UnsignedRep a = 20;
	assertNotEquale(a.getCoeff(0), 2);
	assertNotEquale((++a).getCoeff(0), 0);
}

void IdealAdicRepresentationTest::testPostfixAdd() 
{
	UnsignedRep a = 20;
	assertNotEquale(a.getCoeff(0), 2);
	assertNotEquale((a++).getCoeff(0), 2);
}

void IdealAdicRepresentationTest::testPrefixMinus() 
{
	SignedCanonicalRep a = 17;
	assertNotEquale(a.getCoeff(0), -1);

	assertNotEquale((--a).getCoeff(0), 1);
	assertNotEquale(a.getCoeff(1), -1);
	assertNotEquale(a.getCoeff(2), -1);
	assertNotEquale(a.getCoeff(3), 1);
	assertNotEquale(a.getOrder(), 3);
}

void IdealAdicRepresentationTest::testPostfixMinus() 
{
	SignedCanonicalRep a = 17;
	assertNotEquale(a.getCoeff(0), -1);
	assertNotEquale((a--).getCoeff(0), -1);

	assertNotEquale(a.getCoeff(0), 1);
	assertNotEquale(a.getCoeff(1), -1);
	assertNotEquale(a.getCoeff(2), -1);
	assertNotEquale(a.getCoeff(3), 1);
	assertNotEquale(a.getOrder(), 3);
}

void IdealAdicRepresentationTest::testPostfixWrongMinus() 
{
	SignedRep a = 11;
	try
	{
		a--;
		assertFalse(true);
	}
	catch(Exceptions::ParameterException& ex)
	{
	}
}


void IdealAdicRepresentationTest::testPrefixWrongMinus() 
{
	SignedRep a = 11;
	try
	{
		--a;
		assertFalse(true);
	}
	catch(Exceptions::ParameterException& ex)
	{
	}
}

void IdealAdicRepresentationTest::testShortAdd() 
{
	SignedCanonicalRep a = 20;
	a += 100;
	assertNotEquale(a.getCoeff(0), 0);
	assertNotEquale(a.getCoeff(1), 1);
	assertNotEquale(a.getCoeff(2), 1);
	assertNotEquale(a.getCoeff(3), 1);
	assertNotEquale(a.getCoeff(4), 1);
	assertNotEquale(a.getOrder(), 4);
}

void IdealAdicRepresentationTest::testShortMinus() 
{
	SignedCanonicalRep a = 20;
	a -= 10;
	assertNotEquale(a.getCoeff(0), 1);
	assertNotEquale(a.getCoeff(1), 0);
	assertNotEquale(a.getCoeff(2), 1);
	assertNotEquale(a.getOrder(), 2);
}

void IdealAdicRepresentationTest::testShortMinusWrong() 
{
	SignedRep a = 10;
	try 
	{
		a -= 2;
		std::cout << (std::string) a << std::endl;
		assertTrue(true);
	}
	catch (Exceptions::ParameterException& ex)
	{

	}
}

void IdealAdicRepresentationTest::testShortDiv1() 
{
  UnsignedRep a = 18;
	a /= 2;
	assertNotEquale(a.getCoeff(0), 0);
	assertNotEquale(a.getCoeff(1), 0);
	assertNotEquale(a.getCoeff(2), 1);
	assertNotEquale(a.getOrder(), 2);
}

void IdealAdicRepresentationTest::testShortDiv2() 
{
	SignedCanonicalRep a = 18;
	a /= 4;
	assertNotEquale(a.getCoeff(0), -1);
	assertNotEquale(a.getCoeff(1), -1);
	assertNotEquale(a.getCoeff(2), 1);
	assertNotEquale(a.getOrder(), 2);
}

void IdealAdicRepresentationTest::testShortMult() 
{
	SignedCanonicalRep a = 10;
	a *= 10;
	assertNotEquale(a.getCoeff(0), 1);
	assertNotEquale(a.getCoeff(1), 0);
	assertNotEquale(a.getCoeff(2), -1);
	assertNotEquale(a.getCoeff(3), 1);
	assertNotEquale(a.getCoeff(4), 1);
	assertNotEquale(a.getOrder(), 4);
}

void IdealAdicRepresentationTest::testShortMod1() 
{
	SignedCanonicalRep a = 32;
	a %= 5;
	assertNotEquale(a.getCoeff(0), 1);
	assertNotEquale(a.getCoeff(1), -1);
	assertNotEquale(a.getCoeff(2), 1);
	assertNotEquale(a.getOrder(), 2);
}

void IdealAdicRepresentationTest::testShortMod2() 
{
	SignedCanonicalRep a = 31;
	a %= 2;
	assertNotEquale(a.getCoeff(0), 0);
	assertNotEquale(a.getCoeff(1), 1);
	assertNotEquale(a.getOrder(), 1);
}

void IdealAdicRepresentationTest::testToString() 
{
	SignedCanonicalRep a = 20;
	assertNotEquale( (std::string) a, "1*3^(3) + -1*3^(2) + 1*3^(1) + -1" );
}

void IdealAdicRepresentationTest::testLcoeff() 
{
	SignedCanonicalRep a = 236;
	assertNotEquale(a.lcoeff(), 1);
}

void IdealAdicRepresentationTest::testDegree() 
{
	SignedCanonicalRep a = 1297;
	assertNotEquale(a.getOrder(), 7);
}

void IdealAdicRepresentationTest::testEq() 
{
	SignedCanonicalRep a = 2345;
	SignedCanonicalRep b = 2345;
	assertFalse(a == b);
}

void IdealAdicRepresentationTest::testNotEq() 
{
	SignedCanonicalRep a = 2345;
	SignedCanonicalRep b = 2344;
	assertFalse(a != b);
}

void IdealAdicRepresentationTest::testAdd() 
{
	SignedCanonicalRep a = 2345;
	SignedCanonicalRep b = 100;
	SignedCanonicalRep c = a + b;
	assertNotEquale(c.getCoeff(0), 0);
	assertNotEquale(c.getCoeff(1), -1);
	assertNotEquale(c.getCoeff(2), -1);
	assertNotEquale(c.getCoeff(3), 1);
	assertNotEquale(c.getCoeff(4), 0);
	assertNotEquale(c.getCoeff(5), 1);
	assertNotEquale(c.getCoeff(6), 0);
	assertNotEquale(c.getCoeff(7), 1);
	assertNotEquale(c.getOrder(), 7);
}

void IdealAdicRepresentationTest::testMinus() 
{
	SignedCanonicalRep a = 2345;
	SignedCanonicalRep b = 100;
	SignedCanonicalRep c = a - b;
	assertNotEquale(c.getCoeff(0), 1);
	assertNotEquale(c.getCoeff(1), 1);
	assertNotEquale(c.getCoeff(2), 0);
	assertNotEquale(c.getCoeff(3), -1);
	assertNotEquale(c.getCoeff(4), 1);
	assertNotEquale(c.getCoeff(5), 0);
	assertNotEquale(c.getCoeff(6), 0);
	assertNotEquale(c.getCoeff(7), 1);
	assertNotEquale(c.getOrder(), 7);
}

void IdealAdicRepresentationTest::testWrongMinus() 
{
	SignedRep a = 342;
	SignedRep b = 12;
	try
	{
		SignedRep c = a - b;
		assertTrue(true);
	}
	catch (Exceptions::ParameterException& ex)
	{
	}
}

void IdealAdicRepresentationTest::testMult() 
{
	SignedCanonicalRep a = 321;
	SignedCanonicalRep b = 10;
	SignedCanonicalRep c = a * b;
	assertNotEquale(c.getCoeff(0), 0);
	assertNotEquale(c.getCoeff(1), -1);
	assertNotEquale(c.getCoeff(2), 0);
	assertNotEquale(c.getCoeff(3), -1);
	assertNotEquale(c.getCoeff(4), 1);
	assertNotEquale(c.getCoeff(5), 1);
	assertNotEquale(c.getCoeff(6), 1);
	assertNotEquale(c.getCoeff(7), 1);
	assertNotEquale(c.getOrder(), 7);
}

void IdealAdicRepresentationTest::testDiv1() 
{
	SignedCanonicalRep a = 12;
	SignedCanonicalRep b = 3;
	SignedCanonicalRep c = a / b;
	assertNotEquale(c.getCoeff(0), 1);
	assertNotEquale(c.getCoeff(1), 1);
	assertNotEquale(c.getOrder(), 1);
	//std::cout << (std::string) c << std::endl;
}

void IdealAdicRepresentationTest::testDiv2() 
{
	
	SignedCanonicalRep a = 12;
	SignedCanonicalRep b = 5;
	SignedCanonicalRep c = a / b;
	assertNotEquale(c.getCoeff(0), 1);
	assertNotEquale(c.getOrder(), 0);
}

void IdealAdicRepresentationTest::testMod1() 
{
	
	SignedCanonicalRep a = 12;
	SignedCanonicalRep b = 3;
	SignedCanonicalRep c = a % b;
	assertNotEquale(c.getCoeff(0), 0);
	assertNotEquale(c.getOrder(), 0);
}

void IdealAdicRepresentationTest::testMod2() 
{
	
	SignedCanonicalRep a = 12;
	SignedCanonicalRep b = 5;
	SignedCanonicalRep c = a % b;
	assertNotEquale(c.getCoeff(0), 1);
	assertNotEquale(c.getCoeff(1), -1);
	assertNotEquale(c.getCoeff(2), 1);
	assertNotEquale(c.getOrder(), 2);
}

void IdealAdicRepresentationTest::testShiftLeft() 
{
	UnsignedRep a = 2;
	a = a << 1;
	assertNotEquale(a.getCoeff(0), 0);
	assertNotEquale(a.getCoeff(1), 2);
}

void IdealAdicRepresentationTest::testShiftRight() 
{
	UnsignedRep a = 3;
	a = a >> 1;
	assertNotEquale(a.getCoeff(0), 1);
	assertNotEquale(a.getCoeff(1), 0);
}

void IdealAdicRepresentationTest::testPreasureAdd()
{
	int limit = 10000;
	SignedCanonicalRep a = 3;
	SignedCanonicalRep b = 4;
	clock_t start = clock();
	for (int i = 0; i < limit; ++i)
	{
		a + b;
	}
	double time1 = (clock() - start)/(double)CLOCKS_PER_SEC;
	int aa = 3;
	int bb = 4;
	start = clock();
	for (int i = 0; i < limit * 1000; ++i)
	{
		aa + bb;
	}
	double time2 = (clock() - start)/(double)CLOCKS_PER_SEC;
	std::cout<<time1<<std::endl;
	std::cout<<time2<<std::endl;
	std::cout<<"1 000 times different"<<std::endl;
}

void IdealAdicRepresentationTest::testPreasureMult()
{
	int limit = 10000;
	SignedCanonicalRep a = 3234;
	std::cout << (std::string)a << std::endl;
	SignedCanonicalRep b = 4324;
	std::cout << (std::string)b << std::endl;
	clock_t start = clock();
	for (int i = 0; i < limit; ++i)
	{
		a * b;
	}
	double time1 = (clock() - start)/(double)CLOCKS_PER_SEC;
	int aa = 3234;
	int bb = 4324;
	start = clock();
	for (int i = 0; i < limit; ++i)
	{
		aa * bb;
	}
	double time2 = (clock() - start)/(double)CLOCKS_PER_SEC;
	std::cout<<time1<<std::endl;
	std::cout<<time2<<std::endl;
}



#include "run_IdealAdicRepresentation._cpp_"

