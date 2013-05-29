#ifndef __MATH__ALGEBRA__NUMBER_TRAITS_H
#define __MATH__ALGEBRA__NUMBER_TRAITS_H

/**
	* @file number_traits.h
	* @brief Contains a number traits class
	*/

#include "integertypes.h"

namespace MATH
{
	namespace Algebra
	{
		namespace Private
		{
			/**
				* @brief Private class for specialization
				* @details This class is responsible, that the specialization
				*          of only one member is work.
				*/
			template<class T>
			struct PrecisionValue
			{
				/**
					* @brief the value of the precision
					*/
				static const double value;
			};
		}

		/**
			* @brief Base of Number_traits class.
			* @details This class contains basic information for 
			*          a number type
			* @tparam T the number type
			*/
		template<class T>
		struct Number_traits_core
		{

			/**
				* @brief is an integer type
				*/
			static const bool isInteger;

			/**
				* @brief The base type of the number
				* @details This is the primitive reprezentation
				*          of the given type. For example a \f$Z_3\f$
				*          field base type's is the unsigned
				*/
			typedef T BaseType;

			/**
				* @brief The precision of the type
				*/
			static const double precision;

			/**
				* @brief Additive unit element
				* @note default int 0
				*/
			static const T additiveUnit;

			/**
				* @brief multiplicative unit
				* @note default int 1
				*/
			static const T multiplicativeUnit;

			/**
				* @brief Safty conversion to other types
				* @tparam TO_TYPE the output type
				* @param number the number which will be converted
				* @return the converted number
				*/
			template<class TO_TYPE>
			static TO_TYPE convert(const T& number);

			/**
				* @brief Safty parse from other types
				* @tparam From_TYPE the input type
				* @param number the number which will be parsed
				* @return the parsed number
				*/
			template<class FROM_TYPE>
			static T parse(const FROM_TYPE& number);

			/**
			  * @brief Determines that the conversion is possible to base type
				* @details Default it is always true
				* @param number the given number
				* @return The Conversion is possible or not
				*/
			static bool isConvertableToBase(const T& number);

		};

		/**
			* @brief Number_traits class.
			* @details This class contains basic information for 
			*          a number type
			* @tparam T the number type
			*/
    template<class T>
    struct Number_traits: Number_traits_core<T>
    {
    };
	}
}

#include "number_traits_spec.h"
#include "number_traits.hpp"

#endif //__MATH__ALGEBRA__NUMBER_TRAITS_H

