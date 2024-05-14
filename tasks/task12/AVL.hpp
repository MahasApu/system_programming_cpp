#pragma once
#include <iostream>
#include <string>
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
        Node(T val):  
                    left(nullptr), 
                    right(nullptr),
                    height(1),
                    rank(0),
                    value(val) { }
    };

    class Iterator {
        Node* curr_;
        std::vector<Node*> stack;
    public:
        Iterator(Node* ptr) {
            push_node_trace(ptr); 
            curr_ = has_next() ? next() : nullptr;
        }
        Iterator(const Iterator& other);
        Iterator& operator=(const Iterator& other);
        ~Iterator() { }

        // Iterator's operators
        Node& operator*();
        Node* operator->();
        Iterator& operator++();
        Iterator operator++(int);
        friend bool operator==(const Iterator& first, const Iterator& second) { return first.curr_ == second.curr_; }
        friend bool operator!=(const typename AVL<T>::Iterator& first, const AVL<T>::Iterator& second) { return !(first == second); }
    private:
        void push_node_trace(Node* node);
        bool has_next();
        Node* next();
    };

    Iterator begin() { return Iterator(head); }
    Iterator end() { return Iterator(nullptr); }
    
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
    static void _ordered_nodes(Node* head, std::vector<AVL<T>::Node*>& buffer);
    static void _print_tree(Node* head, std::string indent, bool last);
    static Node* left_rotation(Node* node);
    static Node* right_rotation(Node* node);
    static Node* _search(Node* node, T value);
    Node* _insert(Node* node, T new_value);
    Node* _delete(Node* node, T old_value);


};

// Iterator methods implementation

template <typename T>
AVL<T>::Iterator::Iterator(const Iterator& other) { curr_ = other.curr_; stack = other.stack;}

template <typename T>
typename AVL<T>::Iterator& AVL<T>::Iterator::operator=(const AVL<T>::Iterator& other) {
    stack = other.stack;
    curr_ = other.curr_;
    return *this;
}

template <typename T>
void AVL<T>::Iterator::push_node_trace(Node* node) {
    if (node) {
        stack.push_back(node);
        push_node_trace(node->left);
    }
}

template <typename T>
bool AVL<T>::Iterator::has_next() { return !stack.empty(); }

template <typename T>
typename AVL<T>::Node* AVL<T>::Iterator::next() {
    if (!has_next()) return nullptr;
    Node* curr = stack.back();
    stack.pop_back();
    if (curr->right) push_node_trace(curr->right);
    return curr;
}

// Iterator's operators

template <typename T>
typename AVL<T>::Node& AVL<T>::Iterator::operator*() { return *curr_; }

template <typename T>
typename AVL<T>::Node* AVL<T>::Iterator::operator->() { return curr_; }

template <typename T>
typename AVL<T>::Iterator& AVL<T>::Iterator::operator++() {
    curr_ = next();
    return *this;
}

template <typename T>
typename AVL<T>::Iterator AVL<T>::Iterator::operator++(int) {
    Iterator tmp(*this);
    ++(*this);
    return tmp;
}


// AVLTree structure methods implementation

static int max(int a, int b) {
  return (a > b) ? a : b;
}

template<typename T>
AVL<T>::AVL(): head(nullptr), 
            size(0) {}

template<typename T>
AVL<T>::AVL(T values[], size_t size):
            head(nullptr), 
            size(0)
            {for (size_t i = 0; i < size; i++){insert_node(values[i]);}
}

template<typename T>
AVL<T>::AVL(const AVL<T>& other): 
            head(nullptr),
            size(0) 
            {copyAVL(other.head);}

template<typename T>
AVL<T>::AVL(AVL<T>&& other) {
    head = other.head;
    other.head = nullptr;  
}

template<typename T>
AVL<T>& AVL<T>::operator=(AVL<T> other){
    if (this != &other){
        std::swap(head, other.head);
    }
    return *this;
}

template<typename T>
void AVL<T>::copyAVL(AVL<T>::Node* node){
    if (node != nullptr){
        insert_node(node->value);
        copyAVL(node->left);
        copyAVL(node->right);
    }
}

template<typename T>
AVL<T>::~AVL(){
    AVL<T>::destructAVL(this->head);
}

template<typename T>
void AVL<T>::destructAVL(AVL<T>::Node*& node) {
    if (node != nullptr) {
        destructAVL(node->left);
        destructAVL(node->right);
        delete node;
        node = nullptr;  
    }
}

template<typename T>
typename AVL<T>::Node* AVL<T>::get_head() const {
    return head; 
}

template<typename T>
int AVL<T>::get_height(AVL<T>::Node* node) {
    if (node == nullptr){ return 0; }
    return node->height;
}

template<typename T>
int AVL<T>::get_balance(AVL<T>::Node* node) {
    if (node == nullptr){ return 0; }
    return get_height(node->left) - get_height(node->right);
}

template<typename T>
typename AVL<T>::Node* AVL<T>::get_min(AVL<T>::Node* node) {
    if (node == nullptr or node->left == nullptr) { return node;}
    return get_min(node->left);
}

template<typename T>
typename AVL<T>::Node* AVL<T>::get_max(AVL<T>::Node* node) {
    if (node == nullptr or node->right == nullptr) { return node;}
    return get_min(node->right);
}

