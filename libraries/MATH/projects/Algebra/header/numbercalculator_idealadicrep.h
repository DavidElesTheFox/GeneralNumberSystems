#ifndef MATH__ALGEBRA__NUMBERCALCULATOR_IDEALADICREP_H
#define MATH__ALGEBRA__NUMBERCALCULATOR_IDEALADICREP_H

#include "numbercalculator.h"

namespace MATH
{
  namespace Algebra
  {
    /**
      * @brief NumberCalculator specialization
      */
    template<class BType,
             class Expansion,
             class Container,
             class number_traits,
             class FNum_traits>
    struct NumberCalculator<IdealAdicRepresentation<BType,
                                           Expansion,
                                           Container,
                                           number_traits>,
                            FNum_traits,
                            true>
    {
      private:
        typedef IdealAdicRepresentation<BType,
                               Expansion,
                               Container,
                               number_traits> T;
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
				* @brief determind that a is devide b \f$ a\|b\f$
				* @param a the divisior
				* @param b the divided
				* @return a is divide b
				*/
			static bool isDevide(const T& a, const T& b);

			/**
				* @brief Compute integer power of an number
				* @param number the base of power
				* @param exponent the exponenet of an number
				* @return the \f$ number^exponent \f$
				*/
			static T pow(const T& number, const unsigned exponent);

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
        * @brief Absolut value function
        * @note This is the \f$\|.\|_{l_2}\f$ norm
        */
      static double abs(const T& a);

      private:
			/**
				* @brief Compute integer power of an number
				* @param number the base of power
				* @param exponent the exponenet of an number
				* @return the \f$ number^exponent \f$
				*/
			static T pow(const T& number, const int exponent)
      {}
    };

    /**
      * @brief NumberCalculator specialization
      */
    template<class BType,
             class Expansion,
             class Container,
             class number_traits,
             class FNum_traits>
    struct NumberCalculator<IdealAdicRepresentation<BType,
                                           Expansion,
                                           Container,
                                           number_traits>,
                            FNum_traits,
                            false>
      :NumberCalculator<IdealAdicRepresentation<BType,
                                           Expansion,
                                           Container,
                                           number_traits>,
                            FNum_traits,
                            true>
    {
    };
  }
}

#include "numbercalculator_idealadicrep.hpp"


#endif
