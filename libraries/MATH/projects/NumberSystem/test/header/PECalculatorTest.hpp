#ifndef PECALCULATOR_TEST_H
#error usage without header
#endif


#include <MATH/LinearAlgebra/euclideannorm.h>

#define DEF_TEMP template<class PE_CALC, \
                          bool canDetermineNumberSystem>

#define PE_TEST PECalculatorTest<PE_CALC, canDetermineNumberSystem>


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
typedef NumSys::DigitSet NSDigitSet;

typedef MATH::LinearAlgebra::Vector<int> iVector;
typedef MATH::LinearAlgebra::Vector<float> fVector;
typedef MATH::LinearAlgebra::Matrix<int> iMatrix;
typedef MATH::LinearAlgebra::Matrix<float> fMatrix;
typedef MATH::NumberSystem::AbstractPeriodicElementCalculator<int, float,
				  MATH::LinearAlgebra::Matrix,
					MATH::LinearAlgebra::Vector,
					SimpleMatrixNorm,
					SimpleVectorNorm> AbstractCalc;

DEF_TEMP
void PE_TEST::run()
{
	bool tmp = true;
	testCalculatePeriodicElements();
	if(isOk())
		std::cout<<"\tOK................testCalculatePeriodicElements"<<std::endl;
	else
		std::cout<<"\tNOK...............testCalculatePeriodicElements"<<std::endl;
	tmp = tmp && isOk();
	ok = true;

	if (canDetermineNumberSystem)
	{
		testIsNumberSystem();
		if (isOk())
			std::cout<<"\tOK................testIsNumberSystem"<<std::endl;
		else
			std::cout<<"\tNOK................testIsNumberSystem"<<std::endl;
	}
}

DEF_TEMP
void PE_TEST::testCalculatePeriodicElements()
{
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
	AbstractCalc* pcalc = 
		new PE_CALC(&ns);
	try
	{
		typename PE_CALC::Parameter params(number,
			                 number2,
											 0,
											 1,
											 1,
											 10,
											 10);
		NSDigitSet ret = pcalc->calculatePeriodicElements(params);
		assertNotEquale(ret.size(), 1);
	}catch(Exceptions::RuntimeException& ex)
	{
		std::cout<<ex<<std::endl;
	}

	delete pcalc;
}

DEF_TEMP
void PE_TEST::testIsNumberSystem()
{
	std::cout<<"NOT IMPLEMENTED YET"<<std::endl;
}

#undef PE_TEST
#undef DEF_TEMP


