#ifndef MATH__ALGEBRA__COMPLEX_H
#define MATH__ALGEBRA__COMPLEX_H

#include "polynomial.h"
#include "fieldexpansion.h"
#include "numbercalculator.h"

namespace MATH
{
  namespace Algebra
  {
    namespace Private
    {
      /**
        * @brief Ideal for generate field with the imaginal element
        * @tparam BaseType The Base type
        * @tparam Container The used container
        * @tparam number_traits The number traits class for BaseType
        */
      template<class BaseType,
               class Container,
               class number_traits>
      struct ImaginalIdeal
      {
				private:
					/**
						* @brief Pure static class
						*/
					ImaginalIdeal()
					{}

					/**
						* @brief Pure static class
						*/
					ImaginalIdeal(const ImaginalIdeal&)
					{}

					/**
						* @brief Pure static class
						*/
					ImaginalIdeal& operator=(const ImaginalIdeal&)
					{}

				public:
					/**
						* @brief It is a necessary function, which is used by the representation.
						* @details This function determines that representation element from
						*          the given number and the Ideal generalt classification.
						*/
					static bool isCongruentElement(const BaseType&)
					{  return true;  }

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
					static void division(const BaseType& a,
															 BaseType& divisior,
															 BaseType& rem)
					{ 
						divisior = number_traits::additiveUnit;
						rem = a;
					}
          /**
            * @brief The miminal polynomial of the expansion element
            */
          static Polynomial<BaseType, Container, number_traits> poly;

          /**
            * @brief Getter function for the minimal polynomial
            * @details return null if it isn't an algebric expansion
            * @return A pointer to the minimal polynomial
            */
          static Polynomial<BaseType,
                            Container,
                            number_traits>* getMinimalPolynomial()
          {
            return &poly;
          }

					/**
						* @brief The string shape of the variable.
						*/
					static std::string strShape;
      };
			template<class BaseType,
               class Container,
							 class number_traits>
			std::string ImaginalIdeal<BaseType, Container, number_traits>::strShape = "i";

			template<class BaseType,
               class Container,
							 class number_traits>
			Polynomial<BaseType,Container,number_traits>
        ImaginalIdeal<BaseType, Container, number_traits>::poly(3,1.0,
                                                                  0.0,
                                                                  1.0);
    }

    /**
      * @brief Complex number implementation
      * @details This implementation is based on
      *          Ideal-adic representation.
      * @tparam BaseType The type which is expand with the Imaginar element
      * @tparam Container The used Container type
      * @tparam number_traits The number traits of BaseType
      */
    template<class BaseType,
             class Container = std::vector<BaseType>,
             class number_traits = Number_traits<BaseType> >
    class Complex
      :public FieldExpansion<BaseType,
                             Private::ImaginalIdeal<BaseType, Container, number_traits>,
                             Container,
                             number_traits>
    {
      public:
        Complex()
          :FieldExpansion<BaseType,
                      Private::ImaginalIdeal<BaseType, Container, number_traits>,
                      Container,
                      number_traits>()
      {      }

        /**
          * @brief constructor
          * @param re The real part of the element
          * @param im the imaginar part of the element
          */
        Complex(const BaseType& re, const BaseType& im = number_traits::additiveUnit)
          :FieldExpansion<BaseType,
                      Private::ImaginalIdeal<BaseType, Container, number_traits>,
                      Container,
                      number_traits>()
        {
          this->_coeffs[0] = re;
          this->_coeffs.push_back(im);
        }
        /**
          * @brief Copy constructor from idealadic representation
          * @param other the Other element
          */
        Complex(const IdealAdicRepresentation<BaseType,
                                              Private::ImaginalIdeal<BaseType, Container, number_traits>,
                                              Container,
                                              number_traits>& other)
          :FieldExpansion<BaseType,
                          Private::ImaginalIdeal<BaseType, Container, number_traits>,
                          Container,
                          number_traits>(other)
        {
          this->correctShape();
        }

        /**
          * @brief Assigne operator
          * @param other The other element
          * @return Reference to this
          */
        Complex& operator=(const IdealAdicRepresentation<BaseType,
                                              Private::ImaginalIdeal<BaseType, Container, number_traits>,
                                              Container,
                                              number_traits>& other)
        {
          if (this != &other)
          {
            FieldExpansion<BaseType,
                            Private::ImaginalIdeal<BaseType, Container, number_traits>,
                            Container,
                            number_traits>::operator=(other);
          }
          return *this;
        }

        /**
          * @brief Getter for the real part
          * @return The real part
          */
        BaseType getRe() const
        {
          return getCoeff(0);
        }

        /**
          * @brief Getter for the real part
          * @return reference to the real part
          */
        BaseType& getRe()
        {
          return (*this)[0];
        }

        /**
          * @brief Getter for the imaginar part
          * @return Reference to the imaginar part
          */
        BaseType& getIm()
        {
          return (*this)[1];
        }

        /**
          * @brief Getter for the imaginar part
          * @return The imaginar part
          */
        BaseType getIm() const
        {
          return getCoeff(1);
        }

        /**
          * @brief Determinates it is a real number or not
          * @return true if it is a real number
          */
        bool isReal() const
        {
          return NumberCalculator<BaseType, number_traits>::equals(
                   getIm(), number_traits::additiveUnit);
        }
      private:
         
        using FieldExpansion<BaseType,
                             Private::ImaginalIdeal<BaseType, Container, number_traits>,
                             Container,
                             number_traits>::getCoeff;

        using FieldExpansion<BaseType,
                             Private::ImaginalIdeal<BaseType, Container, number_traits>,
                             Container,
                             number_traits>::getOrder;

    };
  }
}

#include "numbercalculator_complex.h"
#include "number_traits_complex.h"
#endif

