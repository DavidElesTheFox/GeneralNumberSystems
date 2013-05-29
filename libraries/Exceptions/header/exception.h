#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <iostream>

namespace Exceptions
{
	/**
		* @brief Base exception class
	  */
    class Exception
    {
		protected:
			
			/**
				* @brief the error message
				*/
			std::string _message;
			
			/**
				* @brief special id of exception
				*/
			int _id;
			
			/**
				* @brief the cause of exception
				*/
			Exception* _cause;	

        public:
			/**
			  * Default constructor
			  * @param ex Error message
			  * @param id Special id for exception
			  * @param mainCause The cause of the exception
			  */
      Exception(std::string ex = "ERROR",
					            int id = 0,
					            Exception* mainCause = 0)
			  :_message(ex), _id(id), _cause(mainCause)
      {   }

			/**
				* @brief Simple destructor
				* @details This function delete the cause in recursive way
				*/
			~Exception()
			{
				delete _cause;
			}

			/**
				* @brief getter for error message
				* @deprecated
			  * @return the error message
			  */
      std::string Message()const __attribute__((deprecated))
      {   return _message; }

			/**
				* @brief getter for error message
			  * @return the error message
			  */
			std::string getMessage() const
			{  return _message; }

			/**
			  * @brief getter for special id
				* @deprecated
			  * @return the special id
			  */
      int Id() const __attribute__ ((deprecated))
      {   return _id;  }

			/**
				* @brief getter for error message
			  * @return the error message
			  */
			int getId() const
			{  return _id;  }

			/**
			  * @brief Getter for cause
			  * @return the cause exception, it could be 0
			  */
      Exception* getCause()const
      {   return _cause;   }

			/**
				* @brief Print the stack trace
				* @return Return the string which contains the stack trace
				*/
			std::string printStackTrace() const
			{
				Exception* ex = _cause;
				std::string trace = _message + " coused by: \n";
				while(ex != 0)
				{
					trace += ex->_message;
					if(ex->_cause != 0)
						trace += " coused by: \n";
					ex = ex->_cause;
				}
				return trace;
			}

			/**
			  * @brief Printer operator
			  * @param os the output stream
				* @param ex the exception object
				* @return the parameter output stream due to chaining
			  */
			friend std::ostream& operator << (std::ostream& os,const Exception& ex)
			{
					os<<"ERROR: "<<ex._message<<std::endl;
					return os;
			}
    };

}

#endif
