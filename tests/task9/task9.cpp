#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <bits/stdc++.h>
#include "../../tasks/task9/AVL.hpp"


template<typename T>
int get_height(typename AVL<T>::Node* node) {
    if (node == nullptr){ return 0; }
    return node->height;
}

template<typename T>
bool is_avl(typename AVL<T>::Node* head) {
  if (head == nullptr) return true;
  if (abs(get_height<T>(head->right) - get_height<T>(head->left)) <= 1 && is_avl<T>(head->left) && is_avl<T>(head->right) ) return true;
  return false;
}


TEST(AVLTreeTest, determined) {

  int values[] = {1,2,3,4,5,6,7,8,9};
  AVL<int> determ_tree(values, 9);
  std::vector<int> buffer = {};
  determ_tree.get_ordered_values(buffer);
  ASSERT_THAT(buffer, testing::ElementsAre(4,2,1,3,6,5,8,7,9));
}

TEST(AVLTreeTest, searchAfterDelete) {

  size_t rand_size = rand() % 100;
  int values[rand_size];
  for( size_t i = 0; i < rand_size; i++){
    values[i] = rand() % 10000;
  }

  int rand_index  = rand() % 100;
  int rand_value = values[rand_index % rand_size];
  AVL<int> tree =  AVL<int>(values, rand_size);
  tree.delete_node(rand_value);
  ASSERT_TRUE(tree.search_node(rand_value) == nullptr);
}

TEST(AVLTreeTest, insertNode) {

  size_t rand_size = rand() % 10;
  int values[rand_size];
  for( size_t i = 0; i < rand_size; i++){
    values[i] = rand() % 10000;
  }

  int rand_value = rand() % 10000;
  AVL<int> tree = AVL<int>(values, rand_size);
  tree.insert_node(rand_value);
  ASSERT_TRUE(tree.search_node(rand_value)->value == rand_value);
}

TEST(AVLTreeTest, isAVL) {

  int values[] = {1,2,3,4,5,6,7,8,9};
  AVL<int> determ_tree = AVL<int>(values, 9);
  ASSERT_TRUE(is_avl<int>(determ_tree.get_head()));
}


TEST(AVLTreeTest, copyConstructor) {

  int values[] = {1,2,3,4,5,6,7,8,9};
  size_t size = 9;
  AVL<int> determ_tree = AVL<int>(values, size);
  AVL<int> tree_copy = AVL<int>(determ_tree);

  int rand_value = values[rand() % size];
  tree_copy.delete_node(rand_value);

  ASSERT_TRUE(tree_copy.search_node(rand_value) == nullptr);
  ASSERT_TRUE(determ_tree.search_node(rand_value) != nullptr);
}


TEST(AVLTreeTest, copyOperator) {

  int values[] = {1,2,3,4,5,6,7,8,9};
  size_t size = 9;
  AVL<int> determ_tree = AVL<int>(values, size);
  AVL<int> tree_copy = AVL<int>();
  tree_copy = determ_tree;

  int rand_value = values[rand() % size];
  tree_copy.delete_node(rand_value);

  ASSERT_TRUE(tree_copy.search_node(rand_value) == nullptr);
  ASSERT_TRUE(determ_tree.search_node(rand_value) != nullptr);
}


TEST(AVLTreeTest, moveConstructor) {

  int values[] = {1,2,3,4,5,6,7,8,9};
  size_t size = 9;
  AVL<int> determ_tree = AVL<int>(values, size);
  AVL<int> tree_copy = AVL<int>(std::move(determ_tree));

  int rand_value = values[rand() % size];

  ASSERT_TRUE(tree_copy.search_node(rand_value) != nullptr);
  ASSERT_TRUE(determ_tree.get_head() == nullptr);
  
}


TEST(AVLTreeTest, moveOperator) {

  int values[] = {1,2,3,4,5,6,7,8,9};
  size_t size = 9;
  AVL<int> determ_tree = AVL<int>(values, size);
  AVL<int> tree_copy = AVL<int>();
  tree_copy = std::move(determ_tree);

  int rand_value = values[rand() % size];

  ASSERT_TRUE(tree_copy.search_node(rand_value) != nullptr);
  ASSERT_TRUE(determ_tree.get_head() == nullptr);
}

int main(int argc, char **argv) {

  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
