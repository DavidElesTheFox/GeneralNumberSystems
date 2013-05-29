#ifndef MATH__ALGEBRA__NUMBERCALCULATOR_QUOTIENTFIELD_H
#define MATH__ALGEBRA__NUMBERCALCULATOR_QUOTIENTFIELD_H

/**
	* @file numbercalculator_quotientfield.h
	* @brief this file contains the numbercalculator specialization class.
	*/


#include "number_traits.h"

namespace MATH
{
	namespace Algebra
	{
		/**
			* @brief   Calculator specialization
			* @details This file contains the basic number operations
			*          on numbers.
			* @note    You can specialized it in numbercalculator_spec.h
			* @see     numbercalculator_spec.h
			* @tparam T The type of number
			* @tparam number_traits the number traits class
			* @tparam isInteger is an integer type or not.
			*/
		template<class BaseType,
             class number_traits,
             class Simplifier,
             class QNumber_traits>
		struct NumberCalculator<QuotientField<BaseType,
                                          number_traits,
                                          Simplifier>,
                            QNumber_traits, 
                            false>
       : NumberCalculator_generic<QuotientField<BaseType,
                                                number_traits,
                                                Simplifier>,
                                  QNumber_traits,
                                  false>
		{
      private:
        typedef QuotientField<BaseType, number_traits, Simplifier> T;

      public:
        /**
          * @brief deteremind two numbers is equals
          * @note it's importent see doubles
          * @param a left operand
          * @param b right operand
          * @return they are equals
          */
        static bool equals(const T& a, const T& b);

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

      private:

        /**
          * @brief Remainder calculation
          * @details If the type isnt an UCD, than this
          *          function could be overloaded with 
          *          the speudo remainder function
          * @param number the number
          * @param devisior the devisior
          * @return the number (mod devisior)
          */
        static T rem(const T& number, const T& devisior)
        {
        }
		};

		/**
			* @brief   Calculator specialization
			* @details This file contains the basic number operations
			*          on numbers.
			* @note    You can specialized it in numbercalculator_spec.h
			* @see     numbercalculator_spec.h
			* @tparam T The type of number
			* @tparam number_traits the number traits class
			* @tparam isInteger is an integer type or not.
			*/
		template<class BaseType,
             class number_traits,
             class Simplifier,
             class QNumber_traits>
		struct NumberCalculator<QuotientField<BaseType,
                                          number_traits,
                                          Simplifier>,
                            QNumber_traits, 
                            true>
    {};

	}
}

#include "numbercalculator_quotientfield.hpp"

#endif //__MATH__ALGEBRA__NUMBERCALCULATOR_H

