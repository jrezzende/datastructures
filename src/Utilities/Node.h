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
   Node(const T& data);
   Node(const T& data, Node<T>* nextNode);
   Node(const T& data, Node<T>* nextNode, Node<T>* prevNode);

   next();
   prev();
   data();

   setNext(Node<T>* nextNode);
   setPrev(Node<T>* prevNode);
};

template<typename T>
inline Node<T>::~Node()
{
   delete data_;
}

template<typename T>
inline Node<T>::Node(const T & data) : data_(data), next_(nullptr), prev_(nullptr)
{
}

template<typename T>
inline Node<T>::Node(const T& data, Node<T>* nextNode) : 
data_(new T(data)), next_(nextNode), prev_(nullptr)
{
}

template<typename T>
inline Node<T>::Node(const T & data, Node<T>* nextNode, Node<T>* prevNode) :
data_(new T(data), next_(nextNode), prev_(prevNode))
{
}

template<typename T>
inline Node<T>::next()
{
   return this->next_;
}

template<typename T>
inline Node<T>::prev()
{
   return this->prev_;
}

template<typename T>
inline Node<T>::data()
{
   return this->data_;
}

template<typename T>
inline Node<T>::setNext(Node<T>* nextNode)
{
   next_= nextNode;
}

template<typename T>
inline Node<T>::setPrev(Node<T>* prevNode)
{
   prev_= prevNode;
}

#endif // !INCLUDED_NODE_H
