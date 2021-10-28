//
// Created by admin on 2021/10/26.
//

#ifndef RBTREE_NODE_H
#define RBTREE_NODE_H

#define RED true
#define BLACK false

template <class T>
class Node {

public :
    Node *father ;       // the node's father node
    T val ;       // the value
    bool color ;    // if node's color is red , the value is true , else the value is false
    Node *left ;    // the node's left subtree
    Node *right ;   // the node's right subtree

        // create a node
    Node(T x);
    ~Node() ;
};


#endif //RBTREE_NODE_H
