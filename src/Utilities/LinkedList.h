#pragma once
#ifndef INCLUDED_LINKEDLIST_H
#define INCLUDED_LINKEDLIST_H

#include "Node.h"

template <typename T>
class LinkedList
{
   Node* head;
   std::size_t size_;

   Node* end() {
      auto it= head;
      for (auto i= 1; i < size(); ++i)
         it= it->next();
      return it;
   }

public:
   ~LinkedList();
   LinkedList();

   void clear();
   void push_back(const T& data);
   void push_front(const T& data);
   void insert(const T& data, std::size_t index);
   void insert_sorted(const T& data);
   T& at(std::size_t index);
   T pop();
   T pop_back();
   T pop_front();
   void remove(const T& data);
   bool empty() const;
   bool contains() const;
   std::size_t find(const T& data) const;
   std::size_t size() const;
};


#endif // !INCLUDED_LINKEDLIST_H

template<typename T>
inline LinkedList<T>::~LinkedList()
{
   clear();
}

template<typename T>
inline LinkedList<T>::LinkedList()
{
   size_= 0;
   head= nullptr;
}

template<typename T>
inline void LinkedList<T>::clear()
{
   Node<T>* current;
 
}

template<typename T>
inline void LinkedList<T>::push_back(const T & data)
{
}

template<typename T>
inline void LinkedList<T>::push_front(const T & data)
{
}

template<typename T>
inline void LinkedList<T>::insert(const T & data, std::size_t index)
{
}

template<typename T>
inline void LinkedList<T>::insert_sorted(const T & data)
{
}

template<typename T>
inline T & LinkedList<T>::at(std::size_t index)
{
   // TODO: insert return statement here
}

template<typename T>
inline T LinkedList<T>::pop()
{
   return T();
}

template<typename T>
inline T LinkedList<T>::pop_back()
{
   return T();
}

template<typename T>
inline T LinkedList<T>::pop_front()
{
   return T();
}

template<typename T>
inline void LinkedList<T>::remove(const T & data)
{
}

template<typename T>
inline bool LinkedList<T>::empty() const
{
   return false;
}

template<typename T>
inline bool LinkedList<T>::contains() const
{
   return false;
}

template<typename T>
inline std::size_t LinkedList<T>::find(const T & data) const
{
   return std::size_t();
}

template<typename T>
inline std::size_t LinkedList<T>::size() const
{
   return std::size_t();
}
