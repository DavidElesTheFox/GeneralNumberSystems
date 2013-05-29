#ifndef __MATH__NUMBERSYSTEM__ABSTRACTPERIODICELEMENTCALCULATOR_H
#define __MATH__NUMBERSYSTEM__ABSTRACTPERIODICELEMENTCALCULATOR_H

/**
	* @file abstractperiodicelementcalculator.h
	* @brief Contains abstract class for periodic element calculation
	*/

#include "numbersystem.h"
#include "iperiodicelementcalculator.h"

namespace MATH
{
	namespace NumberSystem
	{

		/**
			* @brief Abstract periodic element calculator
			* @details This class is an interface for periodic element
			*          calculation. There are some different way for
			*          element calculation, and number system determination
			* @tparam INT_TYPE the integer representation
			* @tparam FLOAT_TYPE the float representation
			* @tparam Matrix the templated matrix type
			* @tparam Vector the templated vector type
			* @tparam MatrixNorm Matrix norm calculator class. It must have a calculateNorm static function
			* @tparam VectorNorm Vector norm calculator class. It must have a calculateNorm static function
			* @tparam matrix_traits the matrix traits class
			* @tparam vector_traits the vector traits class
			* @tparam number_traits the number traits class
			* @see MATH::Algebra::Number_traits
			* @see MATH::LinearAlgebra::matrix_traits
			* @see MATH::LinearAlgebra::vector_traits

			*/
		template <class INT_TYPE,
						  class FLOAT_TYPE,
							template<class T> class Matrix,
							template<class T> class Vector,
							template<class T> class MatrixNorm,
							template<class T> class VectorNorm,
							template<typename T, class M> class matrix_traits=
								MATH::LinearAlgebra::Matrix_traits,
							template<typename T, class V> class vector_traits=
							  MATH::LinearAlgebra::Vector_traits,
							template<typename T> class number_traits =
							  MATH::Algebra::Number_traits>
		class AbstractPeriodicElementCalculator
		  :public IPeriodicElementCalculator
			   <INT_TYPE,
				  FLOAT_TYPE,
					Matrix,
					Vector,
					matrix_traits,
					vector_traits,
					number_traits>
		{
			public:
				/* member types */
				/**
					* @brief typedef for the connected number system
					* @details this is the number system, which the 
					*          used by the algorithm.
					* @see NumberSystem
					*/
				typedef NumberSystem<INT_TYPE, FLOAT_TYPE,
													 Matrix, Vector,
													 matrix_traits, vector_traits,
													 number_traits> ConnectedNumberSystem;

				/**
					* @brief type of the connected digit set
					* @see ConnectedNumberSystem
					*/
				typedef typename ConnectedNumberSystem::DigitSet ConnectedDigitSet;

				typedef typename IPeriodicElementCalculator
			   <INT_TYPE,
				  FLOAT_TYPE,
					Matrix,
					Vector,
					matrix_traits,
					vector_traits,
					number_traits>::AbstractParameter AbstractParameter;

			protected:
				/* member types */
				/**
					* @brief Converter for Linear Algebra elements
					* @details INT_TYPE to FLOAT_TYPE
					* @see MATH::LinearAlgebra::Converter
					*/
				typedef MATH::LinearAlgebra::Converter<INT_TYPE, FLOAT_TYPE,
								                               vector_traits, matrix_traits,
																							 number_traits>
					I_F_Converter;
				/**
					* @brief Converter for LinearAlgebra elements
					* @details FLOAT_TYPE to INT_TYPE
					* @see MATH::LinearAlgebra::Converter
					*/
				typedef MATH::LinearAlgebra::Converter<FLOAT_TYPE,
								                               INT_TYPE,
																							 vector_traits,
																							 matrix_traits,
																							 number_traits>
					F_IConverter;

				/**
					* @brief integer typed vector;
					*/
				typedef Vector<INT_TYPE> IVector;

				/**
					* @brief Float typed vector
					*/
				typedef Vector<FLOAT_TYPE> FVector;

				/**
					* @brief Integer typed matrix
					*/
				typedef Matrix<INT_TYPE> IMatrix;

				/**
					* @brief float typed matrix
					*/
				typedef Matrix<FLOAT_TYPE> FMatrix;
				
				/**
					* @brief number traits for integers
					*/
				typedef number_traits<INT_TYPE>
					number_traits_int;
				
				/**
					* @brief number traits for floats
					*/
				typedef number_traits<FLOAT_TYPE>
					number_traits_float;

				/**
					* @brief matrix traits for integer matrices
					*/
				typedef matrix_traits<INT_TYPE, IMatrix> 
					matrix_traits_int;
				
				/**
					* @brief matrix traits for float pointed matrices
					*/
				typedef matrix_traits<FLOAT_TYPE, FMatrix> 
					matrix_traits_float;

				/**
					* @brief vector traits for integer vectors
					*/
				typedef vector_traits<INT_TYPE, IVector>
					vector_traits_int;

				/**
					* @brief vector traits for float pointed vectors
					*/
				typedef vector_traits<FLOAT_TYPE, FVector>
					vector_traits_float;

				/**
					* @brief Calculator for float matrices
					*/
				typedef MATH::LinearAlgebra::
					MatrixCalculator<FLOAT_TYPE, Matrix<FLOAT_TYPE>,
					                 matrix_traits_float, number_traits_float>
					MatrixCalculator_float;

				/**
					* @brief Calculator for integer matrices
					*/
				typedef MATH::LinearAlgebra::
					MatrixCalculator<INT_TYPE, Matrix<INT_TYPE>,
					                 matrix_traits_int, number_traits_float>
					MatrixCalculator_int;

				/**
				  * @brief Matrix norm calculator for INT types
					*/
				typedef MatrixNorm<INT_TYPE> MatrixNorm_int;

				/**
				  * @brief Matrix norm calculator for FLOAT types
					*/
				typedef MatrixNorm<FLOAT_TYPE> MatrixNorm_float;

				/**
					* @brief Calculator for vectors
					* @see MATH::LinearAlgebra::VectorCalculator
					*/
				typedef MATH::LinearAlgebra::
					VectorCalculator<FLOAT_TYPE, FVector,
					                 number_traits_float,
													 vector_traits_float>
					VectorCalculator_float;

				/**
					* @brief Calculator for vectors
					* @see MATH::LinearAlgebra::VectorCalculator
					*/
				typedef MATH::LinearAlgebra::
					VectorCalculator<INT_TYPE, IVector,
					                 number_traits_int,
													 vector_traits_int>
					VectorCalculator_int;

				/**
				  * @brief Vector norm calculator for INT types
					*/
				typedef VectorNorm<INT_TYPE> VectorNorm_int;

				/**
				  * @brief Vector norm calculator for FLOAT types
					*/
				typedef VectorNorm<FLOAT_TYPE> VectorNorm_float;

				/**
					* @brief Number calculator for the floating type
					*/
				typedef MATH::Algebra::
					NumberCalculator<FLOAT_TYPE,
					                 number_traits_float>
					NumCalc_float;

			protected:
				/**
					* @brief the connected number system
					*/
				const ConnectedNumberSystem* _ns;

				/**
					* @brief the focus point of the algorithm
					*/
			  Vector<INT_TYPE> _focusPoint;

			public:
				/* functions */
				/**
					* @brief Default constructor for PeriodicElementCalculators
					*/
				AbstractPeriodicElementCalculator(const ConnectedNumberSystem* ns);

				/**
					* @brief virtual destructor
					*/
				virtual ~AbstractPeriodicElementCalculator()
				{				}
				/**
					* @brief pure virtual function for periodic element searching.
					* @param params parameters of calculation
					*/
				virtual 
					ConnectedDigitSet calculatePeriodicElements
					  (const AbstractParameter& params) = 0; 

				/**
					* @brief determination, it is a number system or not
					*/
				virtual bool isNumberSystem() = 0;

			protected:

				/**
					* @brief default constructor due to inheritation
					*/
				AbstractPeriodicElementCalculator()
				{}

		};
	}
}

#include "abstractperiodicelementcalculator.hpp"

#endif //__MATH__NUMBERSYSTEM__ABSTRACTPERIODICELEMENTCALCULATOR_H

