#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "../../tasks/task10/MixInCounter.hpp"
#include "../../tasks/task10/MixInCounterException.hpp"



template <typename T, size_t LIMIT>
struct Restricted: MixInCounter<LIMIT> {
  T value;
  Restricted(T val): value(val) { }
};

TEST(ExpressionsInheritance, valTest) {
  const size_t limit = 4;
  typedef Restricted<char, limit> restricted_t;
  try {
    restricted_t a('1');
    restricted_t b('a');
    restricted_t c('1');
    restricted_t d = c;
    restricted_t f('1');
    // restricted_t g('a');

  } catch (const MixInCounterException& e) {
    std::cout << e.what() << std::endl;
  }
}


int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
