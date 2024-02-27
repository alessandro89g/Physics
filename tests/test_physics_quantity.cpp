#include <gtest/gtest.h>
#include "../include/physics/physics_quantity.hpp"

using Physics::PhysicsQuantity;
using Physics::Unit;

TEST(PhysicsQuantity, Constructors) {
    PhysicsQuantity<double> quantity1(10);
    PhysicsQuantity<double> quantity2(10, Unit::m);
    PhysicsQuantity<double> quantity3(10, std::vector<Unit>({Unit::m, Unit::s}));

    EXPECT_EQ(quantity1.value(), 10);
    EXPECT_EQ(quantity1.units().size(), 0);

    EXPECT_EQ(quantity2.value(), 10);
    EXPECT_EQ(quantity2.units().size(), 1);
    EXPECT_EQ(quantity2.units()[0], Unit::m);

    EXPECT_EQ(quantity3.value(), 10);
    EXPECT_EQ(quantity3.units().size(), 2);
    EXPECT_EQ(quantity3.units()[0], Unit::m);
    EXPECT_EQ(quantity3.units()[1], Unit::s);
}

TEST(PhysicsQuantity, AddTwoQuantities) {
    PhysicsQuantity<double> quantity1(10, Unit::m);
    PhysicsQuantity<double> quantity2(20, Unit::m);

    PhysicsQuantity<double> result = quantity1 + quantity2;

    EXPECT_EQ(result.value(), 30);
    EXPECT_EQ(result.units().size(), 1);
    EXPECT_EQ(result.units()[0], Unit::m);
}

TEST(PhysicsQuantity, AddTwoQuantitiesDifferentUnits) {
    PhysicsQuantity<double> quantity1(10, Unit::m);
    PhysicsQuantity<double> quantity2(20, Unit::s);
    
    EXPECT_THROW(quantity1 + quantity2, std::invalid_argument);
}

TEST(PhysicsQuantity, AddingDoubleToQuantity) {
    PhysicsQuantity<double> quantity1(10, Unit::m);
    double quantity2 = 20;
    
    EXPECT_THROW(quantity1 + quantity2, std::invalid_argument);
}

TEST(PhysicsQuantity, SubtractTwoQuantities) {
    PhysicsQuantity<double> quantity1(10, Unit::m);
    PhysicsQuantity<double> quantity2(20, Unit::m);

    PhysicsQuantity<double> result = quantity1 - quantity2;

    EXPECT_EQ(result.value(), -10);
    EXPECT_EQ(result.units().size(), 1);
    EXPECT_EQ(result.units()[0], Unit::m);
}

TEST(PhysicsQuantity, SubtractTwoQuantitiesDifferentUnits) {
    PhysicsQuantity<double> quantity1(10, Unit::m);
    PhysicsQuantity<double> quantity2(20, Unit::s);
    
    EXPECT_THROW(quantity1 - quantity2, std::invalid_argument);
}

TEST(PhysicsQuantity, SubtractDoubleFromQuantity) {
    PhysicsQuantity<double> quantity1(10, Unit::m);
    double quantity2 = 20;
    
    EXPECT_THROW(quantity1 - quantity2, std::invalid_argument);
}

TEST(PhysicsQuantity, MultiplyTwoQuantities) {
    PhysicsQuantity<double> quantity1(10, Unit::m);
    PhysicsQuantity<double> quantity2(20, Unit::s);

    PhysicsQuantity<double> result = quantity1 * quantity2;

    EXPECT_EQ(result.value(), 200);
    EXPECT_EQ(result.units().size(), 2);
    EXPECT_EQ(result.units()[0], Unit::m);
    EXPECT_EQ(result.units()[1], Unit::s);
}

TEST(PhysicsQuantity, MultiplyByScalar) {
    PhysicsQuantity<double> quantity1(10, Unit::m);
    double quantity2 = 20;

    PhysicsQuantity<double> result = quantity1 * quantity2;

    EXPECT_EQ(result.value(), 200);
    EXPECT_EQ(result.units().size(), 1);
    EXPECT_EQ(result.units()[0], Unit::m);
}

TEST(PhysicsQuantity, DivideTwoQuantities) {
    PhysicsQuantity<double> quantity1(10, Unit::m);
    PhysicsQuantity<double> quantity2(20, Unit::s);

    PhysicsQuantity<double> result = quantity1 / quantity2;

    EXPECT_EQ(result.value(), 0.5);
    EXPECT_EQ(result.units().size(), 2);
    EXPECT_EQ(result.units()[0], Unit(Unit::m));
    EXPECT_EQ(result.units()[1], Unit(Unit::s, -1));
}

