//
// Created by admin on 2022/3/7.
//

#ifndef RB_TREE_RB_NODE_H
#define RB_TREE_RB_NODE_H

#define BLACK true
#define RED false

template <class T>
class RB_Node {

public:
    RB_Node *father;        // 父亲节点
    RB_Node *left;      // 左子节点
    RB_Node *right;     // 右子节点
    T value;      // 节点的值
    bool color{};     // 节点颜色， false 为 红色， true 为 黑色

    RB_Node();
    RB_Node(T val);
    ~RB_Node();

};


#endif //RB_TREE_RB_NODE_H
