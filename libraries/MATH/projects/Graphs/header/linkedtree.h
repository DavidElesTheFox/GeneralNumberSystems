#ifndef __MATH__GRAPHS__LINKEDTREE_H
#define __MATH__GRAPHS__LINKEDTREE_H

#include "linkedgraph.h"
#include "itree.h"

/**
	* @file linkedtree.h
	* @brief Contains the LinkedTree class
	* @see MATH::Graphs::LinkedTree
	*/

namespace MATH
{
	namespace Graphs
	{

		/**
			* @brief Linked tree class
			* @tparam Weight_t the weight type of tree
			* @tparam Label_t the label type of tree
			* @tparam Tag_t the tag type of tree
			*
			* @see ITree
			* @see LinkedGraph
			* @todo refactor, every function are inlnine
			*/
		template<class Weight_t,
			       class Label_t =Weight_t,
						 class Tag_t = Weight_t>
		class LinkedTree: public ITree<Weight_t, Label_t, Tag_t>,
						          public LinkedGraph<Weight_t, Label_t, Tag_t>
		{
			public:
				/**
					* @brief simple constructor
					* @see LinkedGraph
					*/
				LinkedTree():LinkedGraph()
				{	}

				/** 
					* @brief virtual destructor
					* @see LinkedGraph
					*/
				virtual ~LinkedTree()
				{}

				/**
					* @brief getter for the root element
					* @return the root node of the tree
					*/
				Node<Weight_t, Label_t, Tag_t>* getRoot()
				{
					return _first;
				}
		};
	}
}

#endif // __MATH__GRAPHS__LINKEDTREE_H
