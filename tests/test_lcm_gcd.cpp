#include <gtest/gtest.h>
#include "../include/maths/lcm_gcd.hpp"

TEST(GCD, NoNumbers) {
    EXPECT_EQ(gcd(), 0);
}

TEST(GCD, OneNumber) {
    EXPECT_EQ(gcd(42), 42);
}

TEST(GCD, TwoNumbers) {
    EXPECT_EQ(gcd({210, 100}), 10);
}

TEST(GCD, ThreeNumbers) {
    EXPECT_EQ(gcd({210, 100, 45}), 5);
}

TEST(GCD, FourNumbers) {
    EXPECT_EQ(gcd({210, 300, 45, 15}), 15);
}   

TEST(GCD, ThreeLargerThan1000Numbers) {
    int n1 = 5*9*8*7*4;
    int n2 = 5*9*8*7*3;
    int n3 = 5*9*8*7*2;

    EXPECT_EQ(gcd({n1, n2, n3}), 5*9*8*7);
}

TEST(GCD, NegativeNumbers) {
    EXPECT_EQ(gcd({-210, 100, 45}), 5);
}

TEST(GCD, Zero) {
    EXPECT_EQ(gcd({0, 100, 45}), 5);
}

TEST(LCM, NoNumbers) {
    EXPECT_EQ(lcm(), 0);
}

TEST(LCM, OneNumber) {
    EXPECT_EQ(lcm(42), 42);
}

TEST(LCM, TwoNumbers) {
    EXPECT_EQ(lcm({210, 100}), 7*3*5*2*5*2);
}

TEST(LCM, ThreeNumbers) {
    // 210 = 7^1 * 5^1 * 3^1 * 2^1
    // 100 =       5^2       * 2^2
    // 45  =       5^1 * 3^2
    EXPECT_EQ(lcm({210, 100, 45}), 7*5*5*3*3*2*2);
}

TEST(LCM, TwoNumbersOfWhichOneIsOne) {
    EXPECT_EQ(lcm({1, 42}), 42);
}

TEST(GCD, TwoNumbersOfWhichOneIsOne) {
    EXPECT_EQ(gcd({1, 42}), 1);
}