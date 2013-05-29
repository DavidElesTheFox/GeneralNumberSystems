#ifndef __MATH__LINEARALGEBRA__SMITHNORMALFORM_H
#define __MATH__LINEARALGEBRA__SMITHNORMALFORM_H


#include <MATH/Algebra/gcd.h>
#include <MATH/Algebra/number_traits.h>
#include <MATH/Algebra/numbercalculator.h>

#include "matrix_traits.h"
#include "abstractmatrixform.h"
#include "matrixcalculator.h"

/**
	* @file smithnormalform.h
	*
	* @brief Implementation of Smith normal form
	* @see MATH::LinearAlgebra::SmithNormalForm
	*/

namespace MATH
{

	namespace LinearAlgebra
	{
		/**
			* @brief Smith normal form implementation as templated class
			* @details This class implemented a special matrix form for 
			*          integer matrices. 
			*          A given A matrices is writen the next form: 
			*          \f[ S = U \cdot M \cdot V\f]
			*          It is a linear transformation, and \f$det(U)= \pm 1\f$
			*          and \f$det(V) = \pm 1 \f$ and S is a diagonal matrix.
			*          Further more we know that \f$ S_{i,i} | S_{j,j} \f$, 
			*          where \f$ i < j \f$.
			* @note    The algorithm use transformation matrices, and in 
			*          the beginning the S eqauls M the U and V both are
			*          the identity matrix. When the algorithm do a 
			*          multiplication from left on the S is done U too.
			*          and a same operation is done for V.
			* @param T             the element type of Matrix m
			* @param Matrix        the matrix type
			* @param traits        traits class for Matrix
			* @param number_traits traits class for T type
			* @see MATH::LinearAlgebra::Matrix_traits
			* @see MATH::Algebra::Number_traits
			* @see http://en.wikipedia.org/wiki/Smith_normal_form
			*/
		template<typename T,
			       class Matrix,
						 class traits = Matrix_traits<T, Matrix>,
						 class number_traits = MATH::Algebra::Number_traits<T> >
		class SmithNormalForm : public AbstractMatrixForm<Matrix>
		{
			public:
				/* Member types */
				/**
					* @brief computation type for transformation matrices.
					* @details the determinant of the transformation matrices is
					*          1 or -1. We can compute that the left matrix determinant
					*          will be positive or the right matrix determinant will be positive.
					*          This enum is used to this.
					*/
				enum mode_t {LEFT_POSITIVE, RIGHT_POSITIVE, UNDEF};
				/**
					* @brief enum for getters
					* @see AbstractMatrixForm::operator[]
					*/
				enum {V, S, U};
			private:
				/* Member types */
				/**
					* @brief Euclidian result type
					* @see MATH::Algebra::Gcd
					*/
				typedef typename MATH::Algebra::Gcd<T>::EuclideanResult_t 
					EuclideanRes;
				/**
					* @brief Euclidian algorithm
					* @see MATH::Algebra::Gcd
					*/
				typedef MATH::Algebra::Gcd<T> GCD;
				/**
					* @brief Matrix calculator instantasion
					*/
				typedef MatrixCalculator<T, Matrix, traits, number_traits>
					MCalculator;

				/**
					* @brief Calculator for numbers
					*/
				typedef MATH::Algebra::NumberCalculator<T, number_traits>
					NumCalc;
			protected:
				/* Members */
				/**
					* @brief the calculation mode
					* @see mode_t
					*/
				mode_t _mode;
				/**
					* @brief the transformed matrix elements will be positive
					*        or not.
					*/
				bool _positiveShape;
			public:
				/* functions */
				/**
					* @brief   default constructor
					* @details create a Smith normal form, default,
					*          it is a non positive shape matrix, 
					*          though it is a positive matrix, the U 
					*          transformation matrix will be positive
					* @param matrix The original matrix
					* @param isPositiveShape The transformed matrix will 
					*          be positive element only or not.
					* @param mode transformation matrix determinant will be positive.
					* @see mode_t
					*/
				explicit SmithNormalForm(const Matrix& matrix,
						                     const bool isPositiveShape = false,
												         const mode_t mode = UNDEF):
				  AbstractMatrixForm<Matrix>(matrix),
				  _mode(mode),
				  _positiveShape(isPositiveShape)
				{		}

