#ifndef MATH__LINEARALGEBRA__EUCLIDEANNORM_H
#warn olny body included
#else

#include "matrixcalculator.h"
#include "vectorcalculator.h"

namespace MATH
{
	namespace LinearAlgebra
	{

		/////////////////////////////// Matrix norm ////////////////////////////

		template<class NormContainer,
						 class T, 
						 class Matrix, 
						 class matrix_traits,
						 class number_traits,
						 bool isInteger>
		double EuclideanMatrixNormDynamic<NormContainer,
		                             T, Matrix, matrix_traits, number_traits, isInteger>::
				calculateNorm(const Matrix& m)
		{
			return MatrixCalculator<T, Matrix, matrix_traits, number_traits, isInteger>::
				norm(NormContainer::norm, m);
		}

		/////////////////////////////// Vector norm ////////////////////////////

		template<class NormContainer, 
			       class T,
			       class Vector,
						 class vector_traits,
						 class number_traits>
		double EuclideanVectorNormDynamic<NormContainer, T, Vector, vector_traits, number_traits>::
		    calculateNorm(const Vector& v)
		{
			return VectorCalculator<T, Vector, number_traits, vector_traits>::
				norm(NormContainer::norm, v);
		}

	}
}
#endif
