#ifndef __MATH__GRAPHS__ABSTRACTBFS_H
#define __MATH__GRAPHS__ABSTRACTBFS_H

#include "igraph.h"
#include "node.h"

/**
	* @file abstractbfs.h
	* @brief Contains abstract class for BFS
	* @see MATH::Graphs::AbstractBFS
	*/

namespace MATH
{
	namespace Graphs
	{
		/**
			* @brief Abstract class for BFS
			* @details Breadth first searching
			*         
			* @tparam Weight_t the weight of the graph
			* @tparam Label_t the label of the graph
			* @tparam Tag_t the tag of the graph
			* @see Node
			* @see IGraph
			* @todo refactor: Now all of function are inline
			*/
		template<class Weight_t, class Label_t = Weight_t, class Tag_t = Weight_t>
		class AbstractBFS
		{
			protected:
				/**
					* @brief graph representation
					*/
				IGraph<Weight_t, Label_t, Tag_t>* _graph;
				/**
					* @brief storage vector
					*/
				std::vector<Node<Weight_t, Label_t, Tag_t>*> _vect;

			public:

				/**
					* @brief simple constructor
					* @param graph the graph
					*/
				AbstractBFS(IGraph<Weight_t, Label_t, Tag_t>* graph):_graph(graph)
				{}

				/**
					* @brief default destructor
					*/
				virtual ~AbstractBFS()
				{}

				/**
				  * @brief Starting of the algorithm
				  * @param startLabel start node's label
				  */
				void go(const Label_t& startLabel)
				{
					Node<Weight_t, Label_t, Tag_t>* act = _graph->findNode(startLabel);
					_vect.clear();
					prepare(act);

					while(act != 0)
					{
						core(act);
						act = getNext(act);
					}
					release(act);
				}

			protected:
				/**
					* @brief Abstract function.
					* @details This function called for the actual Node
					* @param act the actual node
					*/
				virtual void core(Node<Weight_t, Label_t, Tag_t>* act) = 0;

				/**
					* @brief This abstract function will be determined the next node
					* @param act the actual node
					*/
				virtual Node<Weight_t, Label_t, Tag_t>* 
				  getNext(Node<Weight_t, Label_t, Tag_t>* act) = 0;

				/**
					* @brief This abstract function will be calling before the starting of algorithm
					* @param startNode the start node
					*/
				virtual void prepare(Node<Weight_t, Label_t, Tag_t>* startNode) = 0;

				/**
					* @brief This abstract function will be calling after the algorithm
					* @param startNode the start node
					*/
				virtual void release(Node<Weight_t, Label_t, Tag_t>* startNode) = 0;
		};
	}
}

#endif // __MATH__GRAPHS__ABSTRACTBFS_H
