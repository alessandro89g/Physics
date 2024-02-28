#include <gtest/gtest.h>
#include "../include/maths/fraction.hpp"

TEST(Fraction, Addition) {
    Fraction f1(1, 2);
    Fraction f2(1, 3);
    Fraction result = f1 + f2;
    EXPECT_EQ(result.getNumerator(), 5);
    EXPECT_EQ(result.getDenominator(), 6);
}

TEST(Fraction, Subtraction) {
    Fraction f1(3, 4);
    Fraction f2(1, 4);
    Fraction result = f1 - f2;
    EXPECT_EQ(result.getNumerator(), 1);
    EXPECT_EQ(result.getDenominator(), 2);
}

TEST(Fraction, Multiplication) {
    Fraction f1(2, 3);
    Fraction f2(3, 4);
    Fraction result = f1 * f2;
    EXPECT_EQ(result.getNumerator(), 1);
    EXPECT_EQ(result.getDenominator(), 2);
}

TEST(Fraction, Division) {
    Fraction f1(3, 4);
    Fraction f2(1, 2);
    Fraction result = f1 / f2;
    EXPECT_EQ(result.getNumerator(), 3);
    EXPECT_EQ(result.getDenominator(), 2);
}

TEST(Fraction, CompoundAddition) {
    Fraction f1(1, 2);
    Fraction f2(1, 3);
    f1 += f2;
    EXPECT_EQ(f1.getNumerator(), 5);
    EXPECT_EQ(f1.getDenominator(), 6);
}

TEST(Fraction, CompoundSubtraction) {
    Fraction f1(3, 4);
    Fraction f2(1, 4);
    f1 -= f2;
    EXPECT_EQ(f1.getNumerator(), 1);
    EXPECT_EQ(f1.getDenominator(), 2);
}

TEST(Fraction, CompoundMultiplication) {
    Fraction f1(2, 3);
    Fraction f2(3, 4);
    f1 *= f2;
    EXPECT_EQ(f1.getNumerator(), 1);
    EXPECT_EQ(f1.getDenominator(), 2);
}

TEST(Fraction, CompoundDivision) {
    Fraction f1(3, 4);
    Fraction f2(1, 2);
    f1 /= f2;
    EXPECT_EQ(f1.getNumerator(), 3);
    EXPECT_EQ(f1.getDenominator(), 2);
}

TEST(Fraction, Equality) {
    Fraction f1(1, 2);
    Fraction f2(2, 4);
    EXPECT_EQ(f1, f2);
}

TEST(Fraction, Inequality) {
    Fraction f1(1, 2);
    Fraction f2(3, 4);
    EXPECT_NE(f1, f2);
}

TEST(Fraction, LessThan) {
    Fraction f1(1, 2);
    Fraction f2(3, 4);
    EXPECT_LT(f1, f2);
}

TEST(Fraction, GreaterThan) {
    Fraction f1(3, 4);
    Fraction f2(1, 2);
    EXPECT_GT(f1, f2);
}

TEST(Fraction, LessThanOrEqual) {
    Fraction f1(1, 2);
    Fraction f2(3, 4);
    Fraction f3(1, 2);
    EXPECT_LE(f1, f2);
    EXPECT_LE(f1, f3);
}

TEST(Fraction, GreaterThanOrEqual) {
    Fraction f1(3, 4);
    Fraction f2(1, 2);
    Fraction f3(3, 4);
    EXPECT_GE(f1, f2);
    EXPECT_GE(f1, f3);
}

TEST(Fraction, Simplify) {
    Fraction f1(3*5*5*7*7*7, 3*5*7*7*7*7*11);
    EXPECT_EQ(f1.getNumerator(), 5);
    EXPECT_EQ(f1.getDenominator(), 77);
}

TEST(Fraction, Output) {
    Fraction f1(3, 4);
    std::stringstream ss;
    ss << f1;
    EXPECT_EQ(ss.str(), " 3/4 ");
}

TEST(Fraction, ZeroDenominator) {
    EXPECT_THROW(Fraction(1, 0), std::invalid_argument);
}

TEST(Fraction, ZeroNumerator) {
    Fraction f1(0, 3);
    EXPECT_EQ(f1.getNumerator(), 0);
    EXPECT_EQ(f1.getDenominator(), 1);
}

TEST(Fraction, NegativeNumerator) {
    Fraction f1(-3, 4);
    EXPECT_EQ(f1.getNumerator(), -3);
    EXPECT_EQ(f1.getDenominator(), 4);
}

TEST(Fraction, NegativeDenominator) {
    Fraction f1(3, -4);
    EXPECT_EQ(f1.getNumerator(), -3);
    EXPECT_EQ(f1.getDenominator(), 4);
}

TEST(Fraction, NegativeBoth) {
    Fraction f1(-3, -4);
    EXPECT_EQ(f1.getNumerator(), 3);
    EXPECT_EQ(f1.getDenominator(), 4);
}

TEST(Fraction, AdditionIntegerOnLeft) {
    Fraction f1(1, 3);
    Fraction result = 5 + f1;
    EXPECT_EQ(result.getNumerator(), 16);
    EXPECT_EQ(result.getDenominator(), 3);
}

TEST(Fraction, SubtractionIntegerOnLeft) {
    Fraction f1(1, 3);
    Fraction result = 5 - f1;
    EXPECT_EQ(result.getNumerator(), 14);
    EXPECT_EQ(result.getDenominator(), 3);
}

TEST(Fraction, MultiplicationIntegerOnLeft) {
    Fraction f1(1, 3);
    Fraction result = 5 * f1;
    EXPECT_EQ(result.getNumerator(), 5);
    EXPECT_EQ(result.getDenominator(), 3);
}

TEST(Fraction, DivisionIntegerOnLeft) {
    Fraction f1(1, 3);
    Fraction result = 5 / f1;
    EXPECT_EQ(result.getNumerator(), 15);
    EXPECT_EQ(result.getDenominator(), 1);
}

TEST(Fraction, DoubleConversion) {
    Fraction f1(1, 3);
    double result = static_cast<double>(f1);
    EXPECT_DOUBLE_EQ(result, 1.0/3.0);
}

TEST(Fraction, FractionThatEvaluatesToDoubleOne) {
    Fraction f1(3, 3);
    double result = static_cast<double>(f1);
    EXPECT_DOUBLE_EQ(result, 1.);
}