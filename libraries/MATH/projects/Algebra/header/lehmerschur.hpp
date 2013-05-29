#ifndef MATH__ALGEBRA__LEHMERSCHUR_H
#error Included only body
#endif


namespace MATH
{
  namespace Algebra
  {
    template<class BaseType,
             class POLYNOMIAL,
             class polynomial_traits>
    bool LehmerSchur<BaseType, POLYNOMIAL, polynomial_traits>::doAlgorithm(const POLYNOMIAL& poly)
    {
      unsigned deg = polynomial_traits::getDegree(poly);
      POLYNOMIAL p = poly;
      while (deg > 0)
      {
        p = transform(p);
        BaseType coeff = p[0];

        if (!NumCalc::isPositive(coeff))
          return false;
        deg = polynomial_traits::getDegree(p);
      }
      return NumCalc::isPositive(p[0]);
    }

    template<class BaseType,
             class POLYNOMIAL,
             class polynomial_traits>
    POLYNOMIAL LehmerSchur<BaseType, POLYNOMIAL, polynomial_traits>::transform(const POLYNOMIAL& poly)
    {
      POLYNOMIAL ret;
      unsigned degree = polynomial_traits::getDegree(poly);
      BaseType first = NumCalc::calculateComplexConjugate(poly[0]);
      BaseType last = NumCalc::calculateComplexConjugate(poly[degree]);
      for (unsigned i = 0; i < degree; ++i)
      {
        ret[i] = first * poly[i] - last * poly[degree - i];
      }
      return ret;
    }
  }
}
