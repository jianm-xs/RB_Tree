#include "RB_Tree.cpp"

using std::cin;

int main() {
    int op, x;
    RB_Tree<int> w;
    while (cin >> op >> x) {
        if (op) {       // ²åÈëÔªËØ
            w.insert(x);
        }
        else {      // É¾³ıÔªËØ
            bool res = w.del(x);
            if (!res) {
                cout << "no this node\n";
                continue;
            }
        }
//        w.tree_show();
        w.floor_show();
    }
    return 0;
}

/*
1 10
1 12
1 14
1 8
0 12

 */