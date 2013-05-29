#ifndef MATH__ALGEBRA__RUSSIONPEASANTMETHOD_H
#define MATH__ALGEBRA__RUSSIONPEASANTMETHOD_H

#include "number_traits.h"

namespace MATH
{
  namespace Algebra
  {
    /**
      * @brief Quick power algorithm implementation.
      * @details This algorithm based on the power shape in
      *          2-adic representation.
      * @tparam T The base type
      * @tparam number_traits Traits class for T
      */
    template<class T,
             class number_traits = Number_traits<T> >
    class RussionPeasantMethod
    {
      public:
        /**
          * @brief This function do the quick powering 
          * @param number the given number
          * @param power the given power
          * @return number^power
          */
        static T pow(const T& number, unsigned power);
    };
  }
}

#include "russionpeasantmethod.hpp"

#endif