template<typename T>
int AVL<T>::get_size() const {
    return size;
}

template<typename T>
int AVL<T>::get_tree_hight() {
    if (get_head() == nullptr) { return 0;}
    return get_head()->height;
}


template<typename T>
typename AVL<T>::Node* AVL<T>::left_rotation(AVL<T>::Node* node){
    if (node == nullptr){
        return nullptr;
    }

    Node* r_node = node->right;
    Node* tmp = r_node->left;

    r_node->left = node;
    node->right = tmp;

    int val = -1;
    
    if (tmp != nullptr) {
        val = tmp->rank;
    }

    node->height = 1 + max(get_height(node->left), get_height(node->right));
    r_node->height = 1 + max(get_height(r_node->left), get_height(r_node->right));

    node->rank = node->rank - (r_node->rank + 1) + (val + 1);
    r_node->rank = r_node->rank - (val + 1) + (node->rank + 1);

    return r_node;
}

template<typename T>
typename AVL<T>::Node* AVL<T>::right_rotation(AVL<T>::Node* node){
    if (node == nullptr){
        return node;
    }

    Node* l_node = node->left;
    Node* tmp = l_node->right;
    l_node->right = node;
    node->left = tmp;

    int val = -1;
    
    if (tmp != nullptr) {
        val = tmp->rank;
    }

    node->height = 1 + max(get_height(node->left), get_height(node->right));
    l_node->height = 1 + max(get_height(l_node->left), get_height(l_node->right));
    

    node->rank = node->rank - (l_node->rank + 1) + (val + 1);
    l_node->rank = l_node->rank - (val + 1) + (node->rank + 1);

    return l_node;
}

template<typename T>
int AVL<T>::comparator_balance(AVL<T>::Node* node) {
    int balance = get_balance(node);
    if (balance > 1) return 1;
    else if (balance < -1) return -1;
    else return 0;
}

template<typename T>
int AVL<T>::comparator_value(AVL<T>::Node* node, T new_value) {
    if (new_value > node->value) return -1;
    else if (new_value < node->value) return 1;
    else return 0;
}

template<typename T>
typename AVL<T>::Node* AVL<T>::search_node(T value){
    return _search(head, value);
}

template<typename T>
typename AVL<T>::Node* AVL<T>::_search(AVL<T>::Node* node, T value) {
    if (node != nullptr) {
        if (node->value == value) {
            return node;
        } else {
            if (value > node->value && node->right != nullptr) {
                return _search(node->right, value);
            } else if (value < node->value && node->left != nullptr) {
                return _search(node->left, value);
            }
        }
    }
    return nullptr;
}

template<typename T>
typename AVL<T>::Node* AVL<T>::_insert(AVL<T>::Node* node, T new_value) {
    if (node == nullptr) {
        size++;
        return new Node(new_value);
    } else {
        switch (comparator_value(node, new_value)) {
            case 1:
                node->left = _insert(node->left, new_value);
                break;
            case -1:
                node->right = _insert(node->right, new_value);
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

template<typename T>
void AVL<T>::insert_node(T value) {
    this->head = _insert(this->head, value);
}

template<typename T>
typename AVL<T>::Node* AVL<T>::_delete(AVL<T>::Node* node, T old_value){
    if (node == nullptr) return nullptr;

    int comp = comparator_value(node, old_value);
    switch (comp) {
        case 1:
            node->rank--;
            node->left = _delete(node->left, old_value);
            break;

        case -1:
            node->rank--;
            node->right = _delete(node->right, old_value);        
            break;

        case 0:
            if (node->right == nullptr) {
                Node* tmp = node->left;
                delete node;
                size--;
                return tmp;
            } else if (node->left == nullptr) {
                Node* tmp = node->right;
                delete node;
                size--;
                return tmp;
            } else {
                Node* tmp =  get_min(node->right);
                node->value = tmp->value;
                node->right = _delete(node->right, node->value);
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

template<typename T>
void AVL<T>::delete_node(T value) {
    this->head = _delete(this->head, value);
}

template<typename T>
void AVL<T>::get_ordered_values(std::vector<T>& buffer){
    std::vector<AVL<T>::Node*> nodes;
    _ordered_nodes(head, nodes);
    for (AVL<T>::Node* node: nodes) buffer.push_back(node->value);
}

template<typename T>
void AVL<T>::_ordered_nodes(AVL<T>::Node* head, std::vector<AVL<T>::Node*>& buffer) {
    if (head != nullptr) {
        buffer.push_back(head);
        _ordered_nodes(head->left, buffer);
        _ordered_nodes(head->right, buffer);
    }
}

template<typename T>
void AVL<T>::print_tree(std::string indent, bool last){
    _print_tree(head, indent, last);
}

template<typename T>
void AVL<T>::_print_tree(AVL<T>::Node* head, std::string indent, bool last) {
    
    if (head != nullptr) {
        std::cout << indent;
        if (last) {
        std::cout << "R----";
        indent += "   ";
        } else {
        std::cout << "L----" ;
        indent += "|  ";
        }
        std::cout << head->value << std::endl;
        _print_tree(head->left, indent, false);
        _print_tree(head->right, indent, true);
    }
}
