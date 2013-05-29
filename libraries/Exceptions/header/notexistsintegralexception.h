#ifndef NOTEXISTSINTEGRALEXCEPTION_H
#define NOTEXISTSINTEGRALEXCEPTION_H

#include "mathexception.h"

namespace Exceptions
{
	/**
		* @brief Special exception for integration
	  */
	class NotExistsIntegralException:public MathException
	{
		public:
			/**
				* @brief Simple constructor
			  * @param ex The message
			  * @param id Special id
			  * @param mainCause The main cause of message
			  */
			NotExistsIntegralException(std::string ex = "Not exists integral ERROR",
					                       int id = 0,
																 Exception* mainCause = 0)
					 :MathException(ex, id, mainCause)
			{                           }
	};
}


#endif
