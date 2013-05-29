#ifndef MATH__ALGEBRA__NUMBER_TRAITS_POLYNOMIAL_H
#error Included only body
#endif

namespace MATH
{
  namespace Algebra
  {

    template<class BType,
             class Container,
             class number_traits>
    const Polynomial<BType,
                     Container,
                     number_traits>
      Number_traits<Polynomial<BType,
                               Container,
                               number_traits> >::additiveUnit =
                                                   number_traits::additiveUnit;

    template<class BType,
             class Container,
             class number_traits>
    const Polynomial<BType,
                     Container,
                     number_traits>
      Number_traits<Polynomial<BType,
                               Container,
                               number_traits> >::multiplicativeUnit =
                                                   number_traits::multiplicativeUnit;
  }
}
