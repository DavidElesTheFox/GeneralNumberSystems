#ifndef __MATH__NUMBERSYSTEM__PECALCULATIONTYPES
#error use without header
#endif

#define DEF_TEMP template <class INT_TYPE,                    \
						               class FLOAT_TYPE,                  \
							             template<class T> class Matrix,    \
							             template<class T> class Vector,    \
                           template<class T> class MatrixNorm,\
                           template<class T> class VectorNorm,\
							             template<typename T, class M>      \
                             class matrix_traits,             \
							             template<typename T, class V>      \
                             class vector_traits,             \
							             template<typename T>               \
                             class number_traits>
#define BASE AbstractPeriodicElementCalculator<INT_TYPE,      \
                                               FLOAT_TYPE,    \
																							 Matrix,        \
																							 Vector,        \
                                               MatrixNorm,    \
                                               VectorNorm,    \
																							 matrix_traits, \
																							 vector_traits, \
																							 number_traits> 
#define ABS_PLANE_PE_CALC AbstractPlanePECalculator\
  <INT_TYPE,      \
   FLOAT_TYPE,    \
   Matrix,        \
   Vector,        \
   MatrixNorm,    \
   VectorNorm,    \
   matrix_traits, \
   vector_traits, \
   number_traits> 

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
#define SIMP_GRAPH_PE_CALC SimpleGraphPECalculator \
  <INT_TYPE,      \
   FLOAT_TYPE,    \
   Matrix,        \
   Vector,        \
   MatrixNorm,    \
   VectorNorm,    \
   matrix_traits, \
   vector_traits, \
   number_traits> 
#define FASTER_GRAPH_PE_CALC FasterGraphPECalculator \
  <INT_TYPE,      \
   FLOAT_TYPE,    \
   Matrix,        \
   Vector,        \
   MatrixNorm,    \
   VectorNorm,    \
   matrix_traits, \
   vector_traits, \
   number_traits> 
#define ABSTRACT_FULL_PE_CALC AbstractFullPECalculator \
  <INT_TYPE,      \
   FLOAT_TYPE,    \
   Matrix,        \
   Vector,        \
   MatrixNorm,    \
   VectorNorm,    \
   matrix_traits, \
   vector_traits, \
   number_traits> 
