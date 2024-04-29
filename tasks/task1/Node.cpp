#include "AVLTree.hpp"

template<typename T>
AVL<T>::Node::Node(T val):  
                    left(nullptr), 
                    right(nullptr),
                    height(1),
                    rank(0),
                    value(val) {}

