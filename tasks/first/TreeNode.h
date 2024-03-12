#pragma once

class TreeNode {

public:
    TreeNode* left;
    TreeNode* right;
    int height;
    int rank;
    int value;

    TreeNode(int val): left(nullptr), 
                       right(nullptr),
                       height(1),
                       rank(0),
                       value(val) {}

    TreeNode(const TreeNode& other):
                        height(other.height),
                        rank(other.rank),
                        value(other.value) 
    {
        if (other.left) left = new TreeNode(*other.left);
        else left = nullptr;

        if (other.right) right = new TreeNode(*other.right);
        else right = nullptr;
    }

    TreeNode& operator=(const TreeNode& other) {
        height = other.height;
        rank = other.rank;
        value = other.value;

        if (other.left) left = new TreeNode(*other.left);
        else left = nullptr;

        if (other.right) right = new TreeNode(*other.right);
        else right = nullptr;

        return *this;

    }
};

