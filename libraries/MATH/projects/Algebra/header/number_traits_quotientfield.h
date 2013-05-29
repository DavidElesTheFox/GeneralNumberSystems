#ifndef MATH__ALGEBRA__NUMBER_TRAITS_QUOTIENTFIELD_H
#define MATH__ALGEBRA__NUMBER_TRAITS_QUOTIENTFIELD_H

#include "number_traits.h"


namespace MATH
{
  namespace Algebra
  {

    /**
      * @brief Specialization of the Number traits class for QuotientFields
      * @see QuotientFields
      */
    template<class BType,
             class number_traits,
             class Simplifier>
    class Number_traits<QuotientField<BType,
                                      number_traits,
                                      Simplifier> >
                         
      :public Number_traits_core<QuotientField<BType,
                                               number_traits,
                                               Simplifier> >

    {
      private:
        typedef QuotientField<BType,
                              number_traits,
                              Simplifier> T;

      public:
        /**
          * @see QuotientField
          */
        static const bool isInteger;

        /**
          * @see Number_traits
          */
        typedef BType BaseType;

        /**
          * @brief Safty conversion to other types
          * @tparam TO_TYPE the output type
          * @param number the number which will be converted
          * @return the converted number
          */
        template<class TO_TYPE>
        static TO_TYPE convert(const T& number);
    };
  }
}

#include "number_traits_quotientfield.hpp"

#endif

