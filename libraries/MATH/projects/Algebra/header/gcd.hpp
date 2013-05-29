

#include "numbercalculator.h"
namespace MATH
{
	namespace Algebra
	{
		template<class T,
             class number_traits>
		T Gcd<T, number_traits>::GCD(const T& num1, const T& num2)
		{
			return Gcd<T>::EuclideanAlg(num1, num2).gcd;
		}

		template<class T, 
             class number_traits>
		typename Gcd<T, number_traits>::EuclideanResult_t Gcd<T, number_traits>::
		  EuclideanAlg(const T& num1,
					         const T& num2)
		{
			typename Gcd<T, number_traits>::EuclideanResult_t ret;
			T x[3];
			T y[3];
			T q[3];
			T r[3];

			x[0] = number_traits::multiplicativeUnit;	y[0] = number_traits::additiveUnit;	r[0] = num1;
			x[1] = number_traits::additiveUnit;	y[1] = number_traits::multiplicativeUnit;	r[1] = num2;
			Integer<3> n = 0;
			while(!NumberCalculator<T, number_traits>::equals(r[(n + 1).toBase()],
                                                        number_traits::additiveUnit))
			{
				q[(n + 1).toBase()] = r[n.toBase()]/r[(n + 1).toBase()];
				r[(n + 2).toBase()] = r[n.toBase()] % r[(n + 1).toBase()];
				x[(n + 2).toBase()] = x[n.toBase()] - x[(n + 1).toBase()]*q[(n + 1).toBase()];
				y[(n + 2).toBase()] = y[n.toBase()] - y[(n + 1).toBase()]*q[(n + 1).toBase()];
				++n;
			}
			ret.a = x[n.toBase()];
			ret.b = y[n.toBase()];
			ret.gcd = r[n.toBase()];
			ret.number1 = x[(n + 1).toBase()];
			ret.number2 = y[(n + 1).toBase()];
			return ret;
		}

		template<class T,
             class number_traits>
		Gcd<T, number_traits>::Gcd(const T& num1, const T& num2):
			_data(Gcd<T, number_traits>::EuclideanAlg(num1, num2))
		{	}

		template<class T,
             class number_traits>
		T Gcd<T, number_traits>::operator()() const
		{
			return _data.gcd;
		}

		template<class T,
             class number_traits>
		T Gcd<T, number_traits>::getGcd()
		{
			return _data.gcd;
		}

		template<class T,
             class number_traits>
		typename Gcd<T, number_traits>::EuclideanResult_t Gcd<T, number_traits>::
               getResult()
		{
			return _data;
		}
	}
}
