#ifndef __MATH__GRAPHS__EDGE_H
#define __MATH__GRAPHS__EDGE_H

#include "node.h"

/**
	* @file edge.h
	* @brief Edge representation
	* @see Edge
	*/

namespace MATH
{
	namespace Graphs
	{
		/**
			* @brief template edge representation class
			* @tparam Weight_t the weight type
			* @tparam Label_t the label type
			* @tparam Tag_t the tag type
			* @todo Refactor, now all function is inline
			*/
		template<class Weight_t,
			       class Label_t = Weight_t,
						 class Tag_t = Weight_t>
		class Edge
		{
			private:
				/**
					* @brief the begin of edge
					*/
				Node<Weight_t, Label_t, Tag_t>* _begin;
				/**
					* @brief the end of the edge
					*/
				Node<Weight_t, Label_t, Tag_t>* _end;
				/**
					* @brief The weight of the edge
					*/
				Weight_t _weight;
				/**
					* @brief The label of the edge
					*/
				Label_t _label;
				/**
					* @brief Tag of the edge for special information
					*/
				Tag_t _tag;
			public:

				/**
					* @brief Constructor
					* @param begin the begin of edge
					* @param end the end of edge
					* @param weight the weight of the edge
					* @param label the label of the edge
					* @param tag the tag of the edge
					*/
				explicit Edge(Node<Weight_t, Label_t, Tag_t>* begin,
					            Node<Weight_t, Label_t, Tag_t>* end,
					            Weight_t weight = Weight_t(),
					            Label_t label = Label_t(),
					            Tag_t tag = Tag_t())
					:  _begin(begin),
					   _end(end),
						_weight(weight),
						_label(label),
						_tag(tag)
				{}

				/**
					* @brief copy constructor
					* @param other the other edge
					*/
				Edge(const Edge& other):_begin(new Node<Weight_t, Label_t, Tag_t>(*other._begin)),
										_end(new Node<Weight_t, Label_t, Tag_t>(*other._end)),
										_weight(other._weight),
										_label(other._label),
										_tag(other._tag)
				{}

				/**
					* @brief Copy of the other
					* @param other the other edge
					* @return reference for this
					*/
				Edge& operator=(const Edge& other)
				{
					if (this != &other)
					{
						delete _begin;
						delete _end;
						_begin = new Node<Weight_t, Label_t, Tag_t>(other._begin);
						_end = new Node<Weight_t, Label_t, Tag_t>(other._end);
						_weight = other._weight;
						_label = other._label;
						_tag = other._tag;
					}
					return *this;
				}

				/**
					* @brief default destructor
					* @details dont delete the connected nodes
					*/
				virtual ~Edge()
				{
//					delete _begin;
//					delete _end;
				}

				/**
					* @brief getter for the tag
					* @return special information of the edge
					*/
				Tag_t getTag() const
				{
					return _tag;
				}

				/**
					* @brief getter for the tag
					* @return reference to special information of the edge
					*/
				Tag_t& getTag()
				{
					return _tag;
				}

				/**
					* @brief setter for the tag
					* @param value value of the new tag
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
					* @brief setter for the lebel
					* @param value value of the new label
					*/
				void setLabel (const Label_t& value)
				{
					this->_label = value;
				}

				/**
					* @brief getter for weight
					* @return the weight of the edge
					*/
				Weight_t getWeight() const
				{
					return _weight;
				}

				/**
					* @brief seter for the weight
					* @param value the new weight
					*/
				void setWeight (const Weight_t& value)
				{
					this->_weight = value;
				}

				/**
					* @brief getter for the begining of the edge
					* @return the source of the edge
					*/
				Node<Weight_t, Label_t, Tag_t>* getBegin()
				{
					return _begin;
				}

				/**
					* @brief setter for the begin of edge
					* @param value new source of the edge
					*/
				void setBegin (Node<Weight_t, Label_t, Tag_t>* value)
				{
					this->_begin = value;
				}

				/**
					* @brief getter for the ending of the edge
					*/
				Node<Weight_t, Label_t, Tag_t>* getEnd()
				{
					return _end;
				}

				/**
					* @brief setter for the ending of the edge
					* @param value the value of the new ending
					*/
				void setEnd (Node<Weight_t, Label_t, Tag_t>* value)
				{
					this->_end = value;
				}

				/**
					* @brief equals operator
					* @param a an edge
					* @param b other edge
					* @return their are equals
					*/
				friend bool operator==(const Edge<Weight_t,
						                              Label_t, Tag_t>& a,
															            Edge<Weight_t,
															            Label_t,
															            Tag_t>& b)
				{
					return a._begin == b._begin && a._end == b._end  && a._label == b._label;
				}
		};
	}
}

#endif // __MATH__GRAPHS__EDGE_H
