#ifndef LINKEDGRAPH_TEST_H
#define LINKEDGRAPH_TEST_H

#include <Tester/testcase.h>
#include <MATH/Graphs/linkedgraph.h>

#include <time.h>

class LinkedGraphTest:public Tester::TestCase
{
    public:
        LinkedGraphTest();

        virtual void run();

        void testCreate();

        void testSearch();

        void testInsert();

        void testPushBack();



};


#endif
