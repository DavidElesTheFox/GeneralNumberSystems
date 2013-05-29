#ifndef __MATH__LINEARALGEBRA_MATRIXCALCULATOR_H
#error include without matrixcalculator.h
#endif


#define DEF_TEMPLATE template<class T,\
	                            class Matrix, \
                              class traits, \
	                            class number_traits,\
                              bool isInteger>
#define MTX_CALC MatrixCalculator_core<T,             \
                                       Matrix,        \
																			 traits,        \
																			 number_traits, \
																			 isInteger>
#include <MATH/LinearAlgebra/matrix.h>
#include <MATH/Algebra/polynomial.h>
#include <MATH/Algebra/lehmerschur.h>

namespace MATH
{
	namespace LinearAlgebra
	{
    DEF_TEMPLATE
    bool MTX_CALC::isExpansive(const Matrix& m)
    {
      MATH::Algebra::Polynomial<T, std::vector<T>, number_traits> p
        = calculateCharacteristicPolynomial<
            MATH::Algebra::Polynomial<T, std::vector<T>, number_traits> >(m);
      return MATH::Algebra::LehmerSchur<T,
               MATH::Algebra::Polynomial<T, std::vector<T>, number_traits> >::
                 doAlgorithm(p);
    }

    DEF_TEMPLATE
    template<class POLYNOMIAL>
    POLYNOMIAL MTX_CALC::calculateCharacteristicPolynomial(const Matrix& m)
    {
      int rowNum, colNum;
      traits::getDimension(rowNum, colNum, m);
      MATH::LinearAlgebra::Matrix<POLYNOMIAL> copy(rowNum, colNum);
      for (int i = 0; i < rowNum; ++i)
        for (int j = 0; j < colNum; ++j)
        {
          POLYNOMIAL p;
          p[0] = -traits::getElement(i, j, m);
          if (i == j)
          {
            p[1] = number_traits::multiplicativeUnit;
          }
          copy(i, j) = p;
        }
      return MatrixCalculator<POLYNOMIAL,
                              MATH::LinearAlgebra::Matrix<POLYNOMIAL> >
                                ::calculateDeterminant(copy);
    }

		DEF_TEMPLATE
		Matrix MTX_CALC::
		  calculateTransponate(const Matrix& m)
		{
			const int rowNum = traits::getRowNum(m);
			const int colNum = traits::getColNum(m);
			Matrix ret = traits::createMatrix(colNum, rowNum);

			for (int i = 0; i < rowNum; ++i)
				for (int j = 0; j < colNum; ++j)
				{
					T& element = traits::getElement(i,j,ret);
					element = traits::getElement(j,i,m);
				}
			return ret;
		}


		DEF_TEMPLATE
		bool MTX_CALC::
		  calculateInverse(const Matrix& m,
					             Matrix& inverse)
		{
			int rank = 0;
			T determinant;
			Matrix rest;
			inverse = calculateInverse(m, rank, determinant, rest);
			return determinant != 0;
		}

		DEF_TEMPLATE
		bool MTX_CALC::
		  calculateInverseRest(const Matrix& m,
					                 Matrix& rest)
		{
			int rank = 0;
			T determinant;
			calculateInverse(m, rank, determinant, rest);
			return determinant != 0;
		}

