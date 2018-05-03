#pragma once
#ifndef RingList_HPP
#define RingList_HPP

#include "Node.h"

template <typename T>
class RingList {

   Node<T>* sentinel;
   Node<T>* head;
   std::size_t size_;

public:
   ~RingList();
   RingList();

  

};

#endif // INCLUDED_RINGLIST_H