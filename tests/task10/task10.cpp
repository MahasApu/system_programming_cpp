#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <vector>

#include "../../tasks/task10/MixInCounter.hpp"
#include "../../tasks/task10/MixInCounterException.hpp"



template <typename T, size_t LIMIT>
struct Restricted: MixInCounter<LIMIT> {
  T value;
  Restricted(T val): value(val) { }
};

TEST(ExpressionsInheritance, valTest) {
  const size_t limit = 2;
  typedef Restricted<char, limit> restricted_t;
  std::vector<restricted_t> instances_vector;

  for (size_t i = 0; i < 10; i++) try {
    instances_vector.push_back(restricted_t('a' + i));
  } catch (const MixInCounterException& e) {
    ASSERT_TRUE(i >= limit);
    std::cout << e.what() << std::endl;
  }
}


int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
