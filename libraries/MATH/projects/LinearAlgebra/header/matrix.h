#ifndef __MATH__LINEARALGEBRA__MATRIX_H
#define __MATH__LINEARALGEBRA__MATRIX_H

#include <stdarg.h>
#include "vector.h"
#include <Exceptions/overflowexception.h>

/**
	* @file matrix.h
	* @brief conatins Matrix class
	* @see MATH::LinearAlgebra::Matrix
	*/

namespace MATH
{
	namespace LinearAlgebra
	{

		/**
			* @brief This is a templated matrix representation.
			* @details It is a special reprezentation. This class
			*        based on the vector class, and the idea was
			*        that the matrix is a set of vectors.
			*        You can determine the matrix vectors type,
			*        row or column vectors, it could be very usefull
			*        for example in vector multiplication, if you know, 
			*        that you always multiply a vector from left side you
			*        can set that the matrix is contains row vectors and it is
			*        faster. In other hand you can get the matrix one col in 
			*        vector object.
			* @see Matrix_traits
			* @see MatrixCalculator
			* @tparam T the type of the element
			*/
		template<typename T>
		class Matrix
		{
			public:
				/**
					* @brief the vectors direction
					*/
				enum DIRECTION{ROW, COL};

			protected:
				/**
					* @brief the vector set of the matrix
					*/
				Vector<T>** _data;

				/**
					* @brief the direction of the current vectors
					*/
				DIRECTION _dir;
			private:
				/**
					* @brief first dimension
					*/
				int _rowNum;

				/**
					* @brief second dimension
					*/
				int _colNum;
			public:
				/**
					* @brief Simple constructor
					* @param rowNum the first dimension of the matrix
					* @param colNum the second dimension of the matrix
					* @param defaultValue the default value of the element
					* @param dir the direction of the vectors
					*/
				explicit Matrix(const int rowNum, const int colNum, const T& defaultValue = T(), const DIRECTION dir = ROW);
		
				/**
					* @brief Uploader constructor
					* @details You can set the element of the matrix
					* @example Matrix m(2,2,1,0,0,1) 
					* @param rowNum the first dimension of the matrix
					* @param colNum the second dimension of the matrix
					* @param dir the direction of the vectors
					* @param ... the element of the matrix
					*/
				explicit Matrix(const int rowNum, const int colNum, const DIRECTION dir, ...);

				/**
					* @brief copy constructor
					* @param other the other matrix
					*/
				Matrix(const Matrix<T>& other);

				/**
					* @brief copy constructor for vecotrs
					* @details you can create matrix form a vector
					* @param other the vector
					*/
				Matrix(const Vector<T>& other);

				/**
					* @brief Default constructor
					* @warning by default a matrix is a -1 x -1 dimensional
					*          matrix with null data
					* @note It is neccessary for containers.
					*/
				Matrix();

				/**
					* @brief simple destructor
					*/
				virtual ~Matrix()
				{
					release();
				}

				/**
					* @brief creation operator for matricies
					* @param other the matrix, wich will be copied
					* @return reference to the current Matrix
					*/
				Matrix& operator=(const Matrix<T>& other);

				/**
					* @brief creation operator for vectors
					* @param other the vector, wich will be copied
					* @return reference to the current Matrix
					*/
				Matrix& operator=(const Vector<T>& other);


				/**
					* @brief return the i-th row vector
					* @details If the matrix has column vectors
					*          it is a slow function
					* @param i the row id
					* @return the i-th row vector
					*/
				Vector<T> operator[] (const int i) const; 

				/**
					* @brief getter for elements
					* @param i the row id
					* @param j the col id
					* @return reference to the matrix (i,j)-th element
					* @warning without check dou to performance
					*/
				inline T& operator() (const int i, const int j) 
				{
					return _dir == ROW ? (*_data[i])[j]: (*_data[j])[i];
				}

				/**
					* @brief getter for elements v
					* @param i the row id
					* @param j the col id
					* @return the matrix (i,j)-th element
					* @warning without check dou to performance
					*/
				inline T operator() (const int i, const int j) const 
				{
					return _dir == ROW ? (*_data[i])[j]: (*_data[j])[i];
				}

