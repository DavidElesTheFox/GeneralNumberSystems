#ifndef MATH__ALGEBRA__NUMBER_TRAITS_COMPLEX_H
#error Included only body
#endif

namespace MATH
{
  namespace Algebra
  {
    template<class BType,
             class Container,
             class number_traits>
    template<class TO_TYPE>
    TO_TYPE
      Number_traits<Complex<BType,
                            Container,
                            number_traits> >::convert(
                                const Complex<BType, Container, number_traits>& a)
    {
      TO_TYPE ret;
      ret.getRe() = a.getRe();
      ret.getIm() = a.getIm();
      return ret;
    }

    template<class BType,
             class Container,
             class number_traits>
    template<class FROM_TYPE>
    Complex<BType, Container, number_traits>
      Number_traits<Complex<BType,
                            Container,
                            number_traits> >::parse(
                                const FROM_TYPE& a)
    {
      Complex<BType,Container, number_traits> ret;
      ret.getRe() = a.getRe();
      ret.getIm() = a.getIm();
      return ret;
    }

    template<class BType,
             class Container,
             class number_traits>
    const Complex<BType,
                  Container,
                  number_traits>
      Number_traits<Complex<BType,
                            Container,
                            number_traits> >::additiveUnit =
                                                   number_traits::additiveUnit;

    template<class BType,
             class Container,
             class number_traits>
    const Complex<BType,
                  Container,
                  number_traits>
      Number_traits<Complex<BType,
                            Container,
                            number_traits> >::multiplicativeUnit =
                                                   number_traits::multiplicativeUnit;
 
  }
}
