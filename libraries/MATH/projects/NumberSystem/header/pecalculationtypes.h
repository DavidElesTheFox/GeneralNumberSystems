#ifndef __MATH__NUMBERSYSTEM__PECALCULATIONTYPES
#define __MATH__NUMBERSYSTEM__PECALCULATIONTYPES

/**
	* @file pecalculationtypes.h
	* @brief This file contains the different calculation
	*        operators for periodic element calculation
	* @see abstractperiodicelementcalculator
	*/

#include "abstractperiodicelementcalculator.h"
#include "numbersystem.h"
#include "numbersystemcalculator.h"

#include <MATH/Graphs/reversetree.h>
#include <MATH/Graphs/forest.h>
#include <Exceptions/runtimeexception.h>
#include <Exceptions/parameterexception.h>
#include <MATH/LinearAlgebra/converter.h>

#include <MATH/LinearAlgebra/matrix_traits.h>
#include <MATH/LinearAlgebra/vector_traits.h>
#include <MATH/Algebra/number_traits.h>

/**
	* @brief tempolary helper macro for readable code
	*/
#define DEF_TEMP template <class INT_TYPE,                          \
						               class FLOAT_TYPE,                        \
							             template<class T> class Matrix,          \
							             template<class T> class Vector,          \
                           template<class T> class MatrixNorm,      \
                           template<class T> class VectorNorm,      \
							             template<typename T, class M>            \
                             class matrix_traits                    \
                               = MATH::LinearAlgebra::Matrix_traits,\
							             template<typename T, class V>            \
                             class vector_traits                    \
                               = MATH::LinearAlgebra::Vector_traits,\
							             template<typename T>                     \
                             class number_traits                    \
                               = MATH::Algebra::Number_traits>


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

namespace MATH
{
	namespace NumberSystem
	{
		/*************************************************************/
		/*             AbstracrPlanePECalculator                     */
		/*************************************************************/

		/**
			* @brief Abstract calculator, where only search periodic
			*        element in a specific plane
			*/
		DEF_TEMP
		class AbstractPlanePECalculator: public virtual BASE
		{
			public:
				
				/**
					* @brief Parameters of calculation
					*/
				struct Parameter: BASE::AbstractParameter
			  {
					/**
						* @brief simple constructor
						* @param number1 A vector in the given plane
						* @param number2 a perpendicular vector to number1
						* @param xCoord a coordinate of the plane
						* @param yCoord a coordinate of the plane
						* @param stepDistance the step distance of the algorithm
						* @param height the number of iteration in y coord
						* @param width the number of iteration in x coord
						* @param circles the periodic element map. Output parameter
						*/
					Parameter(const Vector<INT_TYPE>& number1,
							      const Vector<INT_TYPE>& number2,
										const unsigned short xCoord,
										const unsigned short yCoord,
										const INT_TYPE& stepDistance,
										const int height,
										const int width,
										int** circles = 0):
						vector1(number1),
						vector2(number2),
						xCoord(xCoord),
						yCoord(yCoord),
						stepDistance(stepDistance),
						height(height),
						width(width),
						circles(circles)
					{}

					/**
						* @brief default constructor
						*/
					Parameter()
					{}

					virtual ~Parameter()
					{}
					/**
						* @brief A vector in the given plane
						*/
					Vector<INT_TYPE> vector1;
					/**
						* @brief a perpendicular vector to vector1
						*/
					Vector<INT_TYPE> vector2;
					/**
						* @brief a coordinate of the plane
						* @details That parameter will be determine
						*          the sub space.
						*/
					unsigned short xCoord;
					/**
						* @brief a coordinate of the plane
						* @details That parameter will be determine
						*          the sub space.
						*/
					unsigned short yCoord;

					/**
						* @brief the step distance of the algorithm
						* @note if it is one, that means all element
						*/
					INT_TYPE stepDistance;
					/**
						* @brief the number of iteration in y coords
						*/
					int height;
					/**
						* @brief the number of iteration in x coords
						*/
					int width;

					/**
						* @brief an output parameter
						* @details This dimension is height x width, and
						*          it will contains an id, that which element
						*          belonge to which periodic element
						*/
					int** circles;
			  };
			protected:
				/**
					* @brief parameters of algorithm
					* The parameter of the last running
					*/
				Parameter _params;
			public:
				/**
					* @brief The periodic element finder function
					* @details This function upload the _elementForest, without
					*          edge multiplication
					* @warning it is a very slow algorithm, dou to the element
					*          insertation to the specific tree
					*/
				virtual typename BASE::ConnectedDigitSet calculatePeriodicElements
					  (const typename BASE::AbstractParameter& parameters);

