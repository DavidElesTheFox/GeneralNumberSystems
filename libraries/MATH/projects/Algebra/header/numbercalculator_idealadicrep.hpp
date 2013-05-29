#ifndef MATH__ALGEBRA__NUMBERCALCULATOR_IDEALADICREP_H
#error Included only body
#endif

#define TEMP_DEF template<class BType,\
                          class Expansion,\
                          class Container,\
                          class number_traits,\
                          class FNum_traits>

#define IDEAL_ADIC IdealAdicRepresentation<BType,Expansion,Container,number_traits>

#define NUMCALC NumberCalculator<IDEAL_ADIC, FNum_traits, true>

#include "russionpeasantmethod.h"

namespace MATH
{
  namespace Algebra
  {
    TEMP_DEF
    bool NUMCALC::equals(const IDEAL_ADIC& a, const IDEAL_ADIC& b)
    {
      unsigned max = a.getOrder() > b.getOrder()? a.getOrder() + 1 : b.getOrder() + 1; 
      bool eq = true;
      for (unsigned i = 0; i < max && eq; ++i)
      {
        eq = eq && NumberCalculator<BType, number_traits, number_traits::isInteger>::
               equals(a.getCoeff(i), b.getCoeff(i));
      }
      return eq;
    }

    TEMP_DEF
    bool NUMCALC::isDevide(const IDEAL_ADIC& a, const IDEAL_ADIC&b)
    {
      return equals(b % a, FNum_traits::additiveUnit);
    }

    TEMP_DEF
    IDEAL_ADIC NUMCALC::pow(const IDEAL_ADIC& number, const unsigned exponent)
    {
      return RussionPeasantMethod<IDEAL_ADIC, FNum_traits>::pow(number, exponent);
    }

    TEMP_DEF
    IDEAL_ADIC NUMCALC::rem(const IDEAL_ADIC& number, const IDEAL_ADIC& devisior)
    {
      IDEAL_ADIC rem;
      IDEAL_ADIC::remainderDivision(number, devisior, rem);
      return rem;
    }

    TEMP_DEF
    double NUMCALC::abs(const IDEAL_ADIC& a)
    {
      double ret = 0.0;
      for (unsigned i = 0; i <= a.getOrder(); ++i)
      {
        double tmp = NumberCalculator<BType, number_traits, number_traits::isInteger>
          ::abs(a.getCoeff(i));
        ret += tmp*tmp;
      }
      return ::sqrt(ret);

    }

  }
}

#undef TEMP_DEF
#undef NUMCALC
