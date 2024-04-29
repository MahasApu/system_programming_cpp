#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <vector>

#include "../../tasks/task10/MixInCounter.hpp"

template<typename T, size_t LIMIT>
struct Restricted: MixInCounter<LIMIT> {
    T nice_value;
    Restricted(T value): nice_value(value) { }
};

TEST(MixInTest, restricted) {

    const size_t limit = 2;
    typedef Restricted<char, limit> restricted_t;
    std::vector<restricted_t> instances_list;
    
    for (size_t i = 0; i < 10; i ++) try {
        instances_list.push_back(restricted_t('a' + i));
    } catch (const MixInCounterException& e) {
      std::cout << e.what() << i << std::endl;
      ASSERT_TRUE( i >= limit);
    }
}


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
