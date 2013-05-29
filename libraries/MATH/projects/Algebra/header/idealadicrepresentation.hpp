#ifndef MATH__ALGEBRA__IDEALADICREPRESENTATION_H
#error Included only body
#endif

#include <sstream>
#include <list>
#include <algorithm>

#include <Exceptions/parameterexception.h>


#define TEMP_PAR template<class BaseType,\
                          class IdealType,\
                          class Container,\
                          class number_traits>

#define IDEAL_REP IdealAdicRepresentation<BaseType, IdealType, Container, number_traits>



namespace MATH
{
	namespace Algebra
	{
		TEMP_PAR
		IDEAL_REP::IdealAdicRepresentation(const BaseType& value,
				                               unsigned shiftValue)
		  : _coeffs(shiftValue, number_traits::additiveUnit)
		{
			BaseType q[] = {value, value};
			unsigned i = 0;
			std::list<BaseType> divisiors;
			do
			{
				BaseType coeff;
				IdealType::division(q[i & 0x01], q[(i + 1) & 0x01 ], coeff);
				FindEquals finder = q[(i + 1) & 0x01];
				_coeffs.push_back(coeff);
				if (find_if(divisiors.begin(), divisiors.end(), finder) != divisiors.end())
        {
          //The 0 is the only periodic element
          if (NumCalc::equals(coeff, number_traits::additiveUnit))
            return;
          std::cerr << value << std::endl;
					throw Exceptions::ParameterException("Infinity representation");
        }

				divisiors.push_back(q[(i + 1) & 0x01]);
			}while (!NumCalc::equals(q[++i & 0x01], number_traits::additiveUnit));
		}

		TEMP_PAR
    template<class T>
		IDEAL_REP::IdealAdicRepresentation(const IndexType numOfElement, const T& first, ...)
		{
			va_list vlist;
			va_start(vlist, first);
      constructRepresentation(numOfElement.value, first, vlist);
		}

  /*  TEMP_PAR
    template<class T>
    IDEAL_REP::IdealAdicRepresentation
      (const IdealAdicRepresentation<T, IdealType, Container, number_traits>& other)
    {
      for (unsigned i = 0; i < other._coeffs.size(); ++i)
        (*this)[i] = other[i];
    }

    TEMP_PAR
    template<class T>
    IDEAL_REP&
      IDEAL_REP::operator=
      (const IdealAdicRepresentation<T, IdealType, Container, number_traits>& other)
    {
      if (this != &other)
      {
        _coeffs.clear();
        for (unsigned i = 0; i < other._coeffs.size(); ++i)
          (*this)[i] = other[i];
      }
      return *this;
    }*/

		TEMP_PAR
		IDEAL_REP& IDEAL_REP::operator++()
		{
			(*this) += 1;
			return *this;
		}

		TEMP_PAR
		IDEAL_REP IDEAL_REP::operator++(int)
		{
			IDEAL_REP copy = *this;
			(*this) += 1;
			return copy;
		}

		TEMP_PAR
		IDEAL_REP& IDEAL_REP::operator--()
		{
			(*this) -= 1;
			return *this;
		}

		TEMP_PAR
		IDEAL_REP IDEAL_REP::operator--(int)
		{
			IDEAL_REP copy = *this;
			(*this) -= 1;
			return copy;
		}

		TEMP_PAR
		IDEAL_REP IDEAL_REP::operator-() const
		{
      IDEAL_REP copy = *this;
			copy *= IDEAL_REP(-number_traits::multiplicativeUnit);
			return copy;
		}

		TEMP_PAR
		IDEAL_REP& IDEAL_REP::operator+=(const IDEAL_REP& a)
		{
			for (unsigned i = 0; i < a._coeffs.size(); ++i)
			{
				(*this)[i] += a.getCoeff(i);
			}
			carrying();
			correctShape();
			return *this;
		}

		TEMP_PAR
		IDEAL_REP& IDEAL_REP::operator-=(const IDEAL_REP& a)
		{
			for (unsigned i = 0; i < a._coeffs.size(); ++i)
			{
				(*this)[i] -= a.getCoeff(i);
			}
			carrying();
			correctShape();
			return *this;
		}

