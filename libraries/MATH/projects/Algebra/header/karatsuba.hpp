#ifndef MATH__ALGEBRA__KARATSUBA_H
#error Inlcuded only implementation
#endif

namespace MATH
{
	namespace Algebra
	{
		template<class BaseType,
			       class number_traits>
		BaseType* Karatsuba<BaseType, number_traits>::buffer = 0;

		template<class BaseType,
			       class number_traits>
		unsigned Karatsuba<BaseType, number_traits>::buffer_size = 0;


		template<class BaseType,
			       class number_traits>
		template<class Container>
		void Karatsuba<BaseType, number_traits>::doIt(const Container& a,
																	                const Container& b,
																	                const unsigned start,
																	                const unsigned end,
																	                Container& c)
		{
			if (4 * (end - start + 1) > buffer_size)
			{
				delete [] buffer;
				buffer_size = 4 * (end - start + 1);
				buffer = new BaseType[ buffer_size];
			}
			multiply(a, b, start, end, c, buffer);
		}

		template<class BaseType,
			       class number_traits>
		template<class Container>
		void Karatsuba<BaseType, number_traits>::multiply(const Container& a,
																			                const Container& b,
																			                const unsigned start,
																			                const unsigned end,
																			                Container& c,
																			                BaseType* bufferPointer)
		{
      if (end - start == 0)
      {
      }
      else if (end - start == 1)
      {
        c[start + start] = a[start] * b[start];
      }
      else if (end - start == 2)
			{
				c[start + start] = a[start] * b[start];
				c[end + end - 2] = a[end - 1] * b[end - 1];
				c[start + end - 1] = c[start + start] + c[end + end - 2] 
														 + (a[start] - a[end - 1]) * (b[end - 1] - b[start]);
			}
			else
			{
				BaseType* a2_a1 = bufferPointer;
				BaseType* b1_b2 = bufferPointer + (end - start)/2;
				BaseType* result = bufferPointer + (end - start);
				for(unsigned i = 0; i < (end-start); ++i)
				{
					result[i] = number_traits::additiveUnit;
				}

				//A1 * B1
				multiply(a, b,
						     start, (start + end)/2, 
								 c, bufferPointer + 2 * (end - start));

				//A2 * B2
				multiply(a, b,
						     (start + end) / 2, end, 
								 c, bufferPointer + 2  * (end - start));

				for(unsigned i = 0; i < (end - start)/2; ++i)
				{
					a2_a1[i] = a[(start + end)/2 + i] - a[start + i];
					b1_b2[i] = b[start + i] - b[(start + end)/2 + i];
				}

				multiply(a2_a1, b1_b2, 
						     0, (end - start)/2,
								 result,
								 bufferPointer + 2 * (end - start));

				for (unsigned i = 0; i < (end - start) - 1; ++i)
				{
					  result[i] +=  c[start + end + i] + c[2*start + i];
				}


				for (unsigned i = 0; i < (end - start) - 1; ++i)
				{
					c[2*start + (end - start)/2+ i] += result[i];
				}

			}
		}

	}
}

