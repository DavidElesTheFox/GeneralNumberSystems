#ifndef __MATH__ALGEBRA__NUMBER_TRAITS_H
#error use without number_traits.h
#endif

namespace MATH
{
	namespace Algebra
	{
		namespace Private
		{
			template<class T>
			const double PrecisionValue<T>::value = 0.0;
		}
		template<class T>
		const bool Number_traits_core<T>::isInteger = IsInteger<T>::value;

		template<class T>
		const double Number_traits_core<T>::precision = Private::PrecisionValue<T>::value;

		template<class T>
		const T Number_traits_core<T>::additiveUnit = 
		  Number_traits_core<T>::parse<int>(0);

		template<class T>
		const T Number_traits_core<T>::multiplicativeUnit =
		  Number_traits_core<T>::parse<int>(1);

		template<class T>
		template<class TO_TYPE>
		TO_TYPE Number_traits_core<T>::convert(const T& number)
		{
			return TO_TYPE(number);
		}

		template<class T>
		template<class FROM_TYPE>
		T Number_traits_core<T>::parse(const FROM_TYPE& number)
		{
			return T(number);
		}

		template<class T>
		bool Number_traits_core<T>::isConvertableToBase(const T& number)
		{
			return true;
		}

	}
}
