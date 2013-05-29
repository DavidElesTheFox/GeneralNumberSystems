namespace MATH
{
	namespace Algebra
	{
		template<class T, T Mod>
		Integer_generic<T, Mod>::Integer_generic(): 
			_number()
		{	normalize(); }

		template<class T, T Mod>
		Integer_generic<T, Mod>::Integer_generic(const T number): 
			_number(number)
		{	normalize(); }

		template<class T, T Mod>
		Integer_generic<T, Mod> Integer_generic<T, Mod>::operator-() const
		{
			return -_number;
		}

		template<class T, T Mod>
		Integer_generic<T, Mod>& Integer_generic<T, Mod>::operator++()
		{
			++_number;
			this->_number %= Mod;
	  	normalize();
			return *this;
		}

		template<class T, T Mod>
		Integer_generic<T, Mod>& Integer_generic<T, Mod>::operator--()
		{
			--_number;
			normalize();
			return *this;
		}

		template<class T, T Mod>
		T Integer_generic<T, Mod>::toBase() const
		{
			return _number;
		}

		template<class T, T Mod>
		Integer_generic<T, Mod>& Integer_generic<T, Mod>::
			operator+=(const Integer_generic<T, Mod>& other)
		{
			this->_number += other._number;
			normalize();
			return *this;
		}

		template<class T, T Mod>
		Integer_generic<T, Mod>& Integer_generic<T, Mod>::
			operator-=(const Integer_generic<T, Mod>& other)
		{
			this->_number -= other._number;
			normalize();
			return *this;
		}

		template<class T, T Mod>
		Integer_generic<T, Mod>& Integer_generic<T, Mod>::
			operator*=(const Integer_generic<T, Mod>& other)
		{
			this->_number *= other._number;
			normalize();
			return *this;
		}

		template<class T, T Mod>
		Integer_generic<T, Mod>& Integer_generic<T, Mod>::
			operator/=(const Integer_generic<T, Mod>& other)
		{
			this->_number /= other._number;
			normalize();
			return *this;
		}

		template<class T, T Mod>
		Integer_generic<T, Mod>& Integer_generic<T, Mod>::
			operator%=(const Integer_generic<T, Mod>& other)
		{
			this->_number %= other._number;
			normalize();
			return *this;
		}

		template<class T, T Mod>
		void Integer_generic<T, Mod>::normalize()
		{
			this->_number %= Mod;
		}

	}
}

