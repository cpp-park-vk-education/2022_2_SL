#include <gtest/gtest.h>
#include "calculation.hpp"

using namespace std;

TEST(TestAddition, Subtest_1) {
  ASSERT_TRUE(0 == 0);
}

TEST(TestMultiplication, Subtest_2) {
  ASSERT_TRUE(0 == 0);
}

TEST(TestSubtraction, Subtest_3) {
  ASSERT_TRUE(0 == 0);
}

TEST(TestSubtraction, Subtest_4) {
  ASSERT_TRUE(0 == 0);
}
 //int x = calculation(1.0, 1.0, '+');
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}