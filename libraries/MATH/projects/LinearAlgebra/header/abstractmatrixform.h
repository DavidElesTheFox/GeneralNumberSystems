#ifndef MATH__LINEARALGEBRA__ABSTRACTMATRIXFORM_H
#define MATH__LINEARALGEBRA__ABSTRACTMATRIXFORM_H

#include <Exceptions/parameterexception.h>
#include <Exceptions/runtimeexception.h>

#include <map>

/**
	* @file abstractmatrixform.h
	*
	* @brief   Templated AbstractMatrixForm
	* @details This file contains the implementation of
	*          the AbstractMatrixForm class
	* @see MATH::LinearAlgebra::AbstractMatrixForm
	*/

namespace MATH
{
	namespace LinearAlgebra
	{
		/**
			* @brief This is an abstract class for special matrix forms.
			* @details This class store the original matrix, and the forms in a map
			* @see MATH::LinearAlgebra::AdjointMatrix
			* @param Matrix the used matrix class. It could be any type of Matrices.
			*/
		template<class Matrix>
		class AbstractMatrixForm
		{
			protected:
				/**
					* @brief std::map for string and matrices pairs
					*/
				typedef std::map<std::string, Matrix> MatrixMap;
				/**
					* @brief Const iterator for MatrixMap
					*/
				typedef typename MatrixMap::const_iterator MatrixMap_const_iterator;
				/**
					* @brief the elements of the Matrix form
					*/
				MatrixMap _elements;
				/**
					* @brief the original matrix. If it changed, the Form will be recalculated.
					*/
				Matrix _original;
			private:
				/**
					* @brief This varible strore, that from the last computation the original matrix
					*        is changed or not
					*/
				bool _changed;
			public:
				
				/**
					* @brief Default constructor
					* @param m the "attractor" matrix
					*/
				explicit AbstractMatrixForm(const Matrix& m);
	
				/**
					* @brief empty virtual destructor
					*/
				virtual ~AbstractMatrixForm();
				/*
					 Unnecessary
					 -----------
					 the default is enough 
				AbstractMatrixForm(const AbstractMatrixForm& other);

				AbstractMatrixForm& operator=(const AbstractMatrixForm& other);
				*/

				/**
					* @brief Constant getter for original matrix
					* @return the original matrix
					*/
        Matrix getOriginalMatrix() const;

				/**
					* @brief Getter for original matrix
					* @return reference to the original matrix
					* @note after this function calling the object
					*       the form will be recalculating
					*/
				Matrix& getOriginalMatrix();

				/**
					* @brief Getter for elements of the matrix form
					* @param name special name of matrix form elements
					* @exception Exceptions::RuntimeException element not found
					* @return The spcific matrix form element
					*/
				Matrix operator[](const std::string& name);

				/**
					* @brief Getter for elements of the matrix form
					* @param elementCount number of matrix form elements
					* @exception Exceptions::RuntimeException element not found
					* @return The spcific matrix form element
					*/
				Matrix operator[](const int& elementCount);

			protected:
				/**
					* @brief virtual function for element calculation
					* @warning don't call directly only used from calculate
					*          function
					* @see calculate
					*/
				virtual void calculateElements() = 0;
			private:
				/**
					* @brief This function contains the logic of calculation
					* @details This function is called from operator[], if this
					*          object isn't calculated.
					* @see operator[]
					*/
				void calculate();

		};
	}
}

#include "abstractmatrixform.hpp"


#endif //MATH__LINEARALGEBRA__ABSTRACTMATRIXFORM_H