TEST(PhysicsQuantity, DivideByScalar) {
    PhysicsQuantity<double> quantity1(10, Unit::m);
    double quantity2 = 20;

    PhysicsQuantity<double> result = quantity1 / quantity2;

    EXPECT_EQ(result.value(), 0.5);
    EXPECT_EQ(result.units().size(), 1);
    EXPECT_EQ(result.units()[0], Unit::m);
}

TEST(PhysicsQuantity, UnaryMinus) {
    PhysicsQuantity<double> quantity1(10, Unit::m);

    PhysicsQuantity<double> result = -quantity1;

    EXPECT_EQ(result.value(), -10);
    EXPECT_EQ(result.units().size(), 1);
    EXPECT_EQ(result.units()[0], Unit::m);
}

TEST(PhysicsQuantity, PrintQuantity) {
    PhysicsQuantity<double> quantity1(10, Unit::m);

    std::string result = quantity1.toString();

    EXPECT_EQ(result, "10 m");
}

TEST(PhysicsQuantity, PrintQuantityWithMultipleUnits) {
    PhysicsQuantity<double> quantity1(10, std::vector<Unit>({Unit(Unit::m), Unit(Unit::s,-1)}));

    std::string result = quantity1.toString();

    EXPECT_EQ(result, "10 m s^-1");
}

TEST(PhysicsQuantity, PrintQuantityWithMultipleUnitsAndPowers) {
    PhysicsQuantity<double> quantity1(10, std::vector<Unit>({Unit(Unit::m, 2), Unit(Unit::s,-1)}));

    std::string result = quantity1.toString();

    EXPECT_EQ(result, "10 m^2 s^-1");
}

TEST(PhysicsQuantity, AddDoubleOnTheLeft) {
    PhysicsQuantity<double> quantity1(10, Unit::m);
    double quantity2 = 20;

    EXPECT_THROW(quantity2 + quantity1, std::invalid_argument);
}

TEST(PhysicsQuantity, SubtractDoubleOnTheLeft) {
    PhysicsQuantity<double> quantity1(10, Unit::m);
    double quantity2 = 20;

    EXPECT_THROW(quantity2 - quantity1, std::invalid_argument);
}

TEST(PhysicsQuantity, MultiplyDoubleOnTheLeft) {
    PhysicsQuantity<double> quantity1(10, Unit::m);
    double quantity2 = 20;

    PhysicsQuantity<double> result = quantity2 * quantity1;

    EXPECT_EQ(result.value(), 200);
    EXPECT_EQ(result.units().size(), 1);
    EXPECT_EQ(result.units()[0], Unit::m);
}

TEST(PhysicsQuantity, DivideDoubleOnTheLeft) {
    PhysicsQuantity<double> quantity1(10, Unit::m);
    double quantity2 = 20;

    PhysicsQuantity<double> result = quantity2 / quantity1;

    EXPECT_EQ(result.value(), 2);
    EXPECT_EQ(result.units().size(), 1);
    EXPECT_EQ(result.units()[0], Unit(Unit::m, -1));
}

TEST(PhysicsQuantity, AddDoubleToUnitlessQuantity) {
    PhysicsQuantity<double> quantity1(10);
    double quantity2 = 20;

    EXPECT_EQ(quantity1 + quantity2, PhysicsQuantity<double>(30));
}

TEST(PhysicsQuantity, SubtractDoubleFromUnitlessQuantity) {
    PhysicsQuantity<double> quantity1(10);
    double quantity2 = 20;

    EXPECT_EQ(quantity1 - quantity2, PhysicsQuantity<double>(-10));
}

TEST(PhysicsQuantity, EqualOperator) {
    PhysicsQuantity<double> quantity1(10, Unit::m);
    PhysicsQuantity<double> quantity2(10, Unit::m);
    PhysicsQuantity<double> quantity3(10, Unit::s);
    PhysicsQuantity<double> quantity4(20, Unit::m); 

    EXPECT_TRUE(quantity1 == quantity2);
    EXPECT_FALSE(quantity1 == quantity3);
    EXPECT_FALSE(quantity1 == quantity4);
}

TEST(PhysicsQuantity, NotEqualOperator) {
    PhysicsQuantity<double> quantity1(10, Unit::m);
    PhysicsQuantity<double> quantity2(10, Unit::m);
    PhysicsQuantity<double> quantity3(10, Unit::s);
    PhysicsQuantity<double> quantity4(20, Unit::m); 

    EXPECT_FALSE(quantity1 != quantity2);
    EXPECT_TRUE(quantity1 != quantity3);
    EXPECT_TRUE(quantity1 != quantity4);
}

TEST(PhysicsQuantity, LessThanOperator) {
    PhysicsQuantity<double> quantity1(10, Unit::m);
    PhysicsQuantity<double> quantity2(20, Unit::m);
    PhysicsQuantity<double> quantity3(10, Unit::s);
    PhysicsQuantity<double> quantity4(20, Unit::s);

    EXPECT_TRUE(quantity1 < quantity2);
    EXPECT_THROW(quantity1 < quantity3, std::invalid_argument);
    EXPECT_TRUE(quantity1 < quantity4);
}

TEST(PhysicsQuantity, LessThanOrEqualOperator) {
    PhysicsQuantity<double> quantity1(10, Unit::m);
    PhysicsQuantity<double> quantity2(20, Unit::m);
    PhysicsQuantity<double> quantity3(10, Unit::s);
    PhysicsQuantity<double> quantity4(20, Unit::s);

    EXPECT_TRUE(quantity1 <= quantity2);
    EXPECT_THROW(quantity1 <= quantity3, std::invalid_argument);
    EXPECT_TRUE(quantity1 <= quantity4);
}

TEST(PhysicsQuantity, GreaterThanOperator) {
    PhysicsQuantity<double> quantity1(10, Unit::m);
    PhysicsQuantity<double> quantity2(20, Unit::m);
    PhysicsQuantity<double> quantity3(10, Unit::s);
    PhysicsQuantity<double> quantity4(20, Unit::s);

    EXPECT_TRUE(quantity2 > quantity1);
    EXPECT_THROW(quantity3 > quantity1, std::invalid_argument);
    EXPECT_TRUE(quantity4 > quantity1);
}

TEST(PhysicsQuantity, GreaterThanOrEqualOperator) {
    PhysicsQuantity<double> quantity1(10, Unit::m);
    PhysicsQuantity<double> quantity2(20, Unit::m);
    PhysicsQuantity<double> quantity3(10, Unit::s);
    PhysicsQuantity<double> quantity4(20, Unit::s);

    EXPECT_TRUE(quantity2 >= quantity1);
    EXPECT_THROW(quantity3 >= quantity1, std::invalid_argument);
    EXPECT_TRUE(quantity4 >= quantity1);
}

TEST(PhysicsQuantity, AddAssignOperator) {
    PhysicsQuantity<double> quantity1(10, Unit::m);
    PhysicsQuantity<double> quantity2(20, Unit::m);

    quantity1 += quantity2;

    EXPECT_EQ(quantity1.value(), 30);
    EXPECT_EQ(quantity1.units().size(), 1);
    EXPECT_EQ(quantity1.units()[0], Unit::m);
}

TEST(PhysicsQuantity, SubtractAssignOperator) {
    PhysicsQuantity<double> quantity1(10, Unit::m);
    PhysicsQuantity<double> quantity2(20, Unit::m);

    quantity1 -= quantity2;

    EXPECT_EQ(quantity1.value(), -10);
    EXPECT_EQ(quantity1.units().size(), 1);
    EXPECT_EQ(quantity1.units()[0], Unit::m);
}

TEST(PhysicsQuantity, MultiplyAssignOperator) {
    PhysicsQuantity<double> quantity1(10, Unit::m);
    PhysicsQuantity<double> quantity2(20, Unit::s);

    quantity1 *= quantity2;

    EXPECT_EQ(quantity1.value(), 200);
    EXPECT_EQ(quantity1.units().size(), 2);
    EXPECT_EQ(quantity1.units()[0], Unit::m);
    EXPECT_EQ(quantity1.units()[1], Unit::s);
}

TEST(PhysicsQuantity, DivideAssignOperator) {
    PhysicsQuantity<double> quantity1(10, Unit::m);
    PhysicsQuantity<double> quantity2(20, Unit::s);

    quantity1 /= quantity2;

    EXPECT_EQ(quantity1.value(), 0.5);
    EXPECT_EQ(quantity1.units().size(), 2);
    EXPECT_EQ(quantity1.units()[0], Unit(Unit::m));
    EXPECT_EQ(quantity1.units()[1], Unit(Unit::s, -1));
}
