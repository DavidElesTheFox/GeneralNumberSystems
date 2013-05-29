#ifndef MATH__ALGEBRA__NUMBER_TRAITS_FIELDEXPANSION_H
#define MATH__ALGEBRA__NUMBER_TRAITS_FIELDEXPANSION_H

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
             class IdealType,
             class Container,
             class number_traits>
    class Number_traits<FieldExpansion<BaseType,
                                       IdealType,
                                       Container,
                                       number_traits> >
      :public Number_traits<IdealAdicRepresentation<BaseType,
                                                    IdealType,
                                                    Container,
                                                    number_traits> >

    {
    };
  }
}


#endif

