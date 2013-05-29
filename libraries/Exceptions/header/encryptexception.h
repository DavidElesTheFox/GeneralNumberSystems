#ifndef _EXCEPTIONS__ENCRYPTEXCEPTION_H
#define _EXCEPTIONS__ENCRYPTEXCEPTION_H

#include "exception.h"

namespace Exceptions
{
	/**
		* @brief Excetion to fail any Encryption
	  */
	class EncryptException :public Exception
	{
		public:
			/**
				* @brief Simple constructor
				* @param message The error message
				* @param id The error id
				* @param cause The main cause of the error
				*/
			EncryptException(std::string message ="Encryption error", int id = 0, Exception* cause = 0):
				Exception(message,id,cause){}
	};
}

#endif // _EXCEPTIONS__ENCRYPTEXCEPTION_H
