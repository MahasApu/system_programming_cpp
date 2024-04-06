#include "AVLTree.hpp"


static int max(int a, int b) {
  return (a > b) ? a : b;
}

AVL::AVL(): head(nullptr), 
            size(0) {}

AVL::AVL(int values[], size_t size):
            head(nullptr), 
            size(0)
            {for (size_t i = 0; i < size; i++){insert_node(values[i]);}
}

AVL::AVL(const AVL& other): 
            head(nullptr),
            size(0) 
            {copyAVL(other.head);}

AVL::AVL(AVL&& other) {
    head = other.head;
    other.head = nullptr;  
}

AVL& AVL::operator=(AVL other){
    if (this != &other){
        std::swap(head, other.head);
    }
    return *this;
}

void AVL::copyAVL(Node* node){
    if (node != nullptr){
        insert_node(node->value);
        copyAVL(node->left);
        copyAVL(node->right);
    }
}

AVL::~AVL(){
    destructAVL(this->head);
}

void AVL::destructAVL(Node*& node) {
    if (node != nullptr) {
        destructAVL(node->left);
        destructAVL(node->right);
        delete node;
        node = nullptr;  
    }
}


AVL::Node* AVL::get_head() const {
    return head; 
}

int AVL::get_height(Node* node) {
    if (node == nullptr){ return 0; }
    return node->height;
}

int AVL::get_balance(Node* node) {
    if (node == nullptr){ return 0; }
    return get_height(node->left) - get_height(node->right);
}

AVL::Node* AVL::get_min(Node* node) {
    if (node == nullptr or node->left == nullptr) { return node;}
    return get_min(node->left);
}

AVL::Node* AVL::get_max(Node* node) {
    if (node == nullptr or node->right == nullptr) { return node;}
    return get_min(node->right);
}

int AVL::get_size() const {
    return size;
}

int AVL::get_tree_hight() {
    if (get_head() == nullptr) { return 0;}
    return get_head()->height;
}

AVL::Node* AVL::left_rotation(Node* node){
    if (node == nullptr){
        return nullptr;
    }

    Node* r_node = node->right;
    Node* tmp = r_node->left;
    r_node->left = node;
    node->right = tmp;

    node->height = 1 + max(get_height(node->left), get_height(node->right));
    r_node->height = 1 + max(get_height(r_node->left), get_height(r_node->right));
    int val = -1;
    
    if (tmp != nullptr) {
        val = tmp->rank;
    }
    node->rank = node->rank - (r_node->rank + 1) + (val + 1);
    r_node->rank = r_node->rank - (val + 1) + (node->rank + 1);
    return r_node;
}

AVL::Node* AVL::right_rotation(Node* node){
    if (node == nullptr){
        return node;
    }

    Node* l_node = node->left;
    Node* tmp = l_node->right;
    l_node->right = node;
    node->left = tmp;

    node->height = 1 + max(get_height(node->left), get_height(node->right));
    l_node->height = 1 + max(get_height(l_node->left), get_height(l_node->right));
    int val = -1;
    
    if (tmp != nullptr) {
        val = tmp->rank;
    }
    node->rank = node->rank - (l_node->rank + 1) + (val + 1);
    l_node->rank = l_node->rank - (val + 1) + (node->rank + 1);

    return l_node;
}

int AVL::comparator_balance(Node* node) {
    int balance = get_balance(node);
    if (balance > 1) return 1;
    else if (balance < -1) return -1;
    else return 0;
}

int AVL::comparator_value(Node* node, int new_value) {
    if (new_value > node->value) return -1;
    else if (new_value < node->value) return 1;
    else return 0;
}

AVL::Node* AVL::search_node(int value){
    return _search(head, value);
}

AVL::Node* AVL::_search(Node* node, int value) {
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

AVL::Node* AVL::_insert(Node* node, int new_value) {
    if (node == nullptr) {
        size++;
        Node* tmp = new Node(new_value);
        return (tmp) ;
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


void AVL::insert_node(int value) {
    this->head = _insert(this->head, value);
}


AVL::Node* AVL::_delete(Node* node, int old_value){
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

void AVL::delete_node(int value) {
    this->head = _delete(this->head, value);
}

void AVL::get_ordered_values(std::vector<int>& buffer){
    _order_values(head, buffer);
}

void AVL::_order_values(Node* head, std::vector<int>& buffer) {
    if (head != nullptr) {
        buffer.push_back(head->value);
        _order_values(head->left, buffer);
        _order_values(head->right, buffer);
    }
}

void AVL::print_tree(std::string indent, bool last){
    _print_tree(head, indent, last);
}

void AVL::_print_tree(Node* head, std::string indent, bool last) {
    
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
