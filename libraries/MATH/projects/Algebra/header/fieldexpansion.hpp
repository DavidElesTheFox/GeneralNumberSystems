#ifndef MATH__ALGEBRA__FIELDEXPANSION_H
#error Only body included
#endif

#define TEMP_DEF template<class BaseType,\
                          class ExpansionElement,\
                          class Container,\
                          class number_traits>

#define FIELD_EXP FieldExpansion<BaseType, ExpansionElement, Container, number_traits>

#define POLY Polynomial<BaseType, Container, number_traits>

namespace MATH
{
  namespace Algebra
  {
    template<class BaseType,
             class Container,
             class number_traits>
    class Polynomial;

    TEMP_DEF
    POLY FIELD_EXP::MinimalPolynomIdeal::minimal;

    TEMP_DEF
    FIELD_EXP::FieldExpansion(const BaseType& b)
		  :IdealAdicRepresentation<BaseType,
			                         ExpansionElement,
															 Container,
															 number_traits>()
		{
      this->_coeffs[0] = b;
    }

    TEMP_DEF
    template<class T>
    FIELD_EXP::FieldExpansion(const IndexType numOfCoeffs,
                              T first, ...)
		  :IdealAdicRepresentation<BaseType,
			                         ExpansionElement,
															 Container,
															 number_traits>()
		{
      va_list vlist;
      va_start(vlist, first);
      this->constructRepresentation(numOfCoeffs.value, first, vlist);
		}

    TEMP_DEF
    FIELD_EXP::FieldExpansion(const IdealAdicRepresentation<BaseType,
                                                     ExpansionElement,
                                                     Container,
                                                     number_traits>& other)
		  :IdealAdicRepresentation<BaseType,
						                   ExpansionElement,
														   Container,
														   number_traits>(other)
		{	}

    TEMP_DEF
    FIELD_EXP& FIELD_EXP::operator=(const IdealAdicRepresentation<BaseType,
						                                           ExpansionElement,
																								       Container,
																								       number_traits>& other)
		{
			if (this != &other)
			{
        IdealAdicRepresentation<BaseType,
						                   ExpansionElement,
														   Container,
														   number_traits>::operator=(other);
			}
			return *this;
		}

		TEMP_DEF
		std::ostream& operator<<(std::ostream& os,
				                     const FIELD_EXP& a)
		{
			os << (std::string)a;
			return os;
		}

    TEMP_DEF
    void FIELD_EXP::correctShape()
    {
		  if (ExpansionElement::getMinimalPolynomial())
      {
        reduction();
      }
      else
      {
        IdealAdicRepresentation<BaseType,
                                ExpansionElement,
                                Container,
                                number_traits>::correctShape();
      }
    }

    TEMP_DEF
    std::string FIELD_EXP::MinimalPolynomIdeal::strShape = "(UNDEF)";

    TEMP_DEF
    void FIELD_EXP::reduction()
    {
      MinimalPolynomIdeal::minimal = *ExpansionElement::getMinimalPolynomial();
//      MinimalPolynomIdeal::strShape = "(" + (std::string)MinimalPolynomIdeal::minimal + ")";
      typename MinimalPolynomIdeal::Poly me = *this;
      IdealAdicRepresentation<typename MinimalPolynomIdeal::Poly,
                              MinimalPolynomIdeal> newShape = me;
      typename MinimalPolynomIdeal::Poly res = newShape.getCoeff(0);
      this->_coeffs.clear();
      for (unsigned i = 0; i <= res.getDegree(); ++i)
        (*this)[i] = res.getCoeff(i);
    }

    TEMP_DEF
    bool operator==(const FIELD_EXP& a, const FIELD_EXP& b)
    {
      unsigned max = a.getOrder() > b.getOrder() ?
                     a.getOrder():
                     b.getOrder();
      for(unsigned i = 0; i <= max; ++i)
      {
        if (!FIELD_EXP::NumCalc::equals(a[i],b[i]))
          return false;
      }
      return true;
    }

    TEMP_DEF
    bool operator!=(const FIELD_EXP& a, const FIELD_EXP& b)
    {
      unsigned max = a.getOrder() > b.getOrder() ?
                     a.getOrder():
                     b.getOrder();
      for(unsigned i = 0; i <= max; ++i)
      {
        if (!FIELD_EXP::NumCalc::equals(a[i],b[i]))
          return true;
      }
      return false;
    }

    TEMP_DEF
    bool operator<=(const FIELD_EXP& a, const FIELD_EXP& b)
    {
      unsigned max = a.getOrder() > b.getOrder() ?
                     a.getOrder():
                     b.getOrder();
      for(unsigned i = 0; i <= max; ++i)
      {
        if (!(a[i] <= b[i]))
          return false;
      }
      return true;
    }

    TEMP_DEF
    bool operator<(const FIELD_EXP& a, const FIELD_EXP& b)
    {
      unsigned max = a.getOrder() > b.getOrder() ?
                     a.getOrder():
                     b.getOrder();
      for(unsigned i = 0; i <= max; ++i)
      {
        if (!(a[i] < b[i]))
          return false;
      }
      return true;
    }

    TEMP_DEF
    bool operator>=(const FIELD_EXP& a, const FIELD_EXP& b)
    {
      return !(a < b);
    }

    TEMP_DEF
    bool operator>(const FIELD_EXP& a, const FIELD_EXP& b)
    {
      return !(a <= b);
    }
  }
}

#undef TEMP_DEF
#undef FIELD_EXP
#undef POLY

