namespace MATH
{
	namespace LinearAlgebra
	{
		template<typename T,
			       class Vector,
						 class number_traits,
						 class vector_traits>
		double VectorCalculator<T, Vector, number_traits, vector_traits>::
		  norm(const unsigned norm,
				   const Vector& v)
		{
			int count = vector_traits::getDimension(v);
			if(norm>0)
			{
				double s = 0;
				for(int i=0;i<count;++i)
				{
          double element = NumCalc::abs(vector_traits::getElement(i, v));
				  s += MATH::Algebra::NumberCalculator<double>::pow(element, norm);
				}

				return MATH::Algebra::NumberCalculator<double>::root(s,norm);
			}
			else// if(norm==0)
			{
				double max = NumCalc::abs(vector_traits::getElement(0, v));
				for(int i=1;i<count;++i)
				{
					double element = NumCalc::abs(vector_traits::getElement(i, v));
					if(max < element)
						max = element;
				}
				return max;
			}
		}
	}
}
