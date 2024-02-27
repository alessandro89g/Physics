#include <gtest/gtest.h>
#include "../include/physics/physics_units.hpp"

using Physics::Unit;

TEST(PhysicsUnits, Constructor) {
    Unit u(Unit::UnitType::m, 2);
    EXPECT_EQ(u.getType(), Unit::UnitType::m);
    EXPECT_EQ(u.getPower(), 2);
}

TEST(PhysicsUnits, ConstructorZeroPower) {
    Unit u(Unit::UnitType::m, 0);
    EXPECT_EQ(u.getType(), Unit::UnitType::NoUnit);
    EXPECT_EQ(u.getPower(), 0);
}

TEST(PhysicsUnits, Equality) {
    Unit u1(Unit::UnitType::m, 2);
    Unit u2(Unit::UnitType::m, 2);
    EXPECT_EQ(u1, u2);
}

TEST(PhysicsUnits, InequalityType) {
    Unit u1(Unit::UnitType::m, 2);
    Unit u2(Unit::UnitType::s, 2);
    EXPECT_NE(u1, u2);
}

TEST(PhysicsUnits, InequalityPower) {
    Unit u1(Unit::UnitType::m, 2);
    Unit u2(Unit::UnitType::m, 3);
    EXPECT_NE(u1, u2);
}

TEST(PhysicsUnits, AdditionSameUnit) {
    Unit u1(Unit::UnitType::m, 2);
    Unit u2(Unit::UnitType::m, 2);
    Unit result = u1 + u2;
    EXPECT_EQ(result.getType(), Unit::UnitType::m);
    EXPECT_EQ(result.getPower(), 2);
}

TEST(PhysicsUnits, AdditionSameUnitDifferentPower) {
    Unit u1(Unit::UnitType::m, 2);
    Unit u2(Unit::UnitType::m, 1);
    EXPECT_THROW(u1 + u2, std::invalid_argument);
}

TEST(PhysicsUnits, AdditionDifferentUnit) {
    Unit u1(Unit::UnitType::m, 2);
    Unit u2(Unit::UnitType::s, 1);
    EXPECT_THROW(u1 + u2, std::invalid_argument);
}

TEST(PhysicsUnits, SubtractionSameUnit) {
    Unit u1(Unit::UnitType::m, 2);
    Unit u2(Unit::UnitType::m, 2);
    Unit result = u1 - u2;
    EXPECT_EQ(result.getType(), Unit::UnitType::m);
    EXPECT_EQ(result.getPower(), 2);
}

TEST(PhysicsUnits, SubtractionSameUnitDifferentPower) {
    Unit u1(Unit::UnitType::m, 2);
    Unit u2(Unit::UnitType::m, 1);
    EXPECT_THROW(u1 - u2, std::invalid_argument);
}

TEST(PhysicsUnits, SubtractionDifferentUnit) {
    Unit u1(Unit::UnitType::m, 2);
    Unit u2(Unit::UnitType::s, 1);
    EXPECT_THROW(u1 - u2, std::invalid_argument);
}

TEST(PhysicsUnits, MultiplicationSameUnit) {
    Unit u1(Unit::UnitType::m, 2);
    Unit u2(Unit::UnitType::m, 1);
    std::vector<Unit> result = u1 * u2;
    ASSERT_EQ(result.size(), 1);
    EXPECT_EQ(result[0].getType(), Unit::UnitType::m);
    EXPECT_EQ(result[0].getPower(), 3);
}

TEST(PhysicsUnits, MultiplicationDifferentUnit) {
    Unit u1(Unit::UnitType::m, 2);
    Unit u2(Unit::UnitType::s, 1);
    std::vector<Unit> result = u1 * u2;
    ASSERT_EQ(result.size(), 2);
    EXPECT_EQ(result[0].getType(), Unit::UnitType::m);
    EXPECT_EQ(result[0].getPower(), 2);
    EXPECT_EQ(result[1].getType(), Unit::UnitType::s);
    EXPECT_EQ(result[1].getPower(), 1);
}

TEST(PhysicsUnits, DivisionSameUnit) {
    Unit u1(Unit::UnitType::m, 2);
    Unit u2(Unit::UnitType::m, 1);
    std::vector<Unit> result = u1 / u2;
    ASSERT_EQ(result.size(), 1);
    EXPECT_EQ(result[0].getType(), Unit::UnitType::m);
    EXPECT_EQ(result[0].getPower(), 1);
}

TEST(PhysicsUnits, DivisionDifferentUnit) {
    Unit u1(Unit::UnitType::m, 2);
    Unit u2(Unit::UnitType::s, 1);
    std::vector<Unit> result = u1 / u2;
    ASSERT_EQ(result.size(), 2);
    EXPECT_EQ(result[0].getType(), Unit::UnitType::m);
    EXPECT_EQ(result[0].getPower(), 2);
    EXPECT_EQ(result[1].getType(), Unit::UnitType::s);
    EXPECT_EQ(result[1].getPower(), -1);
}

TEST(PhysicsUnits, DivisionSameUnitSamePower) {
    Unit u1(Unit::UnitType::m, 2);
    Unit u2(Unit::UnitType::m, 2);
    std::vector<Unit> result = u1 / u2;
    ASSERT_EQ(result.size(), 1);
    EXPECT_EQ(result[0].getType(), Unit::UnitType::NoUnit);
    EXPECT_EQ(result[0].getPower(), 0);
}