namespace MATH
{
	namespace LinearAlgebra
	{
		template<typename T,
			       class Matrix,
						 class traits,
						 class number_traits>
		void SmithNormalForm<T, Matrix, traits, number_traits>
		     ::calculateElements()
		{
//			std::cout<<"CalculateElements"<<std::endl;
			Matrix s = traits::copy(this->_original);
			int rowNum = traits::getRowNum(s);
			int colNum = traits::getColNum(s);

			Matrix u = MCalculator::getIdentityMatrix(rowNum, colNum);
			Matrix v = MCalculator::getIdentityMatrix(rowNum, colNum);
			for(int i = 0; i < rowNum - 1; ++i)
			{
//						std::cout<<"iterate (" << i << ") \ns:\n"<<s<<std::endl;
//						std::cout<<"  u:\n"<<u<<std::endl;
//						std::cout<<"  v:\n"<<v<<std::endl;
				if(!pivoting(s, u, v, i))
				{
					break;
				}
//				    std::cout<<"swap: \ns:\n"<<s<<std::endl;
//						std::cout<<"  u:\n"<<u<<std::endl;
//						std::cout<<"  v:\n"<<v<<std::endl;

				bool again = true;
				while (again)
				{
					again = rowTransformation(s, u, i);
//          std::cout<<"rowTransformation\ns:\n"<<s<<std::endl;
//							std::cout<<"  u:\n"<<u<<std::endl;
//							std::cout<<"  v:\n"<<v<<std::endl;

					again = again || colTransformation(s, v, i);
//							std::cout<<"colTransformation\ns:\n"<<s<<std::endl;
//							std::cout<<"  u:\n"<<u<<std::endl;
//							std::cout<<"  v:\n"<<v<<std::endl;
				}

				rowElimination(s, u, i);
//						std::cout<<"rowElim\ns:\n"<<s<<std::endl;
//						std::cout<<"  u:\n"<<u<<std::endl;
//						std::cout<<"  v:\n"<<v<<std::endl;

				colElimination(s, v, i);
//						std::cout<<"colElim\ns:\n"<<s<<std::endl;
//						std::cout<<"  u:\n"<<u<<std::endl;
//						std::cout<<"  v:\n"<<v<<std::endl;
			}

			correction(v, s, u);
			this->_elements["V"] = v;
			this->_elements["S"] = s;
			this->_elements["U"] = u;
		}
		
		template<typename T,
			       class Matrix,
						 class traits,
						 class number_traits>
		Matrix SmithNormalForm<T, Matrix, traits, number_traits>::
		  getLeftTransformationMatrix(const Matrix& s,
					                        const int rowId1,
																	const int rowId2)
		{
			EuclideanRes res = 
				GCD::EuclideanAlg(traits::getElement(rowId1, rowId1, s),
													traits::getElement(rowId2, rowId1, s));

			Matrix mtx = MCalculator::getIdentityMatrix(traits::getRowNum(s),
																									traits::getColNum(s));


			traits::setElement(rowId1,rowId1,res.a,mtx);
			traits::setElement(rowId2, rowId1,
												 -traits::getElement(rowId2, rowId1, s)
												 /res.gcd,
													mtx);
			traits::setElement(rowId1, rowId2, res.b, mtx);
			traits::setElement(rowId2, rowId2,
												 traits::getElement(rowId1, rowId1, s)
												 /res.gcd,
												 mtx);
			return mtx;
		}

		template<typename T,
			       class Matrix, 
						 class traits,
						 class number_traits>
		Matrix SmithNormalForm<T, Matrix, traits, number_traits>::
		  getRightTransformationMatrix(const Matrix& s, 
					                         const int rowId1,
																   const int rowId2)
		{
			EuclideanRes res = 
				GCD::EuclideanAlg(traits::getElement(rowId1, rowId1, s),
												  traits::getElement(rowId1, rowId2, s));
		/*	std::cout<<"RightTransf: "<<std::endl
				       <<"  gcd: "<<res.gcd<<std::endl
			         <<"  a: "<<res.a<<std::endl
							 <<"  b: "<<res.b<<std::endl
							 <<"  element1: "<<traits::getElement(rowId1, rowId1, s)
							   <<std::endl
							 <<"  element2: "<<traits::getElement(rowId1, rowId2, s)
							 <<std::endl;*/

			Matrix mtx = MCalculator::getIdentityMatrix(traits::getRowNum(s),
																									traits::getColNum(s));

			traits::setElement(rowId1,rowId1,res.a,mtx);
			traits::setElement(rowId1, rowId2,
												 -traits::getElement(rowId1, rowId2, s)
												 /res.gcd,
													mtx);
			traits::setElement(rowId2, rowId1, res.b, mtx);
			traits::setElement(rowId2, rowId2,
												 traits::getElement(rowId1, rowId1, s)
												 /res.gcd,
												 mtx);
			return mtx;
		}


