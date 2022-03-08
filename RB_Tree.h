//
// Created by admin on 2022/3/7.
//

#ifndef RB_TREE_RB_TREE_H
#define RB_TREE_RB_TREE_H

#include "RB_Node.h"
#include <iostream>
#include <queue>

template <class T>
class RB_Tree {

private:
    RB_Node<T> *root;

public:
    RB_Tree();      // 构造一颗 红黑树

    void left_rotate(RB_Node<T> *x);        // 左旋操作
    void right_rotate(RB_Node<T> *x);      // 右旋操作
    RB_Node<T>* min_node(RB_Node<T> *x);        // 查找以 x 为根节点的子树中的最小节点
    void transplant(RB_Node<T> *u, RB_Node<T> *v);      // 移植函数
    RB_Node<T>* find(T data);      // 查询值为 data 的节点

    void insert(T data);        // 插入一个节点， value 为 data
    bool del(T data);       // 删除值为 data 的节点
    void del_node(RB_Node<T> *del);       // 删除指定节点

    void insert_fixup(RB_Node<T> *x);       // 插入后调整红黑树使之保持红黑树的性质
    void delete_fixup(RB_Node<T> *x, RB_Node<T> *f);        // 删除节点后调整红黑树

    void tree_show();        // 展示该红黑树的三种遍历
    void floor_show();      // 层序遍历红黑树
    void preorder(RB_Node<T> *x);       // 先序遍历
    void inorder(RB_Node<T> *x);     // 中序遍历
    void postorder(RB_Node<T> *x);      // 后序遍历

    ~RB_Tree();     // 析构函数
};

#endif //RB_TREE_RB_TREE_H
