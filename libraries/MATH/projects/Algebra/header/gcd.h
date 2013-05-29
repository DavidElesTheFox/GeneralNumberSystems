#ifndef __MATH__ALGEBRA__GCD_H
#define __MATH__ALGEBRA__GCD_H

/**
	* @file gcd.h
	* @brief GCD (Gratest Common Divisor) algorithm implementation
	* @see MATH::Algebra::Gcd
	*/


#include "integer.h"
#include "number_traits.h"
#include "numbercalculator.h"


namespace MATH
{
	namespace Algebra
	{
		/**
			* @brief   GCD (Gratest Common Divisor) algorithm implementation
			* @details This class use the Euclidean algorithm to determine it.
			*          Possible to create instances and possible to 
			*          use static functions too
			* @note    The Euclidean algorithm is smarter then a simple Gcd 
			*          algorithm.It determines four more number: x,y,a,b
			*          Let's see \f$gcd(n,m) = GCD\f$
			*          \f[
			*              n \cdot x + m \cdot y = 0
			*          \f]
			*          \f[
			*              n \cdot a + m \cdot b = GCD
			*          \f]
			*/
		template<class T,
             class number_traits = Number_traits<T> >
		class Gcd
		{
			public:
				/**
					* @brief Representaion of Euclidean result
					*/
				struct EuclideanResult_t
				{
					/**
						* @brief The Gratest common divisor
						*/

					T gcd;
					/**
						* @brief the left operand
						*/

					T number1;
					/**
						* @brief the right operand
						*/

					T number2;
					/** 
						* @brief one of the plus information
						* @details \f[number1 \cdot x + number2 \cdot y = 0 \f]
					  */
					T x;

					/** 
						* @brief one of the plus information
						* @details \f[number1 \cdot x + number2 \cdot y = 0 \f]
					  */
					T y;

					/** 
						* @brief one of the plus information
						* @details \f[a \cdot number1 + b \cdot number2 = gcd \f]
					  */
					T a;

					/** 
						* @brief one of the plus information
						* @details \f[a \cdot number1 + b \cdot number2 = gcd \f]
					  */
					T b;
				};
			public:
				/**
					* @brief determines the gratest common divisor
					* @param num1 The left operand
					* @param num2 The right operand
					* @return The Gcd of num1 and num2
					*/
				static T GCD(const T& num1, const T& num2);

				/**
					* @brief Directli use the euclidean algorithm
					* @return A full EuclideanResult_t type
					* @param num1 the left operand
					* @param num2 the right operand
					*/
				static EuclideanResult_t EuclideanAlg(const T& num1,
						                                  const T& num2);

			private:
				/**
					* @brief the data for instance
					*/
				EuclideanResult_t _data;
			public:

				/**
					* @brief constructor
					* @param num1 the left operand
					* @param num2 the right operand
					*/
				Gcd(const T& num1, const T& num2);

				//Gcd(const Gcd& other);

				/**
					* @brief simple destructor
					*/
				virtual ~Gcd()
				{	}

				//Gcd& operator=(const Gcd& other);

				/**
					* @brief operator, which return the Gcd
					* @return the gcd
					*/
				T operator()() const;

				/**
					* @brief getter for gcd
					* @return the gcd
					*/
				T getGcd();

				/**
					* @brief getter for the full result
					* @return the full result
					*/
				EuclideanResult_t getResult();
			private:
				/**
					* @brief Empty parameter constructor
					*/
				Gcd()
				{	}
		};

	}
}
#include "gcd.hpp"

#endif // __MATH__ALGEBRA__GCD_H