		DEF_TEMPLATE
		Matrix MTX_CALC::
		  calculateInverse(const Matrix& m,
			                 int& rank,
			 								 T& determinant,
											 Matrix& rest)
		{
			const int rowNum = traits::getRowNum(m);
			const int colNum = traits::getColNum(m);

			int swaps[rowNum * 2];
			Matrix ret = traits::copy(m);
			Matrix unique = traits::createMatrix(rowNum, rowNum);

			const T number_unique_element = number_traits::multiplicativeUnit;
			const T number_null_element = number_traits::additiveUnit;
			//Create unique matrix
			for (int i = 0; i < rowNum; ++i)
				for (int j = 0; j < rowNum; ++j)
				{
					traits::setElement(i,j,
							               i == j ? number_unique_element:
														          number_null_element,
														 unique);
				}

			int row, col;
			T max;
			rank = 0;
			determinant = number_unique_element;

//				std::cout<<"Orig ret\n"<<ret<<std::endl;

			for(int i = 0; i < colNum && i < rowNum; ++i)
			{
				row = col = i;
				int maxRow, maxCol;
				max = getAbsMaximumValue(row, col,
						                     rowNum, rowNum,
																 ret, maxRow, maxCol);
				if( max == number_traits::additiveUnit
						|| max != max)
				{
					break;
				}
//				std::cout<<"MAX: "<<max<<std::endl;
				row = maxRow;
				col = maxCol;
				//Select max value
				if(swapRows(i, row, ret))
				{
					determinant *= -number_unique_element;
//						std::cout<<"swap Row"<<std::endl;
				}
				swapRows(i, row, unique);

				if(swapCols(i, col, ret))
				{
					determinant *= -number_unique_element;
//						std::cout<<"swap Col"<<std::endl;
				}
				swapCols(i, col, unique);

				//Swap save
				swaps[2*i] = row;
				swaps[2*i + 1] = col;

				T eliminator;
				for(int j = i + 1; j < rowNum; ++j)
				{
					if (NumCalc::equals(traits::getElement(i,i, ret),
								              number_traits::additiveUnit))
					{
						throw Exceptions::RuntimeException("CalculateInverse:"
								                               "devide by zero ");
					}
					eliminator = -traits::getElement(j,i,ret)
						           /traits::getElement(i,i, ret);
					addTwoRow( eliminator, i, j, ret);
					addTwoRow( eliminator, i, j, unique);
				}
				determinant *= ret(i,i);
				rank++;
//   				std::cout<<"ret\n"<<ret<<std::endl;
//					std::cout<<"determinant"<<determinant<<std::endl;
			}
//			std::cout<<"rank: "<<rank<<std::endl;
//			std::cout<<"rowNum: "<<rowNum<<std::endl;
			if(rank != rowNum)
			{
				determinant = number_traits::parse(0);
				rest = traits::copy(ret);
				return unique;
			}

			//Create unique (backward replaceing)
			for(int i = rowNum - 1; i >= 0; --i)
			{
//				std::cout<<"("<<i<<")"<<std::endl;
				multiplyRow(number_unique_element/ret(i,i), i, unique);
				multiplyRow(number_unique_element/ret(i,i), i, ret);
				for(int j = i - 1; j >= 0; --j)
				{
//				std::cout<<"("<<i<<","<<j<<")"<<std::endl;
					addTwoRow(-ret(j,i), i, j, unique);
					addTwoRow(-ret(j,i), i, j, ret);
				}
			}
			//Roll back swaps
			for(int i = rowNum * 2 - 1; i >= 0 ;)
			{
				swapCols(i/2,swaps[i], unique);
				swapCols(i/2, swaps[i], ret);
				i--;

				swapRows(i/2,swaps[i], unique);
				swapRows(i/2, swaps[i], ret);
				i--;
			}
			rest = traits::copy(ret);

			return unique;
		}

    DEF_TEMPLATE
		bool MTX_CALC::
		  isFullRanked(const Matrix& m)
		{
			int rank = calculateRank(m);
			int rowNum = traits::getRowNum(m);
			int colNum = traits::getColNum(m);
			return rowNum > colNum ? rank == rowNum:
				                       rank == colNum;
		}

		DEF_TEMPLATE
		T MTX_CALC::
		  calculateDeterminant(const Matrix& m)
		{
			int colNum = traits::getColNum(m);
			if (colNum > 2)
			{
				T det = number_traits::additiveUnit;
				for (int i = 0; i < colNum; ++i)
				{
					Matrix tmp = removeRowAndCol(0, i, m);
          T subDet = calculateDeterminant(tmp);
          T signum = number_traits::multiplicativeUnit;
          if(i & 1)
          {
            signum = -number_traits::multiplicativeUnit;
          }

          T multiplier = traits::getElement(0, i, m);

					det += signum * multiplier * subDet;

				}
				return det;
			}
			else if (colNum > 1)
			{
				T det = traits::getElement(0,0,m)
					      * traits::getElement(1,1,m);
				det -= traits::getElement(0,1,m)
					     * traits::getElement(1,0,m);
				return det;
			}
			else
			{
				return traits::getElement(0,0,m);
			}
		}

		DEF_TEMPLATE
		int MTX_CALC::
		  calculateRank(const Matrix& m)
		{
			int colNum = traits::getColNum(m);
			int rowNum = traits::getRowNum(m);
			int rank;
			T determinant;
			Matrix rest(rowNum, colNum), inverse(rowNum, colNum);
			inverse = calculateInverse(m, rank, determinant, rest);
			return rank;
		}

		DEF_TEMPLATE
		bool MTX_CALC::
		  isDiagonal(const Matrix& m)
		{
			int rowNum = traits::getRowNum(m);
			int colNum = traits::getColNum(m);
			bool isDiagonal = true;
			for (int i = 0; i < rowNum && isDiagonal; ++i)
			  for (int j = 0; j < colNum && isDiagonal; ++j)
				{
					isDiagonal = isDiagonal && i == j ?
						           true :
						           NumCalc::equals(traits::getElement(i, j, m), 0);
				}
			return isDiagonal;
		}

		DEF_TEMPLATE
		Matrix MTX_CALC::
		  diagModulo(const Matrix& a,
								 const Matrix& b)
		{
			Matrix ret = a;
			for(int i = 0; i < ret._rowNum; ++i)
			{
				T& act = traits::getElement(i,i,ret);
				act %= traits::getElement(i,i,b);
			}
		}

		DEF_TEMPLATE
		bool MTX_CALC::
		  swapRows(const int i, 
			         const int j,
							 Matrix& m)
		{
			int colNum = traits::getColNum(m);
//			std::cout<<"swapRows: m :"<<std::endl<<m<<std::endl;
//			std::cout<<"swapRows: i: "<<i<<std::endl;
//			std::cout<<"swapRows: j: "<<j<<std::endl;
			if (i == j)
				return false;
			for (int k = 0; k < colNum; ++k)
			{
				T i_element = traits::getElement(i, k, m);
				T j_element = traits::getElement(j, k, m);
				traits::setElement(i,k, j_element, m);
				traits::setElement(j,k, i_element, m);
			}
			return true;
		}

		DEF_TEMPLATE
		bool MTX_CALC::
		  swapCols(const int i,
			         const int j,
							 Matrix& m)
		{
			int rowNum = traits::getRowNum(m);
			if (i == j)
				return false;
			for (int k = 0; k < rowNum; ++k)
			{
				T i_element = traits::getElement(k, i, m);
				T j_element = traits::getElement(k, j, m);
				traits::setElement(k, i, j_element, m);
				traits::setElement(k, j, i_element, m);
			}
			return true;
		}

		DEF_TEMPLATE
		void MTX_CALC::
		  addTwoRow(const T& multiplyer,
			          const int source,
			 				  const int destination,
								Matrix& m)
		{
			int rowNum = traits::getRowNum(m);
			int colNum = traits::getColNum(m);

			if (source >= rowNum)
				throw Exceptions::ParameterException("MatrixCalculator_core"
						                                 "addTwoRow"
																						 "'source' param error");

			for (int k = 0; k < colNum;++k)
			{
				T& destinationElement = traits::getElement(destination, k, m);
				destinationElement += multiplyer * traits::getElement(source,
						                                                  k,m);
			}
		}

		DEF_TEMPLATE
		void MTX_CALC::
		  multiplyRow(const T& a,
								  const int row,
								  Matrix& m)
		{
			int colNum = traits::getColNum(m);
			for (int k = 0; k < colNum; ++k)
			{
				T& element = traits::getElement(row, k, m);
				element *= a;
			}
		}

