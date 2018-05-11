#pragma once
#ifndef INCLUDED_LINKEDQUEUE_H
#define INCLUDED_LINKEDQUEUE_H

#include "Node.h"
#include "EmptyStructureException.h"

template<typename T>
class LinkedQueue
{
   Node<T>* head;
   Node<T>* tail;
   std::size_t size_;

public:
   ~LinkedQueue();
   LinkedQueue();
   
   void clear();
   void enqueue(T& data);

   T dequeue();
   T& front() const;
   T& back() const;

   bool empty();

   std::size_t size() const;
};

template<typename T>
inline LinkedQueue<T>::~LinkedQueue()
{
   clear();
}

template<typename T>
inline LinkedQueue<T>::LinkedQueue()
{
   head= tail= nullptr;
   size_= 0;
}

template<typename T>
inline void LinkedQueue<T>::clear()
{
   while(size_)
      dequeue();
}

template<typename T>
inline void LinkedQueue<T>::enqueue(T& data)
{
   if (empty()) {
      head= new Node<T>(data);
      tail= head;
   } 
   else {
      auto new_node= new Node<T>(data);
      tail->setNext(new_node);
      tail= new_node;
   }
   size_++;
}

template<typename T>
inline T LinkedQueue<T>::dequeue()
{
   if (empty())
      throw EmptyStructureException();
   else if (size_ == 1) {
      T temp= head->data();
      head= nullptr;
      tail= nullptr;
      size_--;
      return temp;
   }
   Node<T>* current= head;
   T temp= current->data();
   head= current->next();
   delete current;
   size_--;
   return temp;
}

template<typename T>
inline T &LinkedQueue<T>::front() const
{
   if (empty())
      throw EmptyStructureException();
   return head->data();
}

template<typename T>
inline T &LinkedQueue<T>::back() const
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