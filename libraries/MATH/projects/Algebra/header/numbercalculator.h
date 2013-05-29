#ifndef __MATH__ALGEBRA__NUMBERCALCULATOR_H
#define __MATH__ALGEBRA__NUMBERCALCULATOR_H

/**
	* @file numbercalculator.h
	* @brief this file contains the numbercalculator class.
	*/

#include <cmath>

#include "number_traits.h"

namespace MATH
{
	namespace Algebra
	{
		/**
			* @brief   Base calculation class for different number types.
			* @details This file contains the basic number operations
			*          on numbers.
			* @note    You can specialized it in numbercalculator_spec.h
			* @see     numbercalculator_spec.h
			* @tparam T The type of number
			* @tparam number_traits the number traits class
			* @tparam isInteger is an integer type or not.
			*/
		template<class T, 
			       class number_traits,
						 bool isInteger>
		struct NumberCalculator_generic
		{

			/**
				* @brief Absolute value function
				* @param number the number
				* @return the number's absolute value
				*/
			static double abs(const T& number);

			/**
				* @brief deteremind two numbers is equals
				* @note it's importent see doubles
				* @param a left operand
				* @param b right operand
				* @return they are equals
				*/
			static bool equals(const T& a, const T& b);

			/**
				* @brief determind that a is devide b \f$ a\|b\f$
				* @param a the divisior
				* @param b the divided
				* @return a is divide b
				*/
			static bool isDevide(const T& a, const T& b);

			/**
				* @brief getter for the additive unit in T type
				* @return the additive unit element (null element)
				* @deprecated Use number_traits addditiveUnit variable
				* @see Number_traits
				*/
			static T getAdditiveUnit() __attribute__ ((deprecated));
			
			/**
				* @brief getter for the multiplicative unit element in T
				* @return the multiplicative unit element in T (1)
				* @deprecated Use number_traits multiplicativUnit
				* @see Number_traits
				*/
			static T getMultiplicativeUnit() __attribute__ ((deprecated));

			/**
				* @brief determines that the given number is non negative (>=0)
				* @return the given number is non negative (>=0)
				* @param a the given number
				*/
			static bool isNonNegative(const T& a);

			/**
				* @brief determines that the given number is positive (>0)
				* @return the given number is psoitive (>0)
				* @param a the given number
				*/
			static bool isPositive(const T& a);

			/**
				* @brief Compute the floor of the given number
				* @param number the given number
				* @return the floor of the number
				*/
			static T floor(const T& number);

			/**
				* @brief Compute the ceil of the given number
				* @param number the given number
				* @return the ceil of the number
				*/
			static T ceil(const T& number);

			/**
				* @brief Compute integer power of an number
				* @param number the base of power
				* @param exponent the exponenet of an number
				* @return the \f$ number^exponent \f$
				*/
			static T pow(const T& number, const int exponent);

			/**
				* @brief Compute the root of an number
				* @param number the base of rooting
				* @param exponent the exponent of rooting
				* @return exponent-th root of number
				*/
			static T root(const T& number, const int exponent);

			/**
				* @brief Remainder calculation
				* @details If the type isnt an UCD, than this
				*          function could be overloaded with 
				*          the speudo remainder function
				* @param number the number
				* @param devisior the devisior
				* @return the number (mod devisior)
				*/
			static T rem(const T& number, const T& devisior);


      /**
        * @brief Complex conjugate calculator function.
        * @details This function calculates the complex
        *          conjugate.
        */
      static T calculateComplexConjugate(const T& a);

			private:
			  /**
					* @brief typedef for the basetype of the T
					*/
			  typedef typename number_traits::BaseType BaseType;
		};

		/**
			* @brief Default instantation of number traits class
			* @see NumberCalculator_generic
			* @tparam T the number type
			* @tparam number_traits the number traits class
			* @tparam isInteger is an integer type
			* @see    Number_traits
			*/
		template<class T,
			       class number_traits = Number_traits<T>,
			       bool isInteger = number_traits::isInteger>
		struct NumberCalculator:
			NumberCalculator_generic<T, number_traits, isInteger>
		{
		};
	}
}



#include "numbercalculator.hpp"

#include "numbercalculator_spec.h"

#endif //__MATH__ALGEBRA__NUMBERCALCULATOR_H

