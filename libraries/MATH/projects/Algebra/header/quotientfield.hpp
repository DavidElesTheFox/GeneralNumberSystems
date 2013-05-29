#ifndef MATH__ALGEBRA__QUOTIENTFIELD_H
#error Included only body
#endif

#define TEMP_DEF template<class BaseType,\
                          class number_traits,\
                          class Simplifier>
#define QUO QuotientField<BaseType, number_traits, Simplifier>

namespace MATH
{
  namespace Algebra
  {
    TEMP_DEF
    QUO::QuotientField(const BaseType& a, const BaseType& b):
      _counter(a),
      _nominator(b)
    {
      simplify();
    }

    TEMP_DEF
    template<class S>
    QUO::QuotientField(const QuotientField<BaseType, number_traits, S>& other):
      _counter(other._counter),
      _nominator(other._nominator)
    {
      simplify();
    }

    TEMP_DEF
    template<class S>
    QUO& QUO::operator=(const QuotientField<BaseType, number_traits, S>& other)
    {
      if (&other != this)
      {
        _counter = other._counter;
        _nominator = other._nominator;
        simplify();
      }
      return *this;
    }

    TEMP_DEF
    QUO QUO::operator-() const
    {
      return -number_traits::multiplicativeUnit * (*this);
    }

    TEMP_DEF
    QUO& QUO::operator++()
    {
      (*this) += number_traits::multiplicativeUnit;
      simplify();
      return *this;
    }

    TEMP_DEF
    QUO QUO::operator++(int)
    {
      QUO copy = *this;
      (*this) += number_traits::multiplicativeUnit;
      simplify();
      return copy;
    }

    TEMP_DEF
    QUO& QUO::operator--()
    {
      (*this) -= number_traits::multiplicativeUnit;
      simplify();
      return *this;
    }

    TEMP_DEF
    QUO QUO::operator--(int)
    {
      QUO copy = *this;
      (*this) -= number_traits::multiplicativeUnit;
      simplify();
      return copy;
    }

    TEMP_DEF
    QUO& QUO::operator+=(const QUO& a)
    {
      _counter *= a._nominator;
      _counter += (a._counter * _nominator);

      _nominator *= a._nominator;
      simplify();
      return *this;
    }

    TEMP_DEF
    QUO& QUO::operator-=(const QUO& a)
    {
      _counter *= a._nominator;
      _counter -= (a._counter * _nominator);
      
      _nominator *= a._nominator;
      simplify();
      return *this;
    }

    TEMP_DEF
    QUO& QUO::operator/=(const QUO& a)
    {
      _counter *= a._nominator;
      _nominator *= a._counter;
      simplify();
      return *this;
    }

    TEMP_DEF
    QUO& QUO::operator*=(const QUO& a)
    {
      _counter *= a._counter;
      _nominator *= a._nominator;
      simplify();
      return *this;
    }

    TEMP_DEF
    QUO operator+(const QUO& a, const QUO& b)
    {
      QUO ret = a;
      ret += b;
      return ret;
    }

    TEMP_DEF
    QUO operator-(const QUO& a, const QUO& b)
    {
      QUO ret = a;
      ret -= b;
      return ret;
    }

    TEMP_DEF
    QUO operator/(const QUO& a, const QUO& b)
    {
      QUO ret = a;
      ret /= b;
      return ret;
    }

    TEMP_DEF
    QUO operator*(const QUO& a, const QUO& b)
    {
      QUO ret = a;
      ret *= b;
      return ret;
    }

    TEMP_DEF
    std::ostream& operator<<(std::ostream& os,
                             const QUO& a)
    {
      os << "(" << a._counter << ")/(" << a._nominator << ")";
      return os;
    }

    TEMP_DEF
    bool operator==(const QUO& a, const QUO& b)
    {
      return NumberCalculator<BaseType, number_traits>::equals(a._counter,
                                                               b._counter)
             && NumberCalculator<BaseType, number_traits>::equals(a._nominator,
                                                                  b._nominator);
    }

    TEMP_DEF
    bool operator!=(const QUO& a, const QUO& b)
    {
      return !(a == b);
    }

    TEMP_DEF
    bool operator<(const QUO& a, const QUO& b)
    {
      QUO tmp = b - a;
      return tmp._counter > number_traits::additiveUnit
             && tmp._nominator > number_traits::additiveUnit;
    }

    TEMP_DEF
    bool operator>(const QUO& a, const QUO& b)
    {
      QUO tmp = a - b;
      return tmp._counter > number_traits::additiveUnit
             && tmp._nominator > number_traits::additiveUnit;
    }

    TEMP_DEF
    bool operator<=(const QUO& a, const QUO& b)
    {
      return !(a > b);
    }

    TEMP_DEF
    bool operator>=(const QUO& a, const QUO& b)
    {
      return !(a < b);
    }
  }
}

#undef TEMP_DEF
#undef QUO

