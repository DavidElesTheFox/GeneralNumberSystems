#ifndef __MATH__LINEARALGEBRA_MATRIXCALCULATOR_H
#error include without matrixcalculator.h
#endif


#include <MATH/Algebra/number_traits.h>

#include <Exceptions/runtimeexception.h>

/**
	* @file matrixcalculator_spec.h
	*
	* @brief   Contains the specializazion of MatrixCalculator class.
	* @details This file contains the implementation of the
	*          MatrixCalculator specializations.
	* @see matrixcalculator_spec.h
	*/

namespace MATH
{
	namespace LinearAlgebra
	{
		/**
			* @brief   Matrix Calculator for Matrices, which contains int.
			* @details There are importent deferences between integer and 
			*          float-decimal matrices. The problem is around the
			*          division and precision.
			* @note    For example you write this a/b, if a and b is element 
			*          of an integer matrix the result could be a fractional,
			*          not an integer (2/3 = 0), so it's not so good.
			*          Could be a sollution if you always do a conversion from int
			*          to float number, but it possible a such a much inaccuration,
			*          that the result will be wrong, and other hand it cost a lot 
			*          of time. So if it possible you can find an other algorithm to 
			*          int and use the specialization.
			* @param Matrix the matrix type
			* @param traits the matrix traits class
			* @param number_traits the number traits class
			* @see MATH::LinearAlgebra::Matrix_traits
			* @see MATH::Algebra::Number_traits
			*/
		template<class T,
			       class Matrix,
			       class traits,
						 class number_traits>
		struct MatrixCalculator<T,
			                      Matrix,
														traits,
														number_traits,
														true>
		  :public MatrixCalculator_core<T, Matrix, traits, number_traits, true>
		{

      /**
        * @brief Check that the given matrix is expansive.
        * @details A matrix is expansive, if there are no eigenvalue
        *          on the unit circle.
        *          For this check we use the Lehmer Schur method.
        * @param m The given matrix
        * @return True if m is expansive
        */
      static bool isExpansive(const Matrix& m);

			/**
				* @brief   Calculate the rank of the input matrix
				* @param   m input matrix
				* @return  the rank
				* @see Matrix::LinearAlgebra::SmithNormalForm
				*/
			static int calculateRank(const Matrix& m);
			
			/**
				* @brief   Determination of full-ranked.
				* @details This function calculates the rank
				*          with Gauss elimination.
				* @param m the input matrix
				* @warning Doesn't exists integer specialization
				*           of this function
				* @return it's full-ranked or not
				*/
			static bool isFullRanked(const Matrix& m);


			private:

				/* Functions which doesn't work in Integer case */
				/**
					* @brief Calculate the inverse of matrix
					* @details his is an integer matrix
					*                 inverse calculation doesn't exists, 
					*                 this field, use converter class for
					*                 convert a new class.

					* @param m constant matrix
					* @param inverse ouput parameter for inverse
					* @return nothing
					* @throw RuntimeException This is an integer matrix
					*                 inverse calculation doesn't exists, 
					*                 this field, use converter class for
					*                 convert a new class.
					*/
				static bool calculateInverse(const Matrix& m,
																		 Matrix& inverse);

				/**
					* @brief   Calculate the inverse of matrix
					* @param   m constant matrix
					* @param   rank output parameter, the rank of 
					*            the input matrix
					* @param   determinant output parameter, the 
					*            determinant of the input matrix
					* @param   rest the rest matrix of the original
					*            after calculation, it is usedfull if
					*            you use a non squre matrix. 
					*            For example you can solve an equation system
					* @return nothing
					* @throw RuntimeException This is an integer matrix
					*                 inverse calculation doesn't exists, 
					*                 this field, use converter class for
					*                 convert a new class.
					* @note    if the calculation is faild, the determinant is 0
					*/
				static Matrix calculateInverse(const Matrix& m,
																			 int& rank,
																			 T& determinant,
																			 Matrix& rest);

				/**
					* @brief A form of inverse calculation
					* @details This function do an inverse calculation
					*          with gauss elimination, with pivoting, 
					*          and return the rest of the original matrix
					* @param m constant matrix
					* @param rest the rest of original matrix after the 
					*          inverse calculation
					* @return nothing
					* @throw RuntimeException This is an integer matrix
					*                 inverse calculation doesn't exists, 
					*                 this field, use converter class for
					*                 convert a new class.
					*/
				static bool calculateInverseRest(const Matrix& m,
																				 Matrix& rest);
		};

	}
}


#include "matrixcalculator_spec.hpp"

