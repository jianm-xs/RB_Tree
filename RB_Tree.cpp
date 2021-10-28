//
// Created by admin on 2021/10/26.
//

#include "RB_Tree.h"

template <class T>
RB_Tree<T>::RB_Tree()
{
    root = nullptr ;
}

template <class T>
void RB_Tree<T>::Left_Rotate(Node<T> *data)
{
    Node<T> *y = data->right ;     // find the right node of data
    data->right = y->left ;     // let y's left subtree is data's right subtree
    if (y->left != nullptr) {       // if y's left subtree isn't null, y's left subtree is the subtree of data. So its father is data
        y->left->father = data ;
    }
    y->father = data->father ;      // y's father changed
    if (data->father == nullptr) {      // if data's father is nullptr , means data is the root of the RB_Tree. So the root of the RB_Tree is y after rotating it
        root = y ;
    }
    else if (data->father->left == data) {      // connect data's father with y
        data->father->left = y ;
    }
    else if (data->father->right == data) {     // same as above
        data->father->right = y ;
    }
    data->father = y ;      // connect y with data
    y->left = data ;    // data is the right subtree of y
}

template <class T>
void RB_Tree<T>::Right_Rotate(Node<T> *data)
{
    Node<T> *y = data->left ;       // find the left node of data
    data->left = y->right ;         // y's right subtree is the data's left subtree
    if (y->right != nullptr) {      // if y's right subtree isn't nullptr , its father changed
        y->right->father = data ;
    }
    y->father = data->father ;      // change y's father
    if (data->father == nullptr) {      // if data is root , change the root of the RB_Tree
        root = y ;
    }
    else if (data->father->left == data) {      // else change the subtree of data's father
        data->father->left = y ;
    }
    else if (data->father->right == data) {
        data->father->right = y ;
    }
    data->father = y ;      // change data's father
    y->right = data ;       // change y's subtree
}

    // Transplant v ot u
template <class T>
void RB_Tree<T>::Transplant(Node<T> *u , Node<T> *v)
{
    if (u->father == nullptr) {      // if u is the root of the RB_Tree
        root = v;
    }
    else if (u == u->father->left) {
        u->father->left = v ;
    }
    else if (u == u->father->right) {
        u->father->right = v ;
    }
}

    // insert a node value of data
template <class T>
void RB_Tree<T>::insert(T data)
{
    Node<T> *y = nullptr ;  // y is the father of x
    Node<T> *x = root ;     // x is the position of data
    while (x != nullptr) {      // while x isn't nullptr , it isn't the position insert
        y = x ;     // y is the father of x . x will change soon
        if (x->val > data) {        // if data is smaller than x's val , insert in x's left subtree
            x = x->left ;
        }
        else {      // else insert in x's right subtree
            x = x->right ;
        }
    }
    Node<T> *z = new Node<T>(data) ;    //  create a node value of data
    z->father = y ;     // the node insert in x , and its father is y
    if (y == nullptr) {     // if y is nullptr , means z is the root of the RB_Tree
        root = z ;
    }
    else if (z->val < y->val) {     // if z's val is smaller than y , z is y's left subtree
        y->left = z ;
    }
    else {      // else z is y's right subtree
        y->right = z ;
    }
    z->color = RED ;    // z's color is red
    insert_fixup(z) ;       // maintenance the RB_Tree after insert z
}

