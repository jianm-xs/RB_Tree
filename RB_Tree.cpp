//
// Created by admin on 2022/3/7.
//

#include "RB_Tree.h"
#include "RB_Node.cpp"

using std::cout;
using std::queue;

/**
 * @prief   构造函数
 * @tparam T
 */
template <class T>
RB_Tree<T>::RB_Tree() : root(nullptr) {};

/**
 * @brief   左旋操作
 *
 * @tparam T    数据类型
 * @param x     待旋转的父节点
 */
template <class T>
void RB_Tree<T>::left_rotate(RB_Node<T> *x) {
    RB_Node<T> *y = x->right;       // 获取节点 x 的右子节点
    x->right = y->left;     // 更新 x 的右子树
    if (y->left != nullptr) {       // 如果节点 y 的左子树不为空，更新 y 的左子树的父节点
        y->left->father = x;
    }
    y->left = x;        // 更新 y 的左子节点
    y->father = x->father;      // 更新 y 的父节点
    if (x->father == nullptr) {     // 如果 x 的父节点为空，说明节点 x 是根节点，更新根节点
        this->root = y;
    }
    else if (x->father->left == x) {     // 如果节点 x 是其父节点的左子节点，更新节点 x 的父节点的左子节点
        x->father->left = y;
    }
    else {      // 节点 x 是其父节点的右子节点，更新节点 x 的父节点的右子节点
        x->father->right = y;
    }
    x->father = y;      // 更新节点 x 的父节点
}

/**
 * @brief   右旋操作
 *
 * @tparam T    数据类型
 * @param x     待旋转的父节点
 */
template <class T>
void RB_Tree<T>::right_rotate(RB_Node<T> *x) {
    RB_Node<T> *y = x->left;        // 先获取节点 x 的左子节点
    x->left = y->right;     // 更新 x 的左子节点
    if (y->right != nullptr) {      // 如果 y 的右子节点不为空，更新 y->right 的父节点
        y->right->father = x;
    }
    y->right = x;       // 更新节点 y 的右子节点
    y->father = x->father;      // 更新节点 y 的父节点
    if (x->father == nullptr) {     // 如果节点 x 的父节点为 nullptr，说明节点 x 为根节点，更新这棵红黑树的根节点
        this->root = y;
    }
    else if (x->father->left == x) {     // 如果节点 x 是其父节点的左子节点，更新其父节点的左子节点
        x->father->left = y;
    }
    else {      // 如果节点 x 是其父节点的右子节点，更新其父节点的右子节点
        x->father->right = y;
    }
    x->father = y;      // 更新节点 x 的父节点
}

/**
 * @prief   查找以 x 为根节点的子树中的最小元素
 * @tparam T    数据类型
 * @param x 需要查找的子树的根节点
 * @return 返回该子树中的最小的节点
 */
template <class T>
RB_Node<T>* RB_Tree<T>::min_node(RB_Node<T> *x) {
    RB_Node<T> *res = x;
    while (res->left != nullptr) {      // 如果有左子节点，一直往左走
        res = res->left;
    }
    return res;     // 返回最终结果
}

/**
 * @prief 将 v 移植到 u 的位置，仅改变 u 的父节点在子节点和 v 的父节点
 * @tparam T 数据类型
 * @param u 被替换的节点
 * @param v 待移植的节点
 */
template <class T>
void RB_Tree<T>::transplant(RB_Node<T> *u, RB_Node<T> *v) {
    v->father = u->father;      // 更新 v 的父节点
    if (u->father == nullptr) {     // 如果这棵红黑树的根节点为 u，更新根节点
        this->root = v;
    }
    else if (u->father->left == u) {     // u 是左孩子
        u->father->left = v;
    }
    else {      // u 是右孩子
        u->father->right = v;
    }
}

/**
 * @prief   查找值为 data 的节点
 * @tparam T    数据类型
 * @param data      查找的值
 * @return      返回对应的节点，若无该元素，返回 nullptr
 */
template <class T>
RB_Node<T>* RB_Tree<T>::find(T data) {
    RB_Node<T> *q = this->root;
    while (q != nullptr && q->value != data) {      // 查询操作
        if (q->value > data) {      // 如果 q->value 小于 data ，查找左子树
            q = q->left;
        }
        else {      // 否则查找右子树
            q = q->right;
        }
    }
    return q;       // 返回结果
}

