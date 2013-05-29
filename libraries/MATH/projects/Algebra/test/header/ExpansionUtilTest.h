#ifndef EXPANSIONUTIL_TEST_H
#define EXPANSIONUTIL_TEST_H

#include <Tester/testcase.h>

#include <time.h>

class ExpansionUtilTest: public Tester::TestCase
{
    public:
        ExpansionUtilTest();

        virtual void run();

        void testCreateAlgebricalField();

        void testCreateNonAlgebricalField();
};

#endif

