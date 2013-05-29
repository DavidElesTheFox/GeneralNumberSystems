#ifndef __MATH__LINEARALGEBRA_MATRIXCALCULATOR_H
#define __MATH__LINEARALGEBRA_MATRIXCALCULATOR_H

/**
	* @file matrixcalculator.h
	*
	* @brief   Contains the templated MatrixCalculator class, 
	*          and it's all specialization.
	* @details This file contains the implementation of the
	*          MatrixCalculator. If you want to do a specializazion,
	*          please use the matrixcalculator_spec.h file
	* @see matrixcalculator_spec.h
	*/

#include <Exceptions/parameterexception.h>
#include <MATH/Algebra/number_traits.h>
#include <MATH/Algebra/numbercalculator.h>

#include "matrix_traits.h"

namespace MATH
{
	namespace LinearAlgebra
	{	
		/**
			* @brief    This is the base class of MatrixCalculators. 	
			* @details  It contains the basic logic of functions
			* @param Matrix the used matrix class.
			* @param T element type of Matrix
			* @param traits the traits of matrix
			* @param number_traits the traits of the element type
			* @see MATH::LinearAlgebra::Matrix_traits
			* @see MATH::Algebra::Number_traits
			*/
		template <class T,
						  class Matrix,
							class traits = Matrix_traits<T, Matrix>,
							class number_traits = MATH::Algebra::Number_traits<T>,
							bool isInteger = number_traits::isInteger>
		struct MatrixCalculator_core
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
        * @brief Calculates the minimal polynomial of the given matrix 
        * @tparam POLYNOMIAL The type of the polynomial
        * @param m The given matrix
        */
      template<class POLYNOMIAL>
      static POLYNOMIAL calculateCharacteristicPolynomial(const Matrix& m);

			/**
				* @brief Calculate the transpose of matrix
				* @param m constant matrix
				* @return return the matrix transpose
				*/
			static Matrix calculateTransponate(const Matrix& m);

			/**
				* @brief Calculate the inverse of matrix
				* @param m constant matrix
				* @param inverse ouput parameter for inverse
				* @return it's successful or not
				* @note always use the most simplifyed, dou to the 
				*       specialization
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
				* @return  the inverse matrix
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
				* @return it's successful or not
				*/
			static bool calculateInverseRest(const Matrix& m,
																			 Matrix& rest);

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

			/**
				* @brief   Calculate the determinant.
				* @details If it is an integer matrix it uses
				*            the Smith Normal Form of the matrix,
				*            In other case the class is use the Gauss
				*            elimnation
				* @param m input matrix
				* @return the determinant of the input matrix
				* @see MATH::LinearAlgebra::SmithNormalForm
				*/
			static T calculateDeterminant(const Matrix& m);

			/**
				* @brief   Calculate the rank of the input matrix
				* @param   m input matrix
				* @return  the rank
				* @warning Don't exists integer case, but you
				*          can do a specialization with 
				*          Smith Normal Form
				* @see Matrix::LinearAlgebra::SmithNormalForm
				*/
			static int calculateRank(const Matrix& m);

			/**
				* @brief is a diagonal matrix
				* @param m the given matrix
				* @return true if m is a diagonal matrix
				*/
			static bool isDiagonal(const Matrix& m);

			/**
				* @brief modulo function for diagonal matrices
				* @param a a general matrix
				* @param b a diagonal matrix
				* @return a mod b.
				* @warning importent that b is a diagonal matrix
				*/
			static Matrix diagModulo(const Matrix& a,
					                     const Matrix& b);

			/**
				* @brief  Row swaps
				* @details Swap two rows of the matrix
				* @param i one of the row-id
				* @param j the other row-id
				* @param m the matrix
				* @return false if i equals j
				*/
			static bool swapRows(const int i, 
													 const int j, Matrix& m);

			/**
				* @brief  Column swaps
				* @details Swap two columns of the matrix
				* @param i one of the column-id
				* @param j the other column-id
				* @param m the matrix
				* @return false if i equals j
				*/
			static bool swapCols(const int i,
													 const int j, Matrix& m);

			/**
				* @brief Addition of two rows
				* @details This function adds one row with multiply
				*          somewhat to another row
				* @param multiplyer the multiplayer number
				* @param source     the source row-id
				* @param destination the destination row-id
				* @param m input matrix
				*/
			static void addTwoRow(const T& multiplyer,
														const int source,
														const int destination,
														Matrix& m);

