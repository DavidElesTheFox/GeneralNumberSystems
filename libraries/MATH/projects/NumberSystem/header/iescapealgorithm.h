#ifndef MATH__NUMBERSYSTEM__IESCAPEALGORITHM_H
#define MATH__NUMBERSYSTEM__IESCAPEALGORITHM_H

#include <set>

#include <MATH/Algebra/number_traits.h>
#include <MATH/Algebra/numbercalculator.h>
#include <MATH/LinearAlgebra/vector_traits.h>
#include <MATH/LinearAlgebra/matrix_traits.h>
#include <MATH/LinearAlgebra/converter.h>
#include <MATH/LinearAlgebra/matrixcalculator.h>
#include <MATH/LinearAlgebra/vectorcalculator.h>

#include "numbersystem.h"

namespace MATH
{
	namespace NumberSystem
	{
		/**
			* @brief A Norm undependent interface for Escape algorithm to determines the H set
			* @details The H set is the fractional elements in the
			*          number system with 0 integer part.
			*          This algorithm similar the Madelbrot computation
			*          and this class use a convergencie border on the
			*          computation and iterate the element with the
			*          base of the given number system
			* @tparam INT_TYPE the integer representation
			* @tparam FLOAT_TYPE the float representation
			* @tparam Vector the templated vector type
			*/
		template<class INT_TYPE,
			       class FLOAT_TYPE,
						 template<class T> class Vector>
		class IEscapeAlgorithm
		{

			public:
				/**
					* @brief Float typed vector
					*/
				typedef Vector<FLOAT_TYPE> FVector;

				/**
					* @brief Simple constructor
					* @param ns The number system, which is used by the
					*           algorithm
					* @param convergencieBorder The special border of
					*           of the algorihm
					*/
				IEscapeAlgorithm()
        {}

        /**
          * @brief Virtual escape algorithm
          */
        virtual ~IEscapeAlgorithm()
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
				virtual void compute(const short xCoord,
							               const short yCoord,
							               int height,
							               int width,
							               unsigned**& convergencieMatrix,
							               FLOAT_TYPE zoom) = 0;

				virtual unsigned getSuggestion() const = 0;

				/**
					* @brief Getter for the focus point of the algorithm
					* @return Reference to the focus point
					*/
				virtual Vector<FLOAT_TYPE>& focusPoint() = 0;

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
				virtual void computeRectangle(FVector& v1,
						                          FVector& v3) = 0;
		};
	}
}
#endif

