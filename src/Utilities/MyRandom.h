#pragma once
#ifndef INCLUDED_MYRANDOM_H
#define INCLUDED_MYRANDOM_H

#include <random>

namespace MyRandom
{
   inline int generate(int outset, int end)
   {
      std::random_device rd;
      std::mt19937 eng(rd());
      std::uniform_int<> const distr(outset, end);

      return distr(eng);
   }
}

#endif //INCLUDED_MYRANDOM_H