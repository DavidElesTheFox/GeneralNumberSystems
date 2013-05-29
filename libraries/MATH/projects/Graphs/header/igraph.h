#ifndef __MATH__GRAPHS__IGRAPH_H
#define __MATH__GRAPHS__IGRAPH_H

#include "node.h"
#include "edge.h"

/**
	* @file igraph.h
	* @brief Graph interface
	* @see IGraph
	*/

namespace MATH
{
	namespace Graphs
	{
		/**
			* @brief Interface for graphes
			* @tparam Weight_t the Weight's type
			* @tparam Label_t the Label's type
			* @tparam Tag_t the tag's type
			* @see Node
			* @see Edge
			*/
		template<class Weight_t, class Label_t, class Tag_t>
		class IGraph
		{
			public:
				IGraph()	{}

				virtual ~IGraph() {}

				/**
					* @brief Find a node in the graph
				  * @param label node's label
					* @return if it is not exists return 0
				  */
				virtual Node<Weight_t, Label_t, Tag_t>* findNode(const Label_t& label) = 0;

				/**
				  * @brief Add a new Node to an exists node
				  * @param addedLabel new node label
				  * @param addedWeight new node weight
				  * @param label the existing Node
				  * @param edgeWeight the new edge's weight
					* @return it is successful
				  */
				virtual bool addTo(const Label_t& addedLabel,
						               const Weight_t& addedWeight,
													 const Label_t& label,
													 const Weight_t& edgeWeight) = 0;

				/**
				  * @brief Add a new adge between two nodes
				  * @param label1 first node's label
				  * @param label2 second node's label
				  * @param weight the weight of the new edge
					* @return it is successful
				  */
				virtual bool addEdge(const Label_t& label1,
						                 const Label_t& label2,
														 const Weight_t& weight) = 0;

				/**
				  * @brief get a specific edge
				  * @param label1 edge's begin node's label
				  * @param label2 edge's begin node's label
					* @return the finded edge
				  */
				virtual Edge<Weight_t, Label_t, Tag_t>* getEdge(const Label_t label1,
						                                            const Label_t label2) = 0;

				/**
				  * @brief get a specific edge
				  * @param label label of the edge
					* @return the finded edge
				  */
				virtual Edge<Weight_t, Label_t, Tag_t>* getEdge(const Label_t label) = 0;
		};
	}
}

#endif // __MATH__GRAPHS__IGRAPH_H
