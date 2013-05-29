#ifndef __MATH__GRAPHS__FOREST_H
#define __MATH__GRAPHS__FOREST_H

#include <vector>
#include <iostream>

/**
	* @file forest.h
	* @brief This file contains a forest representation
	* @see MATH::Graphs::Forest
	*/

namespace MATH
{
	namespace Graphs
	{
		/**
			* @brief The representation of an forest
			* @tparam T the node type in the tree
			* @tparam the Tree type
			* @todo Refactoring: Now all of the functions are inline
			* @todo use Tree_traits
			*/
		template<class T, class Tree>
		class Forest : public std::vector<Tree>
		{
			public:

				/**
					* @brief virtual destructor
					*/
				virtual ~Forest()
				{	}

				/**
					* @brief find an element in the tree
					* @param item the node
					*/
				int isIn(const T& item)
				{
					unsigned i = 0;
					for(;i < this->size(); ++i)
					{
						if(this->at(i).isIn(item))
							return i;
					}
					return -1;
				}

				/**
					* @brief Insert a new tree to one of the forest
					*        element
					* @details it's not equals the push_back function,
					*          because this function try to inserted
					*          the parameter tree to an existing tree
					* @param tree the new tree
					* @return the id of the tree, where the insertation
					*         was successful, or -1 if it isn't
					*/
				int insert(const Tree& tree)
				{
					unsigned i = 0;
					bool l = false;
					for(; i < this->size() && !l; ++i)
					{
						l = this->at(i).insert(tree);
					}
					return l? static_cast<int>(i - 1) : -1;
				}

				/**
					* @brief Insert a new tree to one of the forest
					*        element
					* @details This function try to join the new tree
					*          to an existing tree's leaf
					* @note This function may has a hughe time cost
					* @param tree the new tree
					* @return the id of the tree, where the join was
					*          successful, or -1 if it isn't
					*/
				int joinToLeafs(const Tree& tree)
				{
					unsigned i = 0;
					bool l = false;
					for(; i < this->size() && !l; ++i)
					{
						l = this->at(i).joinToLeaf(tree);
					}
					return l? static_cast<int>(i - 1) : -1;
				}

				/**
					* @brief simplifing the forest
					* @details this function delete the duplicated elements
					* @note This function may has a hughe time cost
					*/
				void simplify()
				{
					for(unsigned i = 0; i < this->size(); ++i)
					{
						this->at(i).simplify();
					}
				}


				/**
					* @brief Printer function
					* @param os ouput stream
					* @param forest the forest
					*/
				friend std::ostream& operator<<(std::ostream& os, const Forest<T,Tree>& forest)
				{
					unsigned i = 0;
					for(;i < forest.size() ;++i)
					{
						os<<"==========="<<i<<"==============="<<std::endl<<forest[i]<<std::endl<<"==========================="<<std::endl;
					}
					return os;
				}

		};

	}
}

#endif // __MATH__GRAPHS__FOREST_H
