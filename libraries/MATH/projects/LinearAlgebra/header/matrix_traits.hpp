#ifndef __MATH__LINEARALGEBRA_MATRIX_TRAITS_H
#error Include without matrix_traits.h
#endif

namespace MATH
{
	namespace LinearAlgebra
	{

		template<typename T,
			       class Matrix>
		Matrix Matrix_traits<T, Matrix>
		  ::createMatrix(const int rowNum,
									   const int colNum)
		{
			return Matrix(rowNum,
					          colNum);
		}

		template<typename T,
						 class Matrix>
		T Matrix_traits<T, Matrix>
		  ::getElement(const int x,
									 const int y,
									 const Matrix& m)
		{
			return m(x,y);
		}

		template<typename T,
			       class Matrix>
		void Matrix_traits<T, Matrix>::
		  setElement(const int x, 
		             const int y,
		             const T& value,
		             Matrix& m)
		{
			m(x,y) = value;
		}


		template<typename T,
					   class Matrix>
		T& Matrix_traits<T, Matrix>::
		  getElement(const int x,
		             const int y,
		             Matrix& m)
		{
			return m(x,y);
		}


		template<typename T,
						 class Matrix>
		void Matrix_traits<T, Matrix>::
		  resize(const int rowNum,
						 const int colNum,
						 Matrix& m)
		{
			m.resize(rowNum, colNum);
		}

		template<typename T,
						 class Matrix>
		Matrix Matrix_traits<T, Matrix>::
		  copy(const Matrix& m)
		{
			return m;
		}

		template<typename T,
						 class Matrix>
		void Matrix_traits<T, Matrix>::
		  getDimension(int &rowNum,
									 int &colNum,
									 const Matrix& m)
		{
			return m.getDimension(rowNum,
														colNum);
		}

		template<typename T,
						 class Matrix>
		int Matrix_traits<T, Matrix>::
		  getRowNum(const Matrix& m)
		{
			return m.getRowCount();
		}

		template<typename T,
						 class Matrix>
		int Matrix_traits<T, Matrix>::
		  getColNum(const Matrix& m)
		{
			return m.getColCount();
		}

		template<typename T,
						 class Matrix>
		bool Matrix_traits<T, Matrix>::
		  equals(const Matrix& a,
						 const Matrix& b)
		{
			return a == b;
		}

		template<typename T,
						 class Matrix>
		void Matrix_traits<T, Matrix>::
		  print(const Matrix& m,
					  std::ostream& os)
		{
			os << m;
		}

		template<typename T,
						 class Matrix>
		void Matrix_traits<T, Matrix>::
		  read(std::istream& is,
					 Matrix& m)
		{
			is >> m;
		}
	}
}

