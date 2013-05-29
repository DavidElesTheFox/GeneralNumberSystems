#ifndef MATH__LINEARALGEBRA__VECTOR_H
#define MATH__LINEARALGEBRA__VECTOR_H

/**
	* @file vector.h
	* @brief contains the vector class
	* @see MATH::LinearAlgebra::Vector
	*/

#include <iostream>
#include <math.h>


#include <Exceptions/exception.h>
#include <Exceptions/mathexception.h>
#include <Exceptions/overflowexception.h>
#include <Exceptions/wrongdimensionexception.h>
#include <Exceptions/runtimeexception.h>

namespace MATH
{

	namespace LinearAlgebra
	{
		/**
			* @see Matrix
			*/
		template<class T>
		class Matrix;

		/**
			* @brief this class a simple template mathematical vector class
			* @tparam T the content type
			*/
		template<class T>
		class Vector
		{
			private:

				/**
					* @brief the data of element
					*/
				T *_data;			

				/**
					* @brief the dimension number
					*/
				int _count;
			public:
				/**
					* Simple constructor
					* @param n the dimension number
					* @param defaultValue the default value of the element (filler element)
					*/
				explicit Vector(const int n, const T& defaultValue = T());

				/**
					* @brief Default constructor
					* @warning By default a vector is -1 dimensional,
					*          and the data is null!
					* @note It is neccessary for containers!
					*/
				Vector();

				/**
					* @brief copy constructor
					* @param v the copied element
					*/
				Vector(const Vector& v);

				/**
					* @brief filler constructor
					* @param t the element list
					* @param count the dimension of the vector
					*/
				Vector(const T* t,const unsigned count);

				/**
					* @brief simple destructor
					*/
				virtual ~Vector()
				{
					if (_data != 0)
						delete[] _data;
				}

				/**
					* @brief Calculates a sub vector
					* @details the inedexes: [low,high)
					*	@param low the first coordinate of subvector from 0
					*	@param high the last coordinate
					* @return a new vector
					* @throw Exceptinos::RuntimeException at parameter error
					*/
				Vector getSubVector(const int low, const int high) const;

				/**
					* @brief getter for dimension
					* @return the dimension
					*/
				int getDimension() const;

				/**
					* @brief operator for elements
					* @throw OverflowException at parameter error
					* @param n the index of element (from 0)
					* @return the value of element
					* @warning without check, due to performance!
					*/
				T operator[](const int n) const 
				{
					return _data[n];
				}

				/**
					* @brief operator for elements
					* @throw OverflowException at parameter error
					* @param n the index of element (from 0)
					* @return the value of element
					* @warning without check dou to performance!
					*/
				T& operator[](const int n) 
				{
					return _data[n];
				}

				/**
					* @brief simple = operator
					* @param v the other vector
					* @return the reference of this object
					*/
				Vector& operator=(const Vector& v);

				/**
					* @brief simple operator
					* @param v the given vector
					* @return reference to this object
					*/
				Vector& operator+=(const Vector& v);

				/**
					* @brief simpl operator for scalar multiplication
					* @param a the scalar value
					* @return reference to this object
					*/
				Vector& operator*=(const T& a)
				{
					for(int i=0;i<_count;++i)
						_data[i] *= a;
					return *this;
				}

				/**
					* @brief simple operator
					* @param a the left operand
					* @param b the right operand
					* @return a == b
					*/
				friend bool operator==(const Vector<T>& a, const Vector<T>& b)
				{
						if(a._count != b._count)
							return false;
						bool l=true;
						for(int i=0; i<a._count 
								&& l;++i)
							l= (a._data[i] == b._data[i]);
						return l;
				}

				/**
					* @brief simple operator
					* @param a the left operand
					* @param b the right operand
					* @return a != b
					*/
				friend bool operator!=(const Vector<T>& a, const Vector<T>& b)
				{
					return !(a==b);
				}

				/**
					* @brief simple operator
					* @param a the left operand
					* @param b the right operand
					* @return a > b
					*/
				friend bool operator>(const Vector<T>& a, const Vector<T>& b)
				{
					if(a._count!=b._count) return false;
					bool l = true;
					for( int i=0;i<a._count && l;++i)
						l = (a._data[i] > b._data[i]);
					return l;
				}

				/**
					* @brief simple operator
					* @param a the left operand
					* @param b the right operand
					* @return a < b
					*/
				friend bool operator<(const Vector<T>& a, const Vector<T>& b)
				{
					if(a._count != b._count) return false;
					bool l = true;
					for(int i=0;i<a._count && l;++i)
						l = (a._data[i] < b._data[i]);
					return l;
				}

