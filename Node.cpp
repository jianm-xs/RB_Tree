//
// Created by admin on 2021/10/26.
//

#include "Node.h"

template <class T>
Node<T>::Node(T x) : father(nullptr) , color(true) , left(nullptr) , right(nullptr) {
    val = x ;
}

template <class T>
Node<T>::~Node()
= default;
