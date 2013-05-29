
#include <assert.h>

namespace MATH
{
	namespace LinearAlgebra
	{

		template<class T>
		Matrix<T>::Matrix(const int rowNum,
				              const int colNum,
											const T& defaultValue,
											const DIRECTION dir):
				_data(0),
				_dir(dir),
				_rowNum(rowNum),
				_colNum(colNum)
		{
			if(_dir == ROW)
			{
				_data = new Vector<T>*[_rowNum];
				for(int i = 0; i < _rowNum; ++i)
					_data[i] = new Vector<T>(_colNum, defaultValue);
			}
			else
			{
				_data = new Vector<T>*[_colNum];
				for(int i = 0; i < _colNum; ++i)
					_data[i] = new Vector<T>(_rowNum, defaultValue);
			}
		}
		template<class T>
		Matrix<T>::Matrix():
			_data(0),
			_dir(ROW),
			_rowNum(-1),
			_colNum(-1)
		{

		}

		template<class T>
		Matrix<T>::Matrix(const int rowNum,
				              const int colNum,
											const DIRECTION dir, ...):
		_data(0),
		_dir(dir),
		_rowNum(rowNum),
		_colNum(colNum)
		{
			if(_dir == ROW)
			{
				_data = new Vector<T>*[_rowNum];
				for(int i = 0; i < _rowNum; ++i)
					_data[i] = new Vector<T>(_colNum);
			}
			else
			{
				_data = new Vector<T>*[_colNum];
				for(int i = 0; i < _colNum; ++i)
					_data[i] = new Vector<T>(_rowNum);
			}
			va_list vl;
			va_start(vl, dir);
			for(int i = 0; i <_rowNum;++i)
				for(int j = 0; j<_colNum;++j)
				{
					(*this)(i,j) = va_arg(vl,T);
				}
		}

		template<class T>
		Matrix<T>::Matrix(const Matrix<T>& other):
				 _data(0),
				 _dir(other._dir),
				 _rowNum(other._rowNum),
				 _colNum(other._colNum)
		{
			if (!other.isEmpty())
			{
				copy(other,
						 true);
			}
		}

		template<class T>
		Matrix<T>::Matrix(const Vector<T>& other):
				_data(0),
				_dir(COL),
				_rowNum(other.count),
				_colNum(1)
		{
			_data = new Vector<T>*[_colNum];
			_data[0] = new Vector<T>(other);
		}

		template<class T>
		Matrix<T>& Matrix<T>::operator=(const Matrix<T>& other)
		{
			if (this != &other)
			{
				bool needCreation = false;
				if (_colNum != other._colNum
						|| _rowNum != other._rowNum
						|| _dir != other._dir)
				{
					needCreation = true;
					release();
					this->_colNum = other._colNum;
					this->_rowNum = other._rowNum;
					this->_dir = other._dir;
				}

				if (!other.isEmpty())
				{
					copy(other, needCreation);
				}
			}
			return *this;
		}

		template<class T>
		Matrix<T>& Matrix<T>::operator=(const Vector<T>& other)
		{
			release();
			_dir = COL;
			_rowNum = other.count;
			_colNum = 1;
			_data = new Vector<T>*[_colNum];
			_data[0] = new Vector<T>(other);
		}

		template<class T>
		Vector<T> Matrix<T>::operator[] (const int i) const 
		{
			assert(i < _rowNum && i >= 0);
			
			if(_dir == ROW)
			{
				return *_data[i];
			}
			else
			{
				Vector<T> l_ret(_rowNum);
				for(int j = 0; i < _rowNum; ++j)
					l_ret[j] = (*_data[j])[i];
				return l_ret;
			}
		}

		template<class T>
		Matrix<T>& Matrix<T>::operator+=(const Matrix<T>& b) 
		{
			for(int i = 0; i < _rowNum; ++i)
				for(int j = 0; j < _colNum; ++j)
					(*this)(i,j) += b(i,j);
			return *this;
		}

		template<class T>
		void Matrix<T>::resize(const int rowNum, const int colNum)
		{
			release();
			_rowNum = rowNum;
			_colNum = colNum;
			if(_dir == ROW)
			{
				_data = new Vector<T>*[_rowNum];
				for(int i = 0; i < _rowNum; ++i)
					_data[i] = new Vector<T>(_colNum);
			}
			else
			{
				_data = new Vector<T>*[_colNum];
				for(int i = 0; i < _colNum; ++i)
					_data[i] = new Vector<T>(_rowNum);
			}
		}

		template<class T>
		void Matrix<T>::copy(const Matrix& other,
				                 const bool needCreation)
		{
			if(_dir == ROW)
			{
				if (needCreation)
				{
					_data = new Vector<T>*[_rowNum];
					for(int i = 0; i < _rowNum; ++i)
					{
						_data[i] = new Vector<T>(_colNum);
						for (int j = 0; j < _colNum; ++j)
							(*_data[i])[j] = (*other._data[i])[j];
					}
				}
				else
				{
					for (int i = 0; i < _rowNum; ++i)
						for (int j = 0; j < _colNum; ++j)
						{
							(*_data[i])[j] = (*other._data[i])[j];
						}
				}
			}
			else
			{
				if (needCreation)
				{
					_data = new Vector<T>*[_colNum];
					for(int i = 0; i < _colNum; ++i)
					{
						_data[i] = new Vector<T>(_rowNum);
						for (int j = 0; j < _rowNum; ++j)
						{
							(*_data[i])[j] = (*other._data[i])[j];
						}
					}
				}
				else
				{
					for (int i = 0; i < _colNum; ++i)
						for (int j = 0; j < _rowNum; ++j)
						{
							(*_data[i])[j] = (*other._data[i])[j];
						}
				}
			}
		}

	}
	
}
