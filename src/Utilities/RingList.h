#pragma once
#ifndef INCLUDED_RINGBUFFER_H
#define INCLUDED_RINGBUFFER_H

#include "LinkedList.h"

template <typename T>
class RingList : public LinkedList<T> {
   Node<T>* head;
   std::size_t size_;

public:
   virtual ~RingList()= default;
   RingList() : LinkedList<T>() {
      Node<T>* sentinel= new Node<T>(nullptr, nullptr);
      this->head= sentinel;
      sentinel->setNext(this->head);
      size_= 0;
   }
   void push(const T& data);
   void insert(const T& data, std::size_t index);
   void push_front(const T& data);
   T at(std::size_t index);

};

template<typename T>
inline void RingList<T>::push(const T& data)
{
   return insert(data, size_);
}

template<typename T>
inline void RingList<T>::insert(const T& data, std::size_t index)
{
   if (index < 0 || index > this->size_)
      throw FullStructureException();
   if (index == 0)
      return push_front(data);

   Node<T>* prev= head->next();
   Node<T>* new_node= new Node<T>(data, nullptr);

   if (!new_node)
      throw FullStructureException();

   for (int i= 1; i < index; i++)
      prev= prev->next();

   new_node->setNext(prev->next());
   prev->setNext(new_node);
   this->size_++;
}

template<typename T>
inline void RingList<T>::push_front(const T & data)
{
   Node<T>* new_node= new Node<T>(data, nullptr);
   if (!new_node)
      throw FullStructureException();
   new_node->setNext(this->head->next());
   this->head->setNext(new_node);
   this->size_++;
}

template<typename T>
inline T RingList<T>::at(std::size_t index)
{
   if (size_ == 0)
      throw EmptyStructureException();

   Node<T>* current= this->head->next();
   for (int i= 0; i < index; i++)
      current= current->next();
   return current->data();
}

#endif // INCLUDED_RINGBUFFER_H