#ifndef MATH__ALGEBRA__NUMBER_TRAITS_QUOTIENTFIELD_H
#error Included only header
#endif


namespace MATH
{
  namespace Algebra
  {
    template<class BType,
             class number_traits,
             class Simplifier>
    const bool Number_traits<QuotientField<BType,
                                           number_traits,
                                           Simplifier> >::isInteger = false;

    
    template<class BType,
             class number_traits,
             class Simplifier>
    template<class TO_TYPE>
    TO_TYPE Number_traits<QuotientField<BType,
                                        number_traits,
                                        Simplifier> >::
      convert(const QuotientField<BType,
                                  number_traits,
                                  Simplifier>& number)
    {
      return number.getCounter()/number.getNominator();
    }

  }
}
