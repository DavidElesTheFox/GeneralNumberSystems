#ifndef MATH__LINEARALGEBRA__EUCLIDEANNORM_H
#define MATH__LINEARALGEBRA__EUCLIDEANNORM_H

#include "matrix_traits.h"
#include "vector_traits.h"

#include <MATH/Algebra/number_traits.h>
/**
  * @file euclideannorm.h
	* @brief Euclidean norm template class representation for matrices, and vectors.
	* @details It contains an Euclidean Matrix and Vector norm representation.
	* @see EuclideanMatrixNorm
	* @see EuclideanVectorNorm
	*/

		/////////////////////////////// Matrix norm ////////////////////////////
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

		/////////////////////// Dynamic Matrix norm ////////////////////////////
		/**
			* @brief Euclidean norm calculator class for matrices.
			* @details Basicly it uses the MatrixCalcutlator class norm function.
			* @see MATH::LinearAlgebra::Matrix_traits
			* @tparam NormContainer It is a class, which contains the norm number as a static member: norm.
			* @tparam T the base type of matrices
			* @tparam Matrix The matrix representation
			* @tparam matrix_traits the corresponding traits class for Matrix class
			* @tparam number_traits the corresponding traits class for T
			* @tparam isInteger T is an intger type or not
			*/
		template<class NormContainer, 
			       class T,
			       class Matrix,
						 class matrix_traits = Matrix_traits<T, Matrix>,
						 class number_traits = MATH::Algebra::Number_traits<T>,
						 bool isInteger = number_traits::isInteger>
		class EuclideanMatrixNormDynamic
		{
			public:
				/**
				  * @brief Calculates the given matrix Euclidean norm
					* @param m the matrix
					* @return the NORM-th Euclidean norm of the m matrix
					*/
				static double calculateNorm(const Matrix& m);
			protected:
				/**
				  * @brief Pure static class
					*/
				EuclideanMatrixNormDynamic() {}

				/**
				  * @brief Pure static class
					*/
				EuclideanMatrixNormDynamic(const EuclideanMatrixNormDynamic&) {}

				/**
				  * @brief Pure static class
					*/
				EuclideanMatrixNormDynamic& operator= (EuclideanMatrixNormDynamic&) {}
		};

		/////////////////////////////// Matrix norm ////////////////////////////


		/**
			* @brief Euclidean norm calculator class for matrices.
			* @details Basicly it uses the MatrixCalcutlator class norm function.
			* @see MATH::LinearAlgebra::Matrix_traits
			* @tparam NORM the norm number
			* @tparam T the base type of matrices
			* @tparam Matrix The matrix representation
			* @tparam matrix_traits the corresponding traits class for Matrix class
			* @tparam number_traits the corresponding traits class for T
			* @tparam isInteger T is an intger type or not
			*/
		template<unsigned NORM, 
			       class T,
			       class Matrix,
						 class matrix_traits = Matrix_traits<T, Matrix>,
						 class number_traits = MATH::Algebra::Number_traits<T>,
						 bool isInteger = number_traits::isInteger>
		class EuclideanMatrixNorm 
		  : public EuclideanMatrixNormDynamic<Private::IntToType<NORM>,
			                                    T,
																					Matrix,
																					matrix_traits,
																					number_traits,
																					isInteger>
		{
			private:
				/**
				  * @brief Pure static class
					*/
				EuclideanMatrixNorm() {}

				/**
				  * @brief Pure static class
					*/
				EuclideanMatrixNorm(const EuclideanMatrixNorm&) {}

				/**
				  * @brief Pure static class
					*/
				EuclideanMatrixNorm& operator= (EuclideanMatrixNorm&) {}
		};


		/////////////////////// Dynamic Vector norm ////////////////////////////

		/**
			* @brief Euclidean norm calculator class for vectors
			* @details Basicly it uses the VectorCaclulator class norm function.
			* @see MATH::LinearAlgebra::Vector_traits
			* @tparam NormContainer It is a class, which contains the norm number as a static member: norm.
			* @tparam T the base type of matrices
			* @tparam Vector The matrix representation
			* @tparam vector_traits the corresponding traits class for Matrix class
			* @tparam number_traits the corresponding traits class for T
			*/
		template<class NormContainer, 
			       class T,
			       class Vector,
						 class vector_traits = Vector_traits<T, Vector>,
						 class number_traits = MATH::Algebra::Number_traits<T> >
		class EuclideanVectorNormDynamic
		{
			public:
				/**
				  * @brief Calculates the given vector Euclidean norm
					* @param v the vector
					* @return the NORM-th Euclidean norm of the v vector
					*/
				static double calculateNorm(const Vector& v);
			protected:
				/**
				  * @brief Pure static class
					*/
				EuclideanVectorNormDynamic() {}

				/**
				  * @brief Pure static class
					*/
				EuclideanVectorNormDynamic(const EuclideanVectorNormDynamic&) {}

				/**
				  * @brief Pure static class
					*/
				EuclideanVectorNormDynamic& operator= (EuclideanVectorNormDynamic&) {}
		};

		/////////////////////////////// Vector norm ////////////////////////////

		/**
			* @brief Euclidean norm calculator class for vectors
			* @details Basicly it uses the VectorCaclulator class norm function.
			* @see MATH::LinearAlgebra::Vector_traits
			* @tparam NORM the norm number
			* @tparam T the base type of matrices
			* @tparam Vector The matrix representation
			* @tparam vector_traits the corresponding traits class for Matrix class
			* @tparam number_traits the corresponding traits class for T
			*/
		template<unsigned NORM, 
			       class T,
			       class Vector,
						 class vector_traits = Vector_traits<T, Vector>,
						 class number_traits = MATH::Algebra::Number_traits<T> >
		class EuclideanVectorNorm
		  : public EuclideanVectorNormDynamic<Private::IntToType<NORM>,
			                                    T,
																					Vector,
																					vector_traits,
																					number_traits>
		{
			private:
				/**
				  * @brief Pure static class
					*/
				EuclideanVectorNorm() {}

				/**
				  * @brief Pure static class
					*/
				EuclideanVectorNorm(const EuclideanVectorNorm&) {}

				/**
				  * @brief Pure static class
					*/
				EuclideanVectorNorm& operator= (EuclideanVectorNorm&) {}
		};
	}
}

#include "euclideannorm.hpp"


#endif

