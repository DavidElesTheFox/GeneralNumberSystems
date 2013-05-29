#ifndef MATH__ALGEBRA__QUOTIENTFIELD_H
#define MATH__ALGEBRA__QUOTIENTFIELD_H

/**
  * @file quotientfield.h
  * @brief Quotient Field implementation
  */

#include <ostream>

#include "number_traits.h"
#include "numbercalculator.h"
#include "gcd.h"

namespace MATH
{
  namespace Algebra
  {

    namespace DefaultSimplifiers
    {

      /**
        * @brief Simple simplifier.
        * @details This class usefull, if we can't determine
        *          the representation element.
        */
      struct NoSimplifier
      {
        /**
          * @brief Convert the parameters to the representation element
          * @param a one of the given parameter
          * @param b another parameter
          */
        template<class BaseType>
        static void convertToRepresentation(BaseType& a,
                                            BaseType& b)
        {        }
      };

      /**
        * @brief Simplifier with GCD computation
        * @details This simplifier use the Euclidean algorithm
        */
      template<class BaseType,
               class number_traits = MATH::Algebra::Number_traits<BaseType> >
      struct GCDSimplifier
      {
        /**
          * @brief Convert the parameters to the representation element
          * @param a one of the given parameter
          * @param b another parameter
          */
        static void convertToRepresentation(BaseType& a,
                                            BaseType& b)
        {
          BaseType gcd = MATH::Algebra::Gcd<BaseType, number_traits>::GCD(a,b);
          a /= gcd;
          b /= gcd;
        }
      };
    }

#define TEMP_DEF template<class BType, class num_traits, class S>
#define QUO QuotientField<BType, num_traits, S>

    /**
      * @brief This class implements a quotien field.
      * @details An equivalent relation defines a quotient field, 
      *          and we can say that \f$a/b~c/d\f$, if \f$ad = bc\f$.
      *          This equivalent relation generates a classification.
      *          Therefore we need a base domain and with the Simplifier
      *          parameter we can define the representation element, for
      *          the simplier computation.
      * @tparam BaseType The base domain
      * @tparam Simplifier Helper class for selection of representation element.
      * @tparam number_traits Traits clas for BaseType
      * @see NoSimplifier
      * @see GCDSimplifier
      */
    template<class BaseType,
             class number_traits = Number_traits<BaseType>,
             class Simplifier = 
               DefaultSimplifiers::GCDSimplifier<BaseType, number_traits> >
    class QuotientField
    {
      protected:
        /**
          * @brief The counter
          */
        BaseType _counter;

        /**
          * @brief The nominator
          */
        BaseType _nominator;
      public:

        /**
          * @brief Copy and default constructor
          * @param a The counter part 
          * @param b The numinator part
          */
        QuotientField(const BaseType& a = number_traits::additiveUnit,
                      const BaseType& b = number_traits::multiplicativeUnit);

        /**
          * @brief Simplifier undependent copy constructor
          * @param other the other quotient field element
          * @tparam S the simplifier
          */
        template<class S>
        QuotientField(const QuotientField<BaseType, number_traits, S>& other);

        /**
          * @brief Simple destructor
          */
        virtual ~QuotientField()
        {}

        /**
          * @brief Simplifier undependent assigne operator for quotient field
          * @param other Other quotient field
          * @return A reference to this
          * @tparam S the simplifier
          */
        template<class S>
        QuotientField& operator=(const QuotientField<BaseType, number_traits, S>& other);

        /**
          * @brief getter for counter
          * @return the counter part
          */
        BaseType getCounter() const
        {
          return _counter;
        }

        /**
          * @brief Getter for nominator
          * @return The nominator part
          */
        BaseType getNominator() const
        {
          return _nominator;
        }

        /**
          * @brief additive invert operator 
          * @return a negative copy of this
          */
        QuotientField operator-() const;

        /**
          * @brief Prefix increase operator
          * @return a reference of this
          */
        QuotientField& operator++();