				// Not needed
				//SmithNormalForm(const SmithNormalForm& other);

				/**
					* @brief standard virtual destructor
					*/
				virtual ~SmithNormalForm()
				{	}

				//Not Needed
				//SmithNormalForm& operator=(const SmithNormalForm& other);

			protected:
				/* functions */
				/**
					* @brief element calculation
					* @see AbstractMatrixForm::calculateElements
					*/
				void calculateElements();

			private:
				/* functions */
				/**
					* @breif return return matrix will be transformed
					*        a matrix columns.
					* @details If you use the return matrix as a left
					*          multiplyer you get the next transformation.
					*          If the diagonal element isn't devide the 
					*          rowId2. element then, this transformation
					*          resolve this problem with euclidian algorithm.
					* @param s the matrix where is the problem
					* @param rowId1 the position of diagonal element
					* @param rowId2 the position of other element in the same
					*               column of diagonal element
					* @return a transformation matrix
					* @see rowTransformation
					*/
				Matrix getLeftTransformationMatrix(const Matrix& s,
						                               const int rowId1,
																					 const int rowId2);

				/**
					* @breif return return matrix will be transformed
					*        a matrix rows.
					* @details If you use the return matrix as a right
					*          multiplyer you get the next transformation.
					*          If the diagonal element isn't devide the 
					*          rowId2. element then, this transformation
					*          resolve this problem with euclidian algorithm.
					* @param s the matrix where is the problem
					* @param rowId1 the position of diagonal element
					* @param rowId2 the position of other element in the same
					*               row of diagonal element
					* @return a transformation matrix
					*/
				Matrix getRightTransformationMatrix(const Matrix& s,
						                                const int rowId1,
																						const int rowId2);

				/**
					* @brief find the pivot element in the matrix, and do 
					*        the transformation.
					* @details This function find the absoulute minimum, but
					*          non zero element in the matrix, and if it
					*          exists transform it to the i. minor elemnt.
					* @param s the matrix where do the pivoting
					* @param u the left transformation matrix
					* @param v the right transformation matrix
					* @param i the actual minor element
					* @return there are exists pivot
					*/
				bool pivoting(Matrix& s,
						          Matrix& u,
											Matrix& v,
										  const int i);

				/**
					* @brief transform a row for the elimination.
					* @details this function resolve the problem, if
					*          the pivot element dosn't devide and element
					*          in the given row.
					* @param s the transformed matrix
					* @param u the left transformation matrix
					* @param i the actual minor number
					* @see getLeftTransformationMatrix
					* @return done least one transformation
					*/
				bool rowTransformation(Matrix& s,
						                   Matrix& u,
															 const int i);

				/**
					* @brief Do the elimination of the given row
					* @param s the transformed matrix
					* @param u the left transformation matrix
					* @param i the actual minor number
					*/
				inline void rowElimination(Matrix &s,
						                    Matrix& u, const int i);

				/**
					* @brief transform a column for the elimination.
					* @details this function resolve the problem, if
					*          the pivot element dosn't devide and element
					*          in the given column.
					* @param s the transformed matrix
					* @param v the right transformation matrix
					* @param i the actual minor number
					* @return done least one transformation
					* @see getRightTransformationMatrix
					*/
				bool colTransformation(Matrix& s, Matrix& v, const int i);

				/**
					* @brief Do the elimination of the given column
					* @param s the transformed matrix
					* @param v the right transformation matrix
					* @param i the actual minor number
					*/
				inline void colElimination(Matrix& s, Matrix& v, const int i);

				/**
					* @brief If used the positive shape this function
					*        do the correction of the result matrix,
					*        and handle the calculation mode.
					* @param v the right transformation matrix
					* @param s the transformed matrix
					* @param v the left transformation matrix
					* @see mode_t
					*/
				void correction(Matrix& v, Matrix& s, Matrix& u);
		};
	}
}

#include "smithnormalform.hpp"

#endif // __MATH__LINEARALGEBRA__SMITHNORMALFORM_H
