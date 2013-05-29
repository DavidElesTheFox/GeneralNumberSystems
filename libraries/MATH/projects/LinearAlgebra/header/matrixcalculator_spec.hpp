#ifndef __MATH__LINEARALGEBRA_MATRIXCALCULATOR_H
#error include without matrixcalculator.h
#endif


#ifndef __MATH__LINEARALGEBRA__SMITHNORMALFORM_H
#include "smithnormalform.h"
#else
namespace MATH
{
	namespace LinearAlgebra
	{
		template<class T,
			       class Matrix, 
						 class traits,
						 class number_traits >
		class SmithNormalForm;
	}
}
#endif

#define DEF_TEMP template<class T,         \
													class Matrix,    \
													class traits,    \
													class number_traits>

#define MTX_CALC_SPEC MatrixCalculator<T,            \
                                       Matrix,       \
																			 traits,       \
																			 number_traits,\
																			 true>

#define BASE MatrixCalculator_core<T, Matrix, traits, number_traits, true>

#include <MATH/Algebra/padicshape.h>

namespace MATH
{
	namespace LinearAlgebra
	{

    DEF_TEMP
    bool MTX_CALC_SPEC::isExpansive(const Matrix& m)
    {
      typedef MATH::Algebra::PAdicShape<10, T, std::vector<T>, number_traits > BigNumber;

      MATH::Algebra::Polynomial<T, std::vector<T>, number_traits > p
        = BASE::template calculateCharacteristicPolynomial<
            MATH::Algebra::Polynomial<T,
                                      std::vector<T>, 
                                      number_traits>
                                                          >(m);
      MATH::Algebra::Polynomial<BigNumber> p2;
      for (unsigned i = 0; i <= p.getDegree(); ++i)
        p2[i] = BigNumber(p[i]);
      return MATH::Algebra::LehmerSchur<BigNumber,
               MATH::Algebra::Polynomial<BigNumber> >::doAlgorithm(p2);
    }

		DEF_TEMP
		int MTX_CALC_SPEC::calculateRank(const Matrix& m)
		{
			SmithNormalForm<T, Matrix, traits, number_traits> snf(m);
			const Matrix s = snf["S"];
			const Matrix u = snf["U"];
			const Matrix v = snf["V"];
//			std::cout<<"m: \n"<<m<<std::endl;
//			std::cout<<"u: \n"<<u<<std::endl;
//			std::cout<<"v: \n"<<v<<std::endl;
//			std::cout<<"u*m*v: \n"<<u*m*v<<std::endl;
//			std::cout<<"s: \n"<<s<<std::endl;
			const int rowNum = traits::getRowNum(s);
			int rank = number_traits::additiveUnit;
			for (int i = 0; i < rowNum; ++i)
			{
				if (!BASE::NumCalc::equals(traits::getElement(i,i,m),
							              number_traits::additiveUnit))
				{
					rank++;
				}
			}
//			std::cout<<"det: \n"<<det<<std::endl;
			return rank;
		}

		DEF_TEMP
		bool MTX_CALC_SPEC::isFullRanked(const Matrix& m)
		{
			int rank = calculateRank(m);
			int rowNum = traits::getRowNum(m);
			int colNum = traits::getColNum(m);
			return rowNum > colNum ? rank == rowNum:
				                       rank == colNum;
		}


		DEF_TEMP
		bool MTX_CALC_SPEC::
		  calculateInverse(const Matrix& m,
			                 Matrix& inverse)
		{
			throw Exceptions::RuntimeException("Inverse calculation in"
				                                 "Integer case 01");
		}

		DEF_TEMP
		Matrix MTX_CALC_SPEC::
		  calculateInverse(const Matrix& m,
											 int& rank,
											 T& determinant,
											 Matrix& rest)
		{
			throw Exceptions::RuntimeException("Inverse calculation in"
				                                 "Integer case 02");
		}

		DEF_TEMP
		bool MTX_CALC_SPEC::
		  calculateInverseRest(const Matrix& m,
													 Matrix& rest)
		{
			throw Exceptions::RuntimeException("Inverse calculation in"
				                                 "Integer case 03");
		}

	}
}

#undef DEF_TEMP
#undef MTX_CALC_SPEC
#undef BASE

