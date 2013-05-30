#ifndef MATH__NUMBERSYSTEM__NUMBERSYSTEMCALCULATOR_H
#error Included only body
#endif

#define DEF_TEMP template<class INT_TYPE,                       \
                          class FLOAT_TYPE,                     \
						              template<class T> class Matrix,       \
						              template<class T> class Vector,       \
                          template<class T> class VectorNorm,   \
                          template<class T> class MatrixNorm,   \
						              template<class T, class M>            \
                            class matrix_traits,                \
						              template<class T, class V>            \
                            class vector_traits,                \
						              template<class T> class number_traits>

#define NUMSYS_CALC NumberSystemCalculator<INT_TYPE,      \
                                           FLOAT_TYPE,    \
                                           Matrix,        \
                                           Vector,        \
                                           VectorNorm,    \
                                           MatrixNorm,    \
                                           matrix_traits, \
                                           vector_traits, \
                                           number_traits>

namespace MATH
{
  namespace NumberSystem
  {

		DEF_TEMP
		void NUMSYS_CALC::computeRectangleOfH(FVector& v1,
                                          FVector& v3,
                                          const NUMSYS_CALC::ConnectedNumberSystem& ns)
		{
			int dimension = matrix_traits_int::getRowNum(ns.getBase());
			FMatrix X = ns.getBaseInverse();
			FMatrix MI = ns.getBaseInverse();

			v1 = v3 = vector_traits_float::create(dimension);
			FVector v2 = v1;
			FVector v4 = v3;
			
			int c = 1;
			double norm = FMCalculator::norm(0, X);
			while (norm >= 0.01)
			{
				X = MI*X;
				norm = FMCalculator::norm(0, X);
				c++;
			}
			rectangleComputeCore(v2, v4, dimension, c, ns);
			v2 = v2*FLOAT_TYPE(1.0/(1.0 - norm));
			v4 = v4*FLOAT_TYPE(1.0/(1.0 - norm));
			for(int i = 0; i < dimension; ++i)
			{
				vector_traits_float::setElement(i,
																				NumCalc_float::ceil(
																					-1 * vector_traits_float::
																					  getElement(i,v2))
                                          + number_traits_float::multiplicativeUnit,
																				v1);
				vector_traits_float::setElement(i,
																				NumCalc_float::floor(
																					-1 * vector_traits_float::
																					  getElement(i,v4))
                                        - number_traits_float::multiplicativeUnit,
																				v3);
        //+- 1 is needed due to double precision
			}
		}

		DEF_TEMP
		void NUMSYS_CALC::rectangleComputeCore(FVector& v2,
                                           FVector& v4,
                                           const int dimension,
                                           const int minNorm,
                                           const NUMSYS_CALC::ConnectedNumberSystem& ns)
		{
			FMatrix X = ns.getBaseInverse();
			FMatrix MI = ns.getBaseInverse();
			FLOAT_TYPE min, max;
			ConnectedDigitSet digits = ns.getDigitSet();
			std::vector<FVector> set(digits.size()* minNorm);
			for(int j = 0; j < minNorm; ++j)
			{
				for(unsigned i = 0; i < digits.size(); ++i)
				{
					set[i + j * digits.size()] = 
						X * I_F_Converter::template convertVector<Vector>(digits[i]);
				}
				X = MI * X;
			}
			for (int j = 0; j < minNorm; ++j)
			{
				for (int i = 0; i < dimension; ++i)
				{
					min = vector_traits_float::getElement(i, set[j*digits.size()]);
					max = min;
					for (unsigned k = 0; k < digits.size();++k)
					{
						FLOAT_TYPE element = vector_traits_float::
							getElement(i, set[k + j*digits.size()]);
						if (min > element)
							min = element;
						if (max < element)
							max = element;
					}

					vector_traits_float::
						setElement(
							i,
							j == 0 ? min
						         : vector_traits_float::getElement(i,v2) + min,
							v2);

					vector_traits_float::
						setElement(
							i,
							j == 0 ? max
						         : vector_traits_float::getElement(i,v4) + max,
							v4);
				}
			}
		}

    DEF_TEMP
    double NUMSYS_CALC::
      calculateLimitOfExpansion(const NUMSYS_CALC::ConnectedNumberSystem& ns)
    {
      ConnectedDigitSet digits = ns.getDigitSet();
			double K = VectorNorm_int::calculateNorm(digits[0]);
			for (unsigned i = 0; i < digits.size(); ++i)
			{
				double norm = VectorNorm_int::calculateNorm(digits[i]);
				if ( K < norm)
					K = norm;
			}
			double r = MatrixNorm_float::calculateNorm(ns.getBaseInverse());

			double L = K*r / (double)(1.0-r);
			return L;
    }
  }
}

#undef DEF_TEMP
#undef NUMSYS_CALC

