#ifndef MATH__ALGEBRA__NUMBERCALCULATOR_FIELDEXPANSION_H
#define MATH__ALGEBRA__NUMBERCALCULATOR_FIELDEXPANSION_H

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
    struct NumberCalculator<FieldExpansion<BType,
                                           Expansion,
                                           Container,
                                           number_traits>,
                            FNum_traits,
                            true>
      :NumberCalculator<IdealAdicRepresentation<BType,
                                                Expansion,
                                                Container,
                                                number_traits>,
                        FNum_traits,
                        true>
    {
      /**
        * @brief Return true if the zero coefficient is positive
        * @param num the given number
        */
      static bool isPositive(const FieldExpansion<BType,
                                           Expansion,
                                           Container,
                                           number_traits>& num);

      /**
        * @brief Return true if the zero coefficient is positive
        * @param num the given number
        */
      static bool isNonNegative(const FieldExpansion<BType,
                                                     Expansion,
                                                     Container,
                                                     number_traits>& num);
    };

    /**
      * @brief NumberCalculator specialization
      */
    template<class BType,
             class Expansion,
             class Container,
             class number_traits,
             class FNum_traits>
    struct NumberCalculator<FieldExpansion<BType,
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
                        false>
    {
      /**
        * @brief Return true if the zero coefficient is positive
        * @param num the given number
        */
      static bool isPositive(const FieldExpansion<BType,
                                           Expansion,
                                           Container,
                                           number_traits>& num);

      /**
        * @brief Return true if the zero coefficient is positive
        * @param num the given number
        */
      static bool isNonNegative(const FieldExpansion<BType,
                                                     Expansion,
                                                     Container,
                                                     number_traits>& num);
			/**
				* @brief Compute the floor of the given number
				* @param number the given number
				* @return the floor of the number
				*/
			static FieldExpansion<BType,
                            Expansion,
                            Container,
                            number_traits>
        floor(const FieldExpansion<BType,
                                   Expansion,
                                   Container,
                                   number_traits>& number);

			/**
				* @brief Compute the ceil of the given number
				* @param number the given number
				* @return the ceil of the number
				*/
      static FieldExpansion<BType,
                            Expansion,
                            Container,
                            number_traits>
        ceil(const FieldExpansion<BType,
                                  Expansion,
                                  Container,
                                  number_traits>& number);


    };
  }
}

#include "numbercalculator_fieldexpansion.hpp"


#endif
