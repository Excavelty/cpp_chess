#include<gtest/gtest.h>
#include <memory>
#include "Game.h"

class GamePrepare: public testing::Test //think of it
{
    Game game;

    Game& getGame()
    {
        return game;
    }

    virtual void SetUp() override final
    {
         
    }
}
;
TEST(example_tests, first_test)
{
    GTEST_ASSERT_EQ(22, 22);
}

int main(int argc, char* argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}