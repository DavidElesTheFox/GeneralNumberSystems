#ifndef MATH__ALGEBRA__LEHMERSCHUR_H
#define MATH__ALGEBRA__LEHMERSCHUR_H

#include "polynomial_traits.h"
#include "numbercalculator.h"

namespace MATH
{
  namespace Algebra
  {
    /**
      * @brief A Lehmer Schur algorithm implementation
      * @tparam COMPLEX The complex type
      * @tparam POLYNOMIAL The polynomial representation over COMPLEX
      */
    template<class BaseType,
             class POLYNOMIAL,
             class polynomial_traits = Polynomial_traits<BaseType, 
                                                         POLYNOMIAL>  >
    struct LehmerSchur
    {
      private:
        typedef NumberCalculator<BaseType> NumCalc;
      public:
        /**
          * @brief algorithm runner function
          * @param poly The polynomial
          * @return true If the poly has root in unit curcle, otherwise false.
          */
        static bool doAlgorithm(const POLYNOMIAL& poly);

      private:
        /**
          * @brief Schur transformation
          * @details Let \f$p\f$ a polynomial.
          *          \f[
          *            p(x) = a_0 + a_1x + a_2x + \dots + a_nx^n
          *          \f]
          *          Then 
          *          \f[
          *            p*(x) = \bar{a_n} + \bar{a_{n-1}}x + \dots \bar{a_0}x^n
          *          \f]
          *          Then the transform is 
          *          \f[
          *            \bar{a_0}p(x) - a_np*(x)
          *          \f]
          * @param poly the transformed polynomial
          */
        static POLYNOMIAL transform(const POLYNOMIAL& poly);
    };
  }
}

#include "lehmerschur.hpp"
#endif

