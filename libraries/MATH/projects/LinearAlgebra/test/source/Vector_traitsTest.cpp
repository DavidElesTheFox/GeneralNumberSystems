#include "../header/Vector_traitsTest.h"

typedef MATH::LinearAlgebra::Vector<float> FloatVector;
typedef MATH::LinearAlgebra::Vector_traits<float, FloatVector>
          floatVector_traits;


Vector_traitsTest::Vector_traitsTest():
	Tester::TestCase("Vector_traitsTest.res")
{
}

void Vector_traitsTest::testCreate()
{
	FloatVector v = floatVector_traits::create(3);
	assertNotEquale(v.getDimension(), 3);
}

void Vector_traitsTest::testGetElement()
{
	FloatVector v = floatVector_traits::create(3);
	v[1] = 10;
	assertNotEquale(floatVector_traits::getElement(1,v), 10.0f);
}

void Vector_traitsTest::testRefGetElement()
{
	FloatVector v = floatVector_traits::create(3);
	float& e = floatVector_traits::getElement(0,v);
	e = 10;
	assertNotEquale(v[0],10.0f);
}

void Vector_traitsTest::testCopy()
{
	FloatVector v = floatVector_traits::create(3);
	v[0] = 10;
	FloatVector v2 = floatVector_traits::copy(v);
	assertNotEquale(v2[0],10.0f);
}

void Vector_traitsTest::testGetDimension()
{
	FloatVector v = floatVector_traits::create(3);
	int dim = floatVector_traits::getDimension(v);
	assertNotEquale(dim, 3);
}

void Vector_traitsTest::testEquals()
{
	FloatVector v(3);
	v[2] = 10;
	FloatVector v2 = v;
	assertFalse(floatVector_traits::equals(v,v2));
}


#include "run_Vector_traitsTest._cpp_"

