
#define TEMP_PAR template<class INT_TYPE,                          \
	                        class FLOAT_TYPE,                        \
                          template<class T>                        \
                            class Matrix,                          \
                          template<class T>                        \
													  class Vector,                          \
 													template<typename T, class M>            \
                            class matrix_traits,                   \
													template<typename T, class V>            \
													  class vector_traits,                   \
													template<typename T>                     \
													  class number_traits>
#define NUM_SYS NumberSystem<INT_TYPE,      \
                             FLOAT_TYPE,    \
                             Matrix,        \
                             Vector,        \
                             matrix_traits, \
                             vector_traits, \
                             number_traits>

namespace MATH
{
	namespace NumberSystem
	{
    TEMP_PAR
    int NUM_SYS::PROP_EXC_ID = 5000;

		TEMP_PAR
		NUM_SYS::NumberSystem(const Matrix<INT_TYPE>& base,
				                  const DigitSet digits,
                          const bool checkProperties)
		  :_set(digits), _base(base)
		{
      try
      {
			  compute();
      }
      catch (Exceptions::RuntimeException& ex)
      {
        if (checkProperties 
            || ex.getId() != PROP_EXC_ID)
          throw ex;
      }
		}

		TEMP_PAR
		Vector<INT_TYPE> NUM_SYS::chop(const Vector<INT_TYPE>& z) const 
		{
			IVector a_j = findDigit(z);
			FVector f_a_j = I_FConverter::template convertVector<Vector>(a_j);
			FVector f_z = I_FConverter::template convertVector<Vector>(z);

			FVector ret = _baseInverse*(f_z - f_a_j);
      return F_IConverter::template convertVector<Vector>(ret);
		}

		TEMP_PAR
		typename NUM_SYS::DigitSet 
		  NUM_SYS::getDigits(const Vector<INT_TYPE>& z) const
		{
			bool finished = false;
			IVector v = vector_traits_int::copy(z);
			DigitSet digits;
      digits.reserve(20);
			digits.push_back(v);
			v = chop(v);
			while(!finished)
			{
				if( find_if(digits.begin(), digits.end(), DigitFinder(v)) != 
						digits.end())
				{
					finished = true;
				}
				else
				{
					digits.push_back(v);
					v = chop(v);
				}
			}
			return digits;
		}

		TEMP_PAR
		Matrix<INT_TYPE> NUM_SYS::getBase() const
		{
			return _base;
		}

		TEMP_PAR
		typename NUM_SYS::DigitSet NUM_SYS::getDigitSet() const
		{
			return _set;
		}

		TEMP_PAR
		Matrix<FLOAT_TYPE> NUM_SYS::getBaseInverse() const
		{
			return _baseInverse;
		}

		TEMP_PAR
		void NUM_SYS::compute()
		{
			//Calculate inverse:
			IntSmithNormalForm snf(_base,
					                   true, /* use shape correction */
														 IntSmithNormalForm::LEFT_POSITIVE);
			IntAdjointMatrix adjointForm(_base);
			IMatrix adj = adjointForm["ADJOINT"];
			_G = snf["S"];
			_U = snf["U"];
      BaseProperties props = calculateBaseProperties();
			setBorder();

			createHashTable();

			FMatrix f_adj = I_FConverter::template convertMatrix<Matrix>(adj);
      FMatrix f_G = I_FConverter::template convertMatrix<Matrix>(_G);

      FLOAT_TYPE determinant = FMCalculator::calculateDeterminant(f_G);
			_baseInverse = number_traits_float::multiplicativeUnit/determinant * f_adj;

      if (!(props & EXPANSIVE))
      {
        throw Exceptions::RuntimeException("Number system is not expansive", PROP_EXC_ID);
      }
      else if (!(props & REGULAR))
      {
        throw Exceptions::RuntimeException("Number system is not regular", PROP_EXC_ID);
      }
      else if (!(props & DETERMINANT_NOT_ONE))
      {
        throw Exceptions::RuntimeException("Number system determinant error",
                                           PROP_EXC_ID);
      }
			

      props = calculateBaseProperties();
      if (!(props & CONGRUENT_DIGITSET))
      {
        throw Exceptions::RuntimeException("Number system hasn't got congruent digits",
                                           PROP_EXC_ID);
      }

		}