		TEMP_PAR
		IDEAL_REP& IDEAL_REP::operator*=(const IDEAL_REP& a)
		{
			(*this) = (*this) * a;
			return *this;
		}

		TEMP_PAR
		IDEAL_REP& IDEAL_REP::operator/=(const IDEAL_REP& a)
		{
			IDEAL_REP tmp;
			*this = remainderDivision(*this, a, tmp);
			return *this;
		}

		TEMP_PAR
		IDEAL_REP& IDEAL_REP::operator%=(const IDEAL_REP& a)
		{
			IDEAL_REP tmp;
			remainderDivision(*this, a, tmp);
			*this = tmp;
			return *this;
		}

		TEMP_PAR
		IDEAL_REP::operator std::string() const
		{
			std::ostringstream os;
			for (unsigned i = _coeffs.size() - 1; i > 0; --i)
			{
				os << _coeffs[i] << "*";
			  os << IdealType::strShape << "^(" << i << ")";
				os << " + ";
			}
			os << _coeffs[0] << std::flush;

			return os.str();
		}

		TEMP_PAR
		BaseType IDEAL_REP::getCoeff(const unsigned coeff) const 
		{
			return ((coeff >= _coeffs.size()) ? number_traits::additiveUnit : _coeffs[coeff]);
		}

		TEMP_PAR
		IDEAL_REP IDEAL_REP::operator()(const unsigned startCoeff,
						                        const unsigned lastCoeff) const
		{
			IDEAL_REP ret;
			/*ret._coeffs.insert(ret._coeffs.begin(), 
					               _coeffs.begin() + startCoeff,
												 _coeffs.begin() + lastCoeff);*/
			for (unsigned i = startCoeff; i <= lastCoeff; ++i)
				ret[i - startCoeff] = this->getCoeff(i);
			return ret;
		}

		TEMP_PAR
		unsigned IDEAL_REP::getOrder() const
		{
			return _coeffs.size() - 1;
		}

		TEMP_PAR
		const BaseType& IDEAL_REP::lcoeff() const
		{
			return _coeffs[_coeffs.size() - 1];
		}

		TEMP_PAR
		IDEAL_REP IDEAL_REP::pseudoRemainderDivision(const IDEAL_REP& a,
				                                         const IDEAL_REP& b,
																								 IDEAL_REP& rem)
		{
			if (a.getOrder() < b.getOrder())
			{
				rem = a;
				return IDEAL_REP();
			}

			IDEAL_REP copy = a 
				               * NumCalc::pow(b.lcoeff(), a.getOrder() - b.getOrder() + 1);
			return remainderDivision(copy, b, rem);
		}

		TEMP_PAR
		IDEAL_REP IDEAL_REP::remainderDivision(const IDEAL_REP& a,
				                                   const IDEAL_REP& b,
																				   IDEAL_REP& rem)
		{
      if (a.getOrder() == b.getOrder()
          && a.getOrder() == 0)
      {
        // The % operator not defined every type like float, so
        // we have to compute in a different way
        // a = qb + r => a - qb = r
        rem = a[0] - (a[0] / b[0] * b[0]); 
        return a[0] / b[0];
      }

			IDEAL_REP divisior;
			IDEAL_REP copy = a;
			
			while(copy.getOrder() >= b.getOrder()
					  && !(copy.getOrder() == 0 
						     && NumCalc::equals(copy.getCoeff(0),
                                    number_traits::additiveUnit)))
			{
				unsigned shiftVal = copy.getOrder() - b.getOrder();
				BaseType actCoeff = copy.lcoeff() / b.lcoeff();
				divisior += IDEAL_REP(actCoeff, shiftVal);
				for (unsigned i = 0; i < b.getOrder() + 1; ++i)
				{
					copy[copy.getOrder() - i] -= b.getCoeff(b.getOrder() - i) * actCoeff;
				}
				copy.correctShape();
			}
			copy.carrying();
			rem = copy;
			return divisior;
		}

		TEMP_PAR
		bool operator==(const IDEAL_REP& a, const IDEAL_REP& b)
		{
      bool eq = true;
      unsigned max = a.getOrder() > b.getOrder() ? a.getOrder()
                                                 : b.getOrder();
      for (unsigned i = 0; i <= max && eq; ++i)
      {
        eq = IDEAL_REP::NumCalc::equals(a[i], b[i]);
      }
			return eq;
		}

