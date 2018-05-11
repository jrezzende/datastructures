#pragma once
#ifndef INCLUDED_LINKEDQUEUE_H
#define INCLUDED_LINKEDQUEUE_H

#include "Node.h"
#include "LinkedList.h"
#include "EmptyStructureException.h"

template<typename T>
class LinkedQueue : LinkedList<T> 
{
   Node<T>* tail;

public:
   ~LinkedQueue()= default;
   LinkedQueue() : LinkedList<T>(), tail(nullptr) {}

   void enqueue(T& data);

   T dequeue();
   T front();
   T back();

   bool empty();

   std::size_t size() const;
};

template<typename T>
inline void LinkedQueue<T>::enqueue(T& data)
{
   Node<T>* new_node= new Node<T>(data, nullptr);
   if (!new_node)
      throw FullStructureException();

   if (empty())
      this->head= new_node;
   else
      tail->setNext(new_node);
   tail->setNext(nullptr); // (0)
   tail= new_node;
   this->size_++;
}

template<typename T>
inline T LinkedQueue<T>::dequeue()
{
   if (empty())
      throw EmptyStructureException();
 
   Node<T>* toBePopped= this->head;
   T temp= toBePopped->data();
   this->head= toBePopped->next();

   if (this->size_ == 1)
      tail= nullptr;

   this->size_--;

   delete toBePopped;
   return temp;
}

template<typename T>
inline T LinkedQueue<T>::front()
{
   if (empty())
      throw EmptyStructureException();
   return head->data();
}

template<typename T>
inline T LinkedQueue<T>::back()
{
   if (empty())
      throw EmptyStructureException();
   return tail->data();
}

template<typename T>
inline bool LinkedQueue<T>::empty()
{
   return size_ == 0;
}

template<typename T>
inline std::size_t LinkedQueue<T>::size() const
{
   return size_;
}

#endif // !INCLUDED_LINKEDQUEUE_H