				/**
					* @brief simple operator
					* @param a the left operand
					* @param b the right operand
					* @return a >= b
					*/
				friend bool operator>=(const Vector<T>& a, const Vector<T>& b)
				{
					if(a._count!=b._count) return false;
					bool l = true;
					for(int i=0;i<a._count && l;++i)
						l = (a._data[i] >= b._data[i]);
					return l;
				}

				/**
					* @brief simple operator
					* @param a the left operand
					* @param b the right operand
					* @return a <= b
					*/
				friend bool operator<=(const Vector<T>& a, const Vector<T>& b)
				{
					if(a._count != b._count) return false;
					bool l = true;
					for(int i=0; i < a._count && l;++i)
						l = (a._data[i] <= b._data[i]);
					return l;
				}

				/**
					* @brief simple operator
					* @param a the left operand
					* @param b the right operand
					* @return a + b
					*/
				friend Vector<T> operator+ (const Vector<T>& a, const Vector<T>& b)
				{
					if(a._count == b._count)
					{
						Vector<T> c(a._count);
						for(int i=0; i < c._count; ++i)
						{
								c._data[i] = a._data[i]+b._data[i];
						}
						return c;
					}
					else
					{
						throw Exceptions::WrongDimensionException("Not equale the Vectors's length at Vectors adding");
					}
				}

				/**
					* @brief simple operator
					* @param a the left operand
					* @param b the right operand
					* @return a + b
					*/
				friend Vector<T> operator- (const Vector<T>& a, const Vector<T>& b)
				{
					if (a._count == b._count)
					{
						Vector<T> c(a._count);
						for(int i=0; i<c._count; ++i)
						{
								c._data[i] = a._data[i] - b._data[i];
						}
						return c;
					}
					else
					{
						throw Exceptions::WrongDimensionException("Not equale the Vectors's length in Vectors Decressing");
					}
				}

				/**
					* @brief simple operator
					* @param a the left operand
					* @param b the right operand
					* @return a * b
					*/
				friend Vector<T> operator* (const Vector<T>& a,const T& b)
				{
						Vector<T> c = a;
						return c *= b;
				}

				/**
					* @brief simple operator
					* @param a the left operand
					* @param b the right operand
					* @return a * b
					*/
				friend Vector<T> operator* (const T& b, const Vector<T>& a)
				{
						return a*b;
				}

				/**
					* @brief scalar multiplication by default
					* @param a the left operand
					* @param b the right operand
					* @return <a , b>
					*/
				friend T operator* (const Vector<T>& a,const Vector<T>& b)
				{
					if (a._count == b._count)
					{
						T c = T();
						for(int i=0;i<a._count;++i)
						{
								c += a._data[i] * b._data[i];
						}
						return c;
					}
					else
					{
						throw Exceptions::WrongDimensionException("Not equale the Vectors's length in Vector multiply");
					}
				}

				/**
					* @brief simple operator
					* @param a the left operand
					* @param b the right operand
					* @return a / b
					*/
				friend Vector<T> operator/ (const Vector<T>& a,const T& b)
				{
					if(b!=0)
					{
						Vector<T> c = a;
						for(int i=0; i < c._count; ++i)
							c._data[i] = a._data[i] / b;
						return c;
					}
					else
						throw Exceptions::MathException("Not possible devide by zero!");
				}

				/**
					* @brief printer operator
					* @param os the output stream
					* @param v the given vector
					* @return os due to chaining
					*/
				friend std::ostream& operator<< (std::ostream &os,const Vector<T>& v)
				{
					os<< v._count << " ";
					for (int i = 0; i < v._count; ++i)
					{
						os << v._data[i] << " ";
					}
					return os;
				}

				/**
					* @brief reader operator
					* @details dimension ws element0 ws element1 ...
					* @param is the input stream
					* @param v the given vector
					* @return is due to chaining
					*/
				friend std::istream& operator>> (std::istream& is, Vector<T>& v)
				{
					int x = 0;
					is>>x;
					v._count = x;
					delete[] v._data;
					v._data = new T[x];

					for(int i = 0; i < v._count; ++i)
					{
						is >> v._data[i];
					}
					return is;
				}

				/**
					* @brief a friend class
					*/
				friend class Matrix<T>;

				/**
					* @brief vectorial multiplication at 3 dimensional case
					* @param a the left operand
					* @param b the right operand
					*/
				static Vector<T> Xmultiply(const Vector<T>& a, const Vector<T>& b) 
				{
						if(a._count != b._count
							 && a._count != 3) 
							throw Exceptions::WrongDimensionException("Not equale the Vectors's length in Vector Xmultiply");
						Vector<T> c(3);
						c[0]=a[1]*b[2]-a[2]*b[1];
						c[1]=a[2]*b[0]-a[0]*b[2];
						c[2]=a[0]*b[1]-a[1]*b[0];
						return c;
				}
		};
	}
}

#include "vector.hpp"

#endif

