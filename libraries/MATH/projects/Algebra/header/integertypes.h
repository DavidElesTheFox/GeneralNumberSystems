#ifndef __MATH__ALGEBRA__INTEGERTYPES_H
#define __MATH__ALGEBRA__INTEGERTYPES_H

/**
	* @file integertypes.h
	* @brief Contains the type list of integer types
	*/

#include <loki/Typelist.h>

namespace MATH
{
	namespace Algebra
	{
		/**
			* @brief Basic integer types
			* @details If you want to expand this list
			*          don't modify, just use Loki append function
			* @see http://loki-lib.sourceforge.net/index.php?n=Main.HomePage
			*/
		typedef Loki::TL::MakeTypelist<int,
						                       unsigned,
															     char,
															     unsigned char,
															     short,
															     unsigned short,
															     long,
															     unsigned long>::Result IntegerTypes;

		/**
			* @brief Simple function to determine a type, that is integer
			*        or not.
			* @note This operation bases on Loki library
			*/
		template<class T>
		struct IsInteger
		{
			enum { value = Loki::TL::IndexOf<IntegerTypes, T>::value >= 0 };
		};

	}
}


#endif //__MATH__ALGEBRA__INTEGERTYPES_H