		DEF_TEMPLATE
		T MTX_CALC::
		  getAbsMaximumValue(const int startRow,
												 const int startCol,
												 const int borderRow,
												 const int borderCol,
												 const Matrix& m)
		{
			int rowId = 0, colId = 0;
			return getAbsMaximumValue(startRow,
					                      startCol,
												        borderRow,
												        borderCol,
												        m,
												        rowId,colId);
		}
		DEF_TEMPLATE
		T MTX_CALC::
		  getAbsMaximumValue(const int startRow,
                         const int startCol,
                         const int borderRow,
                         const int borderCol,
                         const Matrix& m,
                         int& rowId, 
                         int& colId)
		{
			return findValueBy<AbsMaxComparer>(startRow,
																				 startCol,
																				 borderRow,
																				 borderCol,
																				 m,
																				 rowId,
																				 colId);
		}

		DEF_TEMPLATE
		T MTX_CALC::
		  getAbsMinNonZeroValue(const int startRow,
												    const int startCol,
												    const int borderRow,
												    const int borderCol,
												    const Matrix& m)
		{
			int rowId = 0, colId = 0;
			return getAbsMinNonZeroValue(startRow,
					                         startCol,
												           borderRow,
												           borderCol,
												           m,
												           rowId,colId);
		}
		DEF_TEMPLATE
		T MTX_CALC::
		  getAbsMinNonZeroValue(const int startRow,
                            const int startCol,
                            const int borderRow,
                            const int borderCol,
                            const Matrix& m,
                            int& rowId, 
                            int& colId)
		{
			return findValueBy<AbsMinNonZeroComparer>(startRow,
					                                      startCol,
																								borderRow,
																								borderCol,
																								m,
																								rowId,
																								colId);
		}

		DEF_TEMPLATE
		double MTX_CALC::
		  norm(const int n, const Matrix& m)
		{
			double ret = NumCalc::abs(traits::getElement(0,0,m));
			int rowNum = traits::getRowNum(m);
			int colNum = traits::getColNum(m);
			if(n == 0 || n == 1)
			{
				int size1 = n == 0 ? rowNum : colNum;
				int size2 =  n == 0 ? colNum : rowNum;
				for(int i = 0; i < size1; ++i)
				{
					double element = NumCalc::abs(traits::getElement(i,0,m));
					double sum = element;
					for(int j = 1; j < size2; ++j)
					{
						element = (n == 0) ? NumCalc::abs(traits::getElement(i,j,m)):
							                   NumCalc::abs(traits::getElement(j,i,m));
						sum += element;
					}
					if(sum > ret)
						ret = sum;
				}
				return ret;
			}
			else if(n == 2)
			{
				throw Exceptions::RuntimeException("Not Implemented norm yet");
			}
			else
			{
				throw Exceptions::RuntimeException("Invalid argument", 0);
			}
		}

		DEF_TEMPLATE
		Matrix MTX_CALC::
		  removeRowAndCol(const int row,
					            const int col,
											const Matrix& m)
		{
		  int rowId = 0, colId = 0;
			const int rowNum = traits::getRowNum(m);
			const int colNum = traits::getColNum(m);
			Matrix ret = traits::createMatrix(rowNum - 1, colNum - 1);
			for(int i  = 0; i < rowNum; ++i)
			{
				for(int j = 0; j < colNum; ++j)
				{
					if(i != row && j != col)
					{
						T element = traits::getElement(i,j,m);
						traits::setElement(rowId, colId++, element, ret);
					}
				}
				if( i != row)
				{
					colId = 0;
					++rowId;
				}
			}
			return ret;
		}

		DEF_TEMPLATE
		Matrix MTX_CALC::
				getIdentityMatrix(const int& rowNum,
						              const int& colNum)
		{
			Matrix m = traits::createMatrix(rowNum, colNum);
			for(int i = 0; i < rowNum; ++i)
			{
				for(int j = 0; j < colNum; ++j)
				{
					if( i != j)
						traits::setElement(i, j, number_traits::additiveUnit, m);
					else
						traits::setElement(i, j, number_traits::multiplicativeUnit,m);
				}
			}
			return m;
		}

		DEF_TEMPLATE
		Matrix MTX_CALC::
		    getSwapMatrix(const int& rowNum,
						          const int& colNum,
											const int& i,
											const int& j)
		{
			Matrix m = getIdentityMatrix(rowNum, colNum);
			traits::setElement(i, i, number_traits::additiveUnit, m);
			traits::setElement(j, j, number_traits::additiveUnit, m);
			traits::setElement(i, j, number_traits::multiplicativeUnit, m);
			traits::setElement(j, i, number_traits::multiplicativeUnit, m);
			return m;
		}

		DEF_TEMPLATE
		Matrix MTX_CALC::
				getLeftEliminatorMatrix(const Matrix& m,
																const int id)
		{
			int rowNum = traits::getRowNum(m);
			int colNum = traits::getColNum(m);
			Matrix ret = traits::createMatrix(rowNum, colNum);
			for(int i = 0; i < rowNum; ++i)
			{
				for(int j = 0; j < rowNum; ++j)
				{
					if(i == j)
					{
						traits::setElement(i, j, number_traits::multiplicativeUnit, ret);
					}
					else if( j == id)
					{
						traits::setElement(i, j,
								               -traits::getElement(i,j,m)
															 /traits::getElement(j,j,m),
															 ret);
					}
					else
					{
						traits::setElement(i, j, number_traits::additiveUnit, ret);
					}
				}
			}
			return ret;
		}

		DEF_TEMPLATE
		Matrix MTX_CALC::
				getRightEliminatorMatrix(const Matrix& m,
																 const int id)
		{
			int rowNum = traits::getRowNum(m);
			int colNum = traits::getColNum(m);
			Matrix ret = traits::createMatrix(rowNum, colNum);
			for(int i = 0; i < rowNum; ++i)
			{
				for(int j = 0; j < rowNum; ++j)
				{
					if(i == j)
					{
						traits::setElement(i, j, number_traits::multiplicativeUnit, ret);
					}
					else if( i == id)
					{
						traits::setElement(i, j,
								               -traits::getElement(i,j,m)
															 /traits::getElement(i,i,m),
															 ret);
					}
					else
					{
						traits::setElement(i, j, number_traits::additiveUnit, ret);
					}
				}
			}
			return ret;
		}

		DEF_TEMPLATE
		template<class comparer>
		T MTX_CALC::
		  findValueBy(const int startRow,
					        const int startCol,
									const int borderRow,
									const int borderCol,
									const Matrix& m,
									int& rowId,
									int& colId)
		{
			int colNum = traits::getColNum(m);
			int rowNum = traits::getRowNum(m);
			if (startRow < 0
					|| startCol < 0
					|| borderRow < 0
					|| borderCol < 0
					|| startRow >= rowNum
					|| startCol >= colNum
					|| borderRow > rowNum
					|| borderCol > rowNum
					|| borderRow < startRow
					|| borderCol < startCol)
			{
				std::cerr<<"WARNING!\n"
					       <<"startRow: "<<startRow<<std::endl
					       <<"startCol: "<<startCol<<std::endl
								 <<"borderRow: "<<borderRow<<std::endl
								 <<"borderCol: "<<borderCol<<std::endl;
				throw Exceptions::ParameterException("getAbsMaximumValue");
			}
			T pivot = traits::getElement(startRow,startCol,m);
			pivot = comparer::assume(pivot);
			rowId = startRow;
			colId = startCol;
			bool found = comparer::condition(pivot,pivot);

			for (int i = startRow; i < borderRow; ++i)
			{
				for (int j = startCol; j < borderCol; ++j)
				{
					T element = traits::getElement(i, j, m);
					if (comparer::condition(pivot,element)
							|| (!found && comparer::condition(element, element)))
					{
						found = true;
						rowId = i;
						colId = j;
						pivot = comparer::assume(element);
					}
				}
			}
			if (!found)
			{
				rowId = colId = -1;
			}
			return pivot;
		}

	}
}
#undef DEF_TEMPLATE
#undef MTX_CALC

