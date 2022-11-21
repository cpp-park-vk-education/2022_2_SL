#include <gtest/gtest.h>
#include "mocks.cpp"

int main(int argc, char **argv) {
    ::testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}
