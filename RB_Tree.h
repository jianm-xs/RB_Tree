//
// Created by admin on 2021/10/26.
//

#ifndef RBTREE_RB_TREE_H
#define RBTREE_RB_TREE_H
#include <iostream>
#include "Node.h"

#define RED true
#define BLACK false

template <class T>
class RB_Tree {

private :
    Node<T> *root ;     // the root node

public :
    RB_Tree() ;
    ~RB_Tree() ;

    void Left_Rotate(Node<T> *data) ;       // left rotate
    void Right_Rotate(Node<T> *data) ;      // right rotate
    void Transplant(Node<T> *u , Node<T> *v) ;        // transplant v to u
    void insert(T data) ;       // insert data into the tree
    bool delete_data(T data) ;      //  delete all nodes value of data
    bool delete_Node(Node<T> *data) ;       // delete the node in the tree
    bool delete_value(T data) ;     // delete the nearest node value of data. just delete one node instead of all nodes value of data
    void insert_fixup(Node<T> *data) ;      // maintenance the RB_Tree after insertion
    void delete_fixup(Node<T> *data , Node<T> *father) ;      // maintenance the RB_Tree after delete a node
    Node<T>* find_Node(T data) ;        // find a node value of data
    Node<T>* Mini_Node(Node<T>* data) ;       // find the smallest node in data

    void show() ;       // print the RB_Tree
    void preorder(Node<T> *data) ;     // print the RB_Tree with preorder
    void inorder(Node<T> *data) ;        // print the RB_Tree with inorder
    void postorder(Node<T> *data) ;      // print the RB_Tree with postorder

};


#endif //RBTREE_RB_TREE_H
