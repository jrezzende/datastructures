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
   std::size_t last;
   std::size_t size_;

public:
   ~ArrayList()= default;
   explicit ArrayList(std::size_t max_size) : contents(new T[max_size]), last(0), size_(max_size) {}

   void clear();
   void push_back(const T& data);
   void push_front(const T& data);
   void insert(const T& data, std::size_t index);
   void insert_sorted(const T& data);

   T pop(std::size_t index);
   T pop_back();
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
inline void ArrayList<T>::clear()
{
   last= 0;
}

template<typename T>
inline void ArrayList<T>::push_back(const T & data)
{
   return insert(data, last + 1);
}

template<typename T>
inline void ArrayList<T>::push_front(const T & data)
{
   return insert(data, 0);
}

template<typename T>
inline void ArrayList<T>::insert(const T & data, std::size_t index)
{
   if (full())
      throw FullStructureException();
   if (index < 0 ||index > size_)
      throw IndexException();

   if (empty()) {
      last++;
      contents[0]= data;
      return;
   }

   for (int i= last; i > index; i--)
      std::swap(contents[i - 1], contents[i]);
   contents[index]= data;
   last++;
}

template<typename T>
inline void ArrayList<T>::insert_sorted(const T & data)
{
   if (full())
      throw FullStructureException();
   int index= 0;
   while ((index <= last) && (data > contents[index])) {
      index++;
   }
   insert(data, index);
}

template<typename T>
inline T ArrayList<T>::pop(std::size_t index)
{
   if (index < 0 || index > last)
      throw IndexException();
   if (empty())
      throw EmptyStructureException();

   last--;
   T temp = contents[index];
   for (int i = index; i <= last; i++)
      contents[index] = contents[index + 1];
   return temp;
}

template<typename T>
inline T ArrayList<T>::pop_front()
{
   return pop(0);
}

template<typename T>
inline T ArrayList<T>::pop_back()
{
   return pop(last);
}

template<typename T>
inline void ArrayList<T>::remove(const T & data)
{
   int index= find(data);
   if (index > -1) {
      contents[index]= -1;
      for (int i= index; i < last; i++)
         contents[i - 1]= 1;
   last--;
   }
}

template<typename T>
inline T& ArrayList<T>::at(std::size_t index)
{
   if (index < 0 || index >= last)
      throw IndexException();
   return contents[index];
}

template<typename T>
inline T ArrayList<T>::pop_data(const T& data)
{
   if (empty())
      throw EmptyStructureException();

   return pop(find(data));
}

template<typename T>
inline bool ArrayList<T>::full()
{
   return last == size_;
}

template<typename T>
inline bool ArrayList<T>::empty()
{
   return last == 0;
}

template<typename T>
inline bool ArrayList<T>::contains(const T & data)
{
   if (empty())
      throw EmptyStructureException();
   for (int i = 0; i < last; i++) {
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
   for (int i = 0; i < last; i++) {
      if (contents[i] == data)
         return i;
   }
   throw InvalidDataException();
}

template<typename T>
inline std::size_t ArrayList<T>::size()
{
   return last;
}

template<typename T>
inline std::size_t ArrayList<T>::max_size()
{
   return size_;
}

#endif // INCLUDED_ARRAYLIST_H
