#ifndef __MATH__NUMBERSYSTEM_NUMBERSYSTEM_H
#define __MATH__NUMBERSYSTEM_NUMBERSYSTEM_H

#include <algorithm>
#include <vector>

#include <Exceptions/runtimeexception.h>

#include <MATH/LinearAlgebra/matrix_traits.h>
#include <MATH/LinearAlgebra/vector_traits.h>
#include <MATH/LinearAlgebra/converter.h>
#include <MATH/LinearAlgebra/matrixcalculator.h>
#include <MATH/LinearAlgebra/smithnormalform.h>
#include <MATH/LinearAlgebra/adjointmatrix.h>

#include <MATH/Algebra/number_traits.h>
#include <MATH/Algebra/numbercalculator.h>

/**
	* @file numbersystem.h
	* @brief Containes templated NumberSystem class
	* @see MATH::NumberSystem::NumberSystem
	*/


namespace MATH
{
	namespace NumberSystem
	{
		/**
			* @brief Template class, which represents a general number system,
			*        in a vector-field.
			* @details This class contains a complex algorith, which can
			*          compute a given vector digits in the given vetor field,
			*          and can compute a Vector, from it's digits.
			* @tparam INT_TYPE integer type of the vector field.
			* @tparam FLOAT_TYPE float-point number type of vector field
			* @tparam Matrix the matrix representation type, must be template
			* @tparam Vector the vector representation type, must be template
			* @tparam matrix_traits matrix traits for the matrices
			* @tparam number_traits traits for number types
			* @tparam vector_traits vector traits for vectors
			* @see MATH::LinearAlgebra::Matrix_traits
			* @see MATH::LinearAlgebra::Vector_traits
			* @see MATH::Algebra::Number_traits
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
		class NumberSystem
		{
			public:
				/* member types */
				/**
					* @brief Type for digit set
					* @warning It's not a bug! Digit set not a set
					*          it's a vector due to performance reasons.
					*/
				typedef std::vector< Vector<INT_TYPE> > DigitSet;

				/**
					* @brief DigitSet const iterator
					*/
				typedef typename DigitSet::const_iterator DigitSet_const_iterator;

					/**
					* @brief Finder functor for finding digits
					*/
				struct DigitFinder
				{
					/**
						* @brief the looking for element
						*/
					Vector<INT_TYPE> value;
					/**
						* @brief simple constructor
						* @param v the looked for element
						*/
					DigitFinder(const Vector<INT_TYPE>& v):value(v)
					{ 	}

					/**
						* @brief functor
						* @param act the actual element in the
						*        collection
						* @return theire are equals according
						*         the number traits
						*/
					bool operator() (const Vector<INT_TYPE>& act)
					{
						return vector_traits_int::equals(act, value);
					}
				};

        /**
          * @brief Base properties of a number system
          */
        enum BaseProperties
        {
          EXPANSIVE = 1,
          REGULAR = 2,
          DETERMINANT_NOT_ONE = 4,
          CONGRUENT_DIGITSET = 8
        };
			private:
				/* member types */
				/**
					* @brief Hash set for digit sashes
					* @see hash
					*/
				typedef std::map<INT_TYPE, unsigned> HashSet;

				/**
					* @brief Hash set const iterator
					*/
				typedef typename HashSet::const_iterator HashSet_const_iterator;
				
				/**
					* @brief matrix traits for integer matrices
					*/
				typedef matrix_traits<INT_TYPE, Matrix<INT_TYPE> > 
					matrix_traits_int;
				
				/**
					* @brief matrix traits for float pointed matrices
					*/
				typedef matrix_traits<FLOAT_TYPE, Matrix<FLOAT_TYPE> > 
					matrix_traits_float;

				/**
					* @brief vector traits for integer vectors
					*/
				typedef vector_traits<INT_TYPE, Vector<INT_TYPE> >
					vector_traits_int;

				/**
					* @brief vector traits for float pointed vectors
					*/
				typedef vector_traits<FLOAT_TYPE, Vector<FLOAT_TYPE> >
					vector_traits_float;

				/**
					* @brief number traits for integers
					*/
				typedef number_traits<INT_TYPE>
					number_traits_int;

				/**
					* @brief number traits for float types
					*/
				typedef number_traits<FLOAT_TYPE>
					number_traits_float;

				/**
					* @brief Calculator for numbers
					* @see MATH::Algebra::NumberCalculator
					*/
				typedef MATH::Algebra::NumberCalculator
					<
					  INT_TYPE,
					  number_traits_int
					>
					NumCalc_int;

				/**
					* @brief Integer vectors
					*/
				typedef Vector<INT_TYPE> IVector;

				/**
					* @brief Float type Vector
					*/
				typedef Vector<FLOAT_TYPE> FVector;

				/**
					* @brief Integer matrix
					*/
				typedef Matrix<INT_TYPE> IMatrix;

				/**
					* @brief Float type matrix
					*/
				typedef Matrix<FLOAT_TYPE> FMatrix;

				/**
					* @brief converter for LinearAlgebra elements
					* @details INT_TYPE to FLOAT_TYPE
					* @see MATH::LinearAlgebra::Converter
					*/
				typedef MATH::LinearAlgebra::Converter<INT_TYPE,
								                               FLOAT_TYPE,
																							 vector_traits,
																							 matrix_traits,
																							 number_traits>
					I_FConverter;

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
					* @brief Matrix calculator for integer types
					* @see MATH::LinearAlgebra::MatrixCalculator
					*/
				typedef MATH::LinearAlgebra::
					MatrixCalculator<INT_TYPE,
					                 Matrix<INT_TYPE>,
													 matrix_traits_int,
													 number_traits_int>
				  IMCalculator;