			/**
				* @brief Multiplied a row
				* @param a the multiplyer
				* @param row the row-id
				* @param m the input matrix
				*/
			static void multiplyRow(const T& a,
															const int row,
															Matrix& m);

			/**
				* @brief find the absolute maximum value
				*        in the given range
				* @param startRow the first row of searching
				* @param startCol the first col of searching
				* @param borderRow the end row of searching
				* @param borderCol the end col of searching
				* @param m the input matrix
				* @note this function uses the findValueBy function
				* @return the maximum value
				* @see findValueBy
				*/
			static T getAbsMaximumValue(const int startRow,
																	const int startCol,
																	const int borderRow,
																	const int borderCol,
																	const Matrix& m);

			/**
				* @brief find the absolute maximum value
				*        in the given range
				* @param startRow the first row of searching
				* @param startCol the first col of searching
				* @param borderRow the end row of searching
				* @param borderCol the end col of searching
				* @param m the input matrix
				* @param rowId output parameter and contains
				*         the maximum row id. If it's negative
				*         there are some problem.
				* @param colId output parameter and contains
				*         the maximum col-id. If it's negative
				*         there are some problem.
				* @see findValueBy
				*/
			static T getAbsMaximumValue(const int startRow,
																	const int startCol,
																	const int borderRow,
																	const int borderCol,
																	const Matrix& m,
																	int& rowId,
																	int& colId);
			/**
				* @brief find the absolute minimum and non zero value
				*        in the given range
				* @param startRow the first row of searching
				* @param startCol the first col of searching
				* @param borderRow the end row of searching
				* @param borderCol the end col of searching
				* @param m the input matrix
				* @note this function uses the findValueBy function
				* @return the finded value
				* @see findValueBy
				*/

			static T getAbsMinNonZeroValue(const int startRow,
																		 const int startCol,
																		 const int borderRow,
																		 const int borderCol,
																		 const Matrix& m);
			/**
				* @brief find the absolute minimum non zero value
				*        in the given range
				* @param startRow the first row of searching
				* @param startCol the first col of searching
				* @param borderRow the end row of searching
				* @param borderCol the end col of searching
				* @param m the input matrix
				* @param rowId output parameter and contains
				*         the searched row id. If it's negative
				*         there are some problem.
				* @param colId output parameter and contains
				*         the searched col-id. If it's negative
				*         there are some problem.
				* @see findValueBy
				*/

			static T getAbsMinNonZeroValue(const int startRow,
																		 const int startCol,
																		 const int borderRow,
																		 const int borderCol,
																		 const Matrix& m,
																		 int& rowId,
																		 int& colId);

			/**
				* @brief Calculate matrix norm
				* @details It's only know the first and infinity norm
				* @param n the number of norm (0 = infinity)
				* @param m the input matrix
				* @return the given matrix norm
				*/
			static double norm(const int n, const Matrix& m);

			/**
				* @brief Remove a specific row and col from the
				*        given matrix
				* @param row the removed row-id
				* @param col the removed col-id
				* @param m the original matrix
				* @return a new matrix
				*/
			static Matrix removeRowAndCol(const int row,
																		const int col,
																		const Matrix& m);

			/**
				* @brief Create an identity matrix
				* @param rowNum the number of rows
				* @param colNum the number if cols
				* @return the identity matrix
				*/
			static Matrix getIdentityMatrix(const int& rowNum,
																			const int& colNum);
		 
			/**
				* @brief create a left oriented swap matrix.
				* @details the result of the multiplication with this 
				*          matrix is the original matrix, where the given
				*          row and col is swapped
				* @param rowNum the number of rows
				* @param colNum the number of cols
				* @param row the row-id
				* @param col the col-id
				* @return the multiplyer matrx
				*/
			static Matrix getSwapMatrix(const int& rowNum,
																	const int& colNum,
																	const int& row,
																	const int& col);

			/**
				* @brief create a left oriented eliminator matrix
				*        like used in Gauss Elimination
				* @param m the matrix
				* @param id the col-id
				* @return a left elemintor matrix
				* @warning This function is available in Integer case,
				*          but may have error at division, so you should
				*          care about the divisibility!
				*/
			static Matrix getLeftEliminatorMatrix(const Matrix& m,
																						const int id);

