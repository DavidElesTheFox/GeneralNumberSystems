#ifndef MATH__ALGEBRA__NUMBERCALCULATOR_PADICSHAPE_H
#define MATH__ALGEBRA__NUMBERCALCULATOR_PADICSHAPE_H

#include "numbercalculator.h"

namespace MATH
{
  namespace Algebra
  {
    /**
      * @brief NumberCalculator specialization
      */
    template<class BaseType,
             unsigned p,
             class Container,
             class number_traits,
             class FNum_traits>
    struct NumberCalculator<PAdicShape<p,
                                       BaseType,
                                       Container,
                                       number_traits>,
                            FNum_traits,
                            true>
      :NumberCalculator<IdealAdicRepresentation<BaseType,
                                                Private::PAdicIdeal<p,BaseType, number_traits>,
                                                Container,
                                                number_traits>,
                        FNum_traits,
                        true>
    {
      typedef PAdicShape<p,
                         BaseType,
                         Container,
                         number_traits> T;

			static bool isPositive(const T& a)
      {
        return NumberCalculator<BaseType, number_traits>::isPositive(a.lcoeff());
      }


      static T calculateComplexConjugate(const T& a)
      {
        return a;
      }
    };

    /**
      * @brief NumberCalculator specialization
      */
    template<class BaseType,
             unsigned p,
             class Container,
             class number_traits,
             class FNum_traits>
    struct NumberCalculator<PAdicShape<p,
                                       BaseType,
                                       Container,
                                       number_traits>,
                            FNum_traits,
                            false>
      :NumberCalculator<IdealAdicRepresentation<BaseType,
                                                Private::PAdicIdeal<p,BaseType, number_traits>,
                                                Container,
                                                number_traits>,
                        FNum_traits,
                        false>
    {
      typedef PAdicShape<p,
                         BaseType,
                         Container,
                         number_traits> T;

			static bool isPositive(const T& a)
      {
        return NumberCalculator<BaseType, number_traits>::isPositive(a.lcoeff());
      }

      static T calculateComplexConjugate(const T& a)
      {
        return a;
      }
    };
  }
}


#endif
