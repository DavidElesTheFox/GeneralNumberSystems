#ifndef MATH__ALGEBRA__KARATSUBA_H
#define MATH__ALGEBRA__KARATSUBA_H

/**
  * @file karatsuba.h
	* @brief Karatsuba fast multiplication algorithm general implementation
	*/

#include "number_traits.h"

namespace MATH
{
	namespace Algebra
	{

		/**
			* @brief Template implementation of Karatsuba fast multiplication.
			* @details The algorithm assume that the elements of the ploinoms are
			*          2 powers and equals.
			*          Basic idea:
			*          \f[
			*            a = a_1 + a_2 x + \cdot a_{n-1} x^{n} = A_1 + A_2 x^{(n+1)/2}
			*          \f]
			*          \f[
			*            b = b_0 + b_1 + \cdot b_{n-1} = B_1 + B_2 x^{(n+1)/2}
			*          \f]
			*          \f[
			*            ab = A_2B_2 x^{n + 1} + (A_1B_2 + A_2B_1)x^{(n+1)/2} + A_1B_1
			*          \f]
			*          We can create a faster algorithm, if we write the next shape
			*          the multiplication.
			*          \f[
			*            ab = A_2B_2 x^{n + 1} 
			*                 + (A_2B_2 + A_1B_1 + (A_2 - A_1)(B_1 - B_2)) x^{(n+1)/2}
			*                 + A_1B_1
			*          \f]
			*          It is contains only 3 multiplication.
			*          The Recursive algorithm result is a \f$O(n\log(n))\f$.
			* @tparam BaseType The type of a representation element
			* @todo singleton
			*/
		template<class BaseType,
			       class number_traits = Number_traits<BaseType> >
		class Karatsuba
		{
			private:

				/**
					* @brief This memory space use the tempolary calculation.
					* @details This buffer structure the following (in D ordered case)
					*         \verbatim
					*           ----------------------------------------------
					*          |  D/2  |  D/2  |     D     |        2D        |
					*           ----------------------------------------------
					*          ^       ^       ^           ^
					*       a2-a1    b1-b2    res          for recursion
					*         \endverbatim
					*         The 2D space is enough for the recursion, because the 
					*         second step seems like the this:
					*         \verbatim
					*             2nd step: D        3rd step: D/2
					*           ---------------------------------
					*          | D/4 | D/4 |  D/2  |D/8|D/8| D/4 |
					*           ---------------------------------
					*          ^     ^     ^       ^   ^   ^ 
					*         \endverbatim
					*         So if we know we has a D ordered representation, we
					*         got the next series 
					*         \f[
					*           \sum (1/2)^2 = \frac{(\frac{1}{2})^{\log(D)} - 1}{1/2} = 2 - (\frac{1}{2})^{\log(D)}
					*         \f]
					*         This is lower than 2 so we enough for recursion \f$2D\f$ space.
					*/
				static BaseType* buffer;

				/**
					* @brief The size of the buffer
					*/
				static unsigned buffer_size;

		  public:

				/**
					* @brief Covering function of the algorithm.
					* @details This function init the buffer, and allocates
					*          new memory for it, only if it is necessary.
					* @tparam Container The type of the container, where the 
					*                   coefficients are located. Only need an
					*                   operator[].
					* @param a a representation
					* @param b another representation
					* @param start The start index of the coefficients
					* @param end The last index of the coefficients
					* @param c the result parameter
					*/
				template<class Container>
				static void doIt(const Container& a,
												 const Container& b,
												 const unsigned start,
												 const unsigned end,
												 Container& c);

			private:

				/**
					* @brief The recursive function.
					* @details The algorithm assume that the elements of the ploinoms are
					*          2 powers and equals.
					*          Basic idea:
					*          \f[
					*            a = a_1 + a_2 x + \cdot a_{n-1} x^{n} = A_1 + A_2 x^{(n+1)/2}
					*          \f]
					*          \f[
					*            b = b_0 + b_1 + \cdot b_{n-1} = B_1 + B_2 x^{(n+1)/2}
					*          \f]
					*          \f[
					*            ab = A_2B_2 x^{n + 1} + (A_1B_2 + A_2B_1)x^{(n+1)/2} + A_1B_1
					*          \f]
					*          We can create a faster algorithm, if we write the next shape
					*          the multiplication.
					*          \f[
					*            ab = A_2B_2 x^{n + 1} 
					*                 + (A_2B_2 + A_1B_1 + (A_2 - A_1)(B_1 - B_2)) x^{(n+1)/2}
					*                 + A_1B_1
					*          \f]
					*          It is contains only 3 multiplication.
					*          The Recursive algorithm result is a \f$O(n\log(n))\f$.
					* @tparam Container The type of the container, where the 
					*                   coefficients are located. Only need an
					*                   operator[].
					* @param a a representation
					* @param b another representation
					* @param start The start index of the coefficients
					* @param end The last index plus one of the coefficients.
					* @param c the result parameter
					* @param bufferPointer The pointer for the relevant global buffer
					*/
				template<class Container>
				static void multiply(const Container& a,
														 const Container& b,
														 const unsigned start,
														 const unsigned end,
														 Container& c,
														 BaseType* bufferPointer);
		};
	}
}

#include "karatsuba.hpp"
#endif

