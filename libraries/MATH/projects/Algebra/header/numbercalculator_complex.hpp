#ifndef MATH__ALGEBRA__NUMBERCALCULATOR_COMPLEX_H
#error Included only body
#endif

#define COMPLEX Complex<BType,\
            Container,\
            number_traits>

namespace MATH
{
  namespace Algebra
  {

    template<class BType,
             class Container,
             class number_traits,
             class FNum_traits>
     COMPLEX NumberCalculator<COMPLEX,
                              FNum_traits,
                              true>::calculateComplexConjugate(const COMPLEX& a)
    {
      COMPLEX copy = a;
      copy.getIm() *= -number_traits::multiplicativeUnit;
      return copy;
    }


    template<class BType,
             class Container,
             class number_traits,
             class FNum_traits>
    COMPLEX NumberCalculator<COMPLEX,
                             FNum_traits,
                             false>::calculateComplexConjugate(const COMPLEX& a)
    {
      COMPLEX copy = a;
      copy.getIm() *= -number_traits::multiplicativeUnit;
      return copy;
    }
  }
}
#undef COMPLEX
