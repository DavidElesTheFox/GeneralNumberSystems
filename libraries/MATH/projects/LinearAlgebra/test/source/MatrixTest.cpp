#include "../header/MatrixTest.h"


void MatrixTest::testConstructor()
{
	iMatrix mx(3,3,1);
	bool l = true;
	for(int i = 0; i < 3 && l; ++i)
		for(int j = 0; j < 3 && l; ++j)
		{
			l = l && mx(i,j)==1;
		}
	assertFalse(l);
}

void MatrixTest::testCopyConstructor()
{
	iMatrix mx(3,3,0);
	iMatrix mx2 = mx;
	bool l = true;
	for(int i = 0; i < 3 && l; ++i)
		for(int j = 0; j < 3 && l; ++j)
			l = l && mx(i,j)==mx2(i,j);
	assertFalse(l);
}

void MatrixTest::testConstructor2()
{
	iMatrix mx(3,3,iMatrix::ROW,0,1,2,
			                        1,2,3,
															2,3,4);
	bool l = true;
	for(int i = 0; i < 3 && l; ++i)
		for(int j = 0; j < 3 && l; ++j)
		{
			l = l && mx(i,j)==i + j;
		}
	assertFalse(l);
}

void MatrixTest::testOperatorBeEq()
{
	iMatrix mx(3,3, iMatrix::ROW, 10, 12, 3,
																32, 43, 1,
																23, 46, 76);
	iMatrix mx2(3,3);
	mx2 = mx;
	int row,col;
	mx.getDimension(row,col);
	bool l = true;
	for(int i = 0; i < row && l; ++i)
		for(int j = 0; j < col && l; ++j)
			l = mx(i,j) == mx2(i,j);
	assertFalse(l);
}

void MatrixTest::testOperatorResize()
{
	dMatrix mx(3, 3, 0 , dMatrix::ROW);
	mx.resize(4,4);
	int row, col;
	mx.getDimension(row, col);
	assertNotEquale(row, 4);
	assertNotEquale(col, 4);
}

void MatrixTest::testOperatorEq()
{
	iMatrix mx(3,3, iMatrix::ROW, 10, 12, 3,
																32, 43, 1,
																23, 46, 76);
	iMatrix mx2 = mx;
	assertFalse(mx == mx2);
}

void MatrixTest::testOperatorNotEq()
{
	iMatrix mx(3,3, iMatrix::ROW, 10, 12, 3,
																32, 43, 1,
																23, 46, 76);
	iMatrix mx2 = mx;
	mx2(0,0) = 0;
	assertTrue(mx == mx2);
}

void MatrixTest::testOperatorAdd()
{
	dMatrix mx(3,3, dMatrix::ROW,
								  10.0, 12.0, 3.0,
								  32.0, 43.0, 1.0,
								  23.0, 46.0, 76.0);
	dMatrix mx2(3,3, dMatrix::ROW,
								  5.0, 22.0, 31.0,
								  4.0, 31.0, 12.0,
								  21.0, 41.0, 26.0);
	dMatrix mx3= mx + mx2;
	assertDifferentHigher(mx3(0,0) , PRECISION,  15.0);
	assertDifferentHigher(mx3(0,1) , PRECISION,  34.0);
	assertDifferentHigher(mx3(0,2) , PRECISION,  34.0);

	assertDifferentHigher(mx3(1,0) , PRECISION,  36.0);
	assertDifferentHigher(mx3(1,1) , PRECISION,  74.0);
	assertDifferentHigher(mx3(1,2) , PRECISION,  13.0);

	assertDifferentHigher(mx3(2,0) , PRECISION,  44.0);
	assertDifferentHigher(mx3(2,1) , PRECISION,  87.0);
	assertDifferentHigher(mx3(2,2) , PRECISION,  102.0);
}

