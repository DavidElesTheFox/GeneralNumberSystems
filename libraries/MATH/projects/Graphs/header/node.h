#ifndef __MATH__GRAPHS__NODE_H
#define __MATH__GRAPHS__NODE_H

#include <iostream>

/**
	* @file node.h
	* @brief Contains Node class
	* @see MATH::Graphs::Node
	*/

namespace MATH
{
	namespace Graphs
	{
		/**
			* @brief Node representation class
			* @tparam Weight_t the weight type of the node
			* @tparam Label_t the label type of the node
			* @tparam Tag_t the tag type of the node
			* @todo refactor, every function are inlnine
			*/
		template<class Weight_t,
			       class Label_t = Weight_t,
						 class Tag_t = Weight_t>
		class Node
		{
			private:
				/**
					* @brief the weight of the node
					*/
				Weight_t _weight;
				/**
					* @brief the label of the node
					*/
				Label_t _label;
				/**
					* @brief the tag of the node
					* @details special information from the node
					*/
				Tag_t _tag;
				/**
					* @brief visited or not
					* @details special variable for specific algorithm
					*/
				bool _visited;
			public:
				/**
					* @brief simple constructor
					* @param label the label of the node
					* @param weight the weight of the node
					* @param tag the tag of the node
					*/
				explicit Node(Label_t label = Label_t(),
					            Weight_t weight = Weight_t(),
					            Tag_t tag = Tag_t()): _weight(weight),
										   _label(label),
										   _tag(tag),
										   _visited(false)
				{			}
//
//				Node(const Node& other):_weight(other._weight),
//										_label(other._label),
//										_tag(other._tag)
//				{	}

				/**
					* @brief simple destructor
					*/
				virtual ~Node()
				{}

				/**
					* @brief getter for tag
					* @return the tag
					*/
				Tag_t getTag() const
				{
					return _tag;
				}

				/**
					* @brief getter for tag
					* @return the tag
					*/
				Tag_t& getTag()
				{
					return _tag;
				}

				/**
					* @brief setter for the tag
					* @param value the value of the new tag
					*/
				void setTag (const Tag_t& value)
				{
					this->_tag = value;
				}

				/**
					* @brief getter for the label
					* @return the label
					*/
				Label_t getLabel() const
				{
					return _label;
				}

				/**
					* @brief getter for the label
					* @return the label
					*/
				Label_t& getLabel()
				{
					return _label;
				}

				/**
					* @brief setter for the label
					* @param value the new label
					*/
				void setLabel (const Label_t& value)
				{
					this->_label = value;
				}

				/**
					* @brief getter for the weight
					* @return the weight
					*/
				Weight_t getWeight() const
				{
					return _weight;
				}

				/**
					* @brief getter for the weight
					* @return the weight
					*/
				Weight_t& getWeight()
				{
					return _weight;
				}

				/**
					* @brief setter for the weight
					* @param value the new weight
					*/
				void setWeight (const Weight_t& value)
				{
					this->_weight = value;
				}

				/**
					* @brief this node is visited or not
					* @return true if visited, false in other case
					*/
				bool isVisited() const
				{
					return _visited;
				}

				/**
					* @brief setter for the visited value
					* @param value the new value of the visitad state
					* @note it's a constant function, because the object
					*       doesn't change logically
					*/
				void setVisited(const bool value) const
				{
					(*const_cast<bool*>(&_visited)) = value;
				}

				/**
					* @brief equals operator
					* @param a a node
					* @param b another node
					* @return theire are equals
					* @note compare by the label of the two node. We
					*       assume that two node is equals if theire label
					*       are equals.
					*/
				friend bool operator==(const Node<Weight_t, Label_t, Tag_t> a,
						                   const Node<Weight_t, Label_t, Tag_t> b)
				{
					return a._label == b._label;
				}

				/**
					* @brief printer function
					* @param os the output stream
					* @param node the printed node
					* @return the output stream 
					*/
				friend std::ostream& operator<<(std::ostream& os,
						                            const Node<Weight_t, Label_t, Tag_t> node)
				{
					node.print(os);
					return os;
				}

			protected:
				/**
					* @brief print function for child classes
					* @param os the output stream
					*/
				virtual void print(std::ostream& os) const
				{
					os<<"label: "<<_label<<std::endl;
					os<<"-------------------------"<<std::endl;
					os<<"\tWeight: "<<_weight<<std::endl;
					os<<"\tTag: "<<_tag<<std::endl;
				}

		};
	}
}


#endif // __MATH__GRAPHS__INODE_H
