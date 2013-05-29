#ifndef MATH__ALGEBRA__NUMBER_TRAITS_IDEALADIC_H
#define MATH__ALGEBRA__NUMBER_TRAITS_IDEALADIC_H

#include "number_traits.h"


namespace MATH
{
  namespace Algebra
  {

    /**
      * @brief Specialization of the Number traits class for IdealAdicRepresentation
      * @see IdealAdicRepresentation
      */
    template<class BType,
             class IdealType,
             class Container,
             class number_traits>
    class Number_traits<IdealAdicRepresentation<BType,
                                                IdealType,
                                                Container,
                                                number_traits> >
      :public Number_traits_core<IdealAdicRepresentation<BType,
                                                         IdealType,
                                                         Container,
                                                         number_traits> >

    {
      public:
        /**
          * @see IdealAdicRepresentation
          */
        static const bool isInteger;

        /**
          * @see Number_traits
          */
        typedef BType BaseType;

      public:
      	/**
				* @brief Additive unit element
				* @note default int 0
				*/
        static const IdealAdicRepresentation<BType,
                                             IdealType,
                                             Container,
                                             number_traits> additiveUnit;

        /**
          * @brief multiplicative unit
          * @note default int 1
          */
        static const IdealAdicRepresentation<BType,
                                             IdealType,
                                             Container,
                                             number_traits> multiplicativeUnit;

    };
  }
}

#include "number_traits_idealadic.hpp"

#endif

