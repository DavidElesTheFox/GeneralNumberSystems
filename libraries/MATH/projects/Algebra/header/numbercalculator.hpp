#ifndef __MATH__ALGEBRA__NUMBERCALCULATOR_H
#error use without number calculator header
#endif

#define TEMP_DEF template<class T, class number_traits, bool isInteger>
#define NUM_CALC NumberCalculator_generic<T, number_traits, isInteger>


namespace MATH
{
	namespace Algebra
	{

		TEMP_DEF
		double NUM_CALC::abs(const T& number)
		{
			return number > number_traits::additiveUnit ? number : -number;
		}

		TEMP_DEF
		bool NUM_CALC::equals(const T& a, const T& b)
		{
			return a == b;
		}

		TEMP_DEF
		bool NUM_CALC::isDevide(const T& a, const T& b)
		{
			return b/a * a == b;
		}

		TEMP_DEF
		T NUM_CALC::getAdditiveUnit()
		{
			return number_traits::template parse<int>(0);
		}

		TEMP_DEF
		T NUM_CALC::getMultiplicativeUnit()
		{
			return number_traits::template parse<int>(1);
		}

		TEMP_DEF
		bool NUM_CALC::isNonNegative(const T& a)
		{
			return a >= number_traits::additiveUnit;
		}

		TEMP_DEF
		bool NUM_CALC::isPositive(const T& a)
		{
			return a > number_traits::additiveUnit;
		}

		TEMP_DEF
		T NUM_CALC::floor(const T& number)
		{
			BaseType num = number_traits::template convert<BaseType>(number);
			T ret = number_traits::
				template parse<BaseType>(std::floor(num));
			return ret;
		}

		TEMP_DEF
		T NUM_CALC::ceil(const T& number)
		{
			return floor(number) + 1;
		}

		TEMP_DEF
		T NUM_CALC::pow(const T& number, const int exponent)
		{
			BaseType num = number_traits::template convert<BaseType>(number);
			T ret = number_traits::
				template parse<BaseType>(std::pow(num, exponent));
			return ret;
		}

		TEMP_DEF
		T NUM_CALC::root(const T& number, const int exponent)
		{
			BaseType num = number_traits::template convert<BaseType>(number);
			T ret = number_traits::
				template parse<BaseType>(std::pow(num, 1/(double)exponent));
			return ret;
		}

		TEMP_DEF
		T NUM_CALC::rem(const T& number, const T& divisior)
		{
			return number % divisior;
		}

    TEMP_DEF
    T NUM_CALC::calculateComplexConjugate(const T& a)
    {
      return a;
    }
	}			
}

#undef TEMP_DEF
#undef NUM_CALC