#define FULL_PE_CALC FullPECalculator \
  <INT_TYPE,      \
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
		DEF_TEMP
		typename BASE::ConnectedDigitSet ABS_PLANE_PE_CALC::
			  calculatePeriodicElements
					  (const typename BASE::AbstractParameter& parameters)
		{
			const Parameter* params = dynamic_cast<const Parameter*>(&parameters); 
			if (params == 0)
			{
				throw Exceptions::ParameterException("Non compatible parameter");
			}
			else
			{
			  _params = *params;
			}
			if(_params.stepDistance 
					 == number_traits<INT_TYPE>::additiveUnit)
			{
				throw Exceptions::RuntimeException("0 step distance");
			}
			initCalc();
			typename BASE::IVector v1 = _params.vector1;
			typename BASE::IVector v2 = _params.vector2;
			int sizeY = _params.height/(2*_params.stepDistance);
			int sizeX = _params.width/(2*_params.stepDistance);
			for(int i = -sizeX; i < sizeX;++i)
			{
				BASE::vector_traits_int::setElement(_params.xCoord,
				  BASE::vector_traits_int::getElement(_params.xCoord,
												                               BASE::_focusPoint)
				  + i * _params.stepDistance,
					v1);
				for(int j = -sizeY; j < sizeY; ++j)
				{
					BASE::vector_traits_int::setElement(_params.yCoord,
						BASE::vector_traits_int::getElement(_params.yCoord,
																												 BASE::_focusPoint)
						+ j * _params.stepDistance,
						v2);
					typename BASE::IVector v = v2 + v1;

					calcPeriodicElement(v, i, j, sizeX, sizeY);
				}
			}
			return getActualPeriodicElements();
		}
		/*************************************************************/
		/*             AbstractTreePlanePECalculator                 */
		/*************************************************************/

		DEF_TEMP
		void ABS_TREE_PLANE_PE_CALC::
		  calcPeriodicElement(const typename BASE::IVector& act,
					                const int i, 
													const int j,
													const int sizeX,
													const int sizeY)
		{
			typename BASE::IVector v = act;
			bool finished = false;
			ElementTree tree(v);
			v = BASE::_ns->chop(v);
			while(!finished)
			{
				if ( !(finished = uploadTree(v, tree, i, j, sizeX, sizeY)))
				{
					v = BASE::_ns->chop(v);
				}
			}
		}

		DEF_TEMP
		typename BASE::ConnectedDigitSet ABS_TREE_PLANE_PE_CALC::getActualPeriodicElements()
		{
			typename BASE::ConnectedDigitSet pe;
			for (unsigned i = 0; i < _elementForest.size(); ++i)
			{
				typename ElementTree::ReverseTreeNode* leaf =
					_elementForest[i].getLeaf();
				if (leaf != 0)
					pe.push_back(leaf->value);
			}
			return pe;
		}

		/*************************************************************/
		/*             SimpleGraphPECalculator                       */
		/*************************************************************/

		DEF_TEMP
		bool SIMP_GRAPH_PE_CALC::
		uploadTree(typename BASE::IVector& v,
				       typename ABS_TREE_PLANE_PE_CALC::ElementTree& tree,
							 const int i,
							 const int j,
							 const int sizeX,
							 const int sizeY)
		{
			int circleId = 0;
			bool finished = false;
			if( 
				 (circleId = ABS_TREE_PLANE_PE_CALC::_elementForest.insert(tree)) 
				  >= 0
				 || tree.isIn(v))
			{
				if( circleId < 0 )
				{
					ABS_TREE_PLANE_PE_CALC::_elementForest.push_back(tree);
					circleId = ABS_TREE_PLANE_PE_CALC::_elementForest.size() - 1;
				}
				if(ABS_TREE_PLANE_PE_CALC::_params.circles != 0)
				{
					ABS_TREE_PLANE_PE_CALC::
						_params.circles[i+sizeX]
						                [j+sizeY]
														  = circleId;
				}
				finished = true;
			}
			else
			{
				tree.push_front(v);
			}
			return finished;
		}

		/*************************************************************/
		/*             FasterGraphPECalculator                       */
		/*************************************************************/

		DEF_TEMP
		bool FASTER_GRAPH_PE_CALC::
		uploadTree(typename BASE::IVector& v,
				       typename ABS_TREE_PLANE_PE_CALC::ElementTree& tree,
							 const int i,
							 const int j,
							 const int sizeX,
							 const int sizeY)
		{
			int circleId = 0;
			bool finished = false;
			if(tree.isIn(v))
			{
				if ((circleId
						 = ABS_TREE_PLANE_PE_CALC::_elementForest.joinToLeafs(tree))
						< 0 )
				{
					ABS_TREE_PLANE_PE_CALC::_elementForest.push_back(tree);
					circleId = ABS_TREE_PLANE_PE_CALC::_elementForest.size() - 1;
				}
				if(ABS_TREE_PLANE_PE_CALC::_params.circles != 0)
				{
					ABS_TREE_PLANE_PE_CALC::
						_params.circles[i+sizeX]
						                [j+sizeY]
														  = circleId;
				}
				finished = true;
			}
			else
			{
				tree.push_front(v);
			}
			return finished;
		}

		/*************************************************************/
		/*               AbstractFullPECalculator                    */
		/*************************************************************/

		DEF_TEMP
		INT_TYPE ABSTRACT_FULL_PE_CALC::getLimit()
		{
      typename BASE::FVector upper;
      typename BASE::FVector lower;
      NumSysCalc::computeRectangleOfH(upper, lower, *this->_ns);
      double normUpper = BASE::VectorCalculator_float::norm(0, upper);
      double normLower = BASE::VectorCalculator_float::norm(0, lower);

      return normUpper > normLower ? normUpper : normLower;
    }

		DEF_TEMP
		typename BASE::ConnectedDigitSet
		ABSTRACT_FULL_PE_CALC::calculatePeriodicElements
		  (const typename BASE::AbstractParameter&)
		{
			initCalc();

			typename BASE::ConnectedDigitSet digits = BASE::_ns->getDigitSet();
			int dimNum = BASE::vector_traits_int::getDimension(digits[0]);
			typename BASE::IVector v = BASE::vector_traits_int::create(dimNum);

			typename BASE::ConnectedDigitSet pe;

			INT_TYPE L = getLimit();

			calcPeriodicElements(v, 0, L, pe);

			finalizeCalc(pe);
			return pe;
		}

		DEF_TEMP
		void 
		ABSTRACT_FULL_PE_CALC::calcPeriodicElements
		  (typename BASE::IVector& v,
			 const int dimId,
			 const INT_TYPE dist,
			 typename BASE::ConnectedDigitSet &pe)
		{
			if (dimId < BASE::vector_traits_int::getDimension(v) - 1)
			{
				INT_TYPE &act = BASE::vector_traits_int::getElement(dimId, v);
				act = -dist;
				while (act < dist)
				{
					calcPeriodicElements(v, dimId + 1, dist, pe);
					act += BASE::number_traits_int::multiplicativeUnit;
				}
				act = -dist;
			}
			else
			{
				findPE(v, pe);
			}
		}

		/*************************************************************/
		/*               FullPECalculator                            */
		/*************************************************************/

		DEF_TEMP
		void FULL_PE_CALC::findPE(typename BASE::IVector& v,
				                      typename BASE::ConnectedDigitSet& pe)
		{
			typename BASE::IVector z = BASE::_ns->getDigits(v).back();
			if (find_if(pe.begin(), pe.end(),
					         typename BASE::ConnectedNumberSystem::DigitFinder(z))
					== pe.end())
			{
				pe.push_back(z);
			}
		}
		
	}
}

#undef DEF_TEMP 
#undef BASE 
#undef ABS_PLANE_PE_CALC
#undef ABS_TREE_PLANE_PE_CALC
#undef SIMP_GRAPH_PE_CALC
#undef FASTER_GRAPH_PE_CALC
#undef ABSTRACT_FULL_PE_CALC 
#undef FULL_PE_CALC

