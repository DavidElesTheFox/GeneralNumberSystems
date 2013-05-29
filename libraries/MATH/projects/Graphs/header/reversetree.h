#ifndef __MATH__GRAPHS__REVERSETREE_H
#define __MATH__GRAPHS__REVERSETREE_H

#include <iostream>
#include <vector>

/**
	* @file reversetree.h
	* @brief Contains a reverse tree implementation
	* @see MATH::Graphs::ReverseTree
	*/

namespace MATH
{
	namespace Graphs
	{
		/**
			* @brief Reverse tree class
			* @details It's a special tree reprezentation.
			*          It's undependent the other classes on this namespace,
			*          and exactly it's tree where every node has predecessors,
			*          but only one successor.
			*          Example:
			*          \verbatim
			           *    *    *   *
			            \  /    /     \
			              *    *       *
			                \ /      /
			                 *      *
			                   \  /
			                     *
			*          \endverbatim
			* @tparam T The contains type
			* @todo Refactor, now all function is inline
			*/
		template<class T>
		class ReverseTree
		{
			public:
				/**
					* @brief Node type for reverse tree
					*/
				struct ReverseTreeNode
				{
					/**
						* @brief list of nodes
						*/
					typedef std::vector<ReverseTreeNode* > NodeList;
					/**
						* @brief const iterator for nodes
						*/
					typedef typename std::vector<ReverseTreeNode* >::const_iterator NodeList_const_iterator;
					/**
						* @brief iterator for nodes
						*/
					typedef typename std::vector<ReverseTreeNode* >::const_iterator NodeList_iterator;

					/**
						* @brief the one successor
						*/
					ReverseTreeNode* next;
					/**
						* @brief the predecessors
						*/
					NodeList prevs;
					/**
						* @brief the value of the node
						*/
					T value;
					/**
						* @brief simple constructor
						* @param val the value of the node
						* @param parent one of the successors
						*/
					ReverseTreeNode(const T& val,
							            ReverseTreeNode* parent = 0):next(0), value(val)
					{
						if(parent != 0)
						{
							prevs.push_back(parent);
						}
					}

					/**
						* @brief simple destructor
						*/
					virtual ~ReverseTreeNode()
					{	}

					//ReverseTreeNode(const ReverseTreeNode& other)
					//{	}



					//ReverseTreeNode& operator=(const ReverseTreeNode& other);

					/**
						* @brief equals operator
						* @details two nodes are equals, if theire values
						*          equals.
						*
						*/
					bool operator==(const ReverseTreeNode& other)
					{
						return value == other.value;
					}

				};
			protected:
				/**
					* @brief pointer to the one leaf object
					* @note exactly this element is the root
					*/
				ReverseTreeNode* _leaf;

			public:
				/**
					* @brief simple constructor
					*/
				ReverseTree(): _leaf(0)
				{				}

				/**
					* @brief constructor from T type
					* @details create an reverseTree with leaf with
					*          the given value
					* @param value the value of the leaf
					*/
				ReverseTree(const T& value):_leaf(new ReverseTreeNode(value))
				{				}

				/**
					* @brief copy constructor
					* @param other other tree
					*/
				ReverseTree(const ReverseTree<T>& other)
				{
					_leaf = copy(other._leaf);
				}

				/**
					* @brief destructor
					* @details delete all element on the tree
					*/
				virtual ~ReverseTree()
				{
					release(_leaf);
				}

				/**
					* @brief value setter operator
					* @param other the other tree
					* @return reference to this object
					*/
				ReverseTree& operator=(const ReverseTree& other)
				{
					release(_leaf);
					_leaf = copy(other._leaf);
					return *this;
				}

				/**
					* @brief push an element towards the leaf
					* @details if the leaf isn't exists this function
					*          create a new one.
					* @param value value of the new node
					*/
				void push_front(const T& value)
				{
					if(_leaf != 0)
					{
						_leaf->next = new ReverseTreeNode(value, _leaf);
						_leaf = _leaf->next;
					}
					else
					{
						_leaf = new ReverseTreeNode(value);
					}
				}

				/**
					* @brief try to join to trees from theire leafs.
					* @param other the other tree
					* @return true if it successfull, false in other case
					*/
				bool joinToLeaf(const ReverseTree& other)
				{
					if(other._leaf->value != this->_leaf->value)
					{
						return false;
					}
					else
					{
						for(unsigned i = 0; i < other._leaf->prevs.size(); ++i)
						{
							this->_leaf->prevs.push_back(copy(other._leaf->prevs[i]));
						}

						return true;
					}
				}

				/**
					* @brief simplify the tree
					* @details Remove the multiple element in neightborn
					* @note it is a time cost function
					*/
				void simplify()
				{
					simplify(_leaf);
				}

				/**
					* @brief Try to insert a new tree to this tree
					* @details Try to find the other tree leaf element
					*          in own elements, and if it successfull, than
					*          insert the value from this
					* @param other the other tree
					* @return it is successfull or not
					* @note it is a time cost operation, if you want to a
					*       faster insert use joinToLeaf
					* @see joinToLeaf
					*/
				bool insert(const ReverseTree& other)
				{
					if(other._leaf != 0)
					{
						ReverseTreeNode* from = 0;
						if(find(other._leaf->value, from))
						{
							ReverseTreeNode* otherFrom = copy(other._leaf);
							for(typename ReverseTreeNode::NodeList_iterator it = otherFrom->prevs.begin(); it != otherFrom->prevs.end(); ++it)
							{
								from->prevs.push_back(*it);
							}
							return true;
						}
						else
						{
							return false;
						}
					}
					else
					{
						return false;
					}
				}