template <class T>
bool RB_Tree<T>::delete_Node(Node<T> *data)
{
    Node<T> *y = data , *x , *father ;
    bool color = data->color ;
    if (data->left == nullptr && data->right != nullptr) {      // replace data with the right subtree
        x = data->right ;
        Transplant(data , x) ;
        father = x->father ;
    }
    else if (data->right == nullptr && data->left != nullptr) {     // replace data with the left subtree
        x = data->left ;
        Transplant(data , x) ;
        father = x->father ;
    }
    else if (data->right != nullptr && data->left != nullptr) {     // find the min node in left subtree , replace data with it
        y = Mini_Node(data->right) ;      // find the smallest node in left subtree
        color = y->color ;      // notice the color of node will change
        x = y->right ;      // x is the right subtree of y
        father = y->father ;        // the father of the node x ;
        if (y->father != data) {    // if y isn't the right subtree of data
            if (y->right != nullptr) {      // if y's right subtree isn't nullptr , replace y with the right subtree
                Transplant(y , y->right) ;
            }
            else {      // else if y's right is nullptr , and replace y with nullptr
                y->father->left = nullptr ;     // because y is the min node in the tree , so y must is the left subtree of its father node
            }
            y->right = data->right ;        // change y's right subtree
            y->right->father = y ;
        }
        Transplant(data , y) ;      // replace data with y
        y->left = data->left ;      // change y's left subtree
        y->left->father = y ;
        y->color = data->color ;        // change y's color
    }
    else {      // if data's right subtree and left subtree are nullptr
        if (data->father != nullptr) {      // if data->father isn't nullptr ,
            x = nullptr ;
            if (data == data->father->right) {      // change the subtree of data's father
                data->father->right = nullptr ;
            }
            else {
                data->father->left = nullptr ;
            }
            father = data->father ;
        }
        else {      // if data's father is nullptr , data is the root of the RB_Tree
            root = nullptr ;    //   delete the root node
            return true ;       // finish !
        }
    }
    if (color == BLACK) {       // if y's color is black , after delete , we need maintenance the RB_Tree
        delete_fixup(x , father) ;
    }
    return true ;
}

template <class T>
bool RB_Tree<T>::delete_data(T data)
{
    Node<T> *del = find_Node(data) ;
    if (del == nullptr) {
        return false ;      // there is no node value of data in the RB_Tree
    }
    while (del != nullptr) {        // if del isn't nullptr , delete it
        delete_Node(del) ;       // delete the node value of data
        del = find_Node(data) ;     // find the next node value of data
    }
    return true ;
}

template <class T>
bool RB_Tree<T>::delete_value(T data)
{
    Node<T> *del = find_Node(data) ;        // find the nearest node value of data
    if(del == nullptr) {        // there is no node value of data in the RB_Tree
        return false ;
    }
    return delete_Node(del) ;       // delete the node
}

template <class T>
void RB_Tree<T>::insert_fixup(Node<T> *data)
{
    while (data->father != nullptr && data->father->color == RED) {     // if data's father is red node
        if (data->father->father == nullptr) {      // if data's father is root , break
            break ;
        }
        if (data->father->father->left == data->father) {       // if data's father is the left subtree
            Node<T> *uncle = data->father->father->right ;      // find its uncle node
            if (uncle != nullptr && uncle->color == RED) {      // if its uncle is red.let its grandfather's color red , its uncle and father is black
                uncle->color = BLACK ;
                data->father->father->color = RED ;
                data->father->color = BLACK ;
                data = data->father->father ;
                continue ;
            }
            else if (data == data->father->right){      // if data is right subtree , left rotate so that we can solve it as case 3
                data = data->father ;
                Left_Rotate(data) ;
            }
            /* if data is right subtree , after rotation . data is the left subtree. we call it the three case
             * now data is red , data's father is red , and data's uncle is black or data's uncle is nullptr
             * So we just write how to change when data is the left subtree , and its father is red.
             * And we just rotate it after cover their color */
            data->father->color = BLACK ;       // let its father's color is black
            data->father->father->color = RED ;     // let its grandfather's color is red
            Right_Rotate(data->father->father) ;        // rotate its grandfather
        }
        else {      // else if data's father is the right subtree
            Node<T> *uncle = data->father->father->left ;       // find its uncle node
            if (uncle != nullptr && uncle->color == RED) {      // same as above
                uncle->color = BLACK ;
                data->father->father->color = RED ;
                data->father->color = BLACK ;
                data = data->father->father ;
                continue ;
            }
            else if (data == data->father->left) {      // rotate it so that we can solve it as case 3
                data = data->father ;
                Right_Rotate(data) ;
            }
            data->father->color = BLACK ;
            data->father->father->color = RED ;
            Left_Rotate(data->father->father) ;
        }
    }
    root->color = BLACK ;       // root node is black node
}

    // maintenance the RB_Tree after delete a node
