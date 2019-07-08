#include <gtest/gtest.h>
#include "../src/funcs.hpp"

TEST(Main, EqualsOne)
{
    EXPECT_EQ(1, 1);
}

TEST(ParseArgsTest,HandleNoArgs){

    // Create argv and argc
    std::vector<std::string> arguments = {"cren"};
    std::vector<char*> argv;
    for (auto& arg: arguments){
        argv.push_back((char*)(arg.data()));
    }
    argv.push_back(nullptr);
    int argc = argv.size() - 1;

    po::variables_map args;

    // Program shouldn't continue
    ASSERT_FALSE(parse_args(argc, argv.data(), args));
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
