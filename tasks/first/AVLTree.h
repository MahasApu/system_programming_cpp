#pragma once
#include <iostream>
#include <vector>

class AVL {

public:

    AVL();
    AVL(int values[], size_t size);
    AVL(const AVL& other);
    AVL(AVL&& other);
    AVL& operator=(AVL other);
    ~AVL();

    struct Node {
        Node* left;
        Node* right;
        int height;
        int rank;
        int value;
        Node(int val);
        Node(const Node& other);
        Node& operator=(const Node& other);
    };
    
    Node* head;
    int size;

    Node* _search(int value);
    void _insert(int value);
    void _delete(int value);
    void printTree(Node* head, std::string indent, bool last, std::vector<int>& buffer);
    void printTree(Node* head, std::string indent, bool last);


private:
    void copyAVL(Node* node);
    void destructAVL(Node*& node);
    int get_height(Node* node);
    int get_balance(Node* node);
    Node* get_min(Node* node);
    Node* get_max(Node* node);
    int get_size();
    int get_tree_hight();
    Node* left_rotation(Node* node);
    Node* right_rotation(Node* node);
    int comparator_balance(Node* node);
    int comparator_value(Node* node, int new_value);
    Node* search_node(Node* node, int value);
    Node* insert_node(Node* node, int new_value);
    Node* delete_node(Node* node, int old_value);
};
