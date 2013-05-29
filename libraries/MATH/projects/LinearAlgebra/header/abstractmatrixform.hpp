namespace MATH
{
	namespace LinearAlgebra
	{

		template<class Matrix>
		AbstractMatrixForm<Matrix>::AbstractMatrixForm(const Matrix& m):
			_original(m),
			_changed(true)
		{		}

		template<class Matrix>
		AbstractMatrixForm<Matrix>::~AbstractMatrixForm()
		{		}

		template<class Matrix>
		Matrix AbstractMatrixForm<Matrix>::getOriginalMatrix() const
		{
			return _original;
		}

		template<class Matrix>
		Matrix& AbstractMatrixForm<Matrix>::getOriginalMatrix()
		{
			_changed = true;
			return _original;
		}

		template<class Matrix>
		Matrix AbstractMatrixForm<Matrix>::
		  operator[](const std::string& name) 
		{
			calculate();
			MatrixMap_const_iterator it = _elements.find(name);
			std::string error = "AbstractMatrixForm element not found: ";
			if (it != _elements.end())
				return it->second;
			else
				throw Exceptions::RuntimeException(error + name);
		}

		template<class Matrix>
		Matrix AbstractMatrixForm<Matrix>::
		  operator[](const int& elementCount) 
		{
			if (elementCount > _elements.size())
				throw Exceptions::ParameterException("Param error "
																						 "AbstractMatrixForm::"
						                                 "operator[](const int&)");
			calculate();
			MatrixMap_const_iterator it = _elements.begin();
			for(int i = 0 ;i < elementCount && it != _elements.end(); ++it, ++i);
			return it->second;
		}

		template<class Matrix>
		void AbstractMatrixForm<Matrix>::calculate()
		{
			if (_changed)
			{
				calculateElements();
				_changed = false;
			}
		}




	}
}
