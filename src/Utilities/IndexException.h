#pragma once
#ifndef INCLUDED_INDEXEXCEPTION_H
#define INCLUDED_INDEXEXCEPTION_H

#include <exception>
#include <string>

class IndexException : public std::exception
{
public:
   virtual std::string* except() const throw() {
      return &std::string("Index out of bounds.");
   }
};

#endif // !INCLUDED_INDEXEXCEPTION_H