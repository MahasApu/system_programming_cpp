#pragma once
#include <iostream>
#include <vector>

template<typename T>
class AVL {

public:

    AVL();
    AVL(T values[], size_t size);
    AVL(const AVL& other);
    AVL(AVL&& other);
    AVL& operator=(AVL other);
    ~AVL();
    struct Node {
        Node* left;
        Node* right;
        int height;
        int rank;
        T value;
        Node(T val);

    };
    
    Node* search_node(T value);
    void insert_node(T value);
    void delete_node(T value);
    void get_ordered_values(std::vector<T>& buffer);
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
    static int comparator_value(Node* node, T new_value);
    static void _order_values(Node* head, std::vector<T>& buffer);
    static void _print_tree(Node* head, std::string indent, bool last);
    static Node* left_rotation(Node* node);
    static Node* right_rotation(Node* node);
    static Node* _search(Node* node, T value);
    Node* _insert(Node* node, T new_value);
    Node* _delete(Node* node, T old_value);
};