		template<typename T,
			       class Matrix,
						 class traits, 
						 class number_traits>
		bool SmithNormalForm<T, Matrix, traits, number_traits>::
		  pivoting(Matrix& s,
						   Matrix& u,
							 Matrix& v,
							 const int i)
		{
			int rowNum = traits::getRowNum(s);
			int colNum = traits::getColNum(s);
			int minRow, minCol;
			MCalculator::getAbsMinNonZeroValue(i, i,
					                               rowNum, colNum,
																				 s,
																				 minRow, minCol);
//			std::cout<<"minRow"<<minRow<<std::endl;
//			std::cout<<"minCol"<<minCol<<std::endl;
//			std::cout<<"i: "<<i<<std::endl;
			if (minRow  < 0
					|| minCol < 0)
				return false;
			
			if (minRow != i)
			{
				Matrix tmp = MCalculator::getSwapMatrix(rowNum, colNum, i, minRow);
				s = tmp * s;
		    u = tmp * u;
			}
			if (minCol != i)
			{
				Matrix tmp = MCalculator::getSwapMatrix(rowNum, colNum, i, minCol);
				s = s * tmp;
				v = v * tmp;
			}
			return true;
		}

		template<typename T, 
			       class Matrix, 
						 class traits, 
						 class number_traits>
		bool SmithNormalForm<T, Matrix, traits, number_traits>::
		  rowTransformation(Matrix& s,
												Matrix& u,
												const int i)
		{
			bool leastOne = false;
			int rowNum = traits::getRowNum(s);
			for (int j = 1; j + i < rowNum; ++j)
			{
				if (!NumCalc::equals(traits::getElement(i+j, i, s),
																	 number_traits::additiveUnit) //s(i+j,i) != 0
						&& !NumCalc::isDevide(traits::getElement(i, i, s),
																			 traits::getElement(i+j,i, s)) )
				{
					Matrix tmp = getLeftTransformationMatrix(s, i, i+j);
					s = tmp * s;
					u = tmp * u;
					leastOne = true;
				}
			}
			return leastOne;
		}

		template<typename T, 
			       class Matrix, 
						 class traits, 
						 class number_traits>
		void SmithNormalForm<T, Matrix, traits, number_traits>::
		  rowElimination(Matrix &s,
					           Matrix& u,
										 const int i)
		{
			Matrix tmp = MCalculator::getLeftEliminatorMatrix(s, i);
			s = tmp * s;
			u = tmp * u;
		}

		template<typename T,
			       class Matrix, 
						 class traits,
						 class number_traits>
		bool SmithNormalForm<T, Matrix, traits, number_traits>::
		  colTransformation(Matrix& s, Matrix& v, const int i)
		{
			bool leastOne = false;
			int rowNum = traits::getRowNum(s);
			for (int j = 1; j+i < rowNum; ++j)
			{
				if (!NumCalc::equals(traits::getElement(i, i, s),
																		number_traits::additiveUnit)
						&& !NumCalc::isDevide(traits::getElement(i,i,s),
																			 traits::getElement(i,i+j,s)) )
				{
					leastOne = true;
					Matrix tmp = getRightTransformationMatrix(s, i, i+j);
//					std::cout<<"colTransormationMtx(" << i << ", " << j <<"): \n"<<tmp<<std::endl;
					s = s * tmp;
					v = v * tmp;
				}
			}
			return leastOne;
		}

		template<typename T,
			       class Matrix,
						 class traits,
						 class number_traits>
		void SmithNormalForm<T, Matrix, traits, number_traits>::
      colElimination(Matrix& s, Matrix& v, const int i)
		{
			Matrix tmp = MCalculator::getRightEliminatorMatrix(s,i);
			s = s * tmp;
			v = v * tmp;
		}

		template<typename T, 
			       class Matrix, 
						 class traits, 
						 class number_traits>
		void SmithNormalForm<T, Matrix, traits, number_traits>::
		  correction(Matrix& v, Matrix& s, Matrix& u)
		{
			int rowNum = traits::getRowNum(s);
			int colNum = traits::getColNum(s);
			Matrix tmp = MCalculator::getIdentityMatrix(rowNum, colNum);
			if (_positiveShape)
			{
				for (int i = 0; i < rowNum; ++i)
				{
					if (!NumCalc::isNonNegative(traits::getElement(i, i, s))) 
					{
						traits::setElement(i,i, -number_traits::multiplicativeUnit, tmp);
						s = s * tmp;
						v = v * tmp;
						traits::setElement(i,i, number_traits::multiplicativeUnit, tmp);
					}
				}
			}
			if ((_mode == LEFT_POSITIVE
					 && MCalculator::calculateDeterminant(u) < number_traits::additiveUnit )
					|| (_mode == RIGHT_POSITIVE
							&& MCalculator::calculateDeterminant(v) < number_traits::additiveUnit))
			{
				traits::setElement(0,0, -number_traits::multiplicativeUnit, tmp);
				u = tmp * u;
				v = v * tmp;
				traits::setElement(0,0, number_traits::multiplicativeUnit, tmp);
			}
		}
	}
}
