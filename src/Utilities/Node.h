#pragma once
#ifndef INCLUDED_NODE_H
#define INCLUDED_NODE_H

template<typename T>
class Node
{
   T* data_;
   Node<T>* next_;

public:
   ~Node();
   Node(const T& data, Node<T>* nextNode) : data_(new T(data)), next_(nextNode) {}

   Node<T>* next() const;

   T data() const;

   void setNext(Node<T>* nextNode);
};

template<typename T>
inline Node<T>::~Node()
{
   delete data_;
}

template<typename T>
inline Node<T>* Node<T>::next() const
{
   return this->next_;
}

template<typename T>
inline T Node<T>::data() const
{
   return *data_;
}

template<typename T>
inline void Node<T>::setNext(Node<T>* nextNode)
{
   next_= nextNode;
}

#endif // !INCLUDED_NODE_H