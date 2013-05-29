#ifndef __MATH__ALGEBRA__NUMBERCALCULATOR_H
#error use without number calculator header
#endif

#include <iostream>

namespace MATH
{
	namespace Algebra
	{
		template<class T, class number_traits>
		bool NumberCalculator<T, number_traits, false>
		  ::equals(const T& a,
		           const T& b)
		{
			return abs(a-b) < number_traits::precision;
		}
	}
}

