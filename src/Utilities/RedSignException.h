#pragma once
#ifndef INCLUDED_REDSIGNEXCEPTION_H
#define INCLUDED_REDSIGNEXCEPTION_H

#include <exception>
#include <string>

class RedSignException : public std::exception
{
public:
   virtual std::string& except() const throw() {
      return *new std::string("The current semaphore is closed.");
   }
};

#endif // !INCLUDED_REDSIGNEXCEPTION_H