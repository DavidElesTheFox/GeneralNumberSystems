#ifndef __MATH__LINEARALGEBRA_MATRIX_TRAITS_H
#define __MATH__LINEARALGEBRA_MATRIX_TRAITS_H


#include <iostream>

#include <MATH/Algebra/number_traits.h>
#include <MATH/Algebra/numbercalculator.h>

/**
	* @file matrix_traits.h
	*
	* @brief   Traits class for matrices.
	* @details This class contains the basic operations of matrices.
	* @see MATH::LinearAlgebra::Matrix_traits
	*/

namespace MATH
{
	namespace LinearAlgebra
	{
		/**
			* @brief Traits class for matrices
			* @details This class contains the basic operations of matrices,
			*          which is used in different algorithm in this namespace.
			*          if you want to use this library with a different matrix
			*          type you just specialized this class.
			*          This class use the NumberCalculator class for
			*          check equations.
			* @tparam T             the element type of Matrix
			* @tparam Matrix        the matrix type
			* @see MATH::Algebra::NumberCalculator
			*/
		template<typename T,
			       class Matrix>
		struct Matrix_traits
		{

			/**
				* @brief Create a matrix with the given parameters
				* @param rowNum the number of rows
				* @param colNum the number of columns
				*/
			static Matrix createMatrix(const int rowNum,
					                       const int colNum);

			/**
				* @brief Return an element of Matrix m
				* @param x the row id
				* @param y the column id
				* @param m the given matrix
				*/
			static T getElement(const int x,
					                const int y,
													const Matrix& m);

			/**
				* @brief Return a reference to an element of Matrix m
				* @param x the row id
				* @param y the column id
				* @param m the given matrix
				*/
			static T& getElement(const int x, 
					                 const int y,
													 Matrix& m);

			/**
				* @brief Change an element of Matrix m
				* @param x the row id
				* @param y the column id
				* @param value the new value
				* @param m the given matrix
				*/
			static void setElement(const int x,
					                   const int y, 
														 const T& value,
														 Matrix& m);

			/**
				* @brief Resize Matrix m
				* @param rowNum the number of rows
				* @param colNum the number of columns 
				* @param m the given matrix
				*/
			static void resize(const int rowNum,
					               const int colNum,
												 Matrix& m);

			/**
				* @brief Copy of matrix
				* @param m the given matrix
				* @return a new instance of m
				*/
			static Matrix copy(const Matrix& m);

			/**
				* @brief Determination of matrix parameter
				* @param m the given matrix
				* @param rowNum output parameter, number of rows
				* @param colNum output parameter, number of columns
				*/
			static void getDimension(int &rowNum,
															 int &colNum,
															 const Matrix& m);

			/**
				* @brief getter for number of rows
				* @param m the given matrix
				* @return number of rows in the given matrix
				*/
			static int getRowNum(const Matrix& m);

			/**
				* @brief getter for number of rows
				* @param m the given matrix
				* @return number of rows in the given matrix
				*/
			static int getColNum(const Matrix& m);


			/**
				* @brief equals function for matrix
				* @param a a matrix
				* @param b an other matrix
				* @return equals the two matrix
				*/
			static bool equals(const Matrix& a,
					               const Matrix& b);

			/**
				* @brief printer funciton for matrix
				* @param m the matrix
				* @param os output stream
				*/
			static void print(const Matrix& m,
					              std::ostream& os);

			/**
				* @brief read value of matrix
				* @param is imput stream
				* @param m the matrix, which is loaded from the stream
				*/
			static void read(std::istream& is,
					             Matrix& m);

			private:
			  /**
					* @brief Calculator class for the given type
					*/
			  typedef MATH::Algebra::NumberCalculator<T>
					NumCalc;
		};
	}
}

#include "matrix_traits.hpp"

#endif //__MATH__LINEARALGEBRA_MATRIX_TRAITS_H
