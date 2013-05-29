#ifndef MATH__ALGEBRA__NUMBER_TRAITS_COMPLEX_H
#define MATH__ALGEBRA__NUMBER_TRAITS_COMPLEX_H

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
             class Container,
             class number_traits>
    struct Number_traits<Complex<BType,
                                Container,
                                number_traits> >
      :public Number_traits<FieldExpansion<BType,
                                           Private::ImaginalIdeal<BType,
                                                                  Container,
                                                                  number_traits>,
                                           Container,
                                           number_traits> >
    {
      typedef Complex<BType, Container, number_traits> T;

      template<class TO_TYPE>
      static TO_TYPE convert(const T& number);

      	/**
				* @brief Additive unit element
				* @note default int 0
				*/
        static const Complex<BType,
                             Container,
                             number_traits> additiveUnit;

        /**
          * @brief multiplicative unit
          * @note default int 1
          */
        static const Complex<BType,
                             Container,
                             number_traits> multiplicativeUnit;
      template<class FROM_TYPE>
      static T parse(const FROM_TYPE& number);
    };
  }
}

#include "number_traits_complex.hpp"

#endif