/**
 * @brief  将 data 插入红黑树中
 * @tparam T    数据类型
 * @param data      插入的值
 */
template <class T>
void RB_Tree<T>::insert(T data) {
    RB_Node<T> *idx = this->root, *f = nullptr;      // idx 为最终插入的位置， f 为最终插入位置的父节点
    while (idx != nullptr) {
        f = idx;
        if (idx->value > data) {        // 如果 idx->value 大于 data， 查找 idx 的左子树中查找
            idx = idx->left;
        }
        else {
            idx = idx->right;
        }
    }
    RB_Node<T> *x = new RB_Node<T>(data);       // 创建一个新的节点，值为 data
    x->father = f;
    if (f == nullptr) {     // 此时 x 应该为根节点
        this->root = x;
    }
    else if (f->value > x->value) {        // 此时 x 应该为 f 的左子节点
        f->left = x;
    }
    else {      // 此时 x 应该为 f 的右子节点
        f->right = x;
    }
    insert_fixup(x);        // 调整这棵红黑树
}

/**
 * @prief 删除值为 data 的一个节点
 * @tparam T 数据类型
 * @param data 需要删除的元素
 * @return 返回是否删除成功
 */
template <class T>
bool RB_Tree<T>::del(T data) {
    RB_Node<T> *node = find(data);
    if (node == nullptr) {      // 没有该元素，删除失败
        return false;
    }
    del_node(node);     // 删除该节点
    return true;
}

/**
 * @prief 删除指定节点
 * @tparam T 数据类型
 * @param del 待删除的节点
 */
template <class T>
void RB_Tree<T>::del_node(RB_Node<T> *del) {
    RB_Node<T> *x , *f;        // x 为最终影响了红黑树的节点，即调整开始的位置（可能为 nullptr）， f 是调整位置的父节点
    bool color = del->color;        // 记录最终被删除的节点的颜色
    if (del->left == nullptr && del->right != nullptr) {        // 只有右子树
        x = del->right;
        transplant(del, x);
        f = x->father;
    }
    else if (del->left != nullptr && del->right == nullptr) {       // 只有左子树
        x = del->left;
        transplant(del, x);
        f = x->father;
    }
    else if (del->left != nullptr && del->right != nullptr) {       // 左右子树均不为空
        RB_Node<T> *y = min_node(del->right);       // 找到右子树中最小的节点，用来替换 del
        color = y->color;       // 更新 color ， 因为这个时候要删除的节点是 y
        x = y->right;       // 此时删除 del ，用 y 去替换 del 。所以就变成了删除 y ，所以 x 和 f 都要更新
        f = y->father;
        if (y->father != del) {     // y 不是 del 的右子节点
            if (y->right != nullptr) {      // y 的左子树必然为空，以为 y 是最左侧节点，所以此时判断 y 的右子节点是否为空
                transplant(y, y->right);        // 移植 y 的右子树
            }
            else {
                y->father->left = nullptr;      // 此时将 y 的父节点的左子节点更新为 nullptr
            }
            y->right = del->right;      // 更新 y 的右子树
            y->right->father = y;
        }
        else {      // 否则此时的父节点为 y
            f = y;
        }
        transplant(del, y);     // 将 y 移植到 del 处
        y->left = del->left;        // 更新 y 的左子树
        y->left->father = y;
        y->color = del->color;      // 更新 y 的颜色
    }
    else {      // del 的左右子树均为空
        if (del->father == nullptr) {       // 如果 del 是根节点，直接将根节点设置为 nullptr
            this->root = nullptr;
            return;
        }
        else {      // 如果 del 不是根节点
            x = nullptr;
            if  (del->father->left == del) {        // 更新父节点的子节点
                del->father->left = nullptr;
            }
            else {
                del->father->right = nullptr;
            }
        }
        f = del->father;
    }
    if (color == BLACK) {       // 如果被删除的节点的颜色为黑色
        delete_fixup(x, f);        // 调整红黑树
    }
}

/**
 * @brief   插入节点后调整红黑树
 *
 * @tparam T    数据类型
 * @param x     插入的节点
 */
