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
   Node<T>* head;
   std::size_t size_;

   Node<T>* end() {
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
   T pop(std::size_t index);
   T pop_back();
   T pop_front();
   T pop_data(const T& data);

   void remove(const T& data);
   bool empty() const;
   bool contains(const T& data) const;

   std::size_t find(const T& data) const;
   std::size_t size() const;
};

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
   Node<T>* current= head;
   Node<T>* next_node;
   while (current != nullptr) {
      next_node= current->next();
      delete current;
      current= next_node;
   }
   head= nullptr;
   size_= 0;
}

template<typename T>
inline void LinkedList<T>::push_back(const T & data)
{
   Node<T>* new_node= new Node<T>(data);
   if (new_node == nullptr)
      throw std::out_of_range();
   if (empty())
      head= new_node;
   else
      end()->setNext(new_node);
   size_++;
}

template<typename T>
inline void LinkedList<T>::push_front(const T & data)
{
   Node<T>* new_node= new Node<T>(data);
   if (!new_node)
      throw FullStructureException;
   if (empty())
      head= new_node;
   else {
      new_node->setNext(head);
      head= new_node;
   }
   size_++;
}

template<typename T>
inline void LinkedList<T>::insert(const T & data, std::size_t index)
{
   Node<T>* new_node= new Node<T>(data);
   if(!new_node)
      throw FullStructureException();
   else if (empty())
      head = new_node;

   if (index >= size_ )
      push_back(data);
   else if (index < 0)
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
      int pos= 1;
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
inline T& LinkedList<T>::at(std::size_t index)
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
   if (index >= size_)
      pop_back();
   if (index < 0)
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
inline T LinkedList<T>::pop_back()
{
   if (empty())
      throw EmptyStructureException();

   if (size_ == 1) {
      Node<T>* aux= head;
      T temp= aux->data();

      delete tobePopped
      head= nullptr;

      size_--;
      return temp;
   }

   Node<T>* tobePopped= end();
   T temp= tobePopped->data();

   size_--;

   delete tobePopped;
   return temp;
}

template<typename T>
inline T LinkedList<T>::pop_front()
{
   if (empty())
      throw EmptyStructureException();

   if (size_ == 1) {
      Node<T>* aux= head;
      T temp= aux->data();

      delete aux;
      head= nullptr;

      size_--;
      return temp;
   }

   Node<T>* toBePopped= head;
   T temp= toBePopped->data();
   head= toBePopped->next();

   size_--;
   delete toBePopped;
   return temp;
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