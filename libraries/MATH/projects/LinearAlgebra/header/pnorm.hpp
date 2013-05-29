#ifndef MATH__LINEARALGEBRA__PNORM_H
#warn Include without body
#else

namespace MATH
{
	namespace LinearAlgebra
	{

    //////////////////////////// Matrix norm ////////////////////////////////
		template<class NormContainer,
		         class T,
			       class Matrix,
						 class matrix_traits,
						 class number_traits>
		double PMatrixNormDynamic<NormContainer, T, Matrix, matrix_traits, number_traits>::
		    calculateNorm(const Matrix& m)
		{
			int rowNum = 0;
			int colNum = 0;
			matrix_traits::getDimension(rowNum, colNum, m);
			double sum = number_traits::additiveUnit;
			for (int i = 0; i < rowNum; ++i)
			{
				for (int j = 0; j < colNum; ++j)
				{
					double element = NumCalc::abs(matrix_traits::getElement(i, j, m));
					sum += MATH::Algebra::NumberCalculator<double>::pow(element, NormContainer::norm);
				}
			}
			return MATH::Algebra::NumberCalculator<double>::root(sum, NormContainer::norm);
		}

    //////////////////////////// Vector norm ////////////////////////////////

		template<class NormContainer,
		         class T,
			       class Vector,
						 class vector_traits,
						 class number_traits>
		double PVectorNormDynamic<NormContainer, T, Vector, vector_traits, number_traits>::
		    calculateNorm(const Vector& v)
		{
			int colNum = vector_traits::getDimension(v);
			double sum = number_traits::additiveUnit;
			for (int i = 0; i < colNum; ++i)
			{
					double element = NumCalc::abs(vector_traits::getElement(i, v));
					sum += MATH::Algebra::NumberCalculator<double>::pow(element, NormContainer::norm);
			}
			return MATH::Algebra::NumberCalculator<double>::root(sum, NormContainer::norm);
		}

	}
}

#endif
