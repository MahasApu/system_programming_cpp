#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <bits/stdc++.h>
#include "/mnt/c/Users/vaskm/OneDrive/Рабочий стол/2024/system_programming_cpp/tasks/first/AVLTree.h"


bool is_avl(TreeNode* head) {
  if (head == NULL) return true;
  if (abs(head->right->height - head->right->height) <= 1 && is_avl(head->left) && is_avl(head->right)) return true;
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
  ASSERT_TRUE(tree->_search(tree->head, rand_value) == NULL);

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

  // delete values;
  delete tree;
}

TEST(AVLTreeTest, isAVL) {

  int values[] = {1,2,3,4,5,6,7,8,9};
  AVL* determ_tree =  new AVL(values, 9);
  ASSERT_TRUE(is_avl(determ_tree->head));
  
  delete determ_tree;
}

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}