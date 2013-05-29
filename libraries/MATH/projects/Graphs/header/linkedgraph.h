#ifndef __MATH__GRAPHS__LINKEDGRAPH_H
#define __MATH__GRAPHS__LINKEDGRAPH_H

#include "igraph.h"
#include "linkednode.h"

#include <iostream>
#include <set>

/**
	* @file linkedgraph.h Contains a linked graph representation
	* @see MATH::Graphs::LinkedGraph
	*/
namespace MATH
{
	namespace Graphs
	{
		/**
			* @brief Linked graph representation of a graph
			* @tparam Weight_t weight type of the graph
			* @tparam Label_t label type of the graph
			* @tparam Tag_t tag type of the graph
			* @see IGraph
			* @todo Now all of the functions are inline
			* @todo do copieable
			*/
		template< class Weight_t,
			        class Label_t = Weight_t,
							class Tag_t = Weight_t>
		class LinkedGraph: public virtual IGraph<Weight_t, Label_t, Tag_t>
		{
			protected:
				/**
					* @brief vector of nodes
					*/
				std::vector<LinkedNode<Weight_t, Label_t, Tag_t>*> _nodes;
			private:
				/**
					* @brief cach for the actual node
					*/
				LinkedNode<Weight_t, Label_t, Tag_t>* _act;
			public:
				/**
					* @brief Simple constructor
					*/
				LinkedGraph(): _act(0)
				{}

				/**
					* @brief simple destructor
					*/
				virtual ~LinkedGraph()
				{
					for(unsigned i = 0;i < _nodes.size(); ++i)
					{
						delete _nodes[i];
					}
				}

				/**
					* @brief adding a new node
					* @param label the lable of the new node
					* @param weight the weight of the new node
					* @note this function doesn't create a new edge
					*/
				virtual void addNode(const Label_t& label, const Weight_t& weight)
				{
					_nodes.push_back(new LinkedNode<Weight_t, Label_t, Tag_t>(label, weight));
				}

				/**
					* @brief search function
					* @param label the label of the searched element
					*/
				virtual Node<Weight_t, Label_t, Tag_t>* findNode(const Label_t& label)
				{
					for(unsigned i = 0;i < _nodes.size(); ++i)
					{
						if(_nodes[i]->getLabel() == label)
						{
							return _nodes[i];
						}
					}
					return 0;
				}

				/**
					* @brief Add a new node to an existing
					* @details this function create an edge and a node
					* @param addedLabel label of the new node
					* @param addedWeight weight of the new node
					* @param label label of the existing node
					* @param edgeWeight weight of the new edge
					* @return creation of the edge was successful
					*/
				virtual bool addTo(const Label_t& addedLabel,
						               const Weight_t& addedWeight,
													 const Label_t& label,
													 const Weight_t& edgeWeight)
				{
					addNode(addedLabel, addedWeight);
					return addEdge(addedLabel, label, edgeWeight);
				}

				/**
					* @brief Add a new node to an existing
					* @details this function create an edge and a node
					* @param addedLabel label of the new node
					* @param label label of the existing node
					* @param edgeWeight weight of the new edge
					* @return creation of the edge was successful
					*/
				virtual bool addTo(const Label_t& addedLabel,
						               const Label_t& label,
													 const Weight_t& edgeWeight = Weight_t())
				{
					return addTo(addedLabel, Weight_t(), label, edgeWeight);
				}

				/**
					* @brief Add a new edge to the graph
					*
					* @param label1 the start label
					* @param label2 the end label
					* @param weight the weight of the new edge
					* @return the labels are valide, and the creation was successful
					*
					* @note The labels must be valide
					*/
				virtual bool addEdge(const Label_t& label1, const Label_t& label2, const Weight_t& weight)
				{
					LinkedNode<Weight_t, Label_t, Tag_t>* node1 = dynamic_cast<LinkedNode<Weight_t, Label_t, Tag_t>*>(findNode(label1));
					LinkedNode<Weight_t, Label_t, Tag_t>* node2 = dynamic_cast<LinkedNode<Weight_t, Label_t, Tag_t>*>(findNode(label2));
					if(node1 == 0 || node2 == 0)
						return false;
					node1->addNode(node2, weight);
					node2->addNode(node1, weight);
					return true;
				}

				/**
					* @brief determines the number of edges
					*/
				unsigned getNodeCount() const
				{
					unsigned ret = 0;
					for(unsigned i = 0; i < _nodes.size(); ++i)
					{
						ret += _nodes[i]->getDegree();
					}
					return ret / 2;
				};

				/**
					* @brief edge finder function
					* @param label1
					* @param label2
					* @deprecated
					*/
				Edge<Weight_t, Label_t, Tag_t>* getEdge(const Label_t label1,
				                                        const Label_t label2) __attribute__ ((deprecated))
				{
					return 0;
				}

				/**
					* @brief edge finder function
					* @param label
					* @deprecated
					*/
				Edge<Weight_t, Label_t, Tag_t>* getEdge(const Label_t label) __attribute__ ((deprecated))
				{
					return 0;
				}

				/**
					* @brief Print function
					* @param os the output stream
					* @param g the graph
					*/
				friend std::ostream& operator<<(std::ostream& os, const LinkedGraph<Weight_t, Label_t, Tag_t>& g)
				{
					for(unsigned i = 0; i < g._nodes.size(); ++i)
					{
						os<<*g._nodes[i]<<std::endl;
					}
					return os;
				}
			private:
				/**
					* @brief copy constructor
					* @param other the graph
					*/
				LinkedGraph(const LinkedGraph& other)
				{
					/*std::set<Label_t> cashe;
					_first = new LinkedNode<Weight_t, Label_t, Tag_t>(*other._first);
					cashe.insert(_first->getLabel());
					copy(_first, other._first, cashe);
					setVisitedFalse(_first);*/
					std::cerr<<"WARNING: LinkedGraph copy"<<std::endl;
				}



		};
	}
}

#endif // __MATH__GRAPHS__LINKEDGRAPH_H
