#ifndef __MATH__GRAPHS_LINKEDNODE_H
#define __MATH__GRAPHS_LINKEDNODE_H

#include "node.h"
#include "edge.h"
#include <vector>
#include <iostream>

/**
	* @file linkednode.h
	* @brief Contains the LinkedNode class
	* @see MATH::Graphs::LinkedNode
	*/

namespace MATH
{
	namespace Graphs
	{

		/**
			* @brief Node linked representaion
			* @details Evry Node join to eachother by edges.
			* 
			* @tparam Weight_t the weight type of the graph
			* @tparam Label_t the Label type of the graph
			* @tparam Tag_t the tag type of the graph
			* 
			* @see MATH::Graphs::Node
			* @see MATH::Graphs::Edge
			*
			* @todo refactor, every function are inlnine
			*/
		template<class Weight_t,
			       class Label_t = Weight_t,
						 class Tag_t = Weight_t>
		class LinkedNode : public Node<Weight_t, Label_t, Tag_t>
		{
			protected:
				/**
					* @brief connected edges
					*/
				std::vector< Edge<Weight_t, Label_t, Tag_t>* > _edges;
			public:
				/**
					* @brief simple constructor
					* @param label the label
					* @param weight the weight of the node
					* @param tag sepcial information for the node
					*/
				explicit LinkedNode(Label_t label,
						                Weight_t weight = Weight_t(),
						                Tag_t tag = Tag_t())
					:Node<Weight_t, Label_t, Tag_t>(label, weight, tag)
				{}

				/**
					* @brief copy constructor
					* @param other the other nod
					*/
				LinkedNode(const LinkedNode& other)
					:Node<Weight_t, Label_t, Tag_t>(other)
				{
					for(unsigned i = 0; i < other._edges.size(); ++i)
					{
						_edges.push_back(new Edge<Weight_t, Label_t, Tag_t>(*other._edges[i]));
					}
				}

				/**
					* @brief Destructor
					* @warning this function delete the all of edges, which,
					*          go from here
					*/
				virtual ~LinkedNode()
				{
					for(unsigned i = 0; i < _edges.size(); ++i)
					{
						_edges[i]->setBegin((Node<Weight_t, Label_t, Tag_t>*) 0);
						delete _edges[i];
					}
					_edges.clear();
				}

				/**
					* @brief getter for edges of the node
					* @return the outgoing edges
					*/
				std::vector< Edge<Weight_t, Label_t, Tag_t>* >* getEdges()
				{
					return &_edges;
				}

				/**
					* @brief Getter for a specific edge
					* @param nodeLabel the label of the node, which
					*                  is connected by edge
					* @return the connected edge, or 0 if it not exists
					*/
				Edge<Weight_t, Label_t, Tag_t>* getEdge(const Label_t& nodeLabel)
				{
					for(unsigned i = 0; i< _edges.size(); ++i)
					{
						if(_edges[i]->getEnd()->getLabel() == nodeLabel)
							return _edges[i];
					}
					return 0;
				}

				/**
					* @brief the outgoing degree of this node
					* @return the degree
					*/
				unsigned getEdgesCount() const
				{
					return _edges.size();
				}

				/**
					* @brief the outgoing degree of this node
					* @return the degree
					*/
				unsigned getDegree() const
				{
					return _edges.size();
				}

				/**
					* @brief getter for a spcific neightborn
					* @param i the id of edge
					* @return the i-th edges end node
					*/
				const LinkedNode<Weight_t, Label_t, Tag_t>* getNeigthborn(unsigned i) const
				{
					const LinkedNode<Weight_t, Label_t, Tag_t>* ret = dynamic_cast<const LinkedNode<Weight_t, Label_t, Tag_t>*>(_edges[i]->getEnd());
					return ret;
				}

				/**
					* @brief getter for a spcific neightborn
					* @param i the id of edge
					* @return the i-th edges end node
					*/
				LinkedNode<Weight_t, Label_t, Tag_t>* getNeigthborn(unsigned i)
				{
					return dynamic_cast<LinkedNode<Weight_t, Label_t, Tag_t>*>(_edges[i]->getEnd());
				}

				/**
					* @brief connect a new node
					* @param node the new node
					* @param weight the weight of the edge
					*/
				void addNode(LinkedNode<Weight_t, Label_t, Tag_t>* node, const Weight_t& weight = Weight_t())
				{
					_edges.push_back(new Edge<Weight_t, Label_t, Tag_t>(this, node, weight));
				}

				/**
					* @brief print function
					* @param os output stream
					* @param node the node
					* @return the output stream for chainging
					*/
				friend std::ostream& operator<<(std::ostream& os, const LinkedNode<Weight_t, Label_t, Tag_t> node)
				{
					node.print(os);
					return os;
				}

			protected:

				/**
					* @brief print function
					* @param os the stream
					*/
				virtual void print(std::ostream& os) const
				{
					Node<Weight_t, Label_t, Tag_t>::print(os);
					os<<"\tNeightborns:"<<std::endl;
					for(unsigned i = 0; i < _edges.size(); ++i)
					{
						os<<"\t\t"<<_edges[i]->getEnd()->getLabel()<<", "<<_edges[i]->getWeight()<<", "<<_edges[i]->getTag()<<std::endl;
					}
				}

		};
	}
}

#endif // __MATH__GRAPHS_LINKEDNODE_H
