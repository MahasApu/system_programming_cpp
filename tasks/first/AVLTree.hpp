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

    };
    
    Node* search_node(int value);
    void insert_node(int value);
    void delete_node(int value);
    void get_ordered_values(std::vector<int>& buffer);
    void print_tree(std::string indent, bool last);
    int get_tree_hight();
    Node* get_head() const;
    int get_size() const;


private:
    Node* head;
    int size;

    void copyAVL(Node* node);
    void destructAVL(Node*& node);
    static int get_height(Node* node);
    static int get_balance(Node* node);
    static Node* get_min(Node* node);
    static Node* get_max(Node* node);
    static int comparator_balance(Node* node);
    static int comparator_value(Node* node, int new_value);
    static void _order_values(Node* head, std::vector<int>& buffer);
    static void _print_tree(Node* head, std::string indent, bool last);
    static Node* left_rotation(Node* node);
    static Node* right_rotation(Node* node);
    static Node* _search(Node* node, int value);
    Node* _insert(Node* node, int new_value);
    Node* _delete(Node* node, int old_value);
};
