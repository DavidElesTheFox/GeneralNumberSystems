#ifndef EXCEPTIONS__RUNTIMEEXCEPTION_H
#define EXCEPTIONS__RUNTIMEEXCEPTION_H

#include "runtimeexception.h"

namespace Exceptions
{
	/**
		* @brief Parameter exception for parameter error
		*/
	class ParameterException: public RuntimeException
	{
		public:
			/**
				* @brief Defalt constuctor
				* @param ex The error message
				* @param id The special id
				* @param mainCause The main cause of the exception
				*/
			ParameterException(std::string ex = "Parameter error",
					               int id = 0,
												 Exception* mainCause = 0)
				:RuntimeException(ex, id, mainCause)
			{	}
	};
}



#endif //EXCEPTIONS__RUNTIMEEXCEPTION_H

