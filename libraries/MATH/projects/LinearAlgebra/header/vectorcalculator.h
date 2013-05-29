#ifndef __MATH__LINEARALGEBRA__VECTORCALCULATOR_H
#define __MATH__LINEARALGEBRA__VECTORCALCULATOR_H

/**
	* @file vectorcalculator.h
	* @brief Contains class for vector calculation
	* @see MATH::LinearAlgebra::VectorCalculator
	*/

#include <MATH/Algebra/number_traits.h>
#include <MATH/Algebra/numbercalculator.h>

#include "vector_traits.h"

namespace MATH
{
	namespace LinearAlgebra
	{
		/**
			* @brief This class contains specific vector
			*        calculation functions
			* @tparam T the type of vector elements
			* @tparam Vector the vector type
			* @tparam number_traits the number_traits for 
			*         T type
			* @tparam vector_traits traits for vectors
			* @todo test
			*/
		template<typename T,
			       class Vector,
						 class number_traits = 
							 MATH::Algebra::Number_traits<T>,
						 class vector_traits=
							 Vector_traits<T, Vector> >
		struct VectorCalculator
		{

			/**
				* @brief Norm calculation function
				* @details First norm : \f[ \sum_{i = 1}^nv_i \f]
				*          Second norm : 
			  *            \f[
				               (\sum_{i = 1}^nv_i^2)^{\frac{1}{2}}
										 \f]
				*          Infinity norm: 
				             \f[ 
										   \max_{i = 1}^nv_i 
										 \f]
				*          m-th norm: 
				             \f[ 
										   (\sum_{i = 1}^nv_i^m)^{\frac{1}{m}}
										 \f]
				* @param norm the norm number
				* @param v the given vector
				* @return the norm-th norm of the vector
				*/
			static double norm(const unsigned norm, 
			                   const Vector& v);
			private:
			  /**
					* @brief calculator for numbers
					*/
			  typedef MATH::Algebra::NumberCalculator<T, number_traits>
					NumCalc;
		};
	}
}

#include "vectorcalculator.hpp"
#endif //__MATH__LINEARALGEBRA__VECTORCALCULATOR_H