				/**
					* @brief Matrix calculator for integer types
					* @see MATH::LinearAlgebra::MatrixCalculator
					*/
				typedef MATH::LinearAlgebra::
					MatrixCalculator<FLOAT_TYPE,
					                 Matrix<FLOAT_TYPE>,
													 matrix_traits_float,
													 number_traits_float>
				  FMCalculator;

				/**
					* @brief Integer Smith normal form
					* @see MATH::LinearAlgebra::SmithNormalForm
					*/
				typedef MATH::LinearAlgebra::
					SmithNormalForm<INT_TYPE, Matrix<INT_TYPE>,
					                matrix_traits_int,
													number_traits_int>
					IntSmithNormalForm;

				/**
					* @brief int adjoint matrix
					* @see MATH::LinearAlgebra::AdjointMatrix
					*/
				typedef MATH::LinearAlgebra::
					AdjointMatrix<INT_TYPE, Matrix<INT_TYPE>, matrix_traits_int>
					IntAdjointMatrix;

      public:
        /**
          * @brief Exception id for property errors
          */
        static int PROP_EXC_ID;

			private:
				/* members */
				/**
					* @brief Left transformation matrix of base matrix
					*        Smith normal form
					* @see MATH::LinearAlgebra::SmithNormalForm
					*/
				Matrix<INT_TYPE> _U;
				/**
					* @brief Smith normal form
					* @see MATH::LinearAlgebra::SmithNormalForm
					*/
				Matrix<INT_TYPE> _G;

				/**
					* @brief The border where the non zero values are began in 
					*        the smith normal form
					*/
				int _border;

				/**
					* @brief hashset of digits
					*/
				HashSet _tableHash;
				/**
					* @brief digit set
					*/
				DigitSet _set;

				/**
					* @brief base of number system
					*/
				Matrix<INT_TYPE> _base;

				/**
					* @brief inverse of the base Matrix
					*/
				Matrix<FLOAT_TYPE> _baseInverse;
			
			public:
				/* functions */
				/**
					* @brief Constructor
					* @param base The base of number system
					* @param digits digi set of number system
          * @param checkBaseProperties enable to check properies
          * @throw Exceptions::RuntimeException At base property error
					*/
				NumberSystem(const Matrix<INT_TYPE>& base,
						         const DigitSet digits,
                     const bool checkProperties = true);

				/**
					* @brief chop the first digit of z.
					* @details I show an example of chop in a simple 
					*          number system. 
					*          I have a number in integer number system
					*          with base 10: \f$13978\f$.
					*          Then the \f$ chop(13978) = 1397\f$.
					*          There are a theorem, that in a number
					*          system always exists a digit (\f$a_j\f$) that
					*          \f[ M \| z - a_j \f] 
					* @note Of course ve can determine a number dinamical path
					* @param z the given "number"
					* @return the choped "number"
					* @see getDigits
					*/
				Vector<INT_TYPE> chop(const Vector<INT_TYPE>& z) const;

				/**
					* @brief This function determines the digits of an number
					* @param z the given number
					* @return A digit set which contains the digit of element.
					*         For example 123 the the digitset contents:
					*         <ul>
					*           <li> 0.: 123 </li>
					*           <li> 1.: 12 </li>
					*           <li> 2.: 1 </li>
					*         </ul> 
					*/
				DigitSet getDigits(const Vector<INT_TYPE>& z) const;

				/**
					* @brief Getter for the base of the number system
					* @return the base of the number system
				  */
				Matrix<INT_TYPE> getBase() const;

				/**
					* @brief Getter for the DigitSet of the number system
					* @return the digit set of the number system
					*/
				DigitSet getDigitSet() const;

				/**
					* @brief Getter for the base inverse
					* @return inverse matrix of base matrix
					*/
				Matrix<FLOAT_TYPE> getBaseInverse() const;

        /**
          * @brief checks the basic number system properties
          * @details There are a theorem about number systems.
          *          If a system is number system, than the base
          *          matrix is regular, expansive, and 
          *          \f$|I - M| \ne \pm 1\f$
          * @return true if all properties are ok.
          */
        BaseProperties calculateBaseProperties() const;

			private:
				/* functions */
				/**
					* @brief This function calculates the members' values.
					* @details This function similar to a constructor, 
					*          In case of more constructor you can call
					*          this function for default tasks.
					* @warning It's needed the digits and the base
					* @todo use MatrixCalculator calculate inverse
					*/
				void compute();

				/**
					* @brief No default constructor for Number systems
					*/
				NumberSystem()
				{ 	}

				/**
					* @brief Calculate the border of relevant element
					*        in the smith normal form
					*/
				void setBorder();

				/**
					* @brief Creation of hash table
					*/
				void createHashTable();

				/**
					* @brief Product the minor elements in the _G Matrix
					*        until the to element, from the border + 1.
					* @param to the latest + 1 element id
					* @return The product of the specific element
					*/
				INT_TYPE minorProduct(const int to) const;

				/**
					* @brief hash table check function.
          * @details Enough check that hash table hasn't multiple element
          *          and the size is equals the dimension
					* @return false if the Digits aren't full CRS.
					*/
				bool checkHashTable() const;

			protected:
				/* functions */
				/**
					* @brief This function find the first digit of a "number"
					* @param z the given number
					* @see chop
					* @return a digit.
          * @todo Realy use hash
					*/
				Vector<INT_TYPE> findDigit(const Vector<INT_TYPE>& z) const;

				/**
					* @brief Hash function for digit searching.
					* @param z the given number
					* @return the hash value
          * @todo Is it correct with positive mod?
					*/
				INT_TYPE hash(const Vector<INT_TYPE>& z) const;

		};
			       
	}
}

#include "numbersystem.hpp"

#endif // __MATH__NUMBERSYSTEM_NUMBERSYSTEM_H