void MatrixTest::testOperatorMinus()
{
	dMatrix mx(3,3, dMatrix::ROW,
								  10.0, 12.0, 3.0,
								  32.0, 43.0, 1.0,
								  23.0, 46.0, 76.0);
	dMatrix mx2(3,3, dMatrix::ROW,
								  5.0, 22.0, 31.0,
								  4.0, 31.0, 12.0,
								  21.0, 41.0, 26.0);
	dMatrix mx3= mx - mx2;
	assertDifferentHigher(mx3(0,0) , PRECISION,  5.0);
	assertDifferentHigher(mx3(0,1) , PRECISION,  -10.0);
	assertDifferentHigher(mx3(0,2) , PRECISION,  -28.0);

	assertDifferentHigher(mx3(1,0) , PRECISION,  28.0);
	assertDifferentHigher(mx3(1,1) , PRECISION,  12.0);
	assertDifferentHigher(mx3(1,2) , PRECISION,  -11.0);

	assertDifferentHigher(mx3(2,0) , PRECISION,  2.0);
	assertDifferentHigher(mx3(2,1) , PRECISION,  5.0);
	assertDifferentHigher(mx3(2,2) , PRECISION,  50.0);
}

void MatrixTest::testOperatorMultScalar()
{
	dMatrix mx(3,3, dMatrix::ROW,
								  10.0, 12.0, 3.0,
								  32.0, 43.0, 1.0,
								  23.0, 46.0, 76.0);
	dMatrix mx2= mx * 15.45;
	assertDifferentHigher(mx2(0,0) , PRECISION,  154.500);
	assertDifferentHigher(mx2(0,1) , PRECISION,  185.400);
	assertDifferentHigher(mx2(0,2) , PRECISION,  46.350);

	assertDifferentHigher(mx2(1,0) , PRECISION,  494.400);
	assertDifferentHigher(mx2(1,1) , PRECISION,  664.350);
	assertDifferentHigher(mx2(1,2) , PRECISION,  15.450);

	assertDifferentHigher(mx2(2,0) , PRECISION,  355.350);
	assertDifferentHigher(mx2(2,1) , PRECISION,  710.700);
	assertDifferentHigher(mx2(2,2) , PRECISION,  1174.200);
}

void MatrixTest::testOperatorMult()
{
	dMatrix mx(3,3, dMatrix::ROW,
								  10.0, 12.0, 3.0,
								  32.0, 43.0, 1.0,
								  23.0, 46.0, 76.0);
	dMatrix mx2(3,3, dMatrix::ROW,
								  5.0, 22.0, 31.0,
								  4.0, 31.0, 12.0,
								  21.0, 41.0, 26.0);
	dMatrix mx3= mx * mx2;

	assertDifferentHigher(mx3(0,0) , PRECISION,  161.000);
	assertDifferentHigher(mx3(0,1) , PRECISION,  715.000);
	assertDifferentHigher(mx3(0,2) , PRECISION,  532.000);

	assertDifferentHigher(mx3(1,0) , PRECISION,  353.000);
	assertDifferentHigher(mx3(1,1) , PRECISION,  2078.000);
	assertDifferentHigher(mx3(1,2) , PRECISION,  1534.000);

	assertDifferentHigher(mx3(2,0) , PRECISION,  1895.000);
	assertDifferentHigher(mx3(2,1) , PRECISION,  5048.000);
	assertDifferentHigher(mx3(2,2) , PRECISION,  3241.000);
}

void MatrixTest::testFill()
{	}

void MatrixTest::testOperatorMultVM()
{
  dMatrix m(3,3,dMatrix::COL,
	                       1.0, 2.0, 3.0,
	                       10.0, 22.0, 31.0,
	                       0.0, -1.0, 2.0);
	dVector v(3, 1.0);
	dVector a = v*m;
	assertDifferentHigher(11.0,0.0001,a[0]);
	assertDifferentHigher(23.0,0.0001,a[1]);
	assertDifferentHigher(36.0,0.0001,a[2]);

}
void MatrixTest::testOperatorMultMV()
{
	dMatrix m(3,3,dMatrix::COL,
	                       1.0, 2.0, 3.0,
	                       10.0, 22.0, -31.0,
	                       0.0, -1.0, 2.0);
	dVector v(3, 1.0);
	dVector a = m*v;
	assertDifferentHigher(6.0,0.0001,a[0]);
	assertDifferentHigher(1.0,0.0001,a[1]);
	assertDifferentHigher(1.0,0.0001,a[2]);
}

void MatrixTest::testPressure()
{
	clock_t start;
	int size = 100;
	double time;
	dMatrix mx(size, size, 10);
	dMatrix mx2(size, size, 30);
	start = ::clock();
	dMatrix mx3= mx * mx2;
	time = ((double)::clock() - start)/CLOCKS_PER_SEC;
	std::cout<<time<<std::endl;
	assertLower(0.1,time);
}

#include "run_MatrixTest._cpp_"

