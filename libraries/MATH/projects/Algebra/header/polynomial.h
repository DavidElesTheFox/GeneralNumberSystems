#ifndef MATH__ALGEBRA__POLYNOMIAL_H
#define MATH__ALGEBRA__POLYNOMIAL_H

/**
  * @file polynomial.h
  * @brief Polynomial implementation
  */


#include "number_traits.h"
#include "idealadicrepresentation.h"

#include <string>
#include <stdarg.h>
#include <iostream>


#define TEMP_DEF template<class BT,\
	                        class C,\
                          class num_traits>

#define POLY Polynomial<BT, C, num_traits>

namespace MATH
{
	namespace Algebra
	{
		namespace Private
		{
			/**
				* @brief Variable Ideal for ideal representation.
				* @tparam BaseType the variable is interpreted over this type
				* @tparam number_traits the used traits class
				* @see Number_traits
				*/
			template<class BaseType,
							 class number_traits = 
								 MATH::Algebra::Number_traits<BaseType> >
			class VariableIdeal
			{
				private:
					/**
						* @brief Pure static class
						*/
					VariableIdeal()
					{}

					/**
						* @brief Pure static class
						*/
					VariableIdeal(const VariableIdeal&)
					{}

					/**
						* @brief Pure static class
						*/
					VariableIdeal& operator=(const VariableIdeal&)
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
						* @brief The string shape of the variable.
						*/
					static std::string strShape;

			};

			template<class BaseType,
							 class number_traits>
			std::string VariableIdeal<BaseType, number_traits>::strShape = "x";
		}

		/********************************************************************************/
		/**
		  * @brief It is a polynomial representation class.
			* @details This implementation is based on the Ideal-adic representation,
			*          where the ideal is the following: \f$I = <x>\f$.
			* @tparam BaseType the base type of the polinom
			* @tparam Container the container type
			* @tparam number_traits traits class of the base type
			* @see Private::VariableIdeal
			* @see FieldExpansion
			*/
		template<class BaseType,
			       class Container = std::vector<BaseType>,
						 class number_traits = Number_traits<BaseType> >
		class Polynomial:
			public IdealAdicRepresentation<BaseType,
			                               Private::VariableIdeal<BaseType, number_traits>,
														         Container,
														         number_traits>
		{
			public:
				/**
				  * @brief unsigned int wrapper class for constructors
					*/
				typedef typename IdealAdicRepresentation<BaseType,
																						     Private::VariableIdeal
																						       <BaseType, number_traits>,
																						     Container,
																						     number_traits>::IndexType
																									 IndexType;

			public:
				/**
				  * @brief Copy constructor for base type, and simple constructor
					* @param baseType the first coeff
					*/
				Polynomial(const BaseType& baseType = number_traits::additiveUnit);

				/**
				  * @brief Copy-constructor from base type
					* @param other The base type
					*/
				Polynomial(const IdealAdicRepresentation<BaseType,
						                                     Private::VariableIdeal
																								   <BaseType, number_traits>,
																								 Container,
																								 number_traits>& other);

        /**
          * @brief Copy constructor for any IdealAdicRepresentation
          * @details It needs some explanation. First look this function
          *          could be dangerous, but not. The reason is in the 
          *          VariableIdeal, because the variable ideal is guarantee 
          *          that the coefficients always congruent.
          *          Backwards this isn't true, so any similar copy constructor
          *          could make error.
          * @tparam Ideal The other ideal
          * @param other The other representation
          */
        template<class Ideal>
        Polynomial(const IdealAdicRepresentation<BaseType,
                                                 Ideal,
                                                 Container,
                                                 number_traits>& other);

				/**
				  * @brief Uploader constructor
					* @param numOfCoeffs the number of coefficients
          * @param first The coeffs of the zero power element
					*/
        template<class T>
				explicit Polynomial(const IndexType numOfCoeffs, T first, ...);

				//Not necessary copy constructor and assign operator

				/**
				  * @brief Assign operator for Base type
					* @param other the base type
					*/
				Polynomial& operator=(const IdealAdicRepresentation<BaseType,
						                                     Private::VariableIdeal
																								   <BaseType, number_traits>,
																								 Container,
																								 number_traits>& other);

				/**
				  * @brief Assign operator for any BaseTyped IdealAdicRepresentation
          * @details It is similary for the copy constructor.
					* @param other the base type
					*/
        template<class Ideal>
				Polynomial& operator=(const IdealAdicRepresentation<BaseType,
						                                     Ideal,
																								 Container,
																								 number_traits>& other);

				/**
				  * @brief The degree of the polynomial
					* @note It is exactly the getOrder function of the 
					*       FieldExpansion
					* @return The degree of the polynomial
					* @see FieldExpansion::getOrder()
					*/
				unsigned getDegree() const;

				/**
				  * @brief Getter and Setter operators for the coefficients
					* @see FieldExpansion::operator[]
					*/
				using IdealAdicRepresentation<BaseType,
			                                Private::VariableIdeal
														            <BaseType, number_traits>,
														          Container,
														          number_traits>::operator[];

				/**
				  * @brief Interpretation of the polynom
					* @details It uses a Interpreter homomorphism
					* @param x the given point
					* @return the value of the polynomial at the given point
					*/
				BaseType operator()(const BaseType& x) const;

				/**
				  * @brief Easily printer function
					* @param os the output string
					* @param a the given polynomial
					* @return the input os parameter
					*/
				TEMP_DEF
				friend std::ostream& operator<<(std::ostream& os, 
						                            const POLY& a);

			private:
				/**
				  * @brief Make private.
					* @details It is nicer, but exists a wrapper: getDegree()
					* @see getDegree()
					*/
				using IdealAdicRepresentation<BaseType,
			                                Private::VariableIdeal
															          <BaseType, number_traits>,
														          Container,
														          number_traits>::getOrder;

		};
	}
}

#undef TEMP_DEF
#undef POLY

#include "polynomial.hpp"
#include "number_traits_polynomial.h"
#include "numbercalculator_polynomial.h"

#endif
