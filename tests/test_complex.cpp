#include <gtest/gtest.h>
#include "../include/maths/complex.hpp"

TEST(Complex, DefaultConstructor) {
    Complex c;
    EXPECT_EQ(c.real(), 0.0);
    EXPECT_EQ(c.img(), 0.0);
}

TEST(Complex, ConstructorWithRealPart) {
    Complex c(3.14);
    EXPECT_EQ(c.real(), 3.14);
    EXPECT_EQ(c.img(), 0.0);
}

TEST(Complex, ConstructorWithRealAndImaginaryPart) {
    Complex c(2.0, 4.0);
    EXPECT_EQ(c.real(), 2.0);
    EXPECT_EQ(c.img(), 4.0);
}

TEST(Complex, ConstructorWithComplexPair) {
    std::pair<double, double> complexPair(2.0, 4.0);
    Complex c(complexPair);
    EXPECT_EQ(c.real(), 2.0);
    EXPECT_EQ(c.img(), 4.0);
}

TEST(Complex, AbsoluteValue) {
    Complex c(3.0, 4.0);
    EXPECT_DOUBLE_EQ(c.abs(), 5.0);
}

TEST(Complex, Conjugate) {
    Complex c(3.0, 4.0);
    Complex conjugate = c.conjugate();
    EXPECT_EQ(conjugate.real(), 3.0);
    EXPECT_EQ(conjugate.img(), -4.0);
}

TEST(Complex, Addition) {
    Complex c1(2.0, 3.0);
    Complex c2(4.0, 5.0);
    Complex result = c1 + c2;
    EXPECT_EQ(result.real(), 6.0);
    EXPECT_EQ(result.img(), 8.0);
}

TEST(Complex, Subtraction) {
    Complex c1(4.0, 5.0);
    Complex c2(2.0, 3.0);
    Complex result = c1 - c2;
    EXPECT_EQ(result.real(), 2.0);
    EXPECT_EQ(result.img(), 2.0);
}

TEST(Complex, Multiplication) {
    Complex c1(2.0, 3.0);
    Complex c2(4.0, 5.0);
    Complex result = c1 * c2;
    EXPECT_EQ(result.real(), -7.0);
    EXPECT_EQ(result.img(), 22.0);
}

TEST(Complex, Division) {
    Complex c1(4.0, 5.0);
    Complex c2(2.0, 3.0);
    Complex result = c1 / c2;
    EXPECT_DOUBLE_EQ(result.real(), 23.0/13.);
    EXPECT_DOUBLE_EQ(result.img(), -2.0/13.);
}

TEST(Complex, DivisionByZero) {
    Complex c1(4.0, 5.0);
    Complex c2(0, 0);
    Complex result = c1 / c2;
    EXPECT_DOUBLE_EQ(result.real(), INFINITY);
    EXPECT_DOUBLE_EQ(result.img(), INFINITY);
}

TEST(Complex, DivisionByZeroDouble) {
    Complex c1(4.0, 5.0);
    Complex result = c1 / 0;
    EXPECT_DOUBLE_EQ(result.real(), INFINITY);
    EXPECT_DOUBLE_EQ(result.img(), INFINITY);
}


TEST(Complex, UnaryMinus) {
    Complex c(2.0, 3.0);
    Complex result = -c;
    EXPECT_EQ(result.real(), -2.0);
    EXPECT_EQ(result.img(), -3.0);
}

TEST(Complex, CompoundAddition) {
    Complex c1(2.0, 3.0);
    Complex c2(4.0, 5.0);
    c1 += c2;
    EXPECT_EQ(c1.real(), 6.0);
    EXPECT_EQ(c1.img(), 8.0);
}

TEST(Complex, CompoundSubtraction) {
    Complex c1(4.0, 5.0);
    Complex c2(2.0, 3.0);
    c1 -= c2;
    EXPECT_EQ(c1.real(), 2.0);
    EXPECT_EQ(c1.img(), 2.0);
}

TEST(Complex, CompoundMultiplication) {
    Complex c1(2.0, 3.0);
    Complex c2(4.0, 5.0);
    c1 *= c2;
    EXPECT_EQ(c1.real(), -7.0);
    EXPECT_EQ(c1.img(), 22.0);
}

TEST(Complex, CompoundDivision) {
    Complex c1(4.0, 5.0);
    Complex c2(2.0, 3.0);
    c1 /= c2;
    EXPECT_DOUBLE_EQ(c1.real(), 23.0/13.);
    EXPECT_DOUBLE_EQ(c1.img(), -2.0/13.);
}

TEST(Complex, ToStringBothPositive) {
    Complex c(2.0, 3.0);
    std::string str = c.to_string();
    EXPECT_EQ(str, "( 2.000000 + 3.000000 i )");
}

TEST(Complex, ToStringRealNegative) {
    Complex c(-2.0, 3.0);
    std::string str = c.to_string();
    EXPECT_EQ(str, "( -2.000000 + 3.000000 i )");
}

TEST(Complex, ToStringImaginaryNegative) {
    Complex c(2.0, -3.0);
    std::string str = c.to_string();
    EXPECT_EQ(str, "( 2.000000 - 3.000000 i )");
}

TEST(Complex, ToStringBothNegative) {
    Complex c(-2.0, -3.0);
    std::string str = c.to_string();
    EXPECT_EQ(str, "( -2.000000 - 3.000000 i )");
}

TEST(Complex, ToStringReal) {
    Complex c(2.0, 0);
    std::string str = c.to_string();
    EXPECT_EQ(str, "2.000000");
}

TEST(Complex, ToStringImaginary) {
    Complex c(0, -2.0);
    std::string str = c.to_string();
    EXPECT_EQ(str, "-2.000000 i");
}

