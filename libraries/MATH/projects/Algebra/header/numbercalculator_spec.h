#ifndef __MATH__ALGEBRA__NUMBERCALCULATOR_H
#error use without number calculator header
#endif

/**
	* @file numbercalculator_spec.h
	* @brief Specialization of NumberCalculator
	*/


namespace MATH
{
	namespace Algebra
	{

		/**
			* @brief Partial template specialization for
			*        non integer types
			* @tparam T the number type
			* @tparam number_traits the number traits class
			* @see NumberCalculator<class T, class number_traits class isInteger>
			*/
		template<class T, class number_traits>
		struct NumberCalculator<T, number_traits, false>
		  :public NumberCalculator_generic<T, number_traits, false>
		{
			/**
			* @brief equals function specialization for double.
			* @details it's importent due to the inaccuration
			* @param a left operand
			* @param b right operand
			* @return there are equals
			*/
			static bool equals(const T& a, const T& b);
		};
	}
}
#include "numbercalculator_spec.hpp"

