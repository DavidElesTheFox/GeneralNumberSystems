#ifndef MATH__ALGEBRA__NUMBERCALCULATOR_POLYNOMIAL_H
#define MATH__ALGEBRA__NUMBERCALCULATOR_POLYNOMIAL_H

#include "numbercalculator.h"

namespace MATH
{
  namespace Algebra
  {
    /**
      * @brief NumberCalculator specialization
      */
    template<class BaseType,
             class Container,
             class number_traits,
             class FNum_traits>
    struct NumberCalculator<Polynomial<BaseType,
                                       Container,
                                       number_traits>,
                            FNum_traits,
                            true>
      :NumberCalculator<IdealAdicRepresentation<BaseType,
                                                Private::VariableIdeal<BaseType,
                                                                       number_traits>,
                                                Container,
                                                number_traits>,
                        FNum_traits,
                        true>
    {
    };

    /**
      * @brief NumberCalculator specialization
      */
    template<class BaseType,
             class Container,
             class number_traits,
             class FNum_traits>
    struct NumberCalculator<Polynomial<BaseType,
                                       Container,
                                       number_traits>,
                            FNum_traits,
                            false>
      :NumberCalculator<IdealAdicRepresentation<BaseType,
                                                Private::VariableIdeal<BaseType,
                                                                       number_traits>,
                                                Container,
                                                number_traits>,
                        FNum_traits,
                        false>
    {
    };
  }
}


#endif

