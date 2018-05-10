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

   Node<T>* sentinel;
   Node<T>* head;
   std::size_t size_;

public:
   ~RingBuffer();
   RingBuffer();

   void push_back(const T& data);
   void push_front(const T& data);
   void insert(const T& data, std::size_t index);

   T pop_back();
   T pop_front();
   T pop(std::size_t index);
   T pop_data(const T& data);

   void remove_front();
   void clear();

   std::size_t find(const T& data) const;
   T& at(std::size_t index);

   bool contains(const T& data) const;
   bool empty() const;
};

template<typename T>
inline RingBuffer<T>::~RingBuffer()
{
   clear();
}

template<typename T>
inline RingBuffer<T>::RingBuffer()
{
   size_= 0;
   head= nullptr;
   sentinel= new Node<T>(0, head);
}

template<typename T>
inline void RingBuffer<T>::push_back(const T& data)
{
   if (empty())
      return push_front(data);
   insert(data, size_);
}

template<typename T>
inline void RingBuffer<T>::push_front(const T & data)
{
   Node<T>* new_node= new Node<T>(data, nullptr);
   if (!new_node)
      throw FullStructureException();
   sentinel->setNext(new_node);
   if (!empty()) {
      new_node->setNext(head);
      head= new_node;
   } else {
      head= new_node;
      head->setNext(sentinel);
   }
   size_++;
}

template<typename T>
inline void RingBuffer<T>::insert(const T& data, std::size_t index)
{
   if (index < 0)
      throw IndexException();
   else if (index >= size_)
      return push_back(data);
   else if (index == 0)
      return push_front(data);

   Node<T>* new_node= new Node<T>(data, nullptr);
   Node<T>* prev;

   if (!new_node)
      throw FullStructureException();

   prev= head;

   while (--index != 0)
      prev= prev->next();

   new_node->setNext(prev->next());
   prev->setNext(new_node);

   size_++;
}

template<typename T>
inline T RingBuffer<T>::pop_back()
{
   if (empty())
      throw EmptyStructureException();
   return pop(size_ - 1);
}

template<typename T>
inline T RingBuffer<T>::pop_front()
{
   if (empty())
      throw EmptyStructureException();
   Node<T>* tempNode= head;
   T aux= tempNode->data();

   head= head->next();
   sentinel->setNext(head);

   size_--;
   delete tempNode;
   return aux;
}

template<typename T>
inline T RingBuffer<T>::pop(std::size_t index)
{
   if (index < 0)
      throw IndexException();
   else if (index >= size_)
      pop_back();
   else if (index == 0)
      return pop_front();

   Node<T> *prevNode, *tempNode;
   T aux;

   prevNode= head;

   while (--index != 0)
      prevNode= prevNode->next();

   tempNode= prevNode->next();
   aux= tempNode->data();
   prevNode->setNext(tempNode->next());

   size_--;
   delete tempNode;
   return aux;
}

template<typename T>
inline T RingBuffer<T>::pop_data(const T & data)
{
   if (empty())
      throw EmptyStructureException;
   return pop(find(data));
}

template<typename T>
inline void RingBuffer<T>::remove_front()
{
   if (empty())
      throw EmptyStructureException();

   delete head;

   head= head->next();
   sentinel->setNext(head);
}

template<typename T>
inline void RingBuffer<T>::clear()
{
   Node<T>* current= head;
   
   while (size_ != 0) {
      current= current->next();
      sentinel->setNext(current);
      remove_front();
      size_--;
   }
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
inline T& RingBuffer<T>::at(std::size_t index)
{
   if (index >= size_)
      std::out_of_range("LIST IS EMPTY!");
   Node<T>* current= head;

   while (--pos != 0)
      current= current->next();

   return current->data();
}

template<typename T>
inline bool RingBuffer<T>::contains(const T & data) const
{
   Node<T>* current= head;

   for (int i = 0; i < size_; i++) {
      if (current->data == data)
         return true;
      current= current->next();
   }
   return false;
}

template<typename T>
inline bool RingBuffer<T>::empty() const
{
   return size_ == 0;
}

#endif // INCLUDED_RINGBUFFER_H
