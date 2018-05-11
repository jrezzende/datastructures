#pragma once
#ifndef INCLUDED_LINKEDLIST_H
#define INCLUDED_LINKEDLIST_H

#include "Node.h"
#include "EmptyStructureException.h"
#include "FullStructureException.h"
#include "IndexException.h"
#include "InvalidDataException.h"

template <typename T>
class LinkedList
{
protected:
   Node<T>* head;
   std::size_t size_;

public:
   ~LinkedList()= default;
   LinkedList() : head(nullptr), size_(0) {}

   void clear();
   void push_back(const T& data);
   void push_front(const T& data);

   void insert(const T& data, std::size_t index);
   void insert_sorted(const T& data);

   T at(std::size_t index);
   T pop(std::size_t index);
   T pop_front();
   T pop_back();
   T pop_data(const T& data);

   void remove(const T& data);
   bool empty() const;
   bool contains(const T& data) const;

   std::size_t find(const T& data) const;
   std::size_t size() const;
};

template<typename T>
inline void LinkedList<T>::clear()
{
   Node<T>* current;
   for (int i = 0; i < size_; i++) {
      current= head;
      head= head->next();
      delete current;
   }
   size_= 0;
}

template<typename T>
inline void LinkedList<T>::push_back(const T& data)
{
   return insert(data, size_)
}

template<typename T>
inline void LinkedList<T>::push_front(const T & data)
{
   Node<T>* new_node= new Node<T>(data, nullptr);
   if (!new_node)
      throw FullStructureException();
   new_node->setNext(head);
   head= new_node;
   size_++;
}

template<typename T>
inline void LinkedList<T>::insert(const T & data, std::size_t index)
{
   Node<T>* new_node= new Node<T>(data, nullptr);
   if(!new_node)
      throw FullStructureException();
   else if (empty() || index == 0)
      head = new_node;

   if (index < 0 || index > size_)
      throw IndexException();

   else {
      Node<T>* aux= head;
      for (int i= 1; i < index; i++)
         aux= aux->next();
      new_node->setNext(aux->next());
      aux->setNext(new_node);
   }
   size_++;
}

template<typename T>
inline void LinkedList<T>::insert_sorted(const T & data)
{
   if (empty())
      push_front(data);
   else {
      Node<T>* aux= head;
      int pos= 0;
      while (aux->next() != nullptr && data > aux->data()) {
         aux= aux->next();
         pos++;
      }
      if (data > aux->data())
         insert(data, pos + 1);
      else 
         insert(data, pos);
   }
}

template<typename T>
inline T LinkedList<T>::at(std::size_t index)
{
   if (empty())
      throw EmptyStructureException();
   if (index < 0 || index >= size_)
      throw IndexException();
   Node<T>* aux= head;
   for (int i= 0; i < index; i++)
      aux= aux->next();
   return aux->data();
}

template<typename T>
inline T LinkedList<T>::pop(std::size_t index)
{
   if (index < 0 || index > size_)
      throw IndexException();
   if (index == 0)
      return pop_front();

   Node<T>* prev= head;
   for (int i= 0; i < index - 2; i++)
      prev= prev->next();
   Node<T>* toBePopped= prev->next();
   T temp= toBePopped->data();
   prev->setNext(toBePopped->next());
   size_--;

   delete toBePopped;
   return temp;
}

template<typename T>
inline T LinkedList<T>::pop_front()
{
   return pop(0);
}

template<typename T>
inline T LinkedList<T>::pop_back()
{
   return pop(size_);
}

template<typename T>
inline T LinkedList<T>::pop_data(const T & data)
{
   return pop(find(data));
}

template<typename T>
inline void LinkedList<T>::remove(const T& data)
{
   if (size_ == 0)
      throw EmptyStructureException();
   pop(find(data));
}

template<typename T>
inline bool LinkedList<T>::empty() const
{
   return size_ == 0;
}

template<typename T>
inline bool LinkedList<T>::contains(const T& data) const
{
   if (empty())
      return false;
   Node<T>* aux= head;
   for (int i= 0; i < size_; i++)
      if (aux->data() == data)
         return true;
   return false;
}

template<typename T>
inline std::size_t LinkedList<T>::find(const T & data) const
{
   if (empty())
      throw EmptyStructureException();
   Node<T>* aux= head;
   for (int i= 0; i < size_; i++)
      if (aux->data() == data)
         return i;
   throw InvalidDataException();
}

template<typename T>
inline std::size_t LinkedList<T>::size() const
{
   return size_;
}

#endif // !INCLUDED_LINKEDLIST_H