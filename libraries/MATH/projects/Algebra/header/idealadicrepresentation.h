#ifndef MATH__ALGEBRA__IDEALADICREPRESENTATION_H
#define MATH__ALGEBRA__IDEALADICREPRESENTATION_H

#include <vector>
#include <stdarg.h>

#include "number_traits.h"
#include "numbercalculator.h"

#include "karatsuba.h"
/**
  * @file idealadicrepresentation.h
	* @brief This file contains the class what implements the Ideal-adic representation.
	* @see IdealAdicRepresentation
	*/

#define TEMP_PAR template<class BType,\
                          class IType,\
                          class Cont,\
                          class num_traits>

#define IDEAL_REP IdealAdicRepresentation<BType, IType, Cont, num_traits>



namespace MATH
{
	namespace Algebra
	{
		/**
		  * @brief Polimorf class for idealadic representation.
			* @details This is a generalization of the p-adic reprezentation. Which is based
			*          on ideal: \f$ I \f$
			*          Where 
			*          \f[
			*            <a_1,a_2,...,a_n> = {a_1r_1 + a_2r_2 + ... + a_nr_n | r_i \in BaseType }
			*          \f]
			*          These case the representation is:
			*          \f[
			*            u = u_1 + \Delta u_1 + \Delta u_2 + ... 
			*          \f]
			*          and \f$ \Delta u_1 I^k\f$.
			*
			*          This class try to implements this generalization. IdealType is the I, it could 
			*          be a simple variable, and in that case we could get an polynom. If The IdealType
			*          is a multi variable type, then we get an multivariable polynom. But if the
			*          IdealType is a symbol for example i it means \f$I = <x^2 - 1>\f$, and the base 
			*          type is double, or float, we get the complex field, or above integer field we
			*          got the field of Gausian integers.
			* @tparam BaseType the base type of the representation
			* @tparam IdealType the ideal type, if could be "symbol", or variable(s).
			*                   Ideal type has to contain 2 static functions. 
			*                   bool isCongruentElement(const BaseType&); and
			*                   void division(const BaseType& a,
			*                                 BaseType& divisior, BaseType rem)
			*                   static values: strShape the string shape of ideal
			* @tparam Container Container type. It Needs operator[] and insert function.
			* @tparam number_traits traits class for the number, it necessary dou to conversation
			* @see Polynom
			* @see Number_traits
			*/
		template<class BaseType,
			       class IdealType,
						 class Container = std::vector<BaseType>,
						 class number_traits = Number_traits<BaseType> >
		class IdealAdicRepresentation
		{
			public:

				/**
				  * @brief Index type for the constructor clarity.
					*/
				struct IndexType
				{
					/**
					  * @brief the value of the index
						*/
					unsigned value;

					/**
					  * @brief Copy constructor from double to index type
						* @param idx the index value
						*/
					IndexType(const unsigned idx):value(idx)
					{  }
				};

			private:

				/**
				  * @brief Algorithm support function
					* @details This function compare element with the NumberCalculator
					*/
				struct FindEquals 
				{
					/**
					  * @brief The element which is looled for.
						*/
					const BaseType sElement;

					/**
					  * @brief Number calculator class
						*/
					typedef NumberCalculator<BaseType> NumCalc;
					
					/**
					  * @brief Simple constructor
						* @param searchElement The element which is looked for.
						*/
					FindEquals(const BaseType& searchElement):sElement(searchElement)
					{}

					/**
					  * @brief Do We find the element?
						* @param act The actual element
						*/
					bool operator()(const BaseType& act)
					{
						return NumCalc::equals(act, sElement);
					}
				};

			private:

				/**
					* @brief Number calculator class
					*/
				typedef NumberCalculator<BaseType> NumCalc;

			public:

				/**
				  * @brief Pseudo Remainder division.
					* @details We not assume, that the BaseType is a Field,
					*          so we don't have devision above BaseType. Therefore
					*          the representation don't have to be an UFD, so there
					*          are not exists remainder devision, but exists pseudo 
					*          remainder division, which has a next shape:
					*          \f[
					*            \alpha^\delta a = q \cdot b + rem
					*          \f],
					*          where \f$ \delta = deg a - deg b + 1\f$, and
					*          \f$ alpha \f$ is the leading coeff of b.
					*          If BaseType is Field, use the remainderDivision function.
					* @param a The appropriate variable in the previous form.
					* @param b The appropriate variable in the previous form.
					* @param rem The pseudo remainder
					* @return The pseudo devisior (\f$q\f$)
					*/
				static IdealAdicRepresentation 
							   pseudoRemainderDivision(const IdealAdicRepresentation& a,
							  												 const IdealAdicRepresentation& b,
							  												 IdealAdicRepresentation& rem);

				/**
				  * @brief Remainder division.
					* @details We assume the ring is an UFD. I special case
					*          You can redfiend this function to speudo remainder
					*          calculation to non UFD rings.
					*          \f[
					*            a = q \cdot b + rem
					*          \f]
					*          There are a funny thing in this function, because
					*          we calculate over BaseType, so the result not always 
					*          the expected. For example the 18 = 5 * 4 - 2, it's 
					*          correct but we not excpect that. It is an modulo calculation
					*          over the representation, it means it not equals the 
					*          modulo over BaseType.
					* @param a The appropriate variable in the previous form.
					* @param b The appropriate variable in the previous form.
					* @param rem The appropriate variable in the previous form.
					* @return the integer part of the representation (\f$q\f$)
					*/
				static IdealAdicRepresentation
					       remainderDivision(const IdealAdicRepresentation& a,
						                       const IdealAdicRepresentation& b,
																	 IdealAdicRepresentation& rem);

			protected:

				/**
					* @brief the coefficients
					*/
				Container _coeffs;

			public:

				/**
				  * @brief Copy constructor for baseType
					* @param value The value
					* @param shiftValue The shifting value of the representation
					* @throw Exceptions::ParameterException If the representation length is infinity.
					*/
				IdealAdicRepresentation(const BaseType& value = number_traits::additiveUnit,
						                    unsigned shiftValue = 0);

				/**
				  * @brief Upload constructor
					* @param numOfCoeffs the number of the coefficients
          * @param first The first coefficient
					* @see IndexType
					* @throw Exceptions::ParameterException if one of the arguments not a 
					*        congruent element
          * @note The first is usedfull, for the correct parameter transformation due to the va_arg
          * @warning The ... parameter only could be primitive type
					*/
        template<class T>
				explicit IdealAdicRepresentation(const IndexType numOfCoeffs, const T& first, ...);

				/*
				  * @brief other copy constructor between representations
					* @param other the other number
					*/
				//IdealAdicRepresentation(const IdealAdicRepresentation& other);

				/*
				  * @brief simple assignement operator
					* @param other the other type
					*/
				//IdealAdicRepresentation& operator=(IdealAdicRepresentation& other);

        /*
          * @brief Copy constructor for base type conversion
          * @param other The other representation
          * @tparam T The base type of the other representation
          */
     /*   template<class T>
        IdealAdicRepresentation(
            const IdealAdicRepresentation<T, IdealType, Container, number_traits>& other);*/

				/**
				  * @brief Empty virtual destructor for polymorphic properties
					*/
				virtual ~IdealAdicRepresentation()
				{}

        /*
          * @brief Assigne operator for another base type conversion
          * @param other The other representation
          * @tparam T The base type of the other representation
          */
 /*       template<class T>
        IdealAdicRepresentation&
          operator=(const IdealAdicRepresentation<T, IdealType, Container, number_traits>& other);*/


				/**
				  * @brief Prefix increase operator
					* @details The operation works with the 0 coefficient.
					* @return a reference to this object.
					* @warning Non transactive
					*/
				IdealAdicRepresentation& operator++();

				/**
				  * @brief Postfix increase operator
					* @details The operation works with the 0 coefficient.
					* @return A copy of the this object
					* @warning could be slow, prefer the prefix operator
					* @warning Non transactive
					*/
				IdealAdicRepresentation operator++(int);

				/**
				  * @brief Prefix decrease operator
					* @details The operation works with the 0 coefficient.
					* @return a reference to this object.
					* @warning Non transactive
					*/
				IdealAdicRepresentation& operator--();

				/**
				  * @brief Postfix decrease operator 
					* @details The operation works with the 0 coefficient.
					* @return A copy of the this object
					* @warning could be slow, prefer the prefix operator
					* @warning Non transactive
					*/
				IdealAdicRepresentation operator--(int);

				/**
				  * @brief Minus operator.
					* @return reference to this.
					*/
				IdealAdicRepresentation operator-() const;

				/**
				  * @brief Short format operator for addition.
					* @param a the given number
					* @return a reference to this object.
					* @warning Non transactive
					*/
				IdealAdicRepresentation& operator+=(const IdealAdicRepresentation& a);

				/**
				  * @brief Short format operator for substraction.
					* @param a the given number
					* @return a reference to this object.
					* @warning Be carefull with the remainder system.
					* @warning Non transactive
					*/
				IdealAdicRepresentation& operator-=(const IdealAdicRepresentation& a);

				/**
				  * @brief Short format operator for division.
					* @details The resoult will be the integer part of the division.
					*          It uses the remaindDivision function
					* @param a the given number
					* @return a reference to this object.
					*/
				IdealAdicRepresentation& operator/=(const IdealAdicRepresentation& a);
				
				/**
				  * @brief Short format operator for multiplication.
					* @param a the given number
					* @return a reference to this object.
					*/
				IdealAdicRepresentation& operator*=(const IdealAdicRepresentation& a);

				/**
					* @brief Short format operator for division.
					* @details The resoult will be the remainder part of the division.
					*          It uses the remaindDivision function
					* @param a the given number
					* @return a reference to this object.
					*/
				IdealAdicRepresentation& operator%=(const IdealAdicRepresentation& a);

				/**
				  * @brief Exactly it is a toString function
					*/
				operator std::string() const;

				/**
				  * @brief return the coefficient
					* @details if coeff bigger than the degree return 0
					* @return the coefficient
					*/
				BaseType getCoeff(const unsigned coeff) const;

				/**
				  * @brief Create a sub idealadic representation.
					* @param startCoeff The first coeff, which is contained by the new
					*                   reprezentation
					* @param lastCoeff The last coeff, which is contained by the new
					*                   reprezentation.
					* @return A new IdealAdicRepresentation from a subset of this
					*         reprezentation's coefficient.
					*/      
				IdealAdicRepresentation operator()(const unsigned startCoeff,
						                               const unsigned lastCoeff) const;

				/**
				  * @brief Gettter for the leader coefficient
					* @return The leader coefficient
					*/
				const BaseType& lcoeff() const;

				/**
				  * @brief getter for the order of the representation
					* @return the order of the representation
					*/
				unsigned getOrder() const;

				/**
				  * @brief eqauls logical operator
					* @details Two representation is equals if the coefficients are eqauls
					* @param a the left operand
					* @param b the right operand
					* @return true if the coefficients are equals, false otherwise.
					*/
				TEMP_PAR
				friend bool operator==(const IDEAL_REP& a,
						                   const IDEAL_REP& b);

				/**
				  * @brief Negation of the eqauls logical operator
					* @details Two representation is equals if the coefficients are eqauls
					* @param a the left operand
					* @param b the right operand
					* @return true if the coefficients are not equals, false othervise
					*/
				TEMP_PAR
				friend bool operator!=(const IDEAL_REP& a,
						                   const IDEAL_REP& b);