				/**
					* @brief Try to insert a new tree to this tree
					* @details Try to find the other tree leaf element
					*          in own elements, and if it successfull, than
					*          insert the value from this.
					*          A faster algorithm which doesn't do copy.
					* @param other the other tree
					* @return it is successfull or not
					* @note it is a time cost operation, if you want to a
					*       faster insert use joinToLeaf
					* @see joinToLeaf
					*/
				bool insert(ReverseTreeNode* other)
				{
					ReverseTreeNode* from = 0;
					if(find(other->value, from))
					{
						ReverseTreeNode* otherFrom = copy(other);
						for(typename ReverseTreeNode::NodeList_iterator it = otherFrom->prevs.begin(); it != otherFrom->prevs.end(); ++it)
						{
							from->prevs.push_back(*it);
						}
						return true;
					}
					else
					{
						return false;
					}
				}

				/**
					* @brief getter for leaf
					* @return the leaf node
					*/
				ReverseTreeNode*& getLeaf()
				{
					return _leaf;
				}

				/**
					* @brief finder function by value)
					* @param value the finding value
					* @return it is in there
					*/
				bool isIn(const T& value)
				{
					const ReverseTreeNode node(value);
					return search(node, _leaf) != 0;
				}

				/**
					* @brief find function
					* @param value the finded value
					* @param finded the finded node
					* @return it was successfull or not
					*/
				bool find(const T& value, ReverseTreeNode*& finded)
				{
					const ReverseTreeNode node(value);
					finded = search(node, _leaf);
					return finded != 0;
				}

				/**
					* @brief Print operator
					* @param os output stream
					* @param tree the tree
					* @return the output stream
					*/
				friend std::ostream& operator<<(std::ostream& os,const ReverseTree<T>& tree)
				{
					return ReverseTree<T>::print(tree._leaf, os, 1);
				}


			private:
				/**
					* @brief Recursive function for searching
					* @param node the search element
					* @param from the start of the searching
					* @see find
					* @see isIn
					* @return the searched element, 0 if it isn't in there
					*/
				ReverseTreeNode* search(const ReverseTreeNode& node, ReverseTreeNode* from)
				{
					ReverseTreeNode* ret = 0;
					if(node.value == from->value)
					{
						ret = from;
					}

					for(typename ReverseTreeNode::NodeList_iterator it = from->prevs.begin(); it != from->prevs.end() && ret == 0 ; ++it)
					{
						ret = search(node, *it);
					}

					return ret;
				}

				/**
					* @brief Recursive function for deletition
					* @param node delete from this node
					*/
				void release(ReverseTreeNode* node)
				{
					if(node != 0)
					{
						for(typename ReverseTreeNode::NodeList_iterator it = node->prevs.begin(); it != node->prevs.end(); ++it)
						{
							release(*it);
						}
						delete node;
					}
				}

				/**
					* @brief Recursive copy function
					* @param other the copied values
					* @return the copyed root element
					*/
				ReverseTreeNode* copy(ReverseTreeNode* other)
				{
					ReverseTreeNode* root = new ReverseTreeNode(other->value);
					for(typename ReverseTreeNode::NodeList_iterator it = other->prevs.begin(); it != other->prevs.end(); ++it)
					{
						root->prevs.push_back(copy(*it));
					}
					return root;
				}

				/**
					* @brief Recursive simplifing function
					* @details this function delete the multiple neightborn elements
					* @param node the start node for the algorithm
					* @note time cost function
					*/
				void simplify(ReverseTreeNode* node)
				{
					unsigned i = 0;
					while( i < node->prevs.size() )
					{
						unsigned j = i + 1;
						while( j < node->prevs.size() )
						{
							std::cout<<"Node:(i/j/size) "<<i<<"/"<<j<<"/"<<node->prevs.size()<<std::endl;
							if(node->prevs[i]->value == node->prevs[j]->value)
							{
								for(unsigned k = 0; k < node->prevs[j]->prevs.size(); ++k)
								{
									node->prevs[i]->prevs.push_back(node->prevs[j]->prevs[k]);
									node->prevs[j]->prevs[k]->next = node->prevs[i];
								}
								delete node->prevs[j];
								node->prevs.erase(node->prevs.begin() + j);
							}
							else
							{
								++j;
							}
						}
						simplify(node->prevs[i]);
						++i;
					}
				}

				/**
					* @brief recursive print function
					* @param node the start of the printing
					* @param os the outputstream
					* @param deep the deep of the element in the tree
					* @return the output stream
					*/
				static std::ostream& print(ReverseTreeNode* node, std::ostream& os,const int deep)
				{
					os<<node->value<<"\t<-\t";
					for(typename ReverseTreeNode::NodeList_iterator it = node->prevs.begin(); it != node->prevs.end(); ++it)
					{
						ReverseTree<T>::print(*it, os, deep + 1);
						os<<std::endl<<ReverseTree<T>::getIspace(deep*2-1)<<"<-\t";
					}
					return os;
				}

				/**
					* @brief Helper function for indent
					* @details this function create a string
					*          with count tab
					* @param count the number of tabs
					* @return the indent string
					*/
				static inline std::string getIspace(const int count)
				{
					std::string ret = "";
					for(int i = 0; i < count; ++i)
					{
						ret += "\t";
					}
					return ret;
				}

		};

	}
}

#endif // __MATH__GRAPHS__REVERSETREENODE_H