		TEMP_PAR
		bool operator!=(const IDEAL_REP& a, const IDEAL_REP& b)
		{
			return !(a == b);
		}

		TEMP_PAR
		IDEAL_REP operator+(const IDEAL_REP& a, const IDEAL_REP& b)
		{
			IDEAL_REP ret = a;
			ret += b;
			return ret;
		}

		TEMP_PAR
		IDEAL_REP operator-(const IDEAL_REP& a, const IDEAL_REP& b)
		{
			IDEAL_REP ret = a;
			ret -= b;
			return ret;
		}

		TEMP_PAR
		IDEAL_REP operator*(const IDEAL_REP& a, const IDEAL_REP& b)
		{
			IDEAL_REP res;
			unsigned size = 0;
			unsigned max = a._coeffs.size() > b._coeffs.size()
							 ? a._coeffs.size() : b._coeffs.size();

			size = pow(2, static_cast<unsigned>(log2(max)));
			if (size != max)
				size *= 2;

			Karatsuba<BaseType, number_traits>::doIt(a, b,
					                                     0, size,
																							 res);
			res.carrying();
			res.correctShape();
			return res;
		}

		TEMP_PAR
		IDEAL_REP operator/(const IDEAL_REP& a, const IDEAL_REP& b)
		{
			IDEAL_REP ret = a;
			ret /= b;
			return ret;
		}

		TEMP_PAR
		IDEAL_REP operator%(const IDEAL_REP& a, const IDEAL_REP& b)
		{
			IDEAL_REP ret = a;
			ret %= b;
			return ret;
		}

		TEMP_PAR
		IDEAL_REP operator<<(const IDEAL_REP& a, const unsigned shiftVal)
		{
			IDEAL_REP ret = a;
			ret._coeffs.insert(ret._coeffs.begin(), shiftVal, number_traits::additiveUnit);
			return ret;
		}

		TEMP_PAR
		IDEAL_REP operator>>(const IDEAL_REP& a, const unsigned shiftVal)
		{
			IDEAL_REP ret = a;
			unsigned newShift = shiftVal < ret._coeffs.size() - 1?
				                  shiftVal : ret._coeffs.size() - 1;
			if (newShift > 0)
				ret._coeffs.erase(ret._coeffs.begin(), ret._coeffs.begin() + newShift);
			return ret;
		}

		TEMP_PAR
		std::ostream& operator<<(std::ostream& os,
				                     const IDEAL_REP& a)
		{
			os << (std::string)a;
			return os;
		}

		
		TEMP_PAR
    template<class T>
      void IDEAL_REP::constructRepresentation(const unsigned numOfElement, const T& first,
                                            va_list vlist)
		{
      _coeffs.clear();
      _coeffs.push_back(first);
			for (unsigned i = 1; i < numOfElement; ++i)
			{
				_coeffs.push_back(va_arg(vlist, T));
				if (!IdealType::isCongruentElement(_coeffs[i]))
					throw Exceptions::ParameterException();
			}
		}

		TEMP_PAR
		BaseType& IDEAL_REP::operator[](const unsigned coeff)
		{
			if (coeff >= _coeffs.size())
				_coeffs.resize(coeff + 1);
				
			return _coeffs[coeff];
		}

		TEMP_PAR
		BaseType IDEAL_REP::operator[](const unsigned coeff) const
		{
			return this->getCoeff(coeff);
		}

		TEMP_PAR
		void IDEAL_REP::carrying()
		{
			for (unsigned i = 0; i < _coeffs.size(); ++i)
			{
				IDEAL_REP carry = _coeffs[i];
				(*this)[i] = carry.getCoeff(0);

				for (unsigned j = 1; j < carry._coeffs.size(); ++j)
					(*this)[j + i] += carry.getCoeff(j); 
			}
		}

		TEMP_PAR
		void IDEAL_REP::correctShape()
		{
			unsigned i = _coeffs.size() - 1;
			while (NumCalc::equals(_coeffs[i],
						                 number_traits::additiveUnit)
					   && i > 0) i--;
			_coeffs.resize(i + 1);
		}

	}
}

#undef TEMP_PAR
#undef IDEAL_REP 


