#ifndef __MATH__ALGEBRA__INTEGER_H
#define __MATH__ALGEBRA__INTEGER_H

#include <Exceptions/mathexception.h>
/**
	* @file integer.h
	* @brief This class contains a templated integer class
	* @see MATH::Algebra::Integer
	*/

namespace MATH
{
	namespace Algebra
	{
		/**
			* @brief A Integer class
			* @details This class represents an residulum system.
			*          Example \f$ Z_3\f$ is could be:
			*          @code
			*             Integer_generic<int, 3>
			*          @endcode
			* @param T the base integer type
			* @param Mod the modulo number
			* @see Integer
			*/
		template<class T, T Mod>
		class Integer_generic
		{
			protected:
				/**
					* @brief The value of the integer
					*/
				T _number;

			public:

				/**
					* @brief Constructor without parameter
					* @details it's needed because, after calling the
					*          T type default constructor we need the 
					*          normalizing
					*/
				Integer_generic();

				/**
					* @brief A simple constructor
					*/
				Integer_generic(const T number = 0);

				//Integer_generic(const Integer_generic& other);	//Not Need to specialization

				/**
					* @brief a simple destructor
					*/
				virtual ~Integer_generic()
				{	}

				/**
					* @brief - operator for Integers
					* @return the a new Integer object
					*/
				Integer_generic<T, Mod> operator-() const;

				/**
					* @brief postfix ++ operator
					* @return the  a reference to this
					*/
				Integer_generic<T, Mod>& operator++();

				/**
					* @brief postfix -- operator
					* @return the  a reference to this
					*/
				Integer_generic<T, Mod>& operator--();

/*				NOT NEEDED
				Integer_generic<T, Mod>& operator=(const Integer_generic<T, Mod>& other) throw(Exceptions::MathException)
*/

				/**
					* @brief convert function to the base type
					* @return the _number value
					*/
				T toBase() const;

				/**
					* @brief a simple operator
					* @param other the other Integer
					* @return reference to this
					*/
				Integer_generic<T, Mod>& 
					operator+=(const Integer_generic<T, Mod>& other);

				/**
					* @brief a simple operator
					* @param other the other Integer
					* @return reference to this
					*/
				Integer_generic<T, Mod>& 
					operator-=(const Integer_generic<T, Mod>& other);

				/**
					* @brief a simple operator
					* @param other the other Integer
					* @return reference to this
					*/
				Integer_generic<T, Mod>& 
					operator*=(const Integer_generic<T, Mod>& other);

				/**
					* @brief a simple operator
					* @param other the other Integer
					* @return reference to this
					*/
				Integer_generic<T, Mod>& 
					operator/=(const Integer_generic<T, Mod>& other);

				/**
					* @brief a simple operator
					* @param other the other Integer
					* @return reference to this
					*/
				Integer_generic<T, Mod>& 
					operator%=(const Integer_generic<T, Mod>& other);

				/**
					* @brief a simple operator
					* @param a the left operand
					* @param b the right operand
					* @return the operator result
					*/
				friend bool operator==(const Integer_generic<T, Mod>& a, const Integer_generic<T, Mod>& b)
				{
					return a._number == b._number;
				}

				/**
					* @brief a simple operator
					* @param a the left operand
					* @param b the right operand
					* @return the operator result
					*/
				friend bool operator>=(const Integer_generic<T, Mod>& a, const Integer_generic<T, Mod>& b)
				{
					return a._number >= b._number;
				}

				/**
					* @brief a simple operator
					* @param a the left operand
					* @param b the right operand
					* @return the operator result
					*/
				friend bool operator<=(const Integer_generic<T, Mod>& a, const Integer_generic<T, Mod>& b)
				{
					return a._number <= b._number;
				}

				/**
					* @brief a simple operator
					* @param a the left operand
					* @param b the right operand
					* @return the operator result
					*/
				friend bool operator>(const Integer_generic<T, Mod>& a, const Integer_generic<T, Mod>& b)
				{
					return a._number > b._number;
				}

