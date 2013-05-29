#ifndef MATH__ALGEBRA__PADICSHAPE_H
#define MATH__ALGEBRA__PADICSHAPE_H

#include "idealadicrepresentation.h"
#include "number_traits.h"
#include "polynomial.h"

namespace MATH
{
  namespace Algebra
  {
    namespace Private
    {
      /**
        * @brief p-adic ideal for p-adic representation
        * @tparam p the generator value
        * @tparam T the base type
        */
      template<unsigned p, class T, class number_traits>
      struct PAdicIdeal
      {
        /**
          * @brief It is a necessary function, which is used by the representation.
          * @details This function determines that representation element from
          *          the given number and the Ideal generalt classification.
          */
        static bool isCongruentElement(const T& element)
        {
          T tp = number_traits::parse(p);
          return (element - element/tp * tp) == element;
        }

        /**
          * @brief It is a necessary function, which is used by the representation.
          * @details It is same like the remainder division function 
          *          with the given ideal.
          *          \f[
          *            a = q \cdot divisior + rem
          *          \f]
          * @param a The devided number
          * @param divisior the divisior
          * @param rem the remainder
          */
        static void division(const T& a,
                             T& divisior,
                             T& rem)
        { 
          T tp = number_traits::parse(p);
          divisior = a / tp;
          rem = a - divisior * tp;
        }

        /**
          * @brief The string shape of the variable.
          */
        static std::string strShape;
      };

      template<unsigned p, class T, class number_traits>
      std::string PAdicIdeal<p, T, number_traits>::strShape = "p";
    }

    /**
      * @brief Implementation of p-adic representaion.
      * @tparam p the modulo
      * @tparam BaseType the Base type of representation
      * @tparam Container The container type
      * @tparam number_trait Traits class of BaseType
      */
    template<unsigned p,
             class BaseType,
             class Container = std::vector<BaseType>,
             class number_traits = Number_traits<BaseType> >
    class PAdicShape:
      public IdealAdicRepresentation<BaseType,
                                     Private::PAdicIdeal<p, BaseType, number_traits>,
                                     Container,
                                     number_traits>                                         
    {
      private:

				/**
				  * @brief unsigned int wrapper class for constructors
					*/
				typedef typename IdealAdicRepresentation<BaseType,
																						     Private::PAdicIdeal<p, BaseType, number_traits>,
																						     Container,
																						     number_traits>::IndexType
																									 IndexType;
      public:
        /**
          * @brief Simple copy constructor
          * @param a copied element
          */
        PAdicShape(const BaseType& a = number_traits::additiveUnit)
          : IdealAdicRepresentation<BaseType,
                                    Private::PAdicIdeal<p, BaseType, number_traits>,
                                    Container,
                                    number_traits>(a)
        {}

        /**
          * @brief Copy constructor for idealadic representation
          * @param other the other type
          */
        PAdicShape(const IdealAdicRepresentation<BaseType,
                                                 Private::PAdicIdeal<p, BaseType, number_traits>,
                                                 Container,
                                                 number_traits>& other)
          : IdealAdicRepresentation<BaseType,
                                    Private::PAdicIdeal<p, BaseType, number_traits>,
                                    Container,
                                    number_traits>(other)
      {  }

        /**
          * @brief Upload constructor
          * @param numOfCoeffs The number of coefficients
          * @param first the coeffs of the zero coeffs element
          */
        template<class T>
        PAdicShape(const IndexType numOfCoeffs, T first, ...)
        {
          va_list vlist;
          va_start(vlist, first);
          this->constructRepresentation(numOfCoeffs.value, first, vlist);
        }

        /**
          * @brief Conversion from baseType
          * @return The value in BaseType
          */
        BaseType toBaseType() const
        {
          Polynomial<BaseType, Container, number_traits> poly = *this;
          return poly(p);
        }
    };
  }
}

#include "number_traits_padicshape.h"
#include "numbercalculator_padicshape.h"


#endif