			/**
				* @brief create a right oriented eliminator matrix
				*        like used in Gauss Elimination
				* @param m the matrix
				* @param id the row-id
				* @return a right eliminator matrix
				* @warning This function is available in Integer case,
				*          but may have error at division, so you should
				*          care about the divisibility!
				*/
			static Matrix getRightEliminatorMatrix(const Matrix& m,
																						 const int id);

			/**
				* @brief template conditional fineder function.
				* @details The importent that there aren't exists
				*          extremal value, so this algorithm use
				*          permissive condition, it means the pivote
				*          compare with pivote is true!
				* @param startRow the first row of searching
				* @param startCol the first col of searching
				* @param borderRow the end row of searching
				* @param borderCol the end col of searching
				* @param m the input matrix
				* @param rowId output parameter and contains
				*         the searched row id. If it's negative
				*         there are some problem.
				* @param colId output parameter and contains
				*         the searched col-id. If it's negative
				*         there are some problem.
				* @return the fineded element
				* @see getAbsMinNonZeroValue
				* @see getAbsMaximumValue
				*/
			template<class comparer>
			static T findValueBy(const int startRow, 
													 const int startCol,
													 const int borderRow,
													 const int borderCol,
													 const Matrix& m,
													 int& rowId,
													 int& colId);

			/**
				* @brief Compare functor for findValueBy (AbsMax)
				* @see findValueBy
				*/
			struct AbsMaxComparer
			{
				/**
					* @brief the condition check
					* @details this condition must be permissive
					* @param pivot the actual pivote element
					* @param element the actual element 
					*         (it'll be the pivote if it's true)
					*/
				static bool condition(const T& pivot, const T& element)
				{
					return NumCalc::abs(pivot) <= NumCalc::abs(element);
				}

				/**
					* @brief Assume for pivot
					* @details special function for pivot element 
					* @param pivot this element will be the pivote 
					*          after this transformation
					* @return the transoformed element
					*/
				static T assume(const T& pivot)
				{
					return NumCalc::abs(pivot);
				}
			};

			/**
				* @brief Compare functor for findValueBy  
				*          (AbsMinNonZero)
				* @see findValueBy
				*/
			struct AbsMinNonZeroComparer
			{
				/**
					* @brief the condition check
					* @details this condition must be permissive
					* @param pivot the actual pivote element
					* @param element the actual element 
					*         (it'll be the pivote if it's true)
					*/

				static bool condition(const T& pivot, const T& element)
				{
          double absPivot = NumCalc::abs(pivot);
          double absElement = NumCalc::abs(element);
					return (absPivot > absElement
                  || MATH::Algebra::NumberCalculator<double>::equals(absPivot,
                                                                     absElement))
								 && !NumCalc::equals(element, number_traits::additiveUnit);
				}
				/**
					* @brief Assume for pivote
					* @details special function for pivot element 
					* @param pivot this element will be the pivote 
					*          after this transformation
					* @return the transoformed element
					*/

				static T assume(const T& pivot)
				{
					return pivot;
				}
			};
			protected:
				/**
					* @brief Number calculator class for T
					*/
				typedef MATH::Algebra::NumberCalculator<T, number_traits, isInteger>
					NumCalc;

		};

		/**
			* @brief The default non specialized Matrix calculator class
			* @see MATH::LinearAlgebra::MatrixCalculator_core 
			* @param Matrix the used matrix class.
			* @param T element type of Matrix
			* @param traits the traits of matrix
			* @param number_traits the traits of the element type
			* @see MATH::LinearAlgebra::Matrix_traits
			* @see MATH::Algebra::Number_traits

			*/
		template <class T,
						  class Matrix,
							class traits = Matrix_traits<T, Matrix>,
							class number_traits = MATH::Algebra::Number_traits<T>,
							bool isInteger = number_traits::isInteger>
		struct MatrixCalculator:
			public MatrixCalculator_core<T, Matrix, traits, number_traits, isInteger>
		{
		};
	}
}

#include "matrixcalculator.hpp"

#include "matrixcalculator_spec.h"

#endif // __MATH__LINEARALGEBRA_MATRIXCALCULATOR_H
