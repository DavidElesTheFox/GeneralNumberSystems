#ifndef __MATH__LINEAR_ALGEBRA__CONVERTER_H
#define __MATH__LINEAR_ALGEBRA__CONVERTER_H

#include "vector_traits.h"
#include "matrix_traits.h"
#include <MATH/Algebra/number_traits.h>


/**
	* @file converter.h
	* @brief contains a converter class for this packeg classes
	* @see MATH::LinearAlgebra::Converter
	*/

namespace MATH
{
	namespace LinearAlgebra
	{
		/**
			* @brief This class contains different conversion
			*        functions, for templated types (Vectors,
			*        Matrices ...)
			* @tparam FROM_TYPE the type of the original
			*                   vector elements
			* @tparam TO_TPYE the output vector's element type
			* @tparam vector_traits the traits class for vectors
			* @tparam matrix_traits the traits class for matrices
			* @tparam number_traits number traits for elements

			* @see MATH::Algebra::Number_traits
			* @see MATH::LinearAlgebra::Vector_traits
			*/
		template<class FROM_TYPE,
						 class TO_TYPE,
						 template<typename T, class V> 
							 class vector_traits = Vector_traits,
						 template<typename T, class M>
							 class matrix_traits = Matrix_traits,
						 template<typename T> 
							 class number_traits
							 = MATH::Algebra::Number_traits>
		class Converter
		{
			public:
				/**
					* @brief Convert function for template vectors
					* @tparam Vector the current vector type
					* @param vector the original vector
					* @return the converted vector
					*/
				template<template<typename T> 
									 class Vector>
				static Vector<TO_TYPE> 
				  convertVector(const Vector<FROM_TYPE>& vector);

				/**
					* @brief Convert function for template matrices
					* @tparam Matrix the matrix type
					* @param matrix the original matrix
					* @return the converted vector
					*/
				template<template<typename T>
					       class Matrix>
				static Matrix<TO_TYPE>
				  convertMatrix(const Matrix<FROM_TYPE>& matrix);


		};
	}
}

#include "converter.hpp"

#endif //__MATH__LINEAR_ALGEBRA__VECTOR_CALCULATOR_H

