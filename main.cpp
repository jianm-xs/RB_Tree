#include "RB_Tree.h"
#include "RB_Tree.cpp"
#include "Node.cpp"

using namespace std ;

int main() {
    RB_Tree<int> w ;
    int n ;
    cin >> n ;
    while (n --) {
        int op , x ;
        cin >> op >> x ;
        if (op == 1) {
            w.insert(x) ;
        }
        else {
            /*  delete all node value of x
            if (w.delete_data(x)) {
                cout << "OK , delete all nodes value of x\n" ;
            }
            else {
                cout << "no such node in the RB_Tree\n" ;
            }
             */
            // delete a node value of x
            if (w.delete_value(x)) {
                cout << "OK , delete all nodes value of x\n" ;
            }
            else {
                cout << "there is no node value of x in the RB_Tree\n" ;
            }
        }
        w.show() ;
    }
    return 0;
}