#ifndef MATH__ALGEBRA__FIELDEXPANSION_H
#define MATH__ALGEBRA__FIELDEXPANSION_H

/**
  * @file fieldexpansion.h
  * @brief Field expansion implementation
  */

#include <stdarg.h>
#include <iostream>

#include "idealadicrepresentation.h"
#include "polynomial.h"
#include "number_traits.h"

#define TEMP_DEF template<class BType,\
                          class EElement,\
                          class Cont,\
                          class num_traits>
#define FIELD_EXP FieldExpansion<BType, EElement, Cont, num_traits>

namespace MATH
{
  namespace Algebra
  {

    /**
      * @brief Field expansion implementation with templates.
      * @details This class implements a field expansion logic
      *          with ideal-adic representation.
      * @tparam BaseType The field which is expanded
      * @tparam ExpansionElement The expansion element
      * @tparam Container The container type
      * @tparam number_traits Traits class for Base type
      * @see IdealAdicRepresentation
      */
    template<class BaseType,
             class ExpansionElement,
             class Container = std::vector<BaseType>,
             class number_traits = Number_traits<BaseType> >
    class FieldExpansion
      :public IdealAdicRepresentation<BaseType,
                                      ExpansionElement,
                                     Container,
                                      number_traits>
    {
      private:

        /**
          * @brief Index type for the constructor
          */
        typedef typename IdealAdicRepresentation<BaseType,
                                                 ExpansionElement,
                                                 Container,
                                                 number_traits>::IndexType
                                                   IndexType;
        /**
          * @brief Calculator class for base type
          */
        typedef NumberCalculator<BaseType,
                                 number_traits,
                                 number_traits::isInteger> NumCalc;
      public:
        /**
          * @brief Copy constructor for BaseType
          * @param b the BaseType
          */
        FieldExpansion(const BaseType& b = number_traits::additiveUnit);

        /**
          * @brief Uploader constructor
          * @param paramNum the number of parameters
          * @param first Coeffs of the zero power element
          */ 
        template<class T>
        explicit FieldExpansion(const IndexType paramNum, T first, ...);

        /**
          * @brief Copy-constructor for Base Type
          * @param other the Base type
          */
        FieldExpansion(const IdealAdicRepresentation<BaseType,
                                                     ExpansionElement,
                                                     Container,
                                                     number_traits>& other);

        /**
          * @brief Simple destructor
          */
        virtual ~FieldExpansion()
        {}

        /**
          * @brief Assign operator for Base type
          * @param other the base type
          */
        FieldExpansion& operator=(const IdealAdicRepresentation<BaseType,
                                                                ExpansionElement,
                                                                Container,
                                                                number_traits>& other);

        /**
          * @brief Free access to coeffs
          */
        using IdealAdicRepresentation<BaseType,
                                      ExpansionElement,
                                      Container,
                                      number_traits>::operator[];
        /**
          * @brief printer operator
          * @param os the output stream
          * @param field the printed field
          * @return the output stream
          */
        TEMP_DEF
        friend std::ostream& operator<<(std::ostream& os, const FIELD_EXP& field);

        /**
          * @brief logical operator implementation
          * @param a left operand
          * @param b right operand
          * @return the result of logical operator
          */
        TEMP_DEF
        friend bool operator==(const FIELD_EXP& a, const FIELD_EXP& b);

        /**
          * @brief logical operator implementation
          * @param a left operand
          * @param b right operand
          * @return the result of logical operator
          */
        TEMP_DEF
        friend bool operator!=(const FIELD_EXP& a, const FIELD_EXP& b);

        /**
          * @brief logical operator implementation
          * @param a left operand
          * @param b right operand
          * @return the result of logical operator
          */
        TEMP_DEF
        friend bool operator>=(const FIELD_EXP& a, const FIELD_EXP& b);

        /**
          * @brief logical operator implementation
          * @param a left operand
          * @param b right operand
          * @return the result of logical operator
          */
        TEMP_DEF
        friend bool operator<=(const FIELD_EXP& a, const FIELD_EXP& b);

        /**
          * @brief logical operator implementation
          * @param a left operand
          * @param b right operand
          * @return the result of logical operator
          */
        TEMP_DEF
        friend bool operator>(const FIELD_EXP& a, const FIELD_EXP& b);

        /**
          * @brief logical operator implementation
          * @param a left operand
          * @param b right operand
          * @return the result of logical operator
          */
        TEMP_DEF
        friend bool operator<(const FIELD_EXP& a, const FIELD_EXP& b);
      protected:

        /**
          * @brief Ideal for reduction.
          * @details Exactly it generates an 2 variant polynomial.
          */
        class MinimalPolynomIdeal
        {
          public:
            /**
              * @brief The equivalent Polynom type
              */
            typedef Polynomial<BaseType, Container, number_traits> Poly;

            /**
              * @brief The minimal polynomial
              */
            static Poly minimal;
            
            /**
              * @brief This function determins the divisior of a and the remainder
              * @details Here happened a Polynomial <-> FieldExpansion conversion
              *          But this is the only place, where we could do it. The
              *          reason is that we now defined the congruntial.
              * @param a The number
              * @param divisior The number wich divide a
              * @param rem the remainder
              */
            static void division(const Poly& a, 
                                 Poly& divisior,
                                 Poly& rem)
            {
              divisior = Poly::remainderDivision(a,
                                               minimal,
                                               rem);
            }

            /**
              * @brief Congruent representation element 'a'?
              * @param a the given number
              * @return true if it is a representant element from their class
              */
            static bool isCongruentElement(const FieldExpansion& a)
            {
              Poly remainder;
              Poly copy = a;
              Polynomial<BaseType,
                         Container,
                         number_traits>::remainderDivision(copy,
                                                           minimal,
                                                           remainder);
              return remainder.getDegree() == 0
                     && remainder[0] == number_traits::additiveUnit;
            } 

            /** 
              * @brief The string shape of the representation
              * @note It is "(UNDEF)", due to performance reasons
              */
            static std::string strShape;
            
        };

        /**
          * @brief Overrided methode
          */
        void correctShape();
        
        /**
          * @brief This function do the reduction of the shape
          */
        void reduction();
    };
  }
}
#undef TEMP_DEF
#undef FIELD_EXP

#include "fieldexpansion.hpp"

#include "numbercalculator_fieldexpansion.h"
#include "number_traits_fieldexpansion.h"

#endif

