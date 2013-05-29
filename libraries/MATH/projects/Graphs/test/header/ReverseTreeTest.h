#ifndef REVERSETREE_TEST_H
#define REVERSETREE_TEST_H

#include <Tester/testcase.h>
#include <MATH/Graphs/reversetree.h>

#include <time.h>

class ReverseTreeTest:public Tester::TestCase
{
    public:
        ReverseTreeTest();

        virtual void run();

        void testCreate();

        void testSearch();

        void testInsert();

        void testInsertGraph();

        void testInsertNode();

        void testJoinToLeaf();

        void testSimplify();


};


#endif