				/**
					* @brief a simple operator
					* @return the operator result
					* @param a the left operand
					* @param b the right operand
					*/
				friend bool operator<(const Integer_generic<T, Mod>& a, const Integer_generic<T, Mod>& b)
				{
					return a._number < b._number;
				}

				/**
					* @brief a simple operator
					* @param a the left operand
					* @param b the right operand
					* @return the operator result
					*/
				friend bool operator!=(const Integer_generic<T, Mod>& a, const Integer_generic<T, Mod>& b)
				{
					return a._number != b._number;
				}

				/**
					* @brief a simple operator
					* @param a the left operand
					* @param b the right operand
					* @return the operator result
					*/
				friend Integer_generic<T, Mod> operator+(const Integer_generic<T, Mod>& a, const Integer_generic<T, Mod>& b)
				{
					return a._number + b._number;
				}

				/**
					* @brief a simple operator
					* @param a the left operand
					* @param b the right operand
					* @return the operator result
					*/
				friend Integer_generic<T, Mod> operator-(const Integer_generic<T, Mod>& a, const Integer_generic<T, Mod>& b)
				{
					return a._number - b._number;
				}

				/**
					* @brief a simple operator
					* @param a the left operand
					* @param b the right operand
					* @return the operator result
					*/
				friend Integer_generic<T, Mod> operator*(const Integer_generic<T, Mod>& a, const Integer_generic<T, Mod>& b)
				{
					return a._number * b._number;
				}

				/**
					* @brief a simple operator
					* @param a the left operand
					* @param b the right operand
					* @return the operator result
					*/
				friend Integer_generic<T, Mod> operator/(const Integer_generic<T, Mod>& a, const Integer_generic<T, Mod>& b)
				{
					return a._number / b._number;
				}

				/**
					* @brief a simple operator
					* @param a the left operand
					* @param b the right operand
					* @return the operator result
					*/
				friend Integer_generic<T, Mod> operator%(const Integer_generic<T, Mod>& a, const Integer_generic<T, Mod>& b)
				{
					return a._number % b._number;
				}

				/**
					* @brief print the number to the os
					* @param os output stream
					* @param a the Integer
					* @return the input output stream
					*/
				friend std::ostream& operator<<(std::ostream& os, const Integer_generic<T, Mod>& a)
				{
					os<<a._number;
					return os;
				}

				/**
					* @brief read the number value to this
					* @param is input stream
					* @param a the Integer
					* @return the input inpustream
					*/
				friend std::istream& operator>>(const std::istream& is, Integer_generic<T, Mod>& a)
				{
					is>>a._number;
					a.normalize();
					return is;
				}

			protected:
				/**
					* @brief normalize function
					* @details this function do the normalizing of _number,
					*          in other words this function do the modulo operation
					*/
				void normalize();
		};


		/**
			* @brief Modulo Integer class, where the base
			*        class is int
			* @param Mod the modulo factor
			*/
		template<int Mod>
		class Integer : public Integer_generic<int, Mod>
		{
			public:
				/**
					* @brief constructor
					* @param number the number
					* @see Integer_generic
					*/
				Integer(const int number = 0):
					Integer_generic<int, Mod>(number)
				{	}
		};

		/**
			* @brief Modulo Integer class, where the base
			*        class is unsigned int
			* @details every modulo is positive so it is
			*          an Complete Residum system
			* @param Mod the modulo factor
			*/
		template<unsigned Mod>
		class IntegerCRS : public Integer_generic<unsigned, Mod>
		{
			public:
				/**
					* @brief constructor
					* @param number the number
					* @see Integer_generic
					*/
				IntegerCRS(const unsigned number = 0): 
					Integer_generic<unsigned, Mod>(number)
				{	}
		};
	}
}

#include "integer.hpp"
#endif // __MATH__ALGEBRA__Integer_generic_H
