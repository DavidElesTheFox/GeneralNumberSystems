#ifndef MATH__LINEARALGEBRA__PNORM_H
#define MATH__LINEARALGEBRA__PNORM_H

/**
  * @file pnorm.h 
  * @brief P norm (almost norm) template implementation for vectors and matrices
	* @see PMartixNorm
	* @see PVectorNorm
	*/

#include <MATH/Algebra/number_traits.h>
#include <MATH/Algebra/numbercalculator.h>
#include "matrix_traits.h"
#include "vector_traits.h"


namespace MATH
{
	namespace LinearAlgebra
	{

		namespace Private
		{
#ifndef MATH__LINEARALGEBRA__PRIVATE__INTTOTYPE
#define MATH__LINEARALGEBRA__PRIVATE__INTTOTYPE
			template<unsigned i>
			struct IntToType
			{
				static unsigned norm;
			};
			template<unsigned i>
			unsigned IntToType<i>::norm = i;
#endif
		}

    //////////////////// Dynamic Matrix norm ////////////////////////////////

		/**
		  * @brief P norm template implementation for matrices
			* @details This class represents for example the Frobenius matrix norm P = 2 case.
			*          The general form:
			*            \f$ \|a\|_p = (\sum_{i = 1}^n\sum_{j = 1}^n |a_{i,j}|^p)^{1/p} \f$
			*          Exactly it isn't a matrix norm, and isn't a corresponding matrix 
			*          norm on the p vector norm. This is the reason why didn't part of 
			*          the MatrixCalculator class.
			* @tparam NormContainer the Norm Container class, what has a static member: p
			* @tparam T the base type of matrix elements
			* @tparam Matrix The martix representation
			* @tparam matrix_traits traits class for matrix representation
			* @tparam number_traits traits class for number type
			* @see Matrix_traits
			* @see Number_traits
			*/
		template<class NormContainer,
		         class T,
			       class Matrix,
						 class matrix_traits = Matrix_traits<T, Matrix>,
						 class number_traits = MATH::Algebra::Number_traits<T> >
		class PMatrixNormDynamic
		{
			private:
				/**
				  * @brief Calculator class for T number type
					*/
				typedef MATH::Algebra::NumberCalculator
					<T, number_traits, number_traits::isInteger> NumCalc;
			public:
				/**
				  * @brief This function calculates the p norm
					* @param m The current matrix
					* @return The p norm of the given matrix
					*/
				static double calculateNorm(const Matrix& m);
			private:

				/**
				  * @brief This is a pure static class 
					*/
				PMatrixNormDynamic() {}

				/**
				  * @brief This is a pure static class 
					*/
				PMatrixNormDynamic(const PMatrixNormDynamic&) {}

				/**
				  * @brief This is a pure static class 
					*/
				PMatrixNormDynamic* operator=(PMatrixNormDynamic&) {}
		};

    //////////////////////////// Matrix norm ////////////////////////////////

		/**
		  * @brief P norm template implementation for matrices
			* @details This class represents for example the Frobenius matrix norm P = 2 case.
			*          The general form:
			*            \f$ \|a\|_p = (\sum_{i = 1}^n\sum_{j = 1}^n |a_{i,j}|^p)^{1/p} \f$
			*          Exactly it isn't a matrix norm, and isn't a corresponding matrix 
			*          norm on the p vector norm. This is the reason why didn't part of 
			*          the MatrixCalculator class.
			* @tparam P the norm id
			* @tparam T the base type of matrix elements
			* @tparam Matrix The martix representation
			* @tparam matrix_traits traits class for matrix representation
			* @tparam number_traits traits class for number type
			* @see Matrix_traits
			* @see Number_traits
			*/
		template<unsigned P,
		         class T,
			       class Matrix,
						 class matrix_traits = Matrix_traits<T, Matrix>,
						 class number_traits = MATH::Algebra::Number_traits<T> >
		class PMatrixNorm
		  :public PMatrixNormDynamic<Private::IntToType<P>,
			                           T,
																 Matrix,
																 matrix_traits,
																 number_traits>
		{
			private:
				/**
				  * @brief Calculator class for T number type
					*/
				typedef MATH::Algebra::NumberCalculator
					<T, number_traits, number_traits::isInteger> NumCalc;
			private:

				/**
				  * @brief This is a pure static class 
					*/
				PMatrixNorm() {}

				/**
				  * @brief This is a pure static class 
					*/
				PMatrixNorm(const PMatrixNorm&) {}

				/**
				  * @brief This is a pure static class 
					*/
				PMatrixNorm* operator=(PMatrixNorm&) {}
		};

    ///////////////// Dynamic  Vector norm ///////////////////////////

		/**
		  * @brief P norm template implementation for matrices
			* @details This class represents for example the Frobenius vector norm P = 2 case.
			*          The general form:
			*            \f$ \|a\|_p = (\sum_{i = 1}^n |a_{i}|^p)^{1/p} \f$
			* @tparam NormContainer the Norm Container class, what has a static member: p
			* @tparam T the base type of vector elements
			* @tparam Vector The martix representation
			* @tparam vector_traits traits class for vector representation
			* @tparam number_traits traits class for number type
			* @see Vector_traits
			* @see Number_traits
			*/
		template<class NormContainer,
		         class T,
			       class Vector,
						 class vector_traits = Vector_traits<T, Vector>,
						 class number_traits = MATH::Algebra::Number_traits<T> >
		class PVectorNormDynamic
		{
			private:
				/**
				  * @brief Calculator class for T number type
					*/
				typedef MATH::Algebra::NumberCalculator
					<T, number_traits> NumCalc;
			public:
				/**
				  * @brief This function calculates the p norm
					* @param v The current vector
					* @return The p norm of the given vector
					*/
				static double calculateNorm(const Vector& v);
			private:

				/**
				  * @brief This is a pure static class 
					*/
				PVectorNormDynamic() {}

				/**
				  * @brief This is a pure static class 
					*/
				PVectorNormDynamic(const PVectorNormDynamic&) {}

				/**
				  * @brief This is a pure static class 
					*/
				PVectorNormDynamic* operator=(PVectorNormDynamic&) {}
		};

    ////////////////////////// Vector norm ///////////////////////////

		/**
		  * @brief P norm template implementation for matrices
			* @details This class represents for example the Frobenius vector norm P = 2 case.
			*          The general form:
			*            \f$ \|a\|_p = (\sum_{i = 1}^n |a_{i}|^p)^{1/p} \f$
			* @tparam P the norm id
			* @tparam T the base type of vector elements
			* @tparam Vector The martix representation
			* @tparam vector_traits traits class for vector representation
			* @tparam number_traits traits class for number type
			* @see Vector_traits
			* @see Number_traits
			*/
		template<unsigned P,
		         class T,
			       class Vector,
						 class vector_traits = Vector_traits<T, Vector>,
						 class number_traits = MATH::Algebra::Number_traits<T> >
		class PVectorNorm
		  :public PVectorNormDynamic<Private::IntToType<P>,
			                           T,
																 Vector,
																 vector_traits,
																 number_traits>
		{
			private:
				/**
				  * @brief Calculator class for T number type
					*/
				typedef MATH::Algebra::NumberCalculator
					<T, number_traits> NumCalc;
			private:

				/**
				  * @brief This is a pure static class 
					*/
				PVectorNorm() {}

				/**
				  * @brief This is a pure static class 
					*/
				PVectorNorm(const PVectorNorm&) {}

				/**
				  * @brief This is a pure static class 
					*/
				PVectorNorm* operator=(PVectorNorm&) {}
		};
	}
}

#include "pnorm.hpp"

#endif
