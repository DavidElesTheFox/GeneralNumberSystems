#ifndef MATH__ALGEBRA__POLYNOMIAL_H
#error Included only body
#endif

#define TEMP_DEF template<class BaseType,\
	                        class Container,\
                          class number_traits>

#define POLY Polynomial<BaseType, Container, number_traits>

namespace MATH
{
	namespace Algebra
	{
		TEMP_DEF
		POLY::Polynomial(const BaseType& number)
		  :IdealAdicRepresentation<BaseType,
			                         Private::VariableIdeal<BaseType, number_traits>,
											         Container,
											         number_traits>(number)
		{
    }

		TEMP_DEF
    template<class T>
		POLY::Polynomial(const IndexType numOfCoeffs, T first, ...)
		  :IdealAdicRepresentation<BaseType,
			                         Private::VariableIdeal<BaseType, number_traits>,
											         Container,
											         number_traits>()

		{
      va_list vlist;
      va_start(vlist, first);
      this->constructRepresentation(numOfCoeffs.value, first, vlist);
		}

		TEMP_DEF
		POLY::Polynomial(const IdealAdicRepresentation<BaseType,
						                 Private::VariableIdeal<BaseType, number_traits>,
														 Container,
														 number_traits>& other)
		  :IdealAdicRepresentation<BaseType,
						                   Private::VariableIdeal<BaseType, number_traits>,
														   Container,
														   number_traits>(other)
		{		}

		TEMP_DEF
    template<class Ideal>
		POLY::Polynomial(const IdealAdicRepresentation<BaseType,
						                 Ideal,
														 Container,
														 number_traits>& other)
		  :IdealAdicRepresentation<BaseType,
						                   Private::VariableIdeal<BaseType, number_traits>,
														   Container,
														   number_traits>()
		{
      this->_coeffs = other._coeffs;
      this->correctShape();
    }

		TEMP_DEF
		POLY& POLY::operator=(const IdealAdicRepresentation<BaseType,
						                                            Private::VariableIdeal
																								          <BaseType, number_traits>,
																								        Container,
																								        number_traits>& other)
		{
			if (this != &other)
			{
				this->_coeffs = other._coeffs;
        this->correctShape();
			}
			return *this;
		}

		TEMP_DEF
    template<class Ideal>
		POLY& POLY::operator=(const IdealAdicRepresentation<BaseType,
						                                            Ideal,
																								        Container,
																								        number_traits>& other)
		{
			if (this != &other)
			{
				this->_coeffs = other._coeffs;
        this->correctShape();
			}
			return *this;
		}

		TEMP_DEF
		unsigned POLY::getDegree() const
		{
      const_cast<POLY*>(this)->correctShape();
			return getOrder();
		}

		TEMP_DEF
		BaseType POLY::operator()(const BaseType& x) const
		{
      const_cast<POLY*>(this)->correctShape();

			static POLY divisior(2, -x, 1);
      divisior[0] = -x;

			return ((*this) % divisior).getCoeff(0);
		}

		TEMP_DEF
		std::ostream& operator<<(std::ostream& os,
				                     const POLY& a)
		{
      const_cast<POLY*>(&a)->correctShape();

			os << (std::string)a;
			return os;
		}


	}
}

#undef TEMP_DEF
#undef POLY

