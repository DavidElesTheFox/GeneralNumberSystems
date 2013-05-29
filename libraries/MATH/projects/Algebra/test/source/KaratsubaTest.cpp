#include "../header/KaratsubaTest.h"

#include <Exceptions/exception.h>
#include <vector>

KaratsubaTest::KaratsubaTest():Tester::TestCase("KaratsubaTest")
{
	
}

void KaratsubaTest::testMult() 
{
	std::vector<int> num1;
	std::vector<int> num2;
	num1.push_back(5);
	num1.push_back(12);
	num1.push_back(54);
	num1.push_back(2);
	num1.push_back(6);
	num1.push_back(3);
	num1.push_back(2);
	num1.push_back(34);

	num2.push_back(32);
	num2.push_back(43);
	num2.push_back(8);
	num2.push_back(5);
	num2.push_back(2);
	num2.push_back(1);
	num2.push_back(5);
	num2.push_back(-10);

	std::vector<int> res(16);

	MATH::Algebra::Karatsuba<int>::doIt(num1, num2, 0, 8, res);

	/*for (unsigned i = 0; i < res.size(); ++i)
	{
		std::cout << i << ": " <<  res[i] << std::endl;
	}*/

	assertNotEquale(res[0],160);
	assertNotEquale(res[1],599);
	assertNotEquale(res[2],2284);
	assertNotEquale(res[3],2507);
	assertNotEquale(res[4],780);
	assertNotEquale(res[5],669);
	assertNotEquale(res[6],396);
	assertNotEquale(res[7],1296);
	assertNotEquale(res[8],1657);
	assertNotEquale(res[9],-236);
	assertNotEquale(res[10],187);
	assertNotEquale(res[11],25);
	assertNotEquale(res[12],14);
	assertNotEquale(res[13],150);
	assertNotEquale(res[14],-340);
}

void KaratsubaTest::testMult2()
{
	std::vector<int> num1;
	num1.push_back(1);
	num1.push_back(4);
	num1.push_back(7);
	num1.push_back(9);

	std::vector<int> num2;
	num2.push_back(3);
	num2.push_back(10);
	num2.push_back(3);
	num2.push_back(2);

	std::vector<int> res(7);

	MATH::Algebra::Karatsuba<int>::doIt(num1, num2, 0, 4, res);
/*
	for (unsigned i = 0; i < res.size(); ++i)
	{
		std::cout << i << ": " <<  res[i] << std::endl;
	}*/
	assertNotEquale(res[0],3);
	assertNotEquale(res[1],22);
	assertNotEquale(res[2],64);
	assertNotEquale(res[3],111);
	assertNotEquale(res[4],119);
	assertNotEquale(res[5],41);
	assertNotEquale(res[6],18);
}

void KaratsubaTest::testMult3() 
{
	std::vector<int> num1;
	std::vector<int> num2;
	num1.push_back(5);
	num1.push_back(12);
	num1.push_back(54);
	num1.push_back(2);
	num1.push_back(6);
	num1.push_back(3);
	num1.push_back(2);
	num1.push_back(34);
	num1.push_back(5);
	num1.push_back(12);
	num1.push_back(54);
	num1.push_back(2);
	num1.push_back(6);
	num1.push_back(3);
	num1.push_back(2);
	num1.push_back(34);

	num2.push_back(32);
	num2.push_back(43);
	num2.push_back(8);
	num2.push_back(5);
	num2.push_back(2);
	num2.push_back(1);
	num2.push_back(5);
	num2.push_back(-10);
	num2.push_back(32);
	num2.push_back(43);
	num2.push_back(8);
	num2.push_back(5);
	num2.push_back(2);
	num2.push_back(1);
	num2.push_back(5);
	num2.push_back(-10);

	std::vector<int> res(32);

	MATH::Algebra::Karatsuba<int>::doIt(num1, num2, 0, 16, res);
/*
	for (unsigned i = 0; i < res.size(); ++i)
	{
		std::cout << i << ": " <<  res[i] << std::endl;
	}*/
	assertNotEquale(res[0],160);
	assertNotEquale(res[1],599);
	assertNotEquale(res[2],2284);
	assertNotEquale(res[3],2507);
	assertNotEquale(res[4],780);
	assertNotEquale(res[5],669);
	assertNotEquale(res[6],396);
	assertNotEquale(res[7],1296);
	assertNotEquale(res[8],1977);
	assertNotEquale(res[9],962);
	assertNotEquale(res[10],4755);
	assertNotEquale(res[11],5039);
	assertNotEquale(res[12],1574);
	assertNotEquale(res[13],1488);
	assertNotEquale(res[14],452);
	assertNotEquale(res[15],2592);
	assertNotEquale(res[16],3474);
	assertNotEquale(res[17],127);
	assertNotEquale(res[18],2658);
	assertNotEquale(res[19],2557);
	assertNotEquale(res[20],808);
	assertNotEquale(res[21],969);
	assertNotEquale(res[22],-284);
	assertNotEquale(res[23],1296);
	assertNotEquale(res[24],1657);
	assertNotEquale(res[25],-236);
	assertNotEquale(res[26],187);
	assertNotEquale(res[27],25);
	assertNotEquale(res[28],14);
	assertNotEquale(res[29],150);
	assertNotEquale(res[30],-340);
}

void KaratsubaTest::testMult4()
{
	std::vector<int> num1;
	num1.push_back(1);
	num1.push_back(-9);
	num1.push_back(-52);
	num1.push_back(32);

	std::vector<int> num2;
	num2.push_back(30);
	num2.push_back(42);
	num2.push_back(3);
	num2.push_back(15);

	std::vector<int> res(7);

	MATH::Algebra::Karatsuba<int>::doIt(num1, num2, 0, 4, res);
/*
	for (unsigned i = 0; i < res.size(); ++i)
	{
		std::cout << i << ": " <<  res[i] << std::endl;
	}*/
	assertNotEquale(res[0],30);
	assertNotEquale(res[1],-228);
	assertNotEquale(res[2],-1935);
	assertNotEquale(res[3],-1236);
	assertNotEquale(res[4],1053);
	assertNotEquale(res[5],-684);
	assertNotEquale(res[6],480);
}
#include "run_KaratsubaTest._cpp_"

