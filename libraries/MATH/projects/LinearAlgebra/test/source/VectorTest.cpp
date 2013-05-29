#include "../header/VectorTest.h"


void VectorTest::testConstructor()
{
    dVector v(3);
    bool l=true;
    for(int i=0;i<3 && l;++i)
    {

        l=l && v[i]==0;
    }
    assertFalse(l);

}

void VectorTest::testCopyConstructor()
{
    dVector v(3);
    dVector v2=v;
    bool l=true;
    for(int i=0;i<3 && l;++i)
    {
        l=l && v2[i]==0;
    }
    assertFalse(l);
}

void VectorTest::testConstructor2()
{
    double t[3];
    t[0]=2;t[1]=1;t[2]=0;
    dVector v(t,3);
    assertDifferentHigher(v[0], PRECISION, 2);
    assertDifferentHigher(v[1], PRECISION, 1);
    assertDifferentHigher(v[2], PRECISION, 0);

}

void VectorTest::testCount()
{
    dVector v(12);
    assertFalse(v.getDimension()==12);
}

void VectorTest::testOperator_BR()
{
    double t[3];
    t[0]=21;
    t[1]=13;
    t[2]=1;
    dVector v(t,3);

    v[2]=10;
    assertDifferentHigher(v[2], PRECISION, 10);
}

void VectorTest::testOperator_BR_C()
{
    double t[3];
    t[0]=21;
    t[1]=13;
    t[2]=1;
    dVector v(t,3);

    assertDifferentHigher(v[2], PRECISION, 1);
}


void VectorTest::testOperatorBeEQ()
{
    double t[3];
    t[0]=21;
    t[1]=13;
    t[2]=1;
    dVector v(t,3);

    dVector v2(3);
    v2=v;
    for(int i=0;i<3;++i)
    {
			assertDifferentHigher(v2[0], PRECISION, v[0]);
    }
}

void VectorTest::testOperatorEQ()
{
    double t[3];
    t[0]=21;
    t[1]=13;
    t[2]=1;
    dVector v(t,3);

    dVector v2(3);
    v2=v;

    assertFalse(v2==v);
}

void VectorTest::testOperatorPlus()
{
    double t[3];
    t[0]=21;
    t[1]=13;
    t[2]=1;
    dVector v(t,3);

    dVector v2=v;
    v2[0]=10.3;
    v2[1]=10.2;
    v2[2]=2.1;

    dVector a=v+v2;

    assertDifferentHigher(a[0], PRECISION, 31.3);
    assertDifferentHigher(a[1], PRECISION, 23.2);
    assertDifferentHigher(a[2], PRECISION, 3.1);
}


void VectorTest::testOperatorMinus()
{
    double t[3];
    t[0]=21;
    t[1]=13;
    t[2]=1;
    dVector v(t,3);

    dVector v2=v;
    v2[0]=10.3;
    v2[1]=10.2;
    v2[2]=2.1;

    dVector a=v2-v;
    assertDifferentHigher(a[0], PRECISION, -10.7);
    assertDifferentHigher(a[1], PRECISION, -2.8);
    assertDifferentHigher(a[2], PRECISION, 1.1);
}


void VectorTest::testOperatorMultV_V()
{
    double t[3];
    t[0]=21;
    t[1]=13;
    t[2]=1;
    dVector v(t,3);

    dVector v2=v;
    v2[0]=10;
    v2[1]=10;
    v2[2]=2;

    double a = v2 * v;
    assertDifferentHigher(a,PRECISION, 342.0);
}

void VectorTest::testOperatorMultV_D()
{
    double t[3];
    t[0]=21;
    t[1]=13;
    t[2]=1;
    dVector v(t,3);
    dVector a = v*4.56;
    assertDifferentHigher(a[0], PRECISION, 95.76);
    assertDifferentHigher(a[1], PRECISION, 59.28);
    assertDifferentHigher(a[2], PRECISION, 4.56);
}


void VectorTest::testOperatorMultD_V()
{
    double t[3];
    t[0]=21;
    t[1]=13;
    t[2]=1;
    dVector v(t,3);
    dVector a=4.56*v;
    assertDifferentHigher(a[0], PRECISION, 95.76);
    assertDifferentHigher(a[1], PRECISION, 59.28);
    assertDifferentHigher(a[2], PRECISION, 4.56);
}

void VectorTest::testXmultiply()
{
    double t[3];
    t[0]=21;
    t[1]=13;
    t[2]=1;
    dVector v(t,3);

    dVector v2=v;
    v2[0]=42;
    v2[1]=26;
    v2[2]=2;

    dVector c = dVector::Xmultiply(v2,v);

    assertDifferentHigher(c[0], PRECISION, 0);
    assertDifferentHigher(c[1], PRECISION, 0);
    assertDifferentHigher(c[2], PRECISION, 0);
		
}

#include "run_VectorTest._cpp_"
