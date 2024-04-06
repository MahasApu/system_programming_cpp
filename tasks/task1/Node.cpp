#include "AVLTree.hpp"


AVL::Node::Node(int val):  
                    left(nullptr), 
                    right(nullptr),
                    height(1),
                    rank(0),
                    value(val) {}

