#ifndef OVERFLOWEXCEPTION_H
#define OVERFLOWEXCEPTION_H

#include "mathexception.h"
#include <sstream>
namespace Exceptions
{
	/**
		* @brief Mathematical overflow exception
	  */
    class OverFlowException:public MathException
    {
			protected:
				/**
					* @brief The limit of the values
					*/
				int _limit;

				/**
					* @brief The overflow value
					*/
				int _value;
		  public:
				/**
					* @brief Simple constructor
					* @param ex Error message
					* @param id Special id
					* @param mainCause The main cause of the error
					*/
				OverFlowException(std::string ex = "overflow ERROR",
													int id = 0,
													Exception* mainCause = 0)
											:MathException(ex, id, mainCause)
				{ }

				/**
					* @brief Special constructor
					* @param ex The error message
					* @param limit The limit of the values
					* @param value The overflowed value
					*/
				OverFlowException(std::string ex,
													int limit, 
													int value)
					:MathException(ex),
					_limit(limit), _value(value)
				{
					std::stringstream ss;
					ss<< ex << " (value: " << value << "; limit: " << limit << ")";
					this->_message = ss.str();
				}
    };
}
#endif