        /**
          * @brief Postfix increase operator
          * @return a reference of this
          */
        QuotientField operator++(int);

        /**
          * @brief Prefix decrease operator
          * @return a reference of this
          */
        QuotientField& operator--();

        /**
          * @brief Postfix decrease operator
          * @return a reference of this
          */
        QuotientField operator--(int);

        /**
          * @brief Short addition
          * @param a the operand
          * @return reference of this
          */
        QuotientField& operator+=(const QuotientField& a);

        /**
          * @brief Short decreas
          * @param a the operand
          * @return reference of this
          */
        QuotientField& operator-=(const QuotientField& a);

        /**
          * @brief Short division
          * @param a the operand
          * @return reference of this
          */
        QuotientField& operator/=(const QuotientField& a);

        /**
          * @brief Short addition
          * @param a the operand
          * @return reference of this
          */
        QuotientField& operator*=(const QuotientField& a);

        /**
          * @brief addition operator
          * @param a the left hand side operand
          * @param b the right hand side operand
          * @return a + b
          */
        TEMP_DEF
        friend QUO operator+(const QUO& a,
                             const QUO& b);

        /**
          * @brief substruction operator
          * @param a the left hand side operand
          * @param b the right hand side operand
          * @return a - b
          */
        TEMP_DEF
        friend QUO operator-(const QUO& a,
                             const QUO& b);

        /**
          * @brief multiplication operator
          * @param a the left hand side operand
          * @param b the right hand side operand
          * @return a * b
          */
        TEMP_DEF
        friend QUO operator*(const QUO& a,
                             const QUO& b);

        /**
          * @brief division operator
          * @param a the left hand side operand
          * @param b the right hand side operand
          * @return a / b
          */
        TEMP_DEF
        friend QUO operator/(const QUO& a,
                             const QUO& b);

        /**
          * @brief printer operator
          * @param os output stream
          * @param b the quotient field
          * @return the input parameter
          */
        TEMP_DEF
        friend std::ostream& operator<<(std::ostream& os,
                                        const QUO& b);

        /**
          * @brief comparesion operator
          * @param a the left hand side operand
          * @param b the right hand side operand
          * @return a == b
          */
        TEMP_DEF
        friend bool operator==(const QUO& a,
                               const QUO& b);

        /**
          * @brief comparesion operator
          * @param a the left hand side operand
          * @param b the right hand side operand
          * @return a != b
          */
        TEMP_DEF
        friend bool operator!=(const QUO& a,
                               const QUO& b);

        /**
          * @brief comparesion operator
          * @param a the left hand side operand
          * @param b the right hand side operand
          * @return a < b
          */
        TEMP_DEF
        friend bool operator<(const QUO& a,
                               const QUO& b);

        /**
          * @brief comparesion operator
          * @param a the left hand side operand
          * @param b the right hand side operand
          * @return a > b
          */
        TEMP_DEF
        friend bool operator>(const QUO& a,
                               const QUO& b);

        /**
          * @brief comparesion operator
          * @param a the left hand side operand
          * @param b the right hand side operand
          * @return a <= b
          */
        TEMP_DEF
        friend bool operator<=(const QUO& a,
                               const QUO& b);

        /**
          * @brief comparesion operator
          * @param a the left hand side operand
          * @param b the right hand side operand
          * @return a >= b
          */
        TEMP_DEF
        friend bool operator>=(const QUO& a,
                               const QUO& b);
      protected:
        
        /**
          * @brief Inline function for simplify methode
          */
        inline void simplify()
        {
          Simplifier::convertToRepresentation(_counter, _nominator);
          if (_nominator < number_traits::additiveUnit)
          {
            _nominator *= -number_traits::multiplicativeUnit;
            _counter *= -number_traits::multiplicativeUnit;
          }
        }
    };
  }
}

#undef TEMP_DEF
#undef QUO

#include "quotientfield.hpp"

#include "number_traits_quotientfield.h"
#include "numbercalculator_quotientfield.h"

#endif

