#include <iostream>

class TreeNode {
    public:
    TreeNode* left;
    TreeNode* right;
    int height = 1;
    int rank = 0;
    int value;

    TreeNode(int value){
        value = value;
    }
};

int max(int a, int b) {
  return (a > b) ? a : b;
}

class AVL {

    public:
    TreeNode* head;
    int size = 0;

    private:
    int get_height(TreeNode* node) {
        if (node == nullptr){ return 0; }
        return node->height;
    }

    int get_balance(TreeNode* node) {
        if (node == nullptr){ return 0; }
        return get_height(node->left) - get_height(node->right);
    }

    TreeNode* get_min(TreeNode* node) {
        if (node == nullptr or node->left == nullptr) { return node;}
        return get_min(node->left);
    }

    TreeNode* get_max(TreeNode* node) {
        if (node == nullptr or node->right == nullptr) { return node;}
        return get_min(node->right);
    }

    int get_size() {
        return size;
    }

    int get_tree_hight() {
        if (head == nullptr) { return 0;}
        return head->height;
    }

    TreeNode* left_rotation(TreeNode* node){
        if (node == nullptr){
            return node;
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

    TreeNode* right_rotation(TreeNode* node){
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

    int comparator_balance(TreeNode* node) {
        int balance = get_balance(node);
        if (balance > 1) return 1;
        else if (balance < -1) return -1;
        else return 0;
    }

    int comparator_value(TreeNode* node, int new_value) {
        if (new_value > node->value) return 1;
        else if (new_value < node->value) return -1;
        else return 0;
    }


    public:
    TreeNode* search(TreeNode* node, int value) {
        if (node != nullptr) {
            if (node->value == value) {
                return node;
            } else {
                if (value > node->value and node->right != nullptr) {
                    return search(node->right, value);
                } else if (value < node->value and node->left != nullptr) {
                    return search(node->left, value);
                }
            }
        }
        return nullptr;
    }

    TreeNode* insert_node(TreeNode* node, int new_value) {
        if (node == nullptr) {
            size++;
            return new TreeNode(new_value);
        } else {
            switch (comparator_value(node, new_value)) {
                case  1:
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

    void _insert(int value) {
        head = insert_node(head, value);
    }


    TreeNode* delete_node(TreeNode* node, int old_value){
        if (node == nullptr) return nullptr;

        int comp = comparator_value(node, old_value);
        switch (comp) {
            case 1:
                node->rank--;
                node->left = delete_node(node->left, old_value);
                break;

            case -1:
                node->rank--;
                node->right =delete_node(node->right, old_value);        
                break;

            case 0:
                if (node->right == nullptr) {
                    size--;
                    return node->left;
                } else if (node->left == nullptr) {
                    size--;
                    return node->right;
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

    void _delete(int value) {
        head = delete_node(head, value);
    }
};

int main()
{
    std::cout<<"Hello World";
    return 0;
}
