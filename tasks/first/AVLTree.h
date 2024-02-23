#pragma once
#include <iostream>
#include "TreeNode.h"

class AVL {
public:
    TreeNode* head;
    int size;
    AVL();
    AVL(int values[], size_t size);
    ~AVL();
    TreeNode* _search(TreeNode* node, int value);
    void _insert(int value);
    void _delete(int value);
    void printTree(TreeNode* head, std::string indent, bool last);


private:
    void destructAVL(TreeNode*& node);
    int get_height(TreeNode* node);
    int get_balance(TreeNode* node);
    TreeNode* get_min(TreeNode* node);
    TreeNode* get_max(TreeNode* node);
    int get_size();
    int get_tree_hight();
    TreeNode* left_rotation(TreeNode* node);
    TreeNode* right_rotation(TreeNode* node);
    int comparator_balance(TreeNode* node);
    int comparator_value(TreeNode* node, int new_value);
    TreeNode* insert_node(TreeNode* node, int new_value);
    TreeNode* delete_node(TreeNode* node, int old_value);
};

int max(int a, int b) {
  return (a > b) ? a : b;
}

AVL::AVL() {
    head = NULL;
    size = 0;
}
AVL::AVL(int values[], size_t size) {
    head = NULL;
    size = 0;
    for (size_t i = 0; i < size; i++){
        _insert(values[i]);
        printTree(head, "", true);
    }
}
AVL::~AVL(){
    destructAVL(head);
}

void AVL::destructAVL(TreeNode*& node) {
    if (node != NULL) {
        destructAVL(node->left);
        destructAVL(node->right);
        delete node;
        node = NULL;
    }
}

int AVL::get_height(TreeNode* node) {
    if (node == NULL){ return 0; }
    return node->height;
}

int AVL::get_balance(TreeNode* node) {
    if (node == NULL){ return 0; }
    return get_height(node->left) - get_height(node->right);
}

TreeNode* AVL::get_min(TreeNode* node) {
    if (node == NULL or node->left == NULL) { return node;}
    return get_min(node->left);
}

TreeNode* AVL::get_max(TreeNode* node) {
    if (node == NULL or node->right == NULL) { return node;}
    return get_min(node->right);
}

int AVL::get_size() {
    return size;
}

int AVL::get_tree_hight() {
    if (head == NULL) { return 0;}
    return head->height;
}

TreeNode* AVL::left_rotation(TreeNode* node){
    if (node == NULL){
        return NULL;
    }

    TreeNode* r_node = node->right;
    TreeNode* tmp = r_node->left;
    r_node->left = node;
    node->right = tmp;

    node->height = 1 + max(get_height(node->left), get_height(node->right));
    r_node->height = 1 + max(get_height(r_node->left), get_height(r_node->right));
    int val = -1;
    
    if (tmp != NULL) {
        val = tmp->rank;
    }
    node->rank = node->rank - (r_node->rank + 1) + (val + 1);
    r_node->rank = r_node->rank - (val + 1) + (node->rank + 1);
    return r_node;
}

TreeNode* AVL::right_rotation(TreeNode* node){
    if (node == NULL){
        return node;
    }

    TreeNode* l_node = node->left;
    TreeNode* tmp = l_node->right;
    l_node->right = node;
    node->left = tmp;

    node->height = 1 + max(get_height(node->left), get_height(node->right));
    l_node->height = 1 + max(get_height(l_node->left), get_height(l_node->right));
    int val = -1;
    
    if (tmp != NULL) {
        val = tmp->rank;
    }
    node->rank = node->rank - (l_node->rank + 1) + (val + 1);
    l_node->rank = l_node->rank - (val + 1) + (node->rank + 1);

    return l_node;
}

int AVL::comparator_balance(TreeNode* node) {
    int balance = get_balance(node);
    if (balance > 1) return 1;
    else if (balance < -1) return -1;
    else return 0;
}

int AVL::comparator_value(TreeNode* node, int new_value) {
    if (new_value > node->value) return -1;
    else if (new_value < node->value) return 1;
    else return 0;
}

TreeNode* AVL::_search(TreeNode* node, int value) {
    if (node != NULL) {
        if (node->value == value) {
            return node;
        } else {
            if (value > node->value && node->right != NULL) {
                return _search(node->right, value);
            } else if (value < node->value && node->left != NULL) {
                return _search(node->left, value);
            }
        }
    }
    return NULL;
}

TreeNode* AVL::insert_node(TreeNode* node, int new_value) {
    if (node == NULL) {
        size++;
        TreeNode* tmp = new TreeNode(new_value);
        return (tmp) ;
    } else {
        switch (comparator_value(node, new_value)) {
            case 1:
                node->left = insert_node(node->left, new_value);
                break;
            case -1:
                node->right = insert_node(node->right, new_value);
                break;
        }
        node->rank += 1;
    }

    node->height = 1 + max(get_height(node->left), get_height(node->right));
    
    switch (comparator_balance(node)) {
        case 1:
            if (new_value > node->left->value) { node->left = left_rotation(node->left); }
            return right_rotation(node);

        case -1: 
            if (new_value < node->right->value) { node->right = right_rotation(node->right); }
            return left_rotation(node);

        default:
            return node;
    }
}


void AVL::_insert(int value) {
    head = insert_node(head, value);
}


TreeNode* AVL::delete_node(TreeNode* node, int old_value){
    if (node == NULL) return NULL;

    int comp = comparator_value(node, old_value);
    switch (comp) {
        case 1:
            node->rank--;
            node->left = delete_node(node->left, old_value);
            break;

        case -1:
            node->rank--;
            node->right = delete_node(node->right, old_value);        
            break;

        case 0:
            if (node->right == NULL) {
                TreeNode* tmp = node->left;
                delete node;
                size--;
                return tmp;
            } else if (node->left == NULL) {
                TreeNode* tmp = node->right;
                delete node;
                size--;
                return tmp;
            } else {
                TreeNode* tmp =  get_min(node->right);
                node->value = tmp->value;
                node->right = delete_node(node->right, node->value);
                node->rank--;
                break;
            }
    }

    node->height = 1 + max(get_height(node->left), get_height(node->right));
    
    switch (get_balance(node)) {
        case 1:
            if (get_balance(node->left) < 0) node->left = left_rotation(node->left);
            return right_rotation(node);
        case -1:
            if (get_balance(node->right) > 0) node->right = right_rotation(node->right);
            return left_rotation(node);
        default:
            return node;
    }
}

void AVL::_delete(int value) {
    head = delete_node(head, value);
}

void AVL::printTree(TreeNode* head, std::string indent, bool last) {
    if (head != NULL) {
        std::cout << indent;
        if (last) {
        std::cout << "R----";
        indent += "   ";
        } else {
        std::cout << "L----" ;
        indent += "|  ";
        }
        std::cout << head->value << std::endl;
        printTree(head->left, indent, false);
        printTree(head->right, indent, true);
    }
}
