#ifndef MATH__ALGEBRA__NUMBER_TRAITS_IDEALADIC_H
#error Included only header
#endif


namespace MATH
{
  namespace Algebra
  {
    template<class BaseType,
             class IdealType,
             class Container,
             class number_traits>
    const bool Number_traits<IdealAdicRepresentation<BaseType,
                                                     IdealType,
                                                     Container,
                                                     number_traits> >::isInteger = 
                                                   Number_traits<BaseType>::isInteger;

    template<class BaseType,
             class IdealType,
             class Container,
             class number_traits>
    const IdealAdicRepresentation<BaseType,
                                  IdealType,
                                  Container,
                                  number_traits>
      Number_traits<IdealAdicRepresentation<BaseType,
                                            IdealType,
                                            Container,
                                            number_traits> >::additiveUnit = number_traits::additiveUnit;

    template<class BaseType,
             class IdealType,
             class Container,
             class number_traits>
    const IdealAdicRepresentation<BaseType,
                                  IdealType,
                                  Container,
                                  number_traits>
      Number_traits<IdealAdicRepresentation<BaseType,
                                            IdealType,
                                            Container,
                                            number_traits> >::multiplicativeUnit = number_traits::multiplicativeUnit;
  }
}
