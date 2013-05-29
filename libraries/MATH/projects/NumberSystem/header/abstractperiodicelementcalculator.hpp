#ifndef __MATH__NUMBERSYSTEM__ABSTRACTPERIODICELEMENTCALCULATOR_H
#error use without header
#endif


namespace MATH
{
	namespace NumberSystem
	{
    template <class INT_TYPE,
						  class FLOAT_TYPE,
							template<class T> class Matrix,
							template<class T> class Vector,
							template<class T> class MatrixNorm,
							template<class T> class VectorNorm,
							template<typename T, class M> class matrix_traits,
							template<typename T, class V> class vector_traits,
							template<typename T> class number_traits>
		AbstractPeriodicElementCalculator<INT_TYPE,
		                                  FLOAT_TYPE,
																			Matrix,
																			Vector,
																			MatrixNorm, 
																			VectorNorm,
																			matrix_traits,
																			vector_traits,
																			number_traits>::
		  AbstractPeriodicElementCalculator(const ConnectedNumberSystem* ns)
			  :_ns(ns),
				 _focusPoint(matrix_traits_int::getRowNum(ns->getBase()))
		{		}
	
	}
}
