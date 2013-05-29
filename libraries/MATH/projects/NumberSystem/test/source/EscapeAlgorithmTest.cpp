#include "../header/EscapeAlgorithmTest.h"

#include <MATH/LinearAlgebra/euclideannorm.h>
#include <MATH/Algebra/complex.h>
template<class T>
class SimpleMatrixNorm 
  : public MATH::LinearAlgebra::EuclideanMatrixNorm<0, 
	                                                  T,
																										MATH::LinearAlgebra::Matrix<T>
				                                            >
{
};

template<class T>
class SimpleVectorNorm
  : public MATH::LinearAlgebra::EuclideanVectorNorm<0,
	                                                  T,
																										MATH::LinearAlgebra::Vector<T>
				                                            >
{
};

typedef MATH::NumberSystem::NumberSystem<int, float,
				                                 MATH::LinearAlgebra::Matrix,
																				 MATH::LinearAlgebra::Vector> NumSys;

typedef MATH::NumberSystem::EscapeAlgorithm<int,float,
				                                    MATH::LinearAlgebra::Matrix,
																						MATH::LinearAlgebra::Vector,
				                                    SimpleVectorNorm,
																						SimpleMatrixNorm > EscAlg; 

typedef NumSys::DigitSet NSDigitSet;

typedef MATH::LinearAlgebra::Vector<int> iVector;
typedef MATH::LinearAlgebra::Vector<float> fVector;
typedef MATH::LinearAlgebra::Matrix<int> iMatrix;
typedef MATH::LinearAlgebra::Matrix<float> fMatrix;

typedef MATH::Algebra::Complex<int> gaussian_t;
typedef MATH::Algebra::Complex<float> complex_t;

typedef MATH::NumberSystem::NumberSystem<gaussian_t, complex_t,
				                                 MATH::LinearAlgebra::Matrix,
																				 MATH::LinearAlgebra::Vector> NumSysI;

typedef MATH::NumberSystem::EscapeAlgorithm<gaussian_t,complex_t,
				                                    MATH::LinearAlgebra::Matrix,
																						MATH::LinearAlgebra::Vector,
				                                    SimpleVectorNorm,
																						SimpleMatrixNorm > EscAlgI; 

typedef NumSysI::DigitSet NSDigitSetI;

typedef MATH::LinearAlgebra::Vector<gaussian_t> iVectorI;
typedef MATH::LinearAlgebra::Vector<complex_t> fVectorI;
typedef MATH::LinearAlgebra::Matrix<gaussian_t> iMatrixI;
typedef MATH::LinearAlgebra::Matrix<complex_t> fMatrixI;

EscapeAlgorithmTest::EscapeAlgorithmTest():Tester::TestCase("EscapeAlgorithmTest.res")
{	}


void EscapeAlgorithmTest::testCompute()
{
	int sizeX = 100, sizeY = 100;
	NSDigitSet digits;
	iVector d(2, 0);
	digits.push_back(d);
	d[0] = 1;
	digits.push_back(d);
	d[0] = -1;
	d[1] = 0;
	digits.push_back(d);

	iMatrix base(2,2);
	base(0,0) = 1;	base(0,1)= -2;
	base(1,0) = 1; base(1,1) = 1;

	NumSys ns(base, digits);
	iVector number(2, 0);
	iVector number2(2, 0);
	number[0] = 1;
	number[1] = 0;
	number2[0] = 0;
	number2[1] = 1;
	clock_t start = clock();
	unsigned** matrix = new unsigned*[sizeX];
	for(int i = 0; i < sizeX; ++i)
	{
		matrix[i] = new unsigned[sizeY];
	}
	try
	{
//		ns.computeGraph(number, number2
//						,0 ,1, 1,
//						 sizeX,sizeY);
//		assertNotEquale(ns.getElementForest()->size(), 1);
		EscAlg escape(&ns, 28);
		escape.compute(0, 1,
					   sizeX,sizeY,
					   matrix);
	}catch(Exceptions::RuntimeException ex)
	{
		std::cout<<ex<<std::endl;
	}
//	for(int i = 0; i < sizeX; ++i)
//	{
//		for(int j = 0; j < sizeY; ++j)
//		{
//			std::cerr<<matrix[i][j]<<"\t";
//		}
//		std::cerr<<std::endl;;
//	}
	std::cout<<((double)clock()-start)/CLOCKS_PER_SEC<<std::endl;
	for(int i = 0; i < sizeX; ++i)
	{
		delete[] matrix[i];
	}
	delete[] matrix;

}

void EscapeAlgorithmTest::testCompute2()
{
	int sizeX = 100, sizeY = 100;
	NSDigitSetI digits;
	iVectorI d(2, 0);
	digits.push_back(d);
	d[0] = (gaussian_t)1;
	digits.push_back(d);
	d[0] = (gaussian_t)-1;
	d[1] = (gaussian_t)0;
	digits.push_back(d);

	iMatrixI base(2,2);
	base(0,0) = (gaussian_t)1;	base(0,1)= (gaussian_t)-2;
	base(1,0) = (gaussian_t)1; base(1,1) = (gaussian_t)1;

	NumSysI ns(base, digits);
	iVectorI number(2, 0);
	iVectorI number2(2, 0);
	number[0] = (gaussian_t)1;
	number[1] = (gaussian_t)0;
	number2[0] = (gaussian_t)0;
	number2[1] = (gaussian_t)1;
	clock_t start = clock();
	unsigned** matrix = new unsigned*[sizeX];
	for(int i = 0; i < sizeX; ++i)
	{
		matrix[i] = new unsigned[sizeY];
	}
	try
	{
//		ns.computeGraph(number, number2
//						,0 ,1, 1,
//						 sizeX,sizeY);
//		assertNotEquale(ns.getElementForest()->size(), 1);
		EscAlgI escape(&ns, 28);
		escape.compute(0, 1,
					   sizeX,sizeY,
					   matrix);
	}catch(Exceptions::RuntimeException ex)
	{
		std::cout<<ex<<std::endl;
	}
//	for(int i = 0; i < sizeX; ++i)
//	{
//		for(int j = 0; j < sizeY; ++j)
//		{
//			std::cerr<<matrix[i][j]<<"\t";
//		}
//		std::cerr<<std::endl;;
//	}
	std::cout<<((double)clock()-start)/CLOCKS_PER_SEC<<std::endl;
	for(int i = 0; i < sizeX; ++i)
	{
		delete[] matrix[i];
	}
	delete[] matrix;

}

#include "run_EscapeAlgorithm._cpp_"
