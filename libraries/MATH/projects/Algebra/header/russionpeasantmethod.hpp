#ifndef MATH__ALGEBRA__RUSSIONPEASANTMETHOD_H
#error Included only body
#endif


namespace MATH
{
  namespace Algebra
  {
    template<class T,
             class number_traits>
    T RussionPeasantMethod<T, number_traits>::pow(const T& number, unsigned power)
    {
      if (power == 0) 
        return number_traits::multiplicativeUnit; 
      if (number == number_traits::additiveUnit)
        return number; 
      if ((power % 2) == 0)
      { 
          return pow(number * number, power / 2); 
      } 
      else // if ((power % 2) == 1)
      { 
          return number * pow(number * number, power / 2); 
      } 
    }
  }
}
