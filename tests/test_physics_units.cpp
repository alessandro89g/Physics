#include <gtest/gtest.h>
#include "../include/physics/physics_units.hpp"

using Physics::Unit;

TEST(PhysicsUnits, Constructor) {
    Unit u(Unit::UnitType::m, 2);
    EXPECT_EQ(u.getType(), Unit::UnitType::m);
    EXPECT_EQ(u.getPower(), 2);
}

TEST(PhysicsUnits, ConstructorZeroPower) {
    EXPECT_THROW(Unit u(Unit::UnitType::m, 0), std::invalid_argument);
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
    Unit u2(Unit::UnitType::m, 2);
    
    std::set<Unit> result_set = (u1 * u2).value();
    std::set<Unit> expected = {Unit(Unit::UnitType::m, 4)};
    EXPECT_EQ(result_set, expected);
}

TEST(PhysicsUnits, MultiplicationDifferentUnit) {
    Unit u1(Unit::UnitType::m, 2);
    Unit u2(Unit::UnitType::s, 1);

    std::set<Unit> result_set = (u1 * u2).value();
    std::set<Unit> expected = {Unit(Unit::UnitType::m, 2), Unit(Unit::UnitType::s, 1)};
    EXPECT_EQ(result_set, expected);
}

TEST(PhysicsUnits, DivisionSameUnit) {
    Unit u1(Unit::UnitType::m, 2);
    Unit u2(Unit::UnitType::m, 1);

    std::set<Unit> result_set = (u1 / u2).value();
    std::set<Unit> expected = {Unit(Unit::UnitType::m, 1)};
    EXPECT_EQ(result_set, expected);
}

TEST(PhysicsUnits, DivisionDifferentUnit) {
    Unit u1(Unit::UnitType::m, 2);
    Unit u2(Unit::UnitType::s, 1);

    std::set<Unit> result_set = (u1 / u2).value();
    std::set<Unit> expected = {Unit(Unit::UnitType::m, 2), Unit(Unit::UnitType::s, -1)};
    EXPECT_EQ(result_set, expected);
}

TEST(PhysicsUnits, DivisionSameUnitSamePower) {
    Unit u1(Unit::UnitType::m, 2);
    Unit u2(Unit::UnitType::m, 2);
    std::optional<std::set<Unit>> result = (u1 / u2);
    EXPECT_FALSE(result.has_value());
}

TEST(PhysicsUnits, DivisionDifferentUnitSamePower) {
    Unit u1(Unit::UnitType::m, 2);
    Unit u2(Unit::UnitType::s, 2);
    std::optional<std::set<Unit>> result = (u1 / u2);
    EXPECT_TRUE(result.has_value());
}

TEST(PhysicsUnits, AdditionAssignment) {
    Unit u1(Unit::UnitType::m, 2);
    Unit u2(Unit::UnitType::m, 2);
    u1 += u2;
    EXPECT_EQ(u1.getType(), Unit::UnitType::m);
    EXPECT_EQ(u1.getPower(), 2);
}


TEST(PhysicsUnit, UnitsVectorsMultiplication) {
    std::set<Unit> u1 = {Unit(Unit::UnitType::m, 2), Unit(Unit::UnitType::s, 1)};
    std::set<Unit> u2 = {Unit(Unit::UnitType::m, 1), Unit(Unit::UnitType::s, 3), Unit(Unit::UnitType::kg)};

    std::set<Unit> result_set = u1*u2;
    std::set<Unit> expected = {Unit(Unit::UnitType::m, 3), Unit(Unit::UnitType::s, 4), Unit(Unit::UnitType::kg)};
    EXPECT_EQ(result_set, expected);
}

TEST(PhysicsUnit, UnitsVectorsDivision) {
    std::set<Unit> u1 = {Unit(Unit::UnitType::m, 2), Unit(Unit::UnitType::s, 1)};
    std::set<Unit> u2 = {Unit(Unit::UnitType::m, 1), Unit(Unit::UnitType::s, 3), Unit(Unit::UnitType::kg)};

    std::set<Unit> result_set = u1/u2;
    std::set<Unit> expected = {Unit(Unit::UnitType::m, 1), Unit(Unit::UnitType::s, -2), Unit(Unit::UnitType::kg, -1)};
    EXPECT_EQ(result_set, expected);
}

TEST(PhysicsUnit, UnitsVectorsMultiplicationNoResult) {
    std::set<Unit> u1 = {Unit(Unit::UnitType::m, 2), Unit(Unit::UnitType::s, 1)};
    std::set<Unit> u2 = {Unit(Unit::UnitType::m, -2), Unit(Unit::UnitType::s, -1)};

    std::set<Unit> result_set = u1*u2;
    std::vector<Unit> result(result_set.begin(), result_set.end());
    EXPECT_EQ(result.size(), 0);
}

TEST(PhysicsUnit, UnitsVectorsDivisionNoResult) {
    std::set<Unit> u1 = {Unit(Unit::UnitType::m, 2), Unit(Unit::UnitType::s, 1)};
    std::set<Unit> u2 = {Unit(Unit::UnitType::m, 2), Unit(Unit::UnitType::s, 1)};

    std::set<Unit> result_set = u1/u2;
    std::vector<Unit> result(result_set.begin(), result_set.end()); 
    EXPECT_EQ(result.size(), 0);
}