#include <gtest/gtest.h>
#include "../src/funcs.hpp"

TEST(Main, EqualsOne)
{
    EXPECT_EQ(1, 1);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