				/**
				  * @brief Addition aritmethic operator
					* @param a the left operand
					* @param b the right operand
					* @return \f$a + b\f$
					*/
				TEMP_PAR
				friend IDEAL_REP operator+(const IDEAL_REP& a,
						                       const IDEAL_REP& b);
				/**
				  * @brief Substraction aritmethic operator
					* @param a the left operand
					* @param b the right operand
					* @return \f$a - b\f$
					*/
				TEMP_PAR
				friend IDEAL_REP operator-(const IDEAL_REP& a,
						                       const IDEAL_REP& b);
				/**
					* @brief Multiplication aritmethic operator
					* @param a the left operand
					* @param b the right operand
					* @todo Do some speed up, with base type operation
					* @return \f$a * b\f$
					*/
				TEMP_PAR
				friend IDEAL_REP operator*(const IDEAL_REP& a,
																	 const IDEAL_REP& b);

				/**
					* @brief Division aritmethic operator
					* @details Operation is use the RemainderDivision function.
					* @param a the left operand
					* @param b the right operand
					* @return \f$a / b\f$
					*/
				TEMP_PAR
				friend IDEAL_REP operator/(const IDEAL_REP& a,
																	 const IDEAL_REP& b);

				/**
					* @brief Remainder aritmethic operator
					* @param a the left operand
					* @param b the right operand
					* @return \f$a - b\f$
					*/
				TEMP_PAR
				friend IDEAL_REP operator%(const IDEAL_REP& a,
																	 const IDEAL_REP& b);


				/**
				  * @brief Shift operator.
					* @details Exactly this opertion division with shiftValue-th power of 
					*          the idealadic element
					* @param a the representation
					* @param shiftValue the value of the shifting.
					*/
				TEMP_PAR
				friend IDEAL_REP operator>>(const IDEAL_REP& a,
																		const unsigned shiftValue);


				/**
				  * @brief Shift operator.
					* @details Exactly this opertion multiply with shiftValue-th power of 
					*          the idealadic element
					* @param a the representation
					* @param shiftValue the value of the shifting.
					*/
				TEMP_PAR
				friend IDEAL_REP operator<<(const IDEAL_REP& a,
																		const unsigned shiftValue);

				/**
				  * @brief Easily printer function
					* @param os the output string
					* @param a the given polynomial
					* @return the input os parameter
					*/
				TEMP_PAR
				friend std::ostream& operator<<(std::ostream& os, 
						                            const IDEAL_REP& a);

				/**
				  * @brief Used for multiplication
					*/
				friend class MATH::Algebra::Karatsuba<BaseType>;

        template<class BType,
                 class Cont,
                 class num_traits>
        friend class Polynomial;

			protected:

        /**
          * @brief Constructor for derived classes
          * @param numOfElement the number of elements
          * @param vlist the list of arguments
          * @param first The zero coefficients of reprezentation
          */
        template<class T>
        void constructRepresentation(const unsigned numOfElement,
                                     const T& first,
                                     va_list vlist);

				/**
				  * @brief getter for coefficients
					* @details If coeff bigger than degree,
					*          a new element is created, and return the
					*          reference of the new element.
					* @return a reference to the specific coefficient
					*/
				BaseType& operator[](const unsigned coeff);

				/**
				  * @brief getter for coefficients const form
					* @details If coeff bigger than degree,
					*          a new element is created, and return the
					*          reference of the new element.
					* @return a reference to the specific coefficient
					* @see getCoeff
					*/
				BaseType operator[](const unsigned coeff) const;


				/**
				  * @brief Do the carry lifting.
					*/
				void carrying();
				
				/**
				  * @brief This function corrects the sape of the reprezentation. 
				  * @details Removes the unnecessery zeros 
					*          from the reprezentation
					*/
				virtual void correctShape();

		};
	}

}
#undef TEMP_PAR
#undef IDEAL_REP

#include "idealadicrepresentation.hpp"
#include "number_traits_idealadic.h"
#include "numbercalculator_idealadicrep.h"


#endif

