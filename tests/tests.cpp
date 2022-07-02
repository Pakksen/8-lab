#include "gtest/gtest.h"
#include "polish.h"
#include <string>

TEST(RPN_TESTS, IS_NUMBER) {
    EXPECT_TRUE(isNumber("13"));
    EXPECT_TRUE(isNumber("-13"));
    EXPECT_TRUE(isNumber("1.3"));
    EXPECT_FALSE(isNumber("-"));
    EXPECT_FALSE(isNumber("*"));
    EXPECT_FALSE(isNumber(" "));
}

TEST(RPN_TESTS, IS_SIGN) {
    EXPECT_TRUE(isSign("+"));
    EXPECT_TRUE(isSign("-"));
    EXPECT_TRUE(isSign("*"));
    EXPECT_TRUE(isSign("/"));
}

TEST(RPN_TESTS, SPLIT) {
    std::vector<std::string> v = split("37 5 - 500 * 7.52 /");
    EXPECT_EQ("37", v[0]);
    EXPECT_EQ("5", v[1]);
    EXPECT_EQ("-", v[2]);
    EXPECT_EQ("500", v[3]);
    EXPECT_EQ("*", v[4]);
    EXPECT_EQ("7.52", v[5]);
    EXPECT_EQ("/", v[6]);
}

TEST(RPN_TESTS, CALCULATE) {
    EXPECT_EQ(10, calculate("5 5 +"));
    EXPECT_EQ(0, calculate("5 5 -"));
    EXPECT_EQ(25, calculate("5 5 *"));
    EXPECT_EQ(1, calculate("5 5 /"));
    EXPECT_EQ(50, calculate("5 5 + 30 - 2.5 * -1 /"));

}

TEST(RPN_TESTS, INCORRECT_DATA) {
    EXPECT_ANY_THROW(calculate("azazaz"));
    EXPECT_ANY_THROW(calculate(""));
    EXPECT_ANY_THROW(calculate(" "));
}