		TEMP_PAR
		void NUM_SYS::setBorder()
		{
			bool l = false;
			int rowNum = matrix_traits_int::getRowNum(_G);
			INT_TYPE one = number_traits_int::multiplicativeUnit;
			for(int i = 0;i < rowNum && !l; ++i)
			{
				INT_TYPE act = matrix_traits_int::getElement(i, i, _G);
				if(! NumCalc_int::equals(act, one))
				{
					l = true;
					_border = i - 1;
				}
			}
		}

		TEMP_PAR
		void NUM_SYS::createHashTable()
		{
      INT_TYPE s = _set.size();
      for(unsigned i = 0; i < _set.size(); ++i)
			{
        INT_TYPE h = hash(_set[i]);
				_tableHash[h] = i;
				_tableHash[h + s] = i;
				_tableHash[h - s] = i;
			}
		}

		TEMP_PAR
		INT_TYPE NUM_SYS::minorProduct(const int to) const 
		{
			if( to < _border + 1)
				return INT_TYPE(); 
			INT_TYPE ret = 
				matrix_traits_int::getElement(_border + 1, _border + 1, _G);
			for(int i = _border + 2; i < to; ++i)
			{
				ret *= 
					matrix_traits_int::getElement(i, i, _G);
			}
			return ret;
		}

		TEMP_PAR
		bool NUM_SYS::checkHashTable() const
		{
      double det = NumCalc_int::abs(IMCalculator::calculateDeterminant(_G));
      bool l = _tableHash.size() == (int) 3 * det;
			return l;
		}

    TEMP_PAR
    typename NUM_SYS::BaseProperties NUM_SYS::calculateBaseProperties() const
    {
      int rowNum, colNum;
      int ret = 0;
      matrix_traits_int::getDimension(rowNum, colNum, _base);
      INT_TYPE detI_M = 
        IMCalculator::calculateDeterminant( 
            IMCalculator::getIdentityMatrix(rowNum, colNum)
            - _base);
      if (IMCalculator::calculateDeterminant(_base) 
              != number_traits_int::additiveUnit)
        ret |= REGULAR;
      if (IMCalculator::isExpansive(_base))
        ret |= EXPANSIVE;
      if (!NumCalc_int::equals(detI_M, number_traits_int::multiplicativeUnit)
          && !NumCalc_int::equals(detI_M, -number_traits_int::multiplicativeUnit))
        ret |= DETERMINANT_NOT_ONE;
      if (checkHashTable())
        ret |= CONGRUENT_DIGITSET;
      return static_cast<BaseProperties>(ret);
    }

		TEMP_PAR
		Vector<INT_TYPE> NUM_SYS::findDigit(const Vector<INT_TYPE>& z) const
		{
      HashSet_const_iterator cit = _tableHash.find(hash(z));
      if (cit == _tableHash.end())
  			throw Exceptions::RuntimeException("Not found digit!");
      
      return _set[cit->second];
		}

		TEMP_PAR
		INT_TYPE NUM_SYS::hash(const Vector<INT_TYPE>& z) const
		{
			IVector Uz = _U * z;
			INT_TYPE uzAct = vector_traits_int::getElement(_border + 1, Uz);
			INT_TYPE gAct = matrix_traits_int::getElement(_border + 1,
					                                          _border + 1,
																										_G);
			INT_TYPE mod = uzAct % gAct;
			INT_TYPE ret = mod;
      INT_TYPE prodG = gAct;

			int rowNum = matrix_traits_int::getRowNum(_G);
			for(int i = _border + 2; i < rowNum; ++i)
			{
				uzAct = vector_traits_int::getElement(i, Uz);
				gAct = matrix_traits_int::getElement(i,i, _G);
				mod = uzAct % gAct;
        

				ret += (mod * prodG);
        prodG *= gAct;
			}
			return ret;
		}
		
	}
}

#undef TEMP_PAR
#undef NUM_SYS
