#ifndef MATH__ALGEBRA__NUMBER_TRAITS_PADICSHAPE_H
#define MATH__ALGEBRA__NUMBER_TRAITS_PADICSHAPE_H

#include "number_traits.h"


namespace MATH
{
  namespace Algebra
  {

    /**
      * @brief Specialization of the Number traits class for IdealAdicRepresentation
      * @see IdealAdicRepresentation
      */
    template<class BaseType,
             unsigned p,
             class Container,
             class number_traits>
    class Number_traits<PAdicShape<p,
                                   BaseType,
                                   Container,
                                   number_traits> >
      :public Number_traits<IdealAdicRepresentation<BaseType,
                                                    Private::PAdicIdeal<p,BaseType, number_traits>,
                                                    Container,
                                                    number_traits> >

    {
    };
  }
}


#endif
