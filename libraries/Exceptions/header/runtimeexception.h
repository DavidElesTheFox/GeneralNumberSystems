#ifndef RUNTIMEEXCEPTION_H
#define RUNTIMEEXCEPTION_H

#include "exception.h"

namespace Exceptions
{
	/**
		* @brief Exception for unexpected errors.
	  */
    class RuntimeException:public Exception
    {
      public:
			  /**
					* @brief Simple constructor
					* @param ex The error message
					* @param id The special id
					* @param mainCause The main cause
					*/
				RuntimeException(std::string ex = "ERROR",
												 int id = 0,
												 Exception* mainCause = 0)
												  :Exception(ex, id, mainCause)
				{               }
    };
}
#endif