template <class T>
void RB_Tree<T>::delete_fixup(Node<T> *data , Node<T> *father)
{
    while (data != root && (data == nullptr || data->color == BLACK)) {
        if (data == father->left) {
            Node<T> *brother = father->right ;
            if (brother->color == RED) {        // if brother is RED , Rotate father , switch to other cases
                father->color = RED ;
                brother->color = BLACK ;
                Left_Rotate(father) ;
                brother = father->right ;       // because the node we delete is BLACK, and its brother is RED , so its brother must have  subtree
            }
            if ((brother->right == nullptr && brother->left == nullptr) || (brother->right->color == BLACK && brother->left->color == BLACK)) {     // if brother is red and its subtree is black or nullptr , change brother's color to red
                brother->color = RED ;
                data = father ;
                father = data->father ;     // there are fewer black nodes in this subtree , recursively adjust upward
                continue ;
            }
            else if (brother->left != nullptr && brother->left->color == RED && (brother->right == nullptr || brother->right->color == BLACK)) {    // if brother's left node is red , and right node is black or nullptr , rotate it to next case
                brother->left->color = BLACK ;
                brother->color = RED ;
                Right_Rotate(brother) ;
                brother = father->right ;
            }
            brother->color = father->color ;        // if brother's color is black and his right subtree is red , rotate father , and change its color
            father->color = BLACK ;
            brother->right->color = BLACK ;
            Left_Rotate(father) ;
            data = root ;       // finish
        }
        else {      // it's the same thing as above , except I've changed the right to left
            Node<T> *brother = father->left ;
            if (brother->color == RED) {
                father->color = RED ;
                brother->color = BLACK ;
                Right_Rotate(father) ;
                brother = father->left ;
            }
            if ((brother->right == nullptr && brother->left == nullptr) || (brother->right->color == BLACK && brother->left->color == BLACK)) {
                brother->color = RED ;
                data = father ;
                father = data->father ;
                continue ;
            }
            else if (brother->right != nullptr && brother->right->color == RED && (brother->left == nullptr || brother->left->color == BLACK)) {
                brother->right->color = BLACK ;
                brother->color = RED ;
                Left_Rotate(brother) ;
                brother = father->left ;
            }
            brother->color = father->color ;
            father->color = BLACK ;
            brother->left->color = BLACK ;
            Right_Rotate(father) ;
            data = root ;
        }
    }
    data->color = BLACK ;       // maintenance the color of the RB_Tree's root
}

    // fin a node value of data. If no such node , return nullptr
template <class T>
Node<T>* RB_Tree<T>::find_Node(T data)
{
    Node<T>* res = root ;       // res is the answer of this query
    while (res != nullptr) {        // if res is nullptr , means no node value of data in the RB_Tree
        if (res->val > data) {      // if the value of res is greater than data , find data in the left subtree of res
            res = res->left ;
        }
        else if (res->val == data) {    // find the data , return the answer
            break ;
        }
        else {      // else if the value of res is less than data , find data in the right subtree of res
            res = res->right ;
        }
    }
    return res ;
}

    // find the smallest node in data , data isn't nullptr
template <class T>
Node<T>* RB_Tree<T>::Mini_Node(Node<T> *data)
{
    Node<T> *res = data ;
    while (res->left != nullptr) {      // if its left subtree isn't nullptr , the value of its left subtree is smaller than it' value
        res = res->left ;
    }
    return res ;
}

    // print the RB_Tree
template <class T>
void RB_Tree<T>::show()
{
        // we print the RB_Tree by preorder first
    std::cout << "preorder : " ;
    preorder(root) ;
    std::cout << "\n" ;
        // print the RB_Tree by inorder
    std::cout << "inorder : " ;
    inorder(root) ;
    std::cout << "\n" ;
        // finally , print the RB_Tree by postorder
    std::cout << "postorder : " ;
    postorder(root) ;
    std::cout << " fine \n" ;       // finish !
}

    // print the RB_Tree by preorder
template <class T>
void RB_Tree<T>::preorder(Node<T> *data)
{
    if (data == nullptr) {
        return ;
    }
    std::cout << "(" << data->val << "," << (data->color ? "red" : "black") << ") " ;
    preorder(data->left) ;
    preorder(data->right) ;
}

    // print the RB_Tree by inorder
template <class T>
void RB_Tree<T>::inorder(Node<T> *data)
{
    if (data == nullptr) {
        return ;
    }
    inorder(data->left) ;
    std::cout << "(" << data->val << "," << (data->color ? "red" : "black") << ") " ;
    inorder(data->right) ;
}

template <class T>
void RB_Tree<T>::postorder(Node<T> *data)
{
    if (data == nullptr) {
        return ;
    }
    postorder(data->left) ;
    postorder(data->right) ;
    std::cout << "(" << data->val << "," << (data->color ? "red" : "black") << ") " ;
}

template <class T>
RB_Tree<T>::~RB_Tree()
= default ;