#ifndef __MATH__NUMBERSYSTEM__ESCAPEALGORITHM_H
#define __MATH__NUMBERSYSTEM__ESCAPEALGORITHM_H

#include <set>

#include <MATH/Algebra/number_traits.h>
#include <MATH/Algebra/numbercalculator.h>
#include <MATH/LinearAlgebra/vector_traits.h>
#include <MATH/LinearAlgebra/matrix_traits.h>
#include <MATH/LinearAlgebra/converter.h>
#include <MATH/LinearAlgebra/matrixcalculator.h>
#include <MATH/LinearAlgebra/vectorcalculator.h>

#include "numbersystem.h"
#include "numbersystemcalculator.h"
#include "iescapealgorithm.h"

namespace MATH
{
	namespace NumberSystem
	{
		/**
			* @brief An Escape algorithm to determines the H set
			* @details The H set is the fractional elements in the
			*          number system with 0 integer part.
			*          This algorithm similar the Madelbrot computation
			*          and this class use a convergencie border on the
			*          computation and iterate the element with the
			*          base of the given number system
			* @tparam INT_TYPE the integer representation
			* @tparam FLOAT_TYPE the float representation
			* @tparam Matrix the templated matrix type
			* @tparam Vector the templated vector type
			* @tparam VectorNorm The norm calculator class. It must have a calculateNorm static function.
			* @tparam MatrixNorm The corresponding matrix norm for the vector norm. It must have too a calculateNorm Static function
			* @tparam matrix_traits the matrix traits class
			* @tparam vector_traits the vector traits class
			* @tparam number_traits the number traits class
			* @see MATH::Algebra::Number_traits
			* @see MATH::LinearAlgebra::matrix_traits
			* @see MATH::LinearAlgebra::vector_traits
			*/
		template<class INT_TYPE,
			       class FLOAT_TYPE,
						 template<class T> class Matrix,
						 template<class T> class Vector,
						 template<class T> class VectorNorm,
						 template<class T> class MatrixNorm,
						 template<class T, class M> class matrix_traits
							 = MATH::LinearAlgebra::Matrix_traits,
						 template<class T, class V> class vector_traits
							 = MATH::LinearAlgebra::Vector_traits,
						 template<class T> class number_traits 
							 = MATH::Algebra::Number_traits>
		class EscapeAlgorithm
      :public IEscapeAlgorithm<INT_TYPE,
                               FLOAT_TYPE,
                               Vector>
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

			private:
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
				  * @brief Matrix norm calculator for FLOAT types
					*/
				typedef MatrixNorm<FLOAT_TYPE> MatrixNorm_float;

				/**
				  * @brief Vector norm calculator for INT types
					*/
				typedef VectorNorm<FLOAT_TYPE> VectorNorm_float;

				/**
					* @brief Calculator for floats
					*/
				typedef MATH::Algebra::
					NumberCalculator<FLOAT_TYPE,
					                 number_traits_float>
					NumCalc_float;

				/**
					* @brief Calculator for ints
					*/
				typedef MATH::Algebra::
					NumberCalculator<INT_TYPE,
					                 number_traits_int>
					NumCalc_int;

        /**
          * @brief Number system calculator
          */
        typedef NumberSystemCalculator<INT_TYPE,
                                       FLOAT_TYPE,
                                       Matrix,
                                       Vector,
                                       VectorNorm,
                                       MatrixNorm,
                                       matrix_traits,
                                       vector_traits,
                                       number_traits>
          NumSysCalc;
					                       
			protected:
				/* members */
				/**
					* @brief the number system 
				  */
				const ConnectedNumberSystem* _ns;

				/**
					* @brief convergence border of the algorhitm 
				  */
				unsigned _convBorder;

				/**
				  * @brief the suggestion for the border
					* @details this number the best border, which isn't
					*          harmfull for the result
					* @see _convBorder
				 */
				unsigned _suggestion;

				/**
				  * @brief the focus point of the algorithm
				  */
				Vector<FLOAT_TYPE> _focusPoint;
			public:
				/* Functions */

				/**
					* @brief Simple constructor
					* @param ns The number system, which is used by the
					*           algorithm
					* @param convergencieBorder The special border of
					*           of the algorihm
					*/
				EscapeAlgorithm(const ConnectedNumberSystem* ns,
						            const unsigned convergencieBorder);

        /**
          * @brief Simple destructor, for polimorphysm
          */
        virtual ~EscapeAlgorithm()
        {}

				/**
					* @brief computation of the convergencie Matrix
					* @details this function use the escape algorith
					*          in a given subspace and determines, 
					*          the convergation speed to elements.
					* @param xCoord one coordinate of the subspace 
					* @param yCoord another coordinate of the subspace
					* @param height height of the convergencieMatrix
					* @param width width of the convergencieMatrix
					* @param convergencieMatrix output parameter
					*               this matrix will be loaded with
					*               the convergencie speed of the
					*               each element in the specific range
					*               (where the H maybe located)
					* @param zoom the percent of the zoom meassure
					*/
				void compute(const short xCoord,
							 const short yCoord,
							 int height,
							 int width,
							 unsigned**& convergencieMatrix,
							 FLOAT_TYPE zoom = 1.0);

				/**
					* @brief Getter for the suggestion to the border.
					* @details This is a suggestion, if you use
					*          this value for convergence border the 
					*          precision of the H set won't be changed.
					* @return the suggestion
					*/
				unsigned getSuggestion() const
				{
					return _suggestion;
				}

				/**
					* @brief Getter for the focus point of the algorithm
					* @return Reference to the focus point
					*/
				Vector<FLOAT_TYPE>& focusPoint()
				{
					return _focusPoint;
				}

				/**
					* @brief This function calculates the rectangle which contains 
					*        the H set
					* @details M is a expansive matrix soo there is a \f$C\in N\f$
					*          that \f$ \|M^{(-C)}\|_\infty < 1 \f$ and we can estimate
					*          the border of the H set. 
					*          \f[ 
					*            \gamma = \frac{1}{1-\|M^{(-C)}\|_\infty}
					*          \f]
					*          And let's see the following vectors:
					*          \f[
					*            \xi_m^{(j)}:= max_{a \in D} |c_m^{(j)}(a)|
					*          \f]
					*          Where \f$ c_m^{(j)} = (M^{-j}a)_m \f$. Now a 
					*          upper estimate of the H set's border:
					*          \f[
					*            \alpha_m = \lceil 
					*                          \gamma \sum_{j=1}^C\xi_m^{(j)}
					*												\rceil
					*          \f]
					*          The lower estimate derivable in a same way
					* @param v1 output parameter, one side of the rectangle
					* @param v3 output paramater, the other side of the rectangle
					*/
				void computeRectangle(FVector& v1,
						                  FVector& v3);

			private:
				/**
					* @brief helper function for computation of rectangle
					* @details This function computes the 
					*          \f$ \sum_{j=1}^C\xi_m^{(j)} \f$ to upper estimate
					*          to v2 and a lover estimate which is based on the
					*          mentioned algorithm.
					* @see computeRectangle
					* @param v2 almost the left down corner of the rectangle
					* @param v4 almost the right up corner of the rectangle
					* @param minNorm The smallest power of the base matrix
					*                inverse, where its norm smoller then 1
					* @param dimension the dimension of the base matrix
					*/
				void rectangleComputeCore(FVector& v2,
												          FVector& v4,
												          const int dimension,
																	const int minNorm);
		};
	}
}
#include "escapealgorithm.hpp"

#endif // __MATH__NUMBERSYSTEM__ESCAPEALGORITHM_H
