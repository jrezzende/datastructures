#pragma once
#ifndef INCLUDED_RINGBUFFER_H
#define INCLUDED_RINGBUFFER_H

#include "Node.h"
#include "EmptyStructureException.h"
#include "InvalidDataException.h"
#include "IndexException.h"
#include "FullStructureException.h"

template <typename T>
class RingBuffer {

   Node<T>* head;
   std::size_t size_;

public:
   virtual ~RingBuffer()= default;
   RingBuffer();

   void push(const T& data);

   std::size_t find(const T& data) const;
   std::size_t size() const { return this->size_; }
   T at(std::size_t index);

   bool empty() const;
};

template<typename T>
inline RingBuffer<T>::RingBuffer()
{
   size_= 0;
   head= nullptr;
}

template<typename T>
inline void RingBuffer<T>::push(const T& data)
{
   if (empty())
      head = new Node<T>(data);
   else if (size_ == 1) {
      Node<T>* node = new Node<T>(data, head, head);
      head->setNext(node);
      head->setPrev(node);
   }
   else {
      Node<T>* node = new Node<T>(data, head->prev(), head);
      head->prev()->setNext(node);
      head->setPrev(node);
   }
   size_++;
}

template<typename T>
inline std::size_t RingBuffer<T>::find(const T & data) const
{
   Node<T>* current= head;
   
   for (int i= 0; i < size_; i++) {
      if (current->data() == data)
         return i;
      current= current->next();
   }
   return size_;
}

template<typename T>
inline T RingBuffer<T>::at(std::size_t index)
{
   if (index >= size_ || index < 0)
      throw IndexException();

   Node<T>* current= head;

   for (int i= 0; i < index; i++)
      current= current->next();

   return current->data();
}

template<typename T>
inline bool RingBuffer<T>::empty() const
{
   return size_ == 0;
}

#endif // INCLUDED_RINGBUFFER_H
