#ifndef MATH__ALGEBRA__NUMBERCALCULATOR_QUOTIENTFIELD_H
#error Only body included
#endif

#define TEMP_DEF template<class BType,\
                          class number_traits,\
                          class Simplifier,\
                          class QNumber_traits>
#define QUO QuotientField<BType, number_traits, Simplifier>
#define NUMCALC NumberCalculator<QUO, QNumber_traits, false>

#include "russionpeasantmethod.h"

namespace MATH
{
  namespace Algebra
  {
    TEMP_DEF
    bool NUMCALC::equals(const QUO& a, const QUO& b)
    {
      return a == b;
    }

    TEMP_DEF
    QUO NUMCALC::pow(const QUO& number, const int exponent)
    {
      return exponent > 0 ?
        RussionPeasantMethod<QUO, QNumber_traits>::pow(number, exponent)
        :RussionPeasantMethod<QUO, QNumber_traits>::pow(
          QNumber_traits::addditiveUnit/number, exponent); 
    }

    TEMP_DEF
    QUO root(const QUO& number, const int exponent)
    {
      QUO ret(NumberCalculator<BType, number_traits>::root(number.getCounter(),
                                                           exponent),
              NumberCalculator<BType, number_traits>::root(number.getNominator(),
                                                           exponent));
      return ret;
    }

  }
}

#undef NUMCALC
#undef TEMP_DEF
#undef QUO

