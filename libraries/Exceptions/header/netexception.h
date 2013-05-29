#ifndef _EXCEPTIONS__NETEXCEPTION_H
#define _EXCEPTIONS__NETEXCEPTION_H

#include "exception.h"

#include <string.h>
#ifndef WIN32

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#endif //WIN32

namespace Exceptions
{
	/**
		Exception of Net libries
	*/
	class NetException:public Exception
	{
		protected:
			/** 
				* @brief socket info 
			  */
			sockaddr_in _address;
		public:

			/**
				* @brief Simple constructor
				* @param message The message of the error
				* @param id      The special id of the error
				* @param cause   The main cause of the error
				*/
			NetException(std::string message = "NET ERROR",
						       int id = 0,
						       Exception* cause = 0): Exception(message, id, cause)
			{	memset( &_address, 0, sizeof(sockaddr_in) );	}

			/**
				* @brief Special constructor
				* @param message The message of the error
				* @param error   The socket where the error is located
				*/
			NetException(std::string message, const sockaddr_in& error):Exception(message)
			{	memcpy( &_address, (void*)&error, sizeof(sockaddr_in) );	}

			/**
				* @brief Printer operator
				* @param os The output operator
				* @param ex The exception
				* @return The input parameter stream due to chaining
				*/
			friend std::ostream& operator<<(std::ostream& os,const NetException ex)
			{
				os << "ERROR: " << ex.message << std::endl;
				if (ex._address.sin_port != 0)
				{
					os << "\tIP: " << inet_ntoa(ex._address.sin_addr) << std::endl;
					os << "\tPort: " << ntohs(ex._address.sin_port) << std::endl;
				}
				return os;
			}
	};



}
#endif
