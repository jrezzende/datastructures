#pragma once
#ifndef INCLUDED_APP_H
#define INCLUDED_APP_H

#include <iostream>

class App
{
public:
  ~App()= default;
  App()
  {
     std::cout << R"(
               TRAFFIC JAM SYSTEM!


                       ##
                      _[]_
                     [____]
                 .----'  '----.
             .===|    .==.    |===.
             \   |   /####\   |   /
             /   |   \####/   |   \
             '===|    `""`    |==='
             .===|    .==.    |===.
             \   |   /::::\   |   /
             /   |   \::::/   |   \
             '===|    `""`    |==='
             .===|    .==.    |===.
             \   |   /&&&&\   |   /
             /   |   \&&&&/   |   \
             '===|    `""`    |==='
                 '--.______.--'


)";
  }
};

#endif // INCLUDED_APP_H
