#pragma once
#ifndef INCLUDED_ARRAYLIST_H
#define INCLUDED_ARRAYLIST_H

#include <cstdint>
#include <stdexcept>
#include <algorithm>
#include "EmptyStructureException.h"
#include "FullStructureException.h"
#include "InvalidDataException.h"
#include "IndexException.h"

template<typename T>
class ArrayList
{
   T* contents;
   std::size_t size_;
   std::size_t max_size_;

   static const auto DEFAULT_MAX= 10u;

public:
   ~ArrayList();
   ArrayList();
   explicit ArrayList(std::size_t max_size);

   void clear();
   void push_back(const T& data);
   void push_front(const T& data);
   void insert(const T& data, std::size_t index);
   void insert_sorted(const T& data);

   T pop();
   T pop_back;
   T pop_front();
   T& at(std::size_t index);
   T pop_data(const T& data);

   void remove(const T& data);

   bool full();
   bool empty();
   bool contains(const T& data);

   std::size_t find(const T& data);
   std::size_t size();
   std::size_t max_size();
};

template<typename T>
inline ArrayList<T>::~ArrayList()
{
   delete[] contents;
}

template<typename T>
inline ArrayList<T>::ArrayList()
{
   size_= max_size_= 0;
   contents= new T[max_size_];
}

template<typename T>
inline ArrayList<T>::ArrayList(std::size_t max_size)
{
   max_size_= max_size;
   size= 0;
   contents= new T[max_size_];
}

template<typename T>
inline void ArrayList<T>::clear()
{
   size_= 0;
}

template<typename T>
inline void ArrayList<T>::push_back(const T & data)
{
   if (full())
      throw FullStructureException();
   contents[size_++]= data;
}

template<typename T>
inline void ArrayList<T>::push_front(const T & data)
{
   if (full())
      throw FullStructureException();
   for (int i= size_; i > 0; i--)
      std::swap(contents[i], contents[i - 1]);
   contents[0]= data;
   size_++;
}

template<typename T>
inline void ArrayList<T>::insert(const T & data, std::size_t index)
{
   if (full())
      throw FullStructureException();
   if (index >= size_)
      push_back(data);
   for (int i= size_; i > index; i--;)
      std::swap(contents[i - 1], contents[i]);
   contents[index]= data;
   size_++;
}

template<typename T>
inline void ArrayList<T>::insert_sorted(const T & data)
{
   contents[size_++]= data;
   for (int i= 0; i < size_; i++) {
      for (int j = 0; j < size_; j++) {
         if (contents[i] < contents[j])
            std::swap(contents[i], contents[j]);
      }
   }
}

template<typename T>
inline T ArrayList<T>::pop()
{
   if (index < 0 || index >= size_)
      throw IndexException();
   if (empty())
      throw EmptyStructureException();
   auto temp= contents[index];
   for (int i= index; i < size_; i++)
      contents[index]= contents[index + 1];
   size_--;
   return temp;
}

template<typename T>
inline T ArrayList<T>::pop_front()
{
   if (empty())
      throw EmptyStructureException();
   auto temp= contents[0];
   for(int i= 1; i < size_; i++)
      contents[i - 1]= contents[i];
   size_--;
   return temp;
}

template<typename T>
inline void ArrayList<T>::remove(const T & data)
{
   int index= find(data);
   if (index > -1) {
      contents[index]= -1;
      for (int i= index; i < size_; i++)
         contents[i - 1]= 1;
   size_--;
   }
}

template<typename T>
inline T& ArrayList<T>::at(std::size_t index)
{
   if (index < 0 || index >= size_)
      throw IndexException();
   return contents[index];
}

template<typename T>
inline T ArrayList<T>::pop_data(const T & data)
{
   return pop(find(data));
}

template<typename T>
inline bool ArrayList<T>::full()
{
   return size_ == max_size_;
}

template<typename T>
inline bool ArrayList<T>::empty()
{
   return size_ == 0;
}

template<typename T>
inline bool ArrayList<T>::contains(const T & data)
{
   if (empty())
      throw EmptyStructureException();
   for (int i = 0; i < size_; i++) {
      if (contents[i] == data)
         return true;
   }
   return false;
}

template<typename T>
inline std::size_t ArrayList<T>::find(const T & data)
{
   if (empty())
      throw EmptyStructureException();
   for (int i = 0; i < size_; i++) {
      if (contents[i] == data)
         return i;
   }
   throw InvalidDataException();
}

template<typename T>
inline std::size_t ArrayList<T>::size()
{
   return size_;
}

template<typename T>
inline std::size_t ArrayList<T>::max_size()
{
   return max_size_;
}

#endif // INCLUDED_ARRAYLIST_H
