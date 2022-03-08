### RB_Tree

#### 红黑树的实现

 网上比较难找到比较完整的红黑树的实现。因此我根据算法导论中的描述，以其中的伪代码作为参考实现一个完整的红黑树。实现语言：C++。以下是一些代码文件的介绍

##### RB_Node.h

 Node类，使用模板编写，为红黑树中的节点。成员如下：

- father ：Node 指针，指向该节点的父亲节点。若无父亲节点，为 nullptr
- val : 变量，存储节点的值
- color : bool 类型，为 `true` 表示红色， 为 `false` 表示为黑色。（我使用了宏定义 ， `RED` 和 `BLACK`）
- left : Node 指针，指向该节点的左子节点，若无左子节点，为 nullptr
- right : Node 指针，指向该节点的右子节点，若无右子节点，为 nullptr

##### RB_Node.cpp

 Node 成员函数的实现

##### RB_Tree.h

 RB_Tree类，使用模板编写。成员为一个 Node 指针 `root` 代表红黑树的根节点

##### RB_Tree.cpp

 RB_Tree.h成员函数的实现

##### main.cpp

 一份简短的测试代码。输入一个 T 代表操作的次数。每次操作两个数字 op 和 x 。 op 为 0 表示删除，否则表示插入
****
**说明：README.md 待完善，暂时没空。懒得写了**