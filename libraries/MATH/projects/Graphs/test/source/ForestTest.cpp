#include "../header/ForestTest.h"


ForestTest::ForestTest():Tester::TestCase("ForestTest.res")
{	}

void ForestTest::testCreate()
{
	MATH::Graphs::ReverseTree<int> tree1;
	MATH::Graphs::ReverseTree<int> tree2;
	MATH::Graphs::ReverseTree<int> tree3;
	MATH::Graphs::ReverseTree<int> tree4;
	MATH::Graphs::Forest<int, MATH::Graphs::ReverseTree<int> >* forest = new MATH::Graphs::Forest<int, MATH::Graphs::ReverseTree<int> >();
	tree1.push_front(8);
	tree1.push_front(7);
	tree1.push_front(6);
	tree1.push_front(5);
	tree1.push_front(4);
	tree1.push_front(3);
	tree1.push_front(2);
	tree1.push_front(1);
	tree1.push_front(0);


	tree2.push_front(10);
	tree2.push_front(9);
	tree2.push_front(0);

	tree3.push_front(13);
	tree3.push_front(12);
	tree3.push_front(5);

	tree4.push_front(20);
	tree4.push_front(19);
	tree4.push_front(18);
	tree4.push_front(17);


	forest->push_back(tree1);
	forest->insert(tree2);
	forest->insert(tree3);
	forest->push_back(tree4);
	std::cout<<*forest<<std::endl;
}

void ForestTest::testSearch()
{
	MATH::Graphs::ReverseTree<int> tree1;
	MATH::Graphs::ReverseTree<int> tree2;
	MATH::Graphs::ReverseTree<int> tree3;
	MATH::Graphs::ReverseTree<int> tree4;
	MATH::Graphs::Forest<int, MATH::Graphs::ReverseTree<int> >* forest = new MATH::Graphs::Forest<int, MATH::Graphs::ReverseTree<int> >();
	tree1.push_front(8);
	tree1.push_front(7);
	tree1.push_front(6);
	tree1.push_front(5);
	tree1.push_front(4);
	tree1.push_front(3);
	tree1.push_front(2);
	tree1.push_front(1);
	tree1.push_front(0);


	tree2.push_front(10);
	tree2.push_front(9);
	tree2.push_front(0);

	tree3.push_front(13);
	tree3.push_front(12);
	tree3.push_front(5);

	tree4.push_front(20);
	tree4.push_front(19);
	tree4.push_front(18);
	tree4.push_front(17);


	forest->push_back(tree1);
	forest->insert(tree2);
	forest->insert(tree3);
	forest->push_back(tree4);

	std::cout<<forest->isIn(17)<<std::endl;
}

void ForestTest::testInsert()
{

}

void ForestTest::testPushBack()
{

}

#include "run_ForestTest._cpp_"
