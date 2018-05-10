#pragma once
#ifndef INCLUDED_FULLSTRUCTUREEXCEPTION_H
#define INCLUDED_FULLSTRUCTUREEXCEPTION_H

#include <exception>
#include <string>

class FullStructureException : public std::exception
{
public:
   virtual std::string* except() const throw() {
      return &std::string("Your structure is full.");
   }
};

#endif // !INCLUDED_FULLSTRUCTUREEXCEPTION_H