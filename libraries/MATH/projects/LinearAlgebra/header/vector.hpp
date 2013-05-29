#ifndef MATH__LINEARALGEBRA__VECTOR_H
#error usage without header
#endif

namespace MATH
{
	namespace LinearAlgebra
	{
		template<typename T>
		Vector<T>::Vector(const int n, const T& defaultValue):
			_data(new T[n]),
			_count(n)
		{
			for(int i=0; i<n; ++i)
				_data[i] = defaultValue;
		}

		template<typename T>
		Vector<T>::Vector():
			_data(0),
			_count(-1)
		{
		}

    template<typename T>
		Vector<T>::Vector(const Vector& v):
			_data(0),
			_count(v._count)
		{
			if (_count >= 0)
			{
				_data = new T[_count];
			  for(int i=0;i<_count;++i)
				  _data[i] = v._data[i];
			}
		}

		template<typename T>
		Vector<T>::Vector(const T* t,const unsigned count):
			_data(new T[count]),
			_count(count)
		{
			for(int i=0;i<_count;++i)
				_data[i]=t[i];
		}

		template<typename T>
		Vector<T> Vector<T>::getSubVector(const int low, const int high) const
		{
			if (_count >= 0)
			{
				if(low >= 0 
					 && high <= this->_count 
					 && high > low)
				{
					Vector<T> subVector(high - low);
					for(int i=low;i<high;++i)
					{
						subVector[i-low] = _data[i];
					}
					return subVector;
				}else if(high==low)
				{
					Vector<T> subVector(1);
					subVector[0] = _data[low];
					return subVector;
				}else
				{
					throw Exceptions::RuntimeException("wrong sub vector dimensions!");
				}
			}
			else
			{
				return Vector<T>();
			}
		}

		template<typename T>
		int Vector<T>::getDimension() const 
		{
			return _count;
		}

		template <typename T>
		Vector<T>& Vector<T>::operator= (const Vector<T>& v)
		{
			if (this != &v)
			{
				if (_count != v._count)
				{
          if (_data != 0)
            delete[] _data;
					_count = v._count;
					if (_count >= 0)
						_data = new T[_count];
					else
						_data = 0;
				}
				if (_count >= 0)
				{
					for(int i=0;i<_count;++i)
						_data[i] = v._data[i];
				}
			}
			return *this;
		}

		template<typename T>
		Vector<T>& Vector<T>::operator+= (const Vector<T>& v)
		{
			for(int i=0; i<_count ; ++i)
			{
				_data[i] += v[i];
			}
			return *this;
		}

	}
}

