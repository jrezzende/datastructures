#pragma once
#ifndef INCLUDED_NODE_H
#define INCLUDED_NODE_H

template<typename T>
class Node
{
   T* data_;
   Node<T>* next_;
   Node<T>* prev_;

public:
   ~Node();
   Node(T& data) : data_(&data), next_(nullptr), prev_(nullptr) {}
   Node(T& data, Node<T>* nextNode);
   Node(T& data, Node<T>* nextNode, Node<T>* prevNode);

   Node<T>* next();
   Node<T>* prev();

   T data();

   void setNext(Node<T>* nextNode);
   void setPrev(Node<T>* prevNode);
};

template<typename T>
inline Node<T>::~Node()
{
   delete data_;
}

template<typename T>
inline Node<T>::Node(T& data, Node<T>* nextNode) :
data_(new T(&data)), next_(nextNode)
{
}

template<typename T>
inline Node<T>::Node(T& data, Node<T>* nextNode, Node<T>* prevNode) :
data_(new T(&data)), next_(nextNode), prev_(prevNode)
{
}

template<typename T>
inline Node<T>* Node<T>::next()
{
   return this->next_;
}

template<typename T>
inline Node<T>* Node<T>::prev()
{
   return this->prev_;
}

template<typename T>
inline T Node<T>::data()
{
   return *data_;
}

template<typename T>
inline void Node<T>::setNext(Node<T>* nextNode)
{
   next_= nextNode;
}

template<typename T>
inline void Node<T>::setPrev(Node<T>* prevNode)
{
   prev_= prevNode;
}

#endif // !INCLUDED_NODE_H