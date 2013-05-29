

#define DEF_TEMP template<class INT_TYPE,                       \
                          class FLOAT_TYPE,                     \
						              template<class T> class Matrix,       \
						              template<class T> class Vector,       \
                          template<class T> class VectorNorm,   \
                          template<class T> class MatrixNorm,   \
						              template<class T, class M>            \
                            class matrix_traits,                \
						              template<class T, class V>            \
                            class vector_traits,                \
						              template<class T> class number_traits>

#define ESC_ALG EscapeAlgorithm<INT_TYPE,      \
	                              FLOAT_TYPE,    \
                                Matrix,        \
                                Vector,        \
                                VectorNorm,    \
                                MatrixNorm,    \
                                matrix_traits, \
                                vector_traits, \
                                number_traits>
namespace MATH
{
	namespace NumberSystem
	{

		DEF_TEMP
		ESC_ALG::EscapeAlgorithm(const ESC_ALG::ConnectedNumberSystem* ns,
														 const unsigned convergencieBorder):
			_ns(ns),
			_convBorder(convergencieBorder),
			_suggestion(0),
			_focusPoint(matrix_traits_int::getRowNum(ns->getBase()))
		{
		}

		DEF_TEMP
		void ESC_ALG::compute(const short xCoord,
													const short yCoord,
							            int height,
							            int width,
							            unsigned**& convergencieMatrix,
							            FLOAT_TYPE zoom)
		{
			int i = 0;
			int j = 0;
			register unsigned k = 0;
			register unsigned l = 0;
			register unsigned size = 0;

			register unsigned lastSetSize = 0;
			std::vector<FVector > convertedDigitSet;
			ConnectedDigitSet digitSet = _ns->getDigitSet();

			for(unsigned i = 0; i < digitSet.size(); ++i)
			{
				convertedDigitSet.push_back(
					I_F_Converter::template convertVector<Vector>(digitSet[i]));
			}
			FMatrix convertedBase = 
				I_F_Converter::template convertMatrix<Matrix>(_ns->getBase());

			FVector vector1, vector2;

      NumSysCalc::computeRectangleOfH(vector1, vector2, *_ns);
			vector1 = vector1 * zoom;
			vector2 = vector2 * zoom; 
//      std::cout << "Vector1: " << vector1 << std::endl;
//      std::cout << "Vector2: " << vector2 << std::endl;
			double v1Norm = VectorNorm_float::calculateNorm(vector1);
			double v2Norm = VectorNorm_float::calculateNorm(vector2);

			double K = v1Norm > v2Norm ? v1Norm 
				                         : v2Norm;
			FLOAT_TYPE stepDistanceX = NumCalc_float::abs(vector_traits_float::getElement(
																		 xCoord, vector1 - vector2));
      stepDistanceX /= static_cast<FLOAT_TYPE>(width);

			FLOAT_TYPE stepDistanceY = NumCalc_float::abs(vector_traits_float::getElement(
					                           yCoord, vector1 - vector2));
      stepDistanceY /= static_cast<FLOAT_TYPE>(height);

			FVector v1 = vector1;//upper estimation
			FVector v2 = vector2;//lower estimation
			_suggestion = 0;
      FVector leftDownCorner = v2;
			FVector z = leftDownCorner;
//      std::cout << "height: " << height << " [" << stepDistanceY << "]" << std::endl;
//      std::cout << "width: " << width << " [" << stepDistanceX << "]" << std::endl;

			register unsigned digitSize = convertedDigitSet.size();
			for(i = 0; i < height; ++i)
			{
				vector_traits_float
					::setElement(yCoord,
											 (FLOAT_TYPE(i) * stepDistanceY
											  + vector_traits_float::getElement(yCoord,leftDownCorner)),
											 z);
        vector_traits_float::
						setElement(xCoord,
											 (vector_traits_float::getElement(xCoord, leftDownCorner)),
											 z);
      //  std::cout << "Z: " << z << std::endl;
				for(j = 0; j < width; ++j)
				{
					vector_traits_float::
						setElement(xCoord,
											 (FLOAT_TYPE(j) * stepDistanceX
										    + vector_traits_float::getElement(xCoord, leftDownCorner)),
											 z);
      //    std::cout << "z: " << z << std::endl;
					/* It is an array of std::vectors which contains FVectors! */
					std::vector<FVector> S[2]; 
					std::vector<FVector> set;
					set.push_back(z);
					S[0] = set;
					size = 1;
					lastSetSize = S[(size - 1) % 2].size();
					while(size < _convBorder && lastSetSize)
					{
						S[size % 2].clear();
						for(k = 0; k < lastSetSize; ++k)
						{
							for(l = 0; l < digitSize; ++l)
							{
								FVector ztmp = convertedBase 
									             * S[(size - 1) % 2][k]
															 - convertedDigitSet[l];
								if(VectorNorm_float::calculateNorm(ztmp) < K) //use vectorCalculator
								{
									S[size % 2].push_back(ztmp);
								}
							}
						}
						lastSetSize = S[size++ % 2].size();
					}
					if(size < _convBorder && size > _suggestion)
						_suggestion = size;
					convergencieMatrix[i][j] = size;
				}
			}
		}

		DEF_TEMP
		void ESC_ALG::computeRectangle(FVector& v1,
						                  FVector& v3)
		{
			int dimension = matrix_traits_int::getRowNum(_ns->getBase());
			FMatrix X = _ns->getBaseInverse();

			v1 = v3 = vector_traits_float::create(dimension);
			FVector v2 = v1;
			FVector v4 = v3;
			
			int c = 1;
			double norm = MatrixNorm_float::calculateNorm(X);
			while (norm >= 1)
			{
				X = X*X;
				norm = MatrixNorm_float::calculateNorm(X);
				c++;
			}
			rectangleComputeCore(v2, v4, dimension, c);
			v2 = v2*FLOAT_TYPE(1.0/(1.0 - norm));
			v4 = v4*FLOAT_TYPE(1.0/(1.0 - norm));
			for(int i = 0; i < dimension; ++i)
			{
				vector_traits_float::setElement(i,
																				NumCalc_float::ceil(
																					vector_traits_float::
																					  getElement(i,v2)),
																				v3);
				vector_traits_float::setElement(i,
																				NumCalc_float::floor(
																					vector_traits_float::
																					  getElement(i,v4)),
																				v1);
			}
		}

		DEF_TEMP
		void ESC_ALG::rectangleComputeCore(FVector& v2,
												               FVector& v4,
												               const int dimension,
																	     const int minNorm)
		{
			FMatrix X = _ns->getBaseInverse();
			FLOAT_TYPE min, max;
			ConnectedDigitSet digits = _ns->getDigitSet();
			std::vector<FVector> set(digits.size()* minNorm);
			for(int j = 0; j < minNorm; ++j)
			{
				for(unsigned i = 0; i < digits.size(); ++i)
				{
					set[i + j * minNorm] = 
						X * I_F_Converter::template convertVector<Vector>(digits[i]);
				}
				X = X * X;
			}
			for (int j = 0; j < minNorm; ++j)
			{
				for (int i = 0; i < dimension; ++i)
				{
					min = vector_traits_float::getElement(i, set[j*minNorm]);
          min = NumCalc_float::abs(min);
					max = min;
					for (unsigned k = 0; k < digits.size();++k)
					{
						FLOAT_TYPE element = vector_traits_float::
							getElement(i, set[k + j*minNorm]);
            element = NumCalc_float::abs(element);
						if (min > element)
							min = element;
						if (max < element)
							max = element;
					}
					vector_traits_float::
						setElement(
							i,
							j == 0 ? min
						         : vector_traits_float::getElement(i,v2) + min,
							v2);

					vector_traits_float::
						setElement(
							i,
							j == 0 ? max
						         : vector_traits_float::getElement(i,v4) + max,
							v4);
				}
			}

		}

	}
}

#undef DEF_TEMP
#undef ESC_ALG

