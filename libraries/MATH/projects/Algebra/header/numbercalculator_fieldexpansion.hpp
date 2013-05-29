#ifndef MATH__ALGEBRA__NUMBERCALCULATOR_FIELDEXPANSION_H
#error Included only body
#endif

#define FIELDEXP FieldExpansion<BType,\
                                Expansion,\
                                Container,\
                                number_traits>

#define NUMCALC_TRUE NumberCalculator<FIELDEXP,\
                                 FNum_traits,\
                                 true>

#define NUMCALC_FALSE NumberCalculator<FIELDEXP,\
                                 FNum_traits,\
                                 false>

namespace MATH
{
  namespace Algebra
  {
    template<class BType,
             class Expansion,
             class Container,
             class number_traits,
             class FNum_traits>
    bool NUMCALC_TRUE::isPositive(const FIELDEXP& num)
    {
      return NumberCalculator<BType,
                              number_traits,
                              number_traits::isInteger>::isPositive(num.getCoeff(0));
    }

    template<class BType,
             class Expansion,
             class Container,
             class number_traits,
             class FNum_traits>
    bool NUMCALC_FALSE::isPositive(const FIELDEXP& num)
    {
      return NumberCalculator<BType,
                              number_traits,
                              number_traits::isInteger>::isPositive(num.getCoeff(0));
    }

    template<class BType,
             class Expansion,
             class Container,
             class number_traits,
             class FNum_traits>
    bool NUMCALC_TRUE::isNonNegative(const FIELDEXP& num)
    {
      return NumberCalculator<BType,
                              number_traits,
                              number_traits::isInteger>::isNonNegative(num.getCoeff(0));
    }

    template<class BType,
             class Expansion,
             class Container,
             class number_traits,
             class FNum_traits>
    bool NUMCALC_FALSE::isNonNegative(const FIELDEXP& num)
    {
      return NumberCalculator<BType,
                              number_traits,
                              number_traits::isInteger>::isNonNegative(num.getCoeff(0));
    }

    template<class BType,
             class Expansion,
             class Container,
             class number_traits,
             class FNum_traits>
    FIELDEXP NUMCALC_FALSE::floor(const FIELDEXP& num)
    {
      FIELDEXP ret;
      for (unsigned i = 0; i <= num.getOrder(); ++i)
      {
        ret[i] = NumberCalculator<BType, number_traits>::floor(num[i]);
      }
      return ret;
    }

    template<class BType,
             class Expansion,
             class Container,
             class number_traits,
             class FNum_traits>
    FIELDEXP NUMCALC_FALSE::ceil(const FIELDEXP& num)
    {
      FIELDEXP ret;
      for (unsigned i = 0; i <= num.getOrder(); ++i)
      {
        ret[i] = NumberCalculator<BType, number_traits>::ceil(num[i]);
      }
      return ret;
    }
  }
}

#undef FIELDEXP
#undef NUMCALC_TRUE
#undef NUMCALC_FALSE

