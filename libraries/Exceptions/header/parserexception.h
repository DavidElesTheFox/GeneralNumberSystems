#ifndef __EXCEPTIONS__PARSEREXCEPTION_H
#define __EXCEPTIONS__PARSEREXCEPTION_H

#include "runtimeexception.h"
#include <iostream>

namespace Exceptions
{
	/**
		Exception at parsing
	*/
	class ParserException:RuntimeException
	{
		protected:
			/**
				* @brief Offset where are the error 
			  */
			int _offset;
			/**
				* @brief The string where the bug is located 
			  */
			std::string _str;
		public:

			/**
				* @brief Simple constructor
				* @param offset The offset of the error
				* @param str The parsed string
				*/
			ParserException(int offset, std::string str)
				:RuntimeException("Parser error"),_offset(offset),_str(str)
			{	}

			/**
				* @brief Getter for the error ofset
				* @return The offset of the error
				*/
			int getOffset() const
			{
				return _offset;
			}

			/**
				* @brief Getter for the parsed string
				* @return The parsed string
				*/
			std::string getString() const
			{
				return _str;
			}

			/**
				* @brief Printer function
				* @param os The output stream
				* @param ex The exceptino
				* @return The input stream due to chaining
				*/
			friend std::ostream& operator<<(std::ostream& os, const ParserException& ex)
			{
				os<<"Parser Error!"<<std::endl;
				os<<"String: \""<<ex._str<<"\""<<std::endl;
				os<<"at: "<<ex._offset<<std::endl;
				std::string str = ex._str;
				str.insert(ex._offset, 1, '[');
				str.push_back(']');
				os<<str<<std::endl;
				return os;
			}
	};
}


#endif //__EXCEPTIONS__PARSEREXCEPTION_H
