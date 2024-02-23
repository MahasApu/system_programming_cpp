#pragma once

class TreeNode {

public:
    TreeNode* left;
    TreeNode* right;
    int height;
    int rank;
    int value;

    TreeNode(int val) {
        left = NULL;
        right = NULL;
        height = 1;
        rank = 0;
        value = val;
    }

};