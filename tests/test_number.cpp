#include <gtest/gtest.h>
#include "../include/maths/number.hpp"
#include <climits>
#include <fstream>

TEST(Number, DefaultConstructor) {
    Number n;
    EXPECT_EQ(n.get(), 0);
}

TEST(Number, ConstructorWithInt) {
    Number n(42);
    EXPECT_EQ(n.get(), 42);
}

TEST(Number, ConstructorWithDouble) {
    EXPECT_THROW(Number n(3.14), std::invalid_argument);
}

TEST(Number, ConstructorWithNegativeInt) {
    EXPECT_THROW(Number n(-42), std::invalid_argument);
}

TEST(Number, ConstructorWithSetOfFactors) {
    std::set<Factor> factors = {Factor(2, 1), Factor(3, 1), Factor(7, 2)};
    Number n(factors);
    EXPECT_EQ(n.get(), 2*3*49);
}

TEST(Number, Get) {
    Number n(42);
    EXPECT_EQ(n.get(), 42);
}

TEST(Number, Set) {
    Number n;
    n.set(42);
    EXPECT_EQ(n.get(), 42);
}

TEST(Number, Factors) {
    Number n(42);
    std::set<Factor> factors = n.factors();
    std::set<Factor> expected = {Factor(2, 1), Factor(3, 1), Factor(7, 1)};
    EXPECT_EQ(factors, expected);
}

TEST(Number, Addition) {
    Number n1(42);
    Number n2(100);

    Number result = n1 + n2;
    EXPECT_EQ(result.get(), 142);
}

TEST(Number, Subtraction) {
    Number n1(100);
    Number n2(42);

    Number result = n1 - n2;
    EXPECT_EQ(result.get(), 58);
}

TEST(Number, Multiplication) {
    Number n1(42);
    Number n2(100);

    Number result = n1 * n2;
    EXPECT_EQ(result.get(), 4200);
}

TEST(Number, Division) {
    Number n1(100);
    Number n2(42);

    Number result = n1 / n2;
    EXPECT_EQ(result.get(), 2);
}

TEST(Number, Equality) {
    Number n1(42);
    Number n2(42);
    Number n3(100);

    EXPECT_EQ(n1, n2);
    EXPECT_NE(n1, n3);
}

TEST(Number, LessThan) {
    Number n1(42);
    Number n2(100);

    EXPECT_LT(n1, n2);
}

TEST(Number, GreaterThan) {
    Number n1(100);
    Number n2(42);

    EXPECT_GT(n1, n2);
}

TEST(Number, LessThanOrEqual) {
    Number n1(42);
    Number n2(100);
    Number n3(42);

    EXPECT_LE(n1, n2);
    EXPECT_LE(n1, n3);
}

TEST(Number, GreaterThanOrEqual) {
    Number n1(100);
    Number n2(42);
    Number n3(100);

    EXPECT_GE(n1, n2);
    EXPECT_GE(n1, n3);
}

TEST(Number, CheckLongFactorization2) {
    Number n(3*8*25*80*17*57);
    std::set<Factor> factors = n.factors();
    for (auto factor : factors) {
        std::cout << factor.prime << "^" << factor.power << " ";
    }
    std::cout << std::endl;
    EXPECT_EQ(factors.size(), 5);
}

TEST(Number, CheckMaxUnsignedLongLongFactorization) {
    Number n(static_cast<unsigned long long>(UINT_MAX));
    std::cout << n.get() << std::endl;
    std::set<Factor> factors = n.factors();
    for (auto factor : factors) {
        std::cout << factor.prime << "^" << factor.power << " ";
    }
    std::cout << std::endl;
    EXPECT_EQ(factors.size(), 5);

    unsigned long long product = 1;
    for (auto factor : factors) {
        for (int i = 0; i < factor.power; i++) {
            product *= factor.prime;
            std::cout << product << std::endl;
        }
    }
    EXPECT_EQ(product, UINT_MAX);
}

TEST(Number, CheckCommonFactorizationOf2Numbers) {
    Number n1(3*8*25*80*17*57*19);
    Number n2(2*16*125*80*19*118);

    for (const Factor& factor : n1.factors()) {
        std::cout << factor.prime << "^" << factor.power << " ";
    }
    std::cout << std::endl;
    for (const Factor& factor : n2.factors()) {
        std::cout << factor.prime << "^" << factor.power << " ";
    }
    std::cout << std::endl;
    
    std::set<Factor> common = common_factors(n1, n2);
    std::set<Factor> expected = {Factor(2, 7), Factor(5, 3), Factor(19, 1)};

    for (const Factor& factor : common) {
        std::cout << factor.prime << "^" << factor.power << " ";
    }
    std::cout << std::endl;

    EXPECT_EQ(common, expected);    
}

TEST(Number, CheckStaticNumberFromFactors) {
    std::set<Factor> factors = {Factor(2, 7), Factor(5, 3), Factor(19, 1)};
    unsigned long long number = Number::numberFromFactors(factors);
    EXPECT_EQ(number, 2*2*2*2*2*2*2*125*19);
}

TEST(Number, CheckGCD) {
    Number n1(3*8*25*80*17*57*19);
    Number n2(2*16*125*80*19*118);

    Number GCD = gcd(n1, n2);
    EXPECT_EQ(GCD.get(), std::pow(2,7)*pow(5,3)*19);
}