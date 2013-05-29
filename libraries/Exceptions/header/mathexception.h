#ifndef MATHEXCEPTION
#define MATHEXCEPTION

#include "exception.h"

namespace Exceptions
{
	/**
		* @brief Exceptions for mathematical errors.
	  */
    class MathException:public Exception
    {
        public:
			/**
			  * @brief Simple constructor
			  * @param ex The error message
			  * @param id The id of the exception
			  * @param mainCause The cause of the error
		      */
			 MathException(std::string ex = "MATH ERROR",
                     int id = 0,
					           Exception* mainCause = 0)
					  :Exceptions::Exception(ex, id, mainCause)
       {  }
    };
}


#endif