				/**
					* @brief simple operator
					* @details add this matrix to an other
					* @param b the other matrix
					* @return refernce to the current matrix
					*/
				Matrix<T>& operator+=(const Matrix<T>& b);

				/**
					* @brief resize the matrix
					* @param rowNum the new parameter of the matrix
					* @param colNum the new parameter of the matrix
					*/
				void resize(const int rowNum, const int colNum);

				/**
					* @brief getter for dimensions
					* @param rowCount the first dimension of the matrix
					* @param colCount the second dimension of the matrix
					*/
				inline void getDimension(int& rowCount, int& colCount) const 
				{
					rowCount = _rowNum;
					colCount = _colNum;
				}

				/**
					* @brief getter for row count
					* @return the first dimension of the matrix
					*/
				inline int getRowCount() const 
				{
					return _rowNum;
				}

				/**
					* @brief getter for column count
					* @return the second dimension of the matrix
					*/
				inline int getColCount() const
				{
					return _colNum;
				}

				/**
					* @brief simple operator
					* @param a the left operand
					* @param b the right operand
					* @return a == b
					*/
				friend bool operator==(const Matrix<T>& a, const Matrix<T>& b)
				{
					if(a._colNum != b._colNum || a._rowNum != b._rowNum)
						return false;
					bool l = true;
					for(int i = 0; i < a._rowNum && l;++i)
						for(int j = 0; j < a._colNum && l; ++j)
							l = l && a(i,j)==b(i,j);
					return l;
				}

				/**
					* @brief simple operator
					* @param a the left operand
					* @param b the right operand
					* @return a + b
					*/
				friend Matrix<T> operator+(const Matrix<T>& a, const Matrix<T>& b)
				{
					if(a._rowNum != b._rowNum || a._colNum != b._colNum)
						throw Exceptions::WrongDimensionException("Wrong dimension at adding matrices");
					Matrix<T> ret(a._rowNum,a._colNum);
					for(int i = 0; i < a._rowNum; ++i)
						for(int j = 0; j < a._colNum; ++j)
							ret(i,j) = a(i,j) + b(i,j);
					return ret;
				}

				/**
					* @brief simple operator
					* @param a the left operand
					* @param b the right operand
					* @return a - b
					*/
				friend Matrix<T> operator-(const Matrix<T>& a, const Matrix<T>& b)
				{
					if(a._rowNum != b._rowNum || a._colNum != b._colNum)
						throw Exceptions::WrongDimensionException("Wrong dimension at minus two matrices");
					Matrix<T> ret(a._rowNum,a._colNum);
					for(int i = 0; i < a._rowNum; ++i)
						for(int j = 0; j < a._colNum; ++j)
							ret(i,j) = a(i,j) - b(i,j);
					return ret;
				}

				/**
					* @brief simple operator
					* @param a the left operand
					* @param b the right operand
					* @return a * b
					*/
				friend Matrix<T> operator*(const Matrix<T>& a, const Matrix<T>& b)
				{
					if(a._colNum != b._rowNum)
						throw Exceptions::WrongDimensionException("Wrong dimension at minus two matrices");
					Matrix<T> ret(a._rowNum,b._colNum, T());
					for(int i = 0; i < a._rowNum; ++i)
						for(int j = 0; j < a._colNum; ++j)
							for(int k = 0; k < a._colNum; ++k)
								ret(i,j) += a(i,k) * b(k,j);
					return ret;
				}

				/**
					* @brief simple operator
					* @param a the left operand
					* @param b the right operand
					* @return a * b
					*/
				friend Vector<T> operator*(const Matrix<T>& a, const Vector<T>& b)
				{
					if(a._colNum != b.getDimension())
						throw Exceptions::WrongDimensionException("Wrong dimension at minus two matrices");
					Vector<T> ret(a._rowNum, T());
					for(int i = 0; i < a._rowNum; ++i)
						for(int j = 0; j < a._colNum; ++j)
								ret[i] += a(i,j) * b[j];
					return ret;
				}

				/**
					* @brief simple operator
					* @param a the left operand
					* @param b the right operand
					* @return a * b
					*/
				friend Vector<T> operator*(const Vector<T>& a, const Matrix<T>& b)
				{
					if(b._rowNum != a.getDimension())
						throw Exceptions::WrongDimensionException("Wrong dimension at minus two matrices");
					Vector<T> ret(b._colNum, T());
					for(int i = 0; i < b._colNum; ++i)
						for(int j = 0; j < b._rowNum; ++j)
								ret[i] += b(j,i) * a[j];
					return ret;
				}

				/**
					* @brief simple operator
					* @param a the left operand
					* @param b the right operand
					* @return a * b
					*/
				friend Matrix<T> operator*(const Matrix<T>& a, const T& b)
				{
					Matrix<T> ret(a._rowNum,a._colNum);
					for(int i = 0; i < a._rowNum; ++i)
						for(int j = 0; j < a._colNum; ++j)
							ret(i,j) = a(i,j) * b;
					return ret;
				}

				/**
					* @brief simple operator
					* @param a the left operand
					* @param b the right operand
					* @return a * b
					*/
				friend Matrix<T> operator*(const T& a, const Matrix<T>& b)
				{
					Matrix<T> ret(b._rowNum,b._colNum);
					for(int i = 0; i < b._rowNum; ++i)
						for(int j = 0; j < b._colNum; ++j)
							ret(i,j) = b(i,j) * a;
					return ret;
				}

				/**
					* @brief simple writer function
					* @param os the output stream
					* @param mx the given matrix
					* @return the os dou to chaining
					*/
				friend std::ostream& operator<<(std::ostream& os, const Matrix<T>& mx)
				{
          os << mx._rowNum << " " << mx._colNum << std::endl;
					for(int i = 0; i < mx._rowNum-1; ++i)
					{
						for(int j = 0; j < mx._colNum-1; ++j)
							os<<mx(i,j)<<"\t";
						os<<mx(i,mx._colNum-1)<<std::endl;
					}
					for(int j = 0; j < mx._colNum-1; ++j)
							os<<mx(mx._rowNum-1,j)<<"\t";
						os<<mx(mx._rowNum-1,mx._colNum-1);
					return os;
				}

				/**
					* @brief reader funciton
					* @details the format: rowNum ws colNum ws element(0,0) ws element(0,1) ...
					*          ws means weith-space
					* @param is the imput stream
					* @param mx the matrix
					* @return is
					*/
				friend std::istream& operator>>(std::istream& is, Matrix<T>& mx)
				{
					is>>mx._rowNum;
					is>>mx._colNum;

					delete[] mx._data;

					if(mx._dir == ROW)
					{
						mx._data = new Vector<T>*[mx._rowNum];
						for(int i = 0; i < mx._rowNum; ++i)
							mx._data[i] = new Vector<T>(mx._colNum);
					}
					else
					{
						mx._data = new Vector<T>*[mx._colNum];
						for(int i = 0; i < mx._colNum; ++i)
							mx._data[i] = new Vector<T>(mx._rowNum);
					}


					for(int i = 0; i < mx._rowNum; ++i)
						for(int j = 0; j < mx._colNum; ++j)
            {
							is>>mx(i,j);
            }
					return is;
				}

			private:

				/**
					* @brief release function for element deletition
					*/
				void release()
				{
					int size = _dir == ROW ? _rowNum : _colNum;
					for(int i = 0; i < size; ++i)
					{
						delete _data[i];
					}
          if (_data != 0)
  					delete[] _data;
					_data = 0;
				}

				/**
					* @brief It is empty if we created the matrix with
					*        default constructor
					* @return is empty or not
					*/
				bool isEmpty() const
				{
					return _rowNum < 0
						     || _colNum < 0
								 || _data == 0;
				}

				void copy(const Matrix& other,
						      const bool needCreation);
		};
	}
}

#include "matrix.hpp"

#endif