template <class T>
void RB_Tree<T>::insert_fixup(RB_Node<T> *x) {
    while (x->father != nullptr && x->father->color == RED) {
        if (x->father->father == nullptr) {     // 如果 x 的父节点为根节点，跳出循环，将这棵红黑树的根节点设为黑色即可
            break;
        }
        if (x->father->father->left == x->father) {     // 如果 x 的父节点是 x 的祖父节点的左子节点，那么 x 的叔叔节点就是 x 的祖父节点的右子节点
            RB_Node<T> *uncle = x->father->father->right;
            if (uncle != nullptr && uncle->color == RED) {      // 情况一： 如果 x 的叔叔节点是红色
                x->father->color = uncle->color = BLACK;        // 将 x 的祖父节点的黑色下沉给 x 的父亲节点和叔叔节点
                x->father->father->color = RED;     // x 的祖父节点变为红色
                x = x->father->father;      // 从祖父节点往上继续调整
                continue;
            }
            else if (x == x->father->right) {        // 情况二： x 的叔叔节点为黑色， x 是 x 的父亲节点的右子节点
                x = x->father;      // 为了转成情况三，所以 x 要变成 x 的父节点
                left_rotate(x);     // 左旋操作
            }
                // 情况三
            x->father->color = BLACK;       // 更改父节点的颜色为黑色，去取代祖父节点的位置
            x->father->father->color = RED;     // 更改祖父节点的颜色为红色
            right_rotate(x->father->father);        // 右旋操作
        }
        else {      // 如果 x 的父节点时 x 的祖父节点的右子节点，那么 x 的叔叔节点就是 x 的祖父节点的左子节点
            RB_Node<T> *uncle = x->father->father->left;
            if (uncle != nullptr && uncle->color == RED) {      // 情况一： 节点 x 的叔叔节点为红色
                x->father->color = uncle->color = BLACK;        // 祖父节点的黑色下沉给 x 的父亲节点和叔叔节点
                x->father->father->color = RED;     // 祖父节点的颜色更改为红色
                x = x->father->father;
                continue;
            }
            else if (x->father->left == x) {        // 情况三：节点 x 的叔叔节点为黑色， x 是 x 的父节点的左子节点
                x = x->father;      // 为了转换为情况二
                right_rotate(x);        // 右旋操作
            }
                // 情况二
            x->father->color = BLACK;
            x->father->father->color = RED;
            left_rotate(x->father->father);
        }
    }
    this->root->color = BLACK;
}

/**
 * @prief 删除节点后调整红黑树
 * @tparam T    数据类型
 * @param x 调整开始的位置
 * @param f 调整开始的位置的父节点
 */
template <class T>
void RB_Tree<T>::delete_fixup(RB_Node<T> *x, RB_Node<T> *f) {
    while (x != root && (x == nullptr || x->color == BLACK)) {      // 需要调整的情况
        if (x == f->left) {     // x 在 f 的左子树的情况
            RB_Node<T> *bro = f->right;     // 兄弟节点
            if (bro->color == RED) {        // 情况一：兄弟节点为红色
                f->color = RED;
                bro->color = BLACK;
                left_rotate(f);
                bro = f->right;     // 兄弟节点发生改变
            }
            else if ((bro->right == nullptr && bro->left == nullptr) || (bro->right->color == BLACK && bro->left->color == BLACK)) {        // 情况二
                bro->color = RED;       // bro 改为红色
                x = f;      // 以 f 为根的子树的黑色节点减少了 1 ，从 x 开始往上调整
                f = x->father;      // 更新 f
                continue;       // 也有可能此时 x 为红色，那么直接跳出循环，把 x 染成黑色即可
            }
            else if (bro->left != nullptr && bro->left->color == RED && (bro->right == nullptr || bro->right->color == BLACK)) {        // 情况三
                bro->color = RED;
                bro->left->color = BLACK;      // 互换颜色
                right_rotate(bro);      // 旋转
                bro = bro->father;      // 更新兄弟节点
            }
                // 情况四
            bro->color = f->color ;        // 交换兄弟节点和父节点的有颜色
            f->color = BLACK ;
            bro->right->color = BLACK ;     // 兄弟节点的右子节点改为黑色
            left_rotate(f) ;        // 旋转
            x = root ;       // 左右平衡了，直接跳出循环， x 设置为根节点，出循环后维护根节点为黑色，保持性质二
        }
        else {
            RB_Node<T> *bro = f->left;     // 兄弟节点
            if (bro->color == RED) {        // 情况一：兄弟节点为红色
                f->color = RED;
                bro->color = BLACK;
                right_rotate(f);
                bro = f->left;     // 兄弟节点发生改变
            }
            else if ((bro->right == nullptr && bro->left == nullptr) || ((bro->right != nullptr && bro->left != nullptr) && (bro->right->color == BLACK && bro->left->color == BLACK))) {        // 情况二
                bro->color = RED;       // bro 改为红色
                x = f;      // 以 f 为根的子树的黑色节点减少了 1 ，从 x 开始往上调整
                f = x->father;      // 更新 f
                continue;       // 也有可能此时 x 为红色，那么直接跳出循环，把 x 染成黑色即可
            }
            else if (bro->right != nullptr && bro->right->color == RED && (bro->left == nullptr || bro->left->color == BLACK)) {        // 情况三
                bro->color = RED;
                bro->right->color = BLACK;      // 互换颜色
                left_rotate(bro);      // 旋转
                bro = bro->father;      // 更新兄弟节点
            }
                // 情况四
            bro->color = f->color ;        // 交换兄弟节点和父节点的有颜色
            f->color = BLACK ;
            bro->left->color = BLACK ;     // 兄弟节点的右子节点改为黑色
            right_rotate(f) ;        // 旋转
            x = root ;       // 左右平衡了，直接跳出循环， x 设置为根节点，出循环后维护根节点为黑色，保持性质二
        }
    }
    x->color = BLACK;      // 如果此时 x 为根节点，将 x 染为黑色。也有可能 x 是情况二中跳出来的，直接将 x 染成黑色即可
}

/**
 * @prief   进行二叉树的三种遍历
 *
 * @tparam T    数据类型
 */
template <class T>
void RB_Tree<T>::tree_show() {
    cout << "---------------RB_Tree--------------\n";
    cout << "preorder: ";
    preorder(this->root);
    cout << "\ninorder: ";
    inorder(this->root);
    cout << "\npostorder: ";
    postorder(this->root);
    cout << "\n";
}

/**
 * @prief   输出二叉树的层序遍历
 *
 * @tparam T    数据类型
 */
template <class T>
void RB_Tree<T>::floor_show() {
    cout << "-------------floor--------------\n";
    queue<RB_Node<T>*> q, p;       // q 为奇数层节点， p 为偶数层节点。（从 1 开始数层数）
    q.push(this->root);
    while (!q.empty() || !p.empty()) {
        while (!q.empty()) {        // 将偶数层的节点放入 p 中
            RB_Node<T> *x = q.front();      // 取出队首节点
            q.pop();
            if (x != nullptr) {     // 如果 x 不为空，输出内容
                cout << "(" << x->value << ", " << (x->color ? "black" : "red") << ") ";
                p.push(x->left);        // 依次放入左右子节点
                p.push(x->right);
            }
            else {
                cout << "(null, null) ";
            }
        }
        cout << "\n";
        while (!p.empty()) {        // 将奇数层的节点放入 q 中
            RB_Node<T> *x = p.front();      // 取出队首节点
            p.pop();
            if (x != nullptr) {
                cout << "(" << x->value << ", " << (x->color ? "black" : "red") << ") ";
                q.push(x->left);        // 依次放入左右子节点
                q.push(x->right);
            }
            else {
                cout << "(null, null) ";
            }
        }
        cout << "\n";
    }
}

/**
 * @prief   先序遍历红黑树
 *
 * @tparam T    数据类型
 * @param x     红黑树节点
 */
template <class T>
void RB_Tree<T>::preorder(RB_Node<T> *x) {
    if (x == nullptr) {
        return;
    }
    cout << "(" << x->value << ", " << (x->color ? "black" : "red") << ") ";
    preorder(x->left);
    preorder(x->right);
}

/**
 * @prief   中序遍历红黑树
 *
 * @tparam T    数据类型
 * @param x     红黑树节点
 */
template <class T>
void RB_Tree<T>::inorder(RB_Node<T> *x) {
    if (x == nullptr) {
        return;
    }
    inorder(x->left);
    cout << "(" << x->value << ", " << (x->color ? "black" : "red") << ") ";
    inorder(x->right);
}

template <class T>
void RB_Tree<T>::postorder(RB_Node<T> *x) {
    if (x == nullptr) {
        return;
    }
    postorder(x->left);
    postorder(x->right);
    cout << "(" << x->value << ", " << (x->color ? "black" : "red") << ") ";
}
/**
 * @prief   析构函数，使用默认析构函数
 *
 * @tparam T
 */
template <class T>
RB_Tree<T>::~RB_Tree() = default;

