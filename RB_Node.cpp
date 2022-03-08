//
// Created by admin on 2022/3/7.
//

#include "RB_Node.h"

template <class T>
RB_Node<T>::RB_Node() = default;

template <class T>
RB_Node<T>::RB_Node(T val) : father(nullptr), left(nullptr), right(nullptr), color(RED), value(val) {};

template <class T>
RB_Node<T>::~RB_Node() = default;