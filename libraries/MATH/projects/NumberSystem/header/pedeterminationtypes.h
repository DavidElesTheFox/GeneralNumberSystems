#ifndef __MATH__NUMBERSYSTEM_PEDETERMINATIONTYPES_H
#define __MATH__NUMBERSYSTEM_PEDETERMINATIONTYPES_H

/**
	* @file pedeterminationtypes.h
	* @brief This class contains the determination algorihms
	*        for a system, that it is really a Number System
	*/

#include "abstractperiodicelementcalculator.h"
#include "numbersystem.h"
#include <Exceptions/runtimeexception.h>

/**
	* @brief tempolary helper macro for readable code
	*/
#define BASE AbstractPeriodicElementCalculator<INT_TYPE,      \
                                               FLOAT_TYPE,    \
																							 Matrix,        \
																							 Vector,        \
                                               MatrixNorm,    \
                                               VectorNorm,    \
																							 matrix_traits, \
																							 vector_traits, \
																							 number_traits> 

/**
	* @brief tempolary helper macro for readable code
	*/
#define DEF_TEMP template <class INT_TYPE,                     \
						               class FLOAT_TYPE,                   \
							             template<class T> class Matrix,     \
							             template<class T> class Vector,     \
                           template<class T> class MatrixNorm, \
                           template<class T> class VectorNorm, \
							             template<typename T, class M>       \
                             class matrix_traits,              \
							             template<typename T, class V>       \
                             class vector_traits,              \
							             template<typename T>                \
                             class number_traits>
namespace MATH
{
	namespace NumberSystem
	{
		/**
			* @brief The most simplier determination
			* @details It is the case, when there is no
			*          ansvare to the question
			*/
		DEF_TEMP
		class NullPEDeterminator: public virtual BASE
		{
			public:
				/**
					* @brief determination, it is a number system or not
					*/
				bool isNumberSystem()
				{
					throw Exceptions::RuntimeException("Cannot be determined"
							                     ", it is really a number system!");
				}
		};

		/**
			* @brief Simple NS determination class.
			* @details This determination is based 
			*          on the calculatePeriodicElements function. Neccessary
			*          that the calculate function doesn't use the parameter,
			*          and can find all of periodic elements.
			*/
		DEF_TEMP
		class SimplePEDeterminator: public virtual BASE
		{
			public:
				/**
					* @brief determination of the given system is number system or not.
					*/
				bool isNumberSystem()
				{
					return calculatePeriodicElements(typename BASE::AbstractParameter()).size() == 1;
				}
		};
	}
}

#undef BASE
#undef DEF_TEMP

#endif //__MATH__NUMBERSYSTEM_PEDETERMINATIONTYPES_H

