#pragma once
#include <iostream>
#include <vector>
#include "TreeNode.h"

class AVL {
public:
    AVL();
    AVL(int values[], size_t size);
    AVL(const AVL& other);
    AVL& operator=(const AVL& other);
    ~AVL();

    TreeNode* head;
    int size;

    TreeNode* _search(int value);
    void _insert(int value);
    void _delete(int value);
    void printTree(TreeNode* head, std::string indent, bool last, std::vector<int>& buffer);
    void printTree(TreeNode* head, std::string indent, bool last);


private:
    void copyAVL(TreeNode* node);
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
    TreeNode* search_node(TreeNode* node, int value);
    TreeNode* insert_node(TreeNode* node, int new_value);
    TreeNode* delete_node(TreeNode* node, int old_value);
};

