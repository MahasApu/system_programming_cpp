#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <bits/stdc++.h>
#include "/mnt/c/Users/vaskm/OneDrive/Рабочий стол/2024/system_programming_cpp/tasks/first/AVLTree.h"


bool is_avl(TreeNode* head) {
  if (head == nullptr) return true;
  if (is_avl(head->left) && is_avl(head->right) && abs(head->right->height - head->right->height) <= 1) return true;
  return false;
}

TEST(AVLTreeTest, determined) {

  int values[] = {1,2,3,4,5,6,7,8,9};
  AVL* determ_tree =  new AVL(values, 9);
  std::vector<int> buffer = {};
  determ_tree->printTree(determ_tree->head, "", true, buffer);
  ASSERT_THAT(buffer, testing::ElementsAre(4,2,1,3,6,5,8,7,9));

  delete determ_tree;
}

TEST(AVLTreeTest, searchAfterDelete) {

  size_t rand_size = rand() % 100;
  int values[rand_size];
  for( size_t i = 0; i < rand_size; i++){
    values[i] = rand() % 10000;
  }

  int rand_index  = rand() % 100;
  int rand_value = values[rand_index % rand_size];
  AVL* tree =  new AVL(values, rand_size);
  tree->_delete(rand_value);
  ASSERT_TRUE(tree->_search(tree->head, rand_value) == nullptr);

  delete tree;
}

TEST(AVLTreeTest, insertNode) {

  size_t rand_size = rand() % 10;
  int values[rand_size];
  for( size_t i = 0; i < rand_size; i++){
    values[i] = rand() % 10000;
  }

  int rand_value = rand() % 10000;
  AVL* tree =  new AVL(values, rand_size);
  tree->_insert(rand_value);
  ASSERT_TRUE(tree->_search(tree->head, rand_value)->value == rand_value);

  delete tree;
}

// TEST(AVLTreeTest, isAVL) {

//   int values[] = {1,2,3,4,5,6,7,8,9};
//   AVL* determ_tree =  new AVL(values, 9);
//   ASSERT_TRUE(is_avl(determ_tree->head));
  
//   delete determ_tree;
// }


TEST(AVLTreeTest, copyConstructor) {

  int values[] = {1,2,3,4,5,6,7,8,9};
  size_t size = 9;
  AVL* determ_tree =  new AVL(values, size);
  AVL* tree_copy = new AVL(*determ_tree);

  int rand_value = values[rand() % size];
  tree_copy->_delete(rand_value);

  ASSERT_TRUE(tree_copy->_search(tree_copy->head, rand_value) == nullptr);
  ASSERT_TRUE(determ_tree->_search(determ_tree->head, rand_value) != nullptr);
  
  delete determ_tree;
  delete tree_copy;
}


TEST(AVLTreeTest, copyOperator) {

  int values[] = {1,2,3,4,5,6,7,8,9};
  size_t size = 9;
  AVL* determ_tree =  new AVL(values, size);
  AVL* tree_copy = new AVL();
  *tree_copy = *determ_tree;

  int rand_value = values[rand() % size];
  tree_copy->_delete(rand_value);

  ASSERT_TRUE(tree_copy->_search(tree_copy->head, rand_value) == nullptr);
  ASSERT_TRUE(determ_tree->_search(determ_tree->head, rand_value) != nullptr);
  
  delete determ_tree;
  delete tree_copy;
}

int main(int argc, char **argv) {

  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}