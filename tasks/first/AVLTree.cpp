#include "AVLTree.h"

int max(int a, int b) {12qaw
  return (a > b) ? a : b;
}

AVL::AVL(): head(nullptr), 
            size(0) {}

AVL::AVL(int values[], size_t size):
            head(nullptr), 
            size(0)
            {for (size_t i = 0; i < size; i++){_insert(values[i]);}
}

AVL::AVL(const AVL& other): 
            head(nullptr),
            size(0) 
            {copyAVL(other.head);}

AVL& AVL::operator=(const AVL& other){
    if (this != &other){
        destructAVL(this->head);
        copyAVL(other.head);
    }
    return *this;
}

void AVL::copyAVL(TreeNode* node){

    if (node != nullptr){
        _insert(node->value);
        copyAVL(node->left);
        copyAVL(node->right);
    }
}

AVL::~AVL(){
    destructAVL(this->head);
}

void AVL::destructAVL(TreeNode*& node) {
    if (node != nullptr) {
        destructAVL(node->left);
        destructAVL(node->right);
        delete node;
        node = nullptr;  
    }
}

int AVL::get_height(TreeNode* node) {
    if (node == nullptr){ return 0; }
    return node->height;
}

int AVL::get_balance(TreeNode* node) {
    if (node == nullptr){ return 0; }
    return get_height(node->left) - get_height(node->right);
}

TreeNode* AVL::get_min(TreeNode* node) {
    if (node == nullptr or node->left == nullptr) { return node;}
    return get_min(node->left);
}

TreeNode* AVL::get_max(TreeNode* node) {
    if (node == nullptr or node->right == nullptr) { return node;}
    return get_min(node->right);
}

int AVL::get_size() {
    return this->size;
}

int AVL::get_tree_hight() {
    if (this->head == nullptr) { return 0;}
    return this->head->height;
}

TreeNode* AVL::left_rotation(TreeNode* node){
    if (node == nullptr){
        return nullptr;
    }

    TreeNode* r_node = node->right;
    TreeNode* tmp = r_node->left;
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

TreeNode* AVL::right_rotation(TreeNode* node){
    if (node == nullptr){
        return node;
    }

    TreeNode* l_node = node->left;
    TreeNode* tmp = l_node->right;
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

TreeNode* AVL::insert_node(TreeNode* node, int new_value) {
    if (node == nullptr) {
        this->size++;
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
    this->head = insert_node(this->head, value);
}


TreeNode* AVL::delete_node(TreeNode* node, int old_value){
    if (node == nullptr) return nullptr;

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
            if (node->right == nullptr) {
                TreeNode* tmp = node->left;
                delete node;
                this->size--;
                return tmp;
            } else if (node->left == nullptr) {
                TreeNode* tmp = node->right;
                delete node;
                this->size--;
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
    this->head = delete_node(this->head, value);
}

void AVL::printTree(TreeNode* head, std::string indent, bool last, std::vector<int>& buffer) {
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
        buffer.push_back(head->value);
        printTree(head->left, indent, false, buffer);
        printTree(head->right, indent, true, buffer);
    }
}

void AVL::printTree(TreeNode* head, std::string indent, bool last) {
    
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
        printTree(head->left, indent, false);
        printTree(head->right, indent, true);
    }
}
