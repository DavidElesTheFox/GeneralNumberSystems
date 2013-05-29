#include "../header/ReverseTreeTest.h"


ReverseTreeTest::ReverseTreeTest():Tester::TestCase("ReverseTreeTest.res")
{	}


void ReverseTreeTest::testCreate()
{
	MATH::Graphs::ReverseTree<int> tree(8);
	tree.push_front(7);
	tree.push_front(6);
	tree.push_front(5);
	tree.push_front(4);
	tree.push_front(3);
	tree.push_front(2);
	tree.push_front(1);
	tree.push_front(0);
	//std::cout<<tree<<std::endl;
}

void ReverseTreeTest::testSearch()
{
	MATH::Graphs::ReverseTree<int> tree(8);
	tree.push_front(7);
	tree.push_front(6);
	tree.push_front(5);
	tree.push_front(4);
	tree.push_front(3);
	tree.push_front(2);
	tree.push_front(1);
	tree.push_front(0);
	MATH::Graphs::ReverseTree<int>::ReverseTreeNode *node = 0;
	for(int i = 1; i<7; ++i)
	{
		if(tree.find(i, node))
		{
			assertNotEquale(node->prevs.size(),1);
			assertNotEquale(node->prevs[0]->value,i + 1);
			assertNotEquale(node->next->value, i -1);
		}
		else
		{
			assertTrue(true,"Find faulier");
		}
	}
}

void ReverseTreeTest::testInsert()
{
	MATH::Graphs::ReverseTree<int> tree(8);
	tree.push_front(7);
	tree.push_front(6);
	tree.push_front(5);
	tree.push_front(4);
	tree.push_front(3);
	tree.push_front(2);
	tree.push_front(1);
	tree.push_front(0);

	MATH::Graphs::ReverseTree<int>::ReverseTreeNode* node = new MATH::Graphs::ReverseTree<int>::ReverseTreeNode(18);
	MATH::Graphs::ReverseTree<int>::ReverseTreeNode* node2 =new MATH::Graphs::ReverseTree<int>::ReverseTreeNode(4, node);
	tree.insert(node2);
	delete node;
	delete node2;

	if(tree.find(4,node))
	{
		assertNotEquale(node->prevs.size(),2);
		assertNotEquale(node->prevs[0]->value,5);
		assertNotEquale(node->prevs[1]->value,18);
	}
	else
	{
		assertTrue(true,"Find faulier");
	}


}

void ReverseTreeTest::testInsertGraph()
{
	MATH::Graphs::ReverseTree<int> tree(8);
	tree.push_front(7);
	tree.push_front(6);
	tree.push_front(5);
	tree.push_front(4);
	tree.push_front(3);
	tree.push_front(2);
	tree.push_front(1);
	tree.push_front(0);

	MATH::Graphs::ReverseTree<int> tree2(12);
	tree2.push_front(11);
	tree2.push_front(10);
	tree2.push_front(9);
	tree2.push_front(5);
	tree.insert(tree2);
	//std::cout<<tree<<std::endl;
	MATH::Graphs::ReverseTree<int>::ReverseTreeNode* node;
	if(tree.find(5,node))
	{
		assertNotEquale(node->prevs.size(), 2);
		assertNotEquale(node->prevs[0]->value, 6);
		assertNotEquale(node->prevs[1]->value, 9);
		assertNotEquale(node->next->value, 4);
	}
	else
	{
		assertTrue(true,"Find faulier");
	}
}

void ReverseTreeTest::testInsertNode()
{
	MATH::Graphs::ReverseTree<int> tree(8);
	tree.push_front(7);
	tree.push_front(6);
	tree.push_front(5);
	tree.push_front(4);
	tree.push_front(3);
	tree.push_front(2);
	tree.push_front(1);
	tree.push_front(0);

	MATH::Graphs::ReverseTree<int> tree2(12);
	tree2.push_front(11);
	tree2.push_front(10);
	tree2.push_front(9);
	tree2.push_front(111);
	assertTrue(tree.insert(tree2));
	//std::cout<<tree<<std::endl;
}

void ReverseTreeTest::testJoinToLeaf()
{
	MATH::Graphs::ReverseTree<int> tree(8);
	tree.push_front(7);
	tree.push_front(6);
	tree.push_front(5);
	tree.push_front(4);
	tree.push_front(3);
	tree.push_front(2);
	tree.push_front(1);
	tree.push_front(0);

	MATH::Graphs::ReverseTree<int> tree2(12);
	tree2.push_front(11);
	tree2.push_front(10);
	tree2.push_front(9);
	tree2.push_front(111);
	tree2.push_front(0);
	assertFalse(tree.joinToLeaf(tree2));
	assertFalse(tree.joinToLeaf(tree2));
	assertNotEquale(tree.getLeaf()->prevs.size(),3);
	//std::cout<<tree<<std::endl;
}

void ReverseTreeTest::testSimplify()
{
	MATH::Graphs::ReverseTree<int> tree(8);
	tree.push_front(7);
	tree.push_front(6);
	tree.push_front(5);
	tree.push_front(4);
	tree.push_front(3);
	tree.push_front(2);
	tree.push_front(1);
	tree.push_front(0);

	MATH::Graphs::ReverseTree<int> tree2(12);
	tree2.push_front(11);
	tree2.push_front(10);
	tree2.push_front(9);
	tree2.push_front(111);
	tree2.push_front(0);
	assertFalse(tree.joinToLeaf(tree2));
	assertFalse(tree.joinToLeaf(tree2));
	tree.simplify();
	assertNotEquale(tree.getLeaf()->prevs.size(),2);
	std::cout<<tree<<std::endl;
}

#include "run_ReverseTreeTest._cpp_"
