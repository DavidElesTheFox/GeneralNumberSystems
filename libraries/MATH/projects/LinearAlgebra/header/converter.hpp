namespace MATH
{
	namespace LinearAlgebra
	{
		template<class FROM_TYPE,
			       class TO_TYPE,
						 template<typename T, class V>
							 class vector_traits,
						 template<typename T, class M>
							 class matrix_traits,
						 template<typename T>
							 class number_traits>
		template<template<typename T>
							 class Vector>
		Vector<TO_TYPE> Converter<FROM_TYPE,
		                          TO_TYPE,
															vector_traits,
															matrix_traits,
															number_traits>::
		  convertVector(const Vector<FROM_TYPE>& vector)
		{
			typedef vector_traits<FROM_TYPE,
			                      Vector<FROM_TYPE> >
												From_Vector_traits;
			typedef vector_traits<TO_TYPE,
							              Vector<TO_TYPE> >
												To_Vector_traits;
								
			const int dimension = From_Vector_traits::getDimension(vector);
			Vector<TO_TYPE> out = To_Vector_traits::create(dimension);
			for (int i = 0; i < dimension; ++i)
			{
				FROM_TYPE act = From_Vector_traits::getElement(i, vector);
				TO_TYPE other = 
					number_traits<FROM_TYPE>::template convert<TO_TYPE>(act);
				To_Vector_traits::setElement(i, other, out);
			}
			return out;
		}


		template<class FROM_TYPE,
			       class TO_TYPE,
						 template<typename T, class V>
							 class vector_traits,
						 template<typename T, class M>
							 class matrix_traits,
						 template<typename T>
							 class number_traits>
		template<template<typename T>
							 class Matrix>
		Matrix<TO_TYPE> Converter<FROM_TYPE,
		                          TO_TYPE,
															vector_traits,
															matrix_traits,
															number_traits>::
		  convertMatrix(const Matrix<FROM_TYPE>& matrix)
		{
			typedef matrix_traits<FROM_TYPE,
			                      Matrix<FROM_TYPE> >
												From_Matrix_traits;
			typedef matrix_traits<TO_TYPE,
							              Matrix<TO_TYPE> >
												To_Matrix_traits;
								
			int rowNum,colNum;
			From_Matrix_traits::getDimension(rowNum, colNum, matrix);
			Matrix<TO_TYPE> out = To_Matrix_traits::createMatrix(rowNum,
					                                                 colNum);
			for (int i = 0; i < rowNum; ++i)
			{
				for (int j = 0; j < colNum; ++j)
				{
					FROM_TYPE act = From_Matrix_traits::getElement(i, j, matrix);
					TO_TYPE other = 
						number_traits<FROM_TYPE>::template convert<TO_TYPE>(act);
					To_Matrix_traits::setElement(i, j, other, out);
				}
			}
			return out;
		}

	}
}
