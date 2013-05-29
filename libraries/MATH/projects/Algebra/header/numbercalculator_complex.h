#ifndef MATH__ALGEBRA__NUMBERCALCULATOR_COMPLEX_H
#define MATH__ALGEBRA__NUMBERCALCULATOR_COMPLEX_H

#include "numbercalculator.h"

namespace MATH
{
  namespace Algebra
  {
    /**
      * @brief NumberCalculator specialization
      */
    template<class BType,
             class Container,
             class number_traits,
             class FNum_traits>
    struct NumberCalculator<Complex<BType,
                                    Container,
                                    number_traits>,
                            FNum_traits,
                            true>
      :NumberCalculator<FieldExpansion<BType,
                                       Private::ImaginalIdeal<BType,Container,number_traits>,
                                       Container,
                                       number_traits>,
                        FNum_traits,
                        true>
    {
      /**
        * @brief Calculation of complex conjugate
        * @param a the number
        */
      static Complex<BType,
              Container,
              number_traits>
                calculateComplexConjugate(const Complex<BType,
                                                        Container,
                                                        number_traits>& a);
    };

    /**
      * @brief NumberCalculator specialization
      */
    template<class BType,
             class Container,
             class number_traits,
             class FNum_traits>
    struct NumberCalculator<Complex<BType,
                                    Container,
                                    number_traits>,
                            FNum_traits,
                            false>
      :NumberCalculator<FieldExpansion<BType,
                                       Private::ImaginalIdeal<BType,Container,number_traits>,
                                       Container,
                                       number_traits>,
                        FNum_traits,
                        false>
    {
      /**
        * @brief Calculation of complex conjugate
        * @param a the number
        */
      static Complex<BType,
              Container,
              number_traits>
                calculateComplexConjugate(const Complex<BType,
                                                        Container,
                                                        number_traits>& a);
    };
  }
}
#include "numbercalculator_complex.hpp"

#endif

