#include <random>
#include "MyRandom.h"

int MyRandom::generate(int outset, int end)
{
   std::random_device rd;
   std::mt19937 eng(rd());
   std::uniform_int_distribution<> const distr(outset, end);

   return distr(eng);
}
