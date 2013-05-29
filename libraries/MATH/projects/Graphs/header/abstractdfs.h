#ifndef __MATH__GRAPHS__ABSTRACTDFS_H
#define __MATH__GRAPHS__ABSTRACTDFS_H

#include "igraph.h"
#include "node.h"

/**
	* @file abstractdfs.h
	* @brief Contains an Abstract DFS
	* @see MATH::Graphs::AbstractDFS
	*/

namespace MATH
{
	namespace Graphs
	{
		/**
			* @brief AbstractDFS
			* @details Abstract DFS implementation (Depth first search)
			* @tparam Weight_t the weight type of the graph
			* @tparam Label_t the label of the graph
			* @tparam Tag_t the tag of the graph
			* @see Node
			* @see IGraph
			* @todo refactor: Now all of function are inline
			*/
		template<class Weight_t, class Label_t, class Tag_t>
		class AbstractDFS
		{
			protected:
				/**
					* @brief the graph
					*/
				IGraph<Weight_t, Label_t, Tag_t>* _graph;
			public:
				/**
					* @brief simple constructor
					* @param graph the graph, where the algorithm will work
					*/
				AbstractDFS(IGraph<Weight_t, Label_t, Tag_t>* graph): _graph(graph)
				{}

				/**
					* @brief simple destructor
					*/
				virtual ~AbstractDFS()
				{	}

				/**
					* @brief Execution of the algorithm
					* @param startLabel the starting label
					*/
				void go(Label_t startLabel)
				{
					Node<Weight_t, Label_t, Tag_t>* startNode = _graph->findNode(startLabel);
					prepare(startNode);
					algorithm(startNode);
					release(startNode);
				}
			protected:
				/**
					* @brief abstract function for preparing
					* @details This function will be called before the starting of algorithm
					* @param startNode the starting node
					*/
				virtual void prepare(Node<Weight_t, Label_t, Tag_t>* startNode) = 0;

				/**
					* @brief abstract release function
					* @details this function will be called after the algorithm
					* @param startNode the starting node
					*/
				virtual void release(Node<Weight_t, Label_t, Tag_t>* startNode) = 0;

				/**
					* @brief Abstract function for logic of algorithm
					* @details This function will be called each of node
					* @param act the actual node
					*/
				virtual void core(Node<Weight_t, Label_t, Tag_t>* act) = 0;

				/**
					* @brief Abstract function for stap back
					* @details This function will be called when the 
					*          Algorithm do a back stapping
					* @param act the actual node
					*/
				virtual void stepBack(Node<Weight_t, Label_t, Tag_t>* act) = 0;

				/**
					* @brief Abstract function for determination of next node
					* @details This function has to detemine the next node
					* @param act the actual node
					*/
				virtual Node<Weight_t, Label_t, Tag_t>* getNext(Node<Weight_t, Label_t, Tag_t>* act) = 0;
			private:

				/**
					* @brief The logic function
					* @details this function contains the dfs logic
					* @param node the actual node
					*/
				void algorithm(Node<Weight_t, Label_t, Tag_t>* node)
				{
					core(node);
					Node<Weight_t, Label_t, Tag_t>* next = getNext(node);
					while(next != 0)
					{
						algorithm(next);
						next = getNext(node);
					}
					stepBack(node);
				}
		};
	}
}

#endif // __MATH__GRAPHS__ABSTRACTDFS_H