TEST(Complex, ToString0) {
    Complex c(0, 0);
    std::string str = c.to_string();
    EXPECT_EQ(str, "0");
}

TEST(Complex, AdditionWithDouble) {
    Complex c(2.0, 3.0);
    Complex result = c + 3.0;
    EXPECT_EQ(result.real(), 5.0);
    EXPECT_EQ(result.img(), 3.0);
}

TEST(Complex, SubtractionWithDouble) {
    Complex c(4.0, 5.0);
    Complex result = c - 3.0;
    EXPECT_EQ(result.real(), 1.0);
    EXPECT_EQ(result.img(), 5.0);
}

TEST(Complex, MultiplicationWithDouble) {
    Complex c(2.0, 3.0);
    Complex result = c * 3.0;
    EXPECT_EQ(result.real(), 6.0);
    EXPECT_EQ(result.img(), 9.0);
}

TEST(Complex, DivisionWithDouble) {
    Complex c(4.0, 5.0);
    Complex result = c / 2.0;
    EXPECT_DOUBLE_EQ(result.real(), 2.0);
    EXPECT_DOUBLE_EQ(result.img(), 2.5);
}

TEST(Complex, CompoundAdditionWithDouble) {
    Complex c(2.0, 3.0);
    c += 3.0;
    EXPECT_EQ(c.real(), 5.0);
    EXPECT_EQ(c.img(), 3.0);
}

TEST(Complex, CompoundSubtractionWithDouble) {
    Complex c(4.0, 5.0);
    c -= 3.0;
    EXPECT_EQ(c.real(), 1.0);
    EXPECT_EQ(c.img(), 5.0);
}

TEST(Complex, CompoundMultiplicationWithDouble) {
    Complex c(2.0, 3.0);
    c *= 3.0;
    EXPECT_EQ(c.real(), 6.0);
    EXPECT_EQ(c.img(), 9.0);
}

TEST(Complex, CompoundDivisionWithDouble) {
    Complex c(4.0, 5.0);
    c /= 2.0;
    EXPECT_DOUBLE_EQ(c.real(), 2.0);
    EXPECT_DOUBLE_EQ(c.img(), 2.5);
}

TEST(Complex, AdditionWithDoubleOnLeft) {
    Complex c(2.0, 3.0);
    Complex result = 3.0 + c;
    EXPECT_EQ(result.real(), 5.0);
    EXPECT_EQ(result.img(), 3.0);
}

TEST(Complex, SubtractionWithDoubleOnLeft) {
    Complex c(4.0, 5.0);
    Complex result = 3.0 - c;
    EXPECT_EQ(result.real(), -1.0);
    EXPECT_EQ(result.img(), -5.0);
}

TEST(Complex, MultiplicationWithDoubleOnLeft) {
    Complex c(2.0, 3.0);
    Complex result = 3.0 * c;
    EXPECT_EQ(result.real(), 6.0);
    EXPECT_EQ(result.img(), 9.0);
}

TEST(Complex, DivisionWithDoubleOnLeft) {
    Complex c(4.0, 5.0);
    Complex result = 2.0 / c;
    EXPECT_EQ(result.real(), 8./41.);
    EXPECT_EQ(result.img(), -10./41.);
}

TEST(Complex, DivisionWithDoubleOnLeftZero) {
    Complex c(0, 0);
    Complex result = 2.0 / c;
    EXPECT_DOUBLE_EQ(result.real(), INFINITY);
    EXPECT_DOUBLE_EQ(result.img(), INFINITY);
}

TEST(Complex, SetReal) {
    Complex c(2.0, 3.0);
    c.set_real(4.0);
    EXPECT_EQ(c.real(), 4.0);
}

TEST(Complex, SetImaginary) {
    Complex c(2.0, 3.0);
    c.set_imaginary(4.0);
    EXPECT_EQ(c.img(), 4.0);
}

TEST(Complex, OutputOperator) {
    Complex c(-2.0, 3.0);
    std::stringstream ss;
    ss << c;
    EXPECT_EQ(ss.str(), "(-2,3)");
}

TEST(Complex, InputOperator) {
    Complex c;
    std::stringstream ss("  (  -5.324 ,    1.1231     ) ");
    ss >> c;
    EXPECT_EQ(c.real(), -5.324);
    EXPECT_EQ(c.img(), 1.1231);
}

TEST(Complex, InputOperatorInvalid) {
    Complex c;
    std::stringstream ss("  (  -5.324 ,    1.1231     ");
    ss >> c;
    EXPECT_EQ(c.real(), 0);
    EXPECT_EQ(c.img(), 0);
    EXPECT_EQ(ss.fail(), true);
}

TEST(Complex, InputOperatorDouble) {
    Complex c;
    std::stringstream ss("  5.324 ");
    ss >> c;
    EXPECT_EQ(c.real(), 5.324);
    EXPECT_EQ(c.img(), 0);
}

TEST(Complex, InputOperatorImaginary) {
    Complex c;
    std::stringstream ss("  5.324i ");
    ss >> c;
    EXPECT_EQ(c.real(), 0);
    EXPECT_EQ(c.img(), 5.324);
}

TEST(Complex, InputOperatorImaginaryNegative) {
    Complex c;
    std::stringstream ss("  -5.324i ");
    ss >> c;
    EXPECT_EQ(c.real(), 0);
    EXPECT_EQ(c.img(), -5.324);
}

TEST(Complex, InputOperatorImaginaryWithIBefore) {
    Complex c;
    std::stringstream ss("  i-5.324 ");
    ss >> c;
    EXPECT_EQ(c.real(), 0);
    EXPECT_EQ(c.img(), -5.324);
}