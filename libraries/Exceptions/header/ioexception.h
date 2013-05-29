#ifndef MATHEXCEPTION
#define MATHEXCEPTION

#include "runtimeexception.h"

namespace Exceptions
{
	/**
		* @brief Exception class for I/O errors
	  */
    class IOException: public RuntimeException
    {
      public:
				/**
					* @brief Simple constructor
					* @param ex Error message
					* @param id Id of the message
					* @param mainCause The cause of the exception
					*/
        IOException(std::string ex = "IO ERROR",
                    int id = 0,
					          Exception* mainCause = 0)
					  :RuntimeException(ex, id, mainCause)
        {  }
    };
}


#endif