			protected:
				/**
					* @brief this function determines which periodic element belong
					*        to the actual elemnt
					* @param act the actual element
					* @param i the x discrate coordinate of the actual field
					* @param j the y discrate coordinate of the actual field
					* @param sizeX the maximum window width
					* @param sizeY the maximum window height
					*/
				virtual void calcPeriodicElement(const typename BASE::IVector& act,
						                             const int i,
																				 const int j,
																				 const int sizeX,
																				 const int sizeY) = 0;

				/**
					* @brief Getter function for actual calculated periodic elements
					* @return the periodic elements in the cashe.
					*/
				virtual typename BASE::ConnectedDigitSet getActualPeriodicElements() = 0;

				/**
					* @brief initialize function for calculation
					*/
				virtual void initCalc()
				{};

		};
		/*************************************************************/
		/*             AbstractTreePlanePECalculator                 */
		/*************************************************************/

		/**
			* @brief An abstract calculator for plane calculator, where
			*        we using a graph.
			*/        
		DEF_TEMP
		class AbstractTreePlanePECalculator: 
			public AbstractPlanePECalculator<INT_TYPE,      
																			 FLOAT_TYPE,    
																			 Matrix,        
																			 Vector,        
																			 MatrixNorm,
																			 VectorNorm,
																			 matrix_traits, 
																			 vector_traits, 
																			 number_traits> 

		{
			public:
				/**
					* @brief Reverse tree of Integer element
					*/
				typedef MATH::Graphs::ReverseTree< Vector<INT_TYPE> >
					ElementTree;
				/**
					* @brief Forest of Integer Vectors
					* @see MATH::Graphs::Forest
					* @see MATH::Graphs::ReverseTree
					*/
				typedef MATH::Graphs::Forest<Vector<INT_TYPE>,
																		 ElementTree> ElementForest;

			protected:
				/**
					* @brief Forset of iterated elements
					* @details This forest contains reverse trees,
					*          where the root element is the periodic element.
					*          So the number of trees in the forest is the same 
					*          the periodic elements number, and the root of the
					*          trees a periodic element.
					*/
				ElementForest _elementForest; 
			public:

				/**
					* @brief Getter for the finished graph
					* @return a graph, which contains the iteration graph
					*/
				const ElementForest* getElementForest() const 
				{ return &_elementForest; }

			protected:
				/**
					* @brief this function determines which periodic element belong
					*        to the actual elemnt
					* @param act the actual element
					* @param i the x coordinate in the plane
					* @param j the y coordinate in the plane
					* @param sizeX the maximum window width
					* @param sizeY the maximum window height
					*/
				void calcPeriodicElement(const typename BASE::IVector& act,
						                     const int i,
																 const int j,
																 const int sizeX,
																 const int sizeY);

				/**
					* @brief Getter function for actual calculated periodic elements
					* @return the periodic elements in the cashe.
					* @note after this function calling the element forest will be empty!
					*/
				typename BASE::ConnectedDigitSet getActualPeriodicElements();

				/**
					* @brief initialize function for calculation
					*/
				void initCalc()
				{
					_elementForest.clear();
				}
				/**
					* @brief Upload function for tree
					* @details this function upload the tree,
					*          or update the element forest
					* @param act the actual vector
					* @param tree the uploaded tree
					* @param i the x coordinate in the plane
					* @param j the y coordinate in the plane
					* @param sizeX the maximum window width
					* @param sizeY the maximum window height
					* @return true if we find a perdiodic element
					*/
				virtual bool uploadTree(typename BASE::IVector& act,
						                    ElementTree& tree,
																const int i,
																const int j,
																const int sizeX,
																const int sizeY) = 0;
		};

		/*************************************************************/
		/*             SimpleGraphPECalculator                       */
		/*************************************************************/

/**
	* @brief tempolary helper macro for readable code
	*/
#define ABS_TREE_PLANE_PE_CALC AbstractTreePlanePECalculator \
  <INT_TYPE,      \
   FLOAT_TYPE,    \
   Matrix,        \
   Vector,        \
	 MatrixNorm,    \
	 VectorNorm,    \
   matrix_traits, \
   vector_traits, \
   number_traits> 

		/**
			* @brief A Periodic element calculator, which result
			*        a simple graph
			* @details This periodic element calculation mode
			*          use a simple graph (whithout multiple edges),
			*          but search element only a given plane
			* @note This is a slow algorithm
			*/
		DEF_TEMP
		class SimpleGraphPECalculator: 
			public AbstractTreePlanePECalculator<INT_TYPE,      
																					 FLOAT_TYPE,    
																					 Matrix,        
																					 Vector,        
																					 MatrixNorm,
																					 VectorNorm,
																					 matrix_traits, 
																					 vector_traits, 
																					 number_traits> 
		{
			protected:
				/**
					* @brief Upload function for tree
					* @details this function upload the tree,
					*          or update the element forest
					* @param act the actual vector
					* @param tree the uploaded tree
					* @param i the x coordinate in the plane
					* @param j the y coordinate in the plane
					* @param sizeX the maximum window width
					* @param sizeY the maximum window height
					* @return true if we find a perdiodic element
					*/
				bool uploadTree(typename BASE::IVector& act,
				  typename ABS_TREE_PLANE_PE_CALC::ElementTree& tree,
					const int i,
					const int j,
				  const int sizeX,
				  const int sizeY);
		};



