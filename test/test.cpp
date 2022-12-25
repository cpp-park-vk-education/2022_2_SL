#include <gtest/gtest.h>
#include "calculation.hpp"

TEST(Test, Subtest_1) {
  ASSERT_TRUE(0 ==  calculation(1, 1, '+', true));
}

TEST(Test, Subtest_2) {
  ASSERT_TRUE(0 ==  calculation(1, 1, '-', true));
}

TEST(Test, Subtest_3) {
  ASSERT_TRUE(0 ==  calculation(1, 1, '*', true));
}

TEST(Test, Subtest_4) {
  ASSERT_TRUE(0 ==  calculation(1, 1, '/', true));
}

TEST(Test, Subtest_5) {
  ASSERT_TRUE(-1 ==  calculation(1, '+', '+', false));
}

TEST(Test, Subtest_6) {
  ASSERT_TRUE(-2 ==  calculation(1, 1, 1, true));
}

TEST(Test, Subtest_7) {
  ASSERT_TRUE(-3 == calculation('+', '+', 2, false));
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

