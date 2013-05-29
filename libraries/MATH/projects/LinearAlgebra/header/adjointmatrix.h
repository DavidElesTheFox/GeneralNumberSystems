#ifndef __MATH__LINEARALGEBRA__ADJOINTMATRIX_H
#define __MATH__LINEARALGEBRA__ADJOINTMATRIX_H

#include "matrix_traits.h"
#include "abstractmatrixform.h"
#include "matrixcalculator.h"

/**
	* @file adjointmatrix.h
	*
	* @brief   Templated Adjoint matrix form representation
	* @details This file contains the implementation of the
	*          classical adjoint matrix.
	* @warning Not the conjugate transpose
	*          
	* @see MATH::LinearAlgebra::AdjointMatrix
	*/

namespace MATH
{
	namespace LinearAlgebra
	{
		/**
			* @brief Implementation of classical adjoint matrix with
			*        templated class.
			* @details The classical adjoint matrix isn't the conjugate transpose
			*          or Hermitian matrix.
			*          This matrices calculate by the sub matrices determinant.
			* @see http://en.wikipedia.org/wiki/Adjugate_matrix
			* @param T the element of the matrix
			* @param Matrix matrix class.
			* @param Matrix_traits<T, Matrix> At tha Adjoint Matrix calculation,
			*          we don't call the matrix functions, only the traits.
			*          If you want to use a new matrix you just do some specialization
			*          at Matrix_traits
			* @see MATH::LinearAlgebra::Matrix_traits
			*/
		template<class T,
			       class Matrix,
						 class traits = Matrix_traits<T, Matrix> >
		class AdjointMatrix : public AbstractMatrixForm<Matrix>
		{
			private:
				/**
					* @brief MatrixCalculator for the given types
					*/
				typedef MatrixCalculator<T, Matrix> MCalculator;
			public:
				/**
					* @brief enum for the getter of matrix form elements
					* @details The member of enums
					*          <ul>
					*            <li> ADJOINT 
					*          </ul>
					*/
				enum {ADJOINT};
				/**
					* @brief adjoint string for getter (safity)
					*/
				static const char* ADJOINT_STR;
			public:

				/**
					* @brief Default constructor
					* @param mtx the matrix, we create this matrices' Adjoint form
					*/
				explicit AdjointMatrix(const Matrix& mtx):
					AbstractMatrixForm<Matrix>(mtx)
				{				}

				//AdjointMatrix(const AdjointMatrix& other);

				/**
					* @brief Empty virtual destructor
					*/
				virtual ~AdjointMatrix()
				{	}

				//AdjointMatrix& operator=(const AdjointMatrix& other);


			protected:
				/**
					* @brief implementation of calculateElements.
					*        In this function we create the Adjugate Matrix
					*/
				void calculateElements();
				
		};
	}
}

#include "adjointmatrix.hpp"


#endif // __MATH__LINEARALGEBRA__ADJOINTMATRIX_H

