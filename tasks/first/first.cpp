#include "AVLTree.h"
#include <iostream>


int main() {
    int values[] = {11, 2, 3, 43, 555, 23, 5, 1, 33};
    AVL* determ_tree = new AVL(values, 9);
    for (int i = 0; i < 9; i++){
        determ_tree->_insert(values[i]);
    }
    determ_tree->printTree(determ_tree->head, "", true);
    determ_tree->_delete(values[3]);
    determ_tree->printTree(determ_tree->head, "", true);
    std::cout << determ_tree->_search(determ_tree->head, values[3]) << std::endl;
    std::cout << determ_tree->_search(determ_tree->head, values[7])->value << std::endl;

    delete determ_tree;
    return 0;
}