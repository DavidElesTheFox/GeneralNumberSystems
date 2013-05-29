#ifndef __MATH__NUMBERSYSTEM__PECALCULATORS_H
#define __MATH__NUMBERSYSTEM__PECALCULATORS_H

#include <MATH/LinearAlgebra/matrix_traits.h>
#include <MATH/LinearAlgebra/vector_traits.h>
#include <MATH/Algebra/number_traits.h>
#include "abstractperiodicelementcalculator.h"
#include "pecalculationtypes.h"
#include "pedeterminationtypes.h"

#define TEMP_PAR <INT_TYPE,\
FLOAT_TYPE,\
Matrix,\
Vector,\
MatrixNorm,\
VectorNorm,\
matrix_traits,\
vector_traits,\
number_traits>

/**
	* @file pecalculators.h
	* @brief Periodic element calculator types are located here
	*/

namespace MATH
{
	namespace NumberSystem
	{
		/**
			* @brief The simplest Periodic element calculator
			* @details This calculation mode is based on a simple tree
			*          (reverse tree)
			* @see SimpleGraphPECalculator
			* @see NullPEDeterminator
			*/
		template <class INT_TYPE,
						  class FLOAT_TYPE,
							template<class T> class Matrix,
              template<class T> class Vector,
							template<class T> class MatrixNorm,
							template<class T> class VectorNorm,
							template<typename T, class M>
                class matrix_traits
								        = MATH::LinearAlgebra::Matrix_traits,
							template<typename T, class V>
                class vector_traits
                        = MATH::LinearAlgebra::Vector_traits,
							template<typename T>
							  class number_traits\
                        = MATH::Algebra::Number_traits>
		class TreePECalculator:
		  public SimpleGraphPECalculator TEMP_PAR,
			public NullPEDeterminator TEMP_PAR
		{
			public:
				/**
					* @brief Simple constructor
					* @param ns the connected number system
					* @see AbstractTreePlanePECalculator
					*/
				TreePECalculator(const typename TreePECalculator::ConnectedNumberSystem* ns):
					AbstractPeriodicElementCalculator TEMP_PAR(ns)
				{				}
		};

		/**
			* @brief A Periodic element calculator
			* @details It's based on a graph, which has multiple 
			*          elements
			* @see SimpleGraphPECalculator
			* @see NullPEDeterminator
			*/
		template <class INT_TYPE,
						  class FLOAT_TYPE,
							template<class T> class Matrix,
              template<class T> class Vector,
							template<class T> class MatrixNorm,
							template<class T> class VectorNorm,
							template<typename T, class M>
                class matrix_traits
								        = MATH::LinearAlgebra::Matrix_traits,
							template<typename T, class V>
                class vector_traits
                        = MATH::LinearAlgebra::Vector_traits,
							template<typename T>
							  class number_traits\
                        = MATH::Algebra::Number_traits>
		class GraphPECalculator:
		  public FasterGraphPECalculator TEMP_PAR,
			public NullPEDeterminator TEMP_PAR
		{
			public:
				/**
					* @brief Simple constructor
					* @param ns the connected number system
					* @see AbstractTreePlanePECalculator
					*/
				GraphPECalculator(const typename GraphPECalculator::ConnectedNumberSystem* ns):
					AbstractPeriodicElementCalculator TEMP_PAR(ns)
				{				}
		};

		/**
			* @brief A Periodic element calculator
			* @details This calculator can determine the number system 
			*          property, and works in multi-dimensional case.
			* @see FullPECalculator
			* @see SimplePEDeterminator
			*/
		template <class INT_TYPE,
						  class FLOAT_TYPE,
							template<class T> class Matrix,
              template<class T> class Vector,
							template<class T> class MatrixNorm,
							template<class T> class VectorNorm,
							template<typename T, class M>
                class matrix_traits
								        = MATH::LinearAlgebra::Matrix_traits,
							template<typename T, class V>
                class vector_traits
                        = MATH::LinearAlgebra::Vector_traits,
							template<typename T>
							  class number_traits\
                        = MATH::Algebra::Number_traits>
		class PECalculator:
		  public FullPECalculator TEMP_PAR,
			public SimplePEDeterminator TEMP_PAR
		{
			public:
				/**
					* @brief Simple constructor
					* @param ns the connected number system
					* @see AbstractTreePlanePECalculator
					*/
				PECalculator(const typename PECalculator::ConnectedNumberSystem* ns):
				  AbstractPeriodicElementCalculator TEMP_PAR(ns)
				{				}
		};
	}
}

#undef TEMP_PAR

#endif //__MATH__NUMBERSYSTEM__PECALCULATORS_H

