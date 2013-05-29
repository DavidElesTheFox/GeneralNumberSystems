#ifndef MATH__ALGEBRA__NUMBER_TRAITS_POLYNOMIAL_H
#define MATH__ALGEBRA__NUMBER_TRAITS_POLYNOMIAL_H

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
    struct Number_traits<Polynomial<BType,
                                   Container,
                                   number_traits> >
      :public Number_traits<IdealAdicRepresentation<BType,
                                                    Private::VariableIdeal<BType,
                                                                           number_traits>,
                                                    Container,
                                                    number_traits> >
    {
      	/**
				* @brief Additive unit element
				* @note default int 0
				*/
        static const Polynomial<BType,
                                Container,
                                number_traits> additiveUnit;

        /**
          * @brief multiplicative unit
          * @note default int 1
          */
        static const Polynomial<BType,
                                Container,
                                number_traits> multiplicativeUnit;
    };
  }
}
#include "number_traits_polynomial.hpp"


#endif

