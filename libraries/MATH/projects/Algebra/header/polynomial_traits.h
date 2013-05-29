#ifndef MATH__ALGEBRA__POLYNOMIAL_TRAITS_H
#define MATH__ALGEBRA__POLYNOMIAL_TRAITS_H

namespace MATH
{
  namespace Algebra
  {
    /**
      * @brief Accessor class for polynomials
      * @tparam The type of coefficients
      * @tparam Poly the polynomial representation
      */
    template<class T,
             class Poly>
    struct Polynomial_traits
    {
      /**
        * @brief get the degree of the polynomial
        * @param a the given polynomial
        * @return the degree of a
        */
      static unsigned getDegree(const Poly& a);
    };
  }
}

#include "polynomial_traits.hpp"

#endif
