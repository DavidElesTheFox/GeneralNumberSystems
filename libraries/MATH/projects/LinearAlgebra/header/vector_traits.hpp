namespace MATH
{
	namespace LinearAlgebra
	{
		template<typename T,
			       class Vector>
		Vector Vector_traits<T, Vector>::
		  create(const int rowNum)
		{
			return Vector(rowNum);
		}

		template<typename T,
			       class Vector>
		T Vector_traits<T, Vector>::
		  getElement(const int x, const Vector& v)
		{
			return v[x];
		}

		template<typename T,
			       class Vector>
		T& Vector_traits<T, Vector>::
		  getElement(const int x, Vector& v)
		{
			return v[x];
		}

		template<typename T,
			       class Vector>
		void Vector_traits<T, Vector>::
		  setElement(const int x, const T& value, Vector& v)
		{
			v[x] = value;
		}

		template<typename T,
			       class Vector>
		Vector Vector_traits<T, Vector>::
		  copy(const Vector& v)
		{
			return v;
		}

		template<typename T,
			       class Vector>
		int Vector_traits<T, Vector>::
		  getDimension(const Vector& v)
		{
			return v.getDimension();
		}

		template<typename T,
			       class Vector>
		bool Vector_traits<T, Vector>::
		  equals(const Vector& a,
					   const Vector& b)
		{
			return a == b;
		}

		template<typename T,
			       class Vector>
		void Vector_traits<T, Vector>::
		  print(const Vector& v,
					  std::ostream& os)
		{
			os << v;
		}

		template<typename T,
			       class Vector>
		void Vector_traits<T, Vector>::
		  read(std::istream& is,
					 Vector& v)
		{
			is >> v;
		}

	}
}

