#pragma once
#ifndef INCLUDED_LINKEDQUEUE_H
#define INCLUDED_LINKEDQUEUE_H

#include "Node.h"

template<typename T>
class LinkedQueue
{
   Node* head;
   Node* tail;
   std::size_t size_;

public:
   ~LinkedQueue();
   LinkedQueue();
   
   void clear();
   void enqueue(const T& data);

   T dequeue();
   T& front() const;
   T& back() const;

   bool empty();

   std::size_t size() const;
};

#endif // !INCLUDED_LINKEDQUEUE_H

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
inline void LinkedQueue<T>::enqueue(const T & data)
{
   if (empty()) {
      head= new Node(data);
      tail= head;
   } 
   else {
      auto new_node= new Node(data);
      tail->setNext(new_node);
      tail= new_node;
   }
   size_++;
}

template<typename T>
inline T LinkedQueue<T>::dequeue()
{
   if (empty())
      throw std::out_of_range("LIST IS EMPTY!");
   else if (size_ == 1) {
      T temp= head->data();
      head= nullptr;
      tail= nullptr;
      size_--;
      return temp;
   }
   Node* current= head;
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
      throw std::out_of_range("LIST IS EMPTY!");
   return head->data();
}

template<typename T>
inline T &LinkedQueue<T>::back() const
{
   if (empty())
      throw std::out_of_range("LIST IS EMPTY!");
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
