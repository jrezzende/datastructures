#pragma once
#ifndef INCLUDED_INVALIDDATAEXCEPTION_H
#define INCLUDED_INVALIDDATAEXCEPTION_H

#include <exception>
#include <string>

class InvalidDataException : public std::exception
{
public:
   virtual std::string* except() const throw() {
      return &std::string("Your structure does not contain such data.");
   }
};

#endif // !INCLUDED_INVALIDDATAEXCEPTION_H