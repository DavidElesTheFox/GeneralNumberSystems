#ifndef __MATH__ALGEBRA__NUMBER_TRAITS_H
#error use without number_traits.h
#endif

/**
	* @file number_traits_spec.h
	* @brief Specializations of number_traits
	*/

namespace MATH
{
	namespace Algebra
	{
		namespace Private
		{
			/**
				* @brief precision specialization value for float
				*/
			template<>
			struct PrecisionValue<float>
			{
				/**
					* @brief the value of the precision
					*/
				static const double value = 0.01;
			};

			/**
				* @brief precision specialization value for double
				*/
			template<>
			struct PrecisionValue<double>
			{
				/**
					* @brief the value of the precision
					*/
				static const double value = 0.001;
			};
		}
	}
}
