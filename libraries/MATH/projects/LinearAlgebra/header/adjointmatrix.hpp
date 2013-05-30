
namespace MATH
{
  namespace LinearAlgebra
	{

		template<class T,
			       class Matrix,
						 class traits>
		const char* AdjointMatrix<T, Matrix, traits>::ADJOINT_STR = "ADJOINT";

		template<class T,
			       class Matrix,
						 class traits>
		void AdjointMatrix<T, Matrix, traits>::calculateElements()
		{
			int rowNum = traits::getRowNum(this->_original);
			int colNum = traits::getColNum(this->_original);
			Matrix adjoint = traits::createMatrix(rowNum, colNum);
//					std::cout<<"Orig:\n"<<_mtx<<std::endl;
			for(int i = 0; i < rowNum; ++i)
			{
				for(int j = 0; j < colNum; ++j)
				{
					Matrix tmp = MCalculator::removeRowAndCol(i,j,this->_original);
//							std::cout<<"tmp: \n"<<tmp<<std::endl;
//							std::cout<<"det:"<<tmp.getDeterminant()<<std::endl;
//					std::cout<<"("<<i<<", "<<j<<")"<<std::endl;
					adjoint(i, j) = 
						(i + j) % 2 ? MCalculator::calculateDeterminant(tmp)
												: -MCalculator::calculateDeterminant(tmp);
				}
			}
			adjoint = MCalculator::calculateTransponate(adjoint);
			this->_elements[ADJOINT_STR] = adjoint;
		}
	}
}

