#ifndef WRONGDIMENSIONEXCEPTION_H
#define WRONGDIMENSIONEXCEPTION_H

#include "mathexception.h"

namespace Exceptions
{

	/**
		* @brief Special mathematical exception for different dimensions problem
	  */
    class WrongDimensionException:public MathException
    {
		  public:
				/**
					* @brief Simple constructor
					* @param ex The error message
					* @param id The special id for errors
					* @param mainCause The main cause of the exception
					*/
				WrongDimensionException(std::string ex = "ERROR",
																int id = 0,
																Exception* mainCause = 0)
											:MathException(ex, id, mainCause)
				{  }
    };
}
#endif
