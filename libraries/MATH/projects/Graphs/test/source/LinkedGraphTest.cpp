#include "../header/LinkedGraphTest.h"


LinkedGraphTest::LinkedGraphTest():Tester::TestCase("LinkedGraphTest.res")
{	}


void LinkedGraphTest::testCreate()
{
	MATH::Graphs::LinkedGraph<int> g;
	g.addNode(0,0);
	g.addTo(1,0,5);
	g.addTo(2,0,7);
	g.addTo(3,1,6);
	g.addEdge(2,3,4);
	g.addEdge(0,3,4);
	std::cout<<"g"<<std::endl<<g<<std::endl;
}

void LinkedGraphTest::testSearch()
{

}

void LinkedGraphTest::testInsert()
{

}

void LinkedGraphTest::testPushBack()
{

}

#include "run_LinkedGraphTest._cpp_"
