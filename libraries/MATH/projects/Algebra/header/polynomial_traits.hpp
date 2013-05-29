#ifndef MATH__ALGEBRA__POLYNOMIAL_TRAITS_H
#error Included only body
#endif

namespace MATH
{
  namespace Algebra
  {
    template<class T,
             class Poly>
    unsigned Polynomial_traits<T, Poly>::getDegree(const Poly& a)
    {
      return a.getDegree();
    }
  }
}

