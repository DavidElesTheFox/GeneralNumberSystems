#ifndef FOREST_TEST_H
#define FOREST_TEST_H

#include <Tester/testcase.h>
#include <MATH/Graphs/forest.h>
#include <MATH/Graphs/reversetree.h>

#include <time.h>

class ForestTest:public Tester::TestCase
{
    public:
        ForestTest();

        virtual void run();

        void testCreate();

        void testSearch();

        void testInsert();

        void testPushBack();



};


#endif