		/*************************************************************/
		/*             FasterGraphPECalculator                       */
		/*************************************************************/

		/**
			* @brief A Periodic element calculator, which result
			*        a graph
			* @details This periodic element calculation mode
			*          use a graph (whit multiple edges),
			*          but search element only a given plane
			* @note This is a slow algorithm
			*/
		DEF_TEMP
		class FasterGraphPECalculator: 
			public AbstractTreePlanePECalculator<INT_TYPE,      
																					 FLOAT_TYPE,    
																					 Matrix,        
																					 Vector,    
																					 MatrixNorm,
																					 VectorNorm,
																					 matrix_traits, 
																					 vector_traits, 
																					 number_traits> 
		{
			protected:
				/**
					* @brief Upload function for tree
					* @details this function upload the tree,
					*          or update the element forest
					* @param act the actual vector
					* @param tree the uploaded tree
					* @param i the x coordinate in the plane
					* @param j the y coordinate in the plane
					* @param sizeX the maximum window width
					* @param sizeY the maximum window height
					* @return true if we find a perdiodic element
					*/
				bool uploadTree(typename BASE::IVector& act,
				  typename ABS_TREE_PLANE_PE_CALC::ElementTree& tree,
					const int i,
					const int j,
				  const int sizeX,
				  const int sizeY);
		};

		/*************************************************************/
		/*               AbstractFullPECalculator                    */
		/*************************************************************/

		/**
			* @brief This class is an abstract implementation of an
			*        multi dimensional periodic element finder algorithm.
			*/
		DEF_TEMP
		class AbstractFullPECalculator: public virtual BASE
		{
      private:
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
                                       
			public:
				/**
					* @see AbstractPeriodicElementCalculator::calculatePeriodicElements
					*/
				typename BASE::ConnectedDigitSet 
					calculatePeriodicElements(const typename BASE::AbstractParameter &parameters);

				/**
					* @brief compute the limit of computation
					* @return the limit
					*/
				INT_TYPE getLimit();

			protected:

				
				/**
					* @brief This function collects the periodic elements, in the dimId-th dimension
					* @param current the current founder vector
					* @param pe the list of periodic elements
					*/
				virtual void findPE(typename BASE::IVector& current,
														typename BASE::ConnectedDigitSet& pe) = 0;

				/**
					* @brief This function a recursive algorithm to walk throw an n dimensional space
					* @param current the current founder vector
					* @param dimId the id of the current dimension
					* @param dist the radius of the multi dimensional circle, where we looking for pe elements
					* @param pe the list of periodic elements
					*/
				virtual void calcPeriodicElements(typename BASE::IVector& current,
						                              const int dimId,
																					const INT_TYPE dist,
																					typename BASE::ConnectedDigitSet& pe);

				/**
					* @brief Initial function for calculation
					*/
				virtual void initCalc() = 0;

				/**
					* @brief Finalization of the calculation
					*/
				virtual void finalizeCalc(typename BASE::ConnectedDigitSet&) = 0;
		};


		/*************************************************************/
		/*               FullPECalculator                            */
		/*************************************************************/


		/**
			* @brief This class can find all of the periodic elements.
			* @details This algorithm works in multidimensional case.
			*/
		DEF_TEMP
		class FullPECalculator: 
			public AbstractFullPECalculator<INT_TYPE,      
																		  FLOAT_TYPE,    
																		  Matrix,        
																		  Vector,        
																			MatrixNorm,
																			VectorNorm,
																		  matrix_traits, 
																		  vector_traits, 
																		  number_traits> 
		{
			protected:
				
				/**
					* @brief This function collects the periodic elements, in the dimId-th dimension
					* @param current the current founder vector
					* @param pe the list of periodic elements
					*/
				void findPE(typename BASE::IVector& current,
										typename BASE::ConnectedDigitSet& pe);

				/**
					* @brief Initial function for calculation
					*/
				void initCalc()
				{}

				/**
					* @brief Finalization of the calculation
					*/
				void finalizeCalc(typename BASE::ConnectedDigitSet&)
				{}
		};
	}
}
#undef ABS_TREE_PLANE_PE_CALC
#undef DEF_TEMP
#undef BASE
#include "pecalculationtypes.hpp"

#endif //__MATH__NUMBERSYSTEM_PECALCUlATIONTYPES

