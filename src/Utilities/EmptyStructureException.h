#pragma once
#ifndef INCLUDED_EMPTYSTRUCTUREEXCEPTION_H
#define INCLUDED_EMPTYSTRUCTUREEXCEPTION_H

#include <exception>
#include <string>

class EmptyStructureException : public std::exception
{
public:
   virtual std::string& except() const throw() {
      return *new std::string("Your structure is empty.");
   }
};

#endif // !INCLUDED_EMPTYSTRUCTUREEXCEPTION_H