#ifndef __MATH__LINEARALGEBRA_VECTOR_TRAITS_H
#define __MATH__LINEARALGEBRA_VECTOR_TRAITS_H


#include <iostream>

#include <MATH/Algebra/number_traits.h>

/**
	* @file vector_traits.h
	*
	* @brief   Traits class for vectors.
	* @details This class contains the basic operations of vectors.
	* @see MATH::LinearAlgebra::Vector_traits
	*/

namespace MATH
{
	namespace LinearAlgebra
	{
		/**
			* @brief Traits class for vectors
			* @details This class contains the basic operations of vectors,
			*          which is used in different algorithm in this namespace.
			*          if you want to use this library with a different vector
			*          type you just specialized this class.
			* @tparam T             the element type of Vector
			* @tparam Vector        the vector type
			*/
		template<typename T,
			       class Vector>
		struct Vector_traits
		{

			/**
				* @brief Create a Vector with the given parameters
				* @param rowNum the number of rows
				*/
			static Vector create(const int rowNum);

			/**
				* @brief Return an element of vector v
				* @param x the row id
				* @param v the given vector
				*/
			static T getElement(const int x,
													const Vector& v);

			/**
				* @brief Return a reference to an element in the given vector
				* @param x the row id
				* @param v the given vector
				*/
			static T& getElement(const int x, 
													 Vector& v);

			/**
				* @brief Change an element in Vector v
				* @param x the row id
				* @param value the new value
				* @param v the given vector
				*/
			static void setElement(const int x,
														 const T& value,
														 Vector& v);


			/**
				* @brief Copy of vector
				* @param v the given vector
				* @return a new instance of v
				*/
			static Vector copy(const Vector& v);

			/**
				* @brief Determination of vector
				* @param v the given vector
				* @return the dimension
				*/
			static int getDimension(const Vector& v);

			/**
				* @brief equals function for vector
				* @param a a vector
				* @param b an other vector
				* @return equals the two vector
				*/
			static bool equals(const Vector& a,
					               const Vector& b);

			/**
				* @brief printer funciton for vectors
				* @param v the vector
				* @param os output stream
				*/
			static void print(const Vector& v,
					              std::ostream& os);

			/**
				* @brief read value of vector
				* @param is imput stream
				* @param v the vector, which is loaded from the stream
				*/
			static void read(std::istream& is,
					             Vector& v);

		};
	}
}

#include "vector_traits.hpp"

#endif //__MATH__LINEARALGEBRA_VECTOR_TRAITS_H
