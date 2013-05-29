#ifndef MATH__NUMBERSYSTEM__IPERIODICELEMENTCALCULATOR_H
#define MATH__NUMBERSYSTEM__IPERIODICELEMENTCALCULATOR_H

/**
  * @file iperiodicelementcalculator.h
	* @brief This file contains an norm independent base class for  periodic element calculators
	*/

namespace MATH
{
	namespace NumberSystem
	{
		/**
		  * @brief Norm independent base class for pe-calculators.
			* @tparam INT_TYPE the integer representation
			* @tparam FLOAT_TYPE the float representation
			* @tparam Matrix the templated matrix type
			* @tparam Vector the templated vector type
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
							template<typename T, class M> class matrix_traits=
								MATH::LinearAlgebra::Matrix_traits,
							template<typename T, class V> class vector_traits=
							  MATH::LinearAlgebra::Vector_traits,
							template<typename T> class number_traits =
							  MATH::Algebra::Number_traits>
		class IPeriodicElementCalculator
		{
			public:

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

				/**
					* @brief Abstract parameter for calculation
					*/
				struct AbstractParameter
				{
					/**
						* @brief Virtual destructor
						* It is neccessary dou to polimorfism
						*/
					virtual ~AbstractParameter()
					{}
				};
			public:

				/**
				  * @brief Simple constructor
					*/
				IPeriodicElementCalculator()
				{ }

				/**
				  * @brief virtual destructor
					*/
				virtual ~IPeriodicElementCalculator()
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
		};
	}
}

#endif

