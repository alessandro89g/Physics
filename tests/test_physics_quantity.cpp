#include <gtest/gtest.h>
#include <cmath>
#include "../include/physics/physics_quantity.hpp"

using Physics::PhysicsQuantity;
using Physics::Unit;

TEST(PhysicsQuantity, Constructors) {
    PhysicsQuantity<double> quantity1(10);
    PhysicsQuantity<double> quantity2(10, Unit::m);
    PhysicsQuantity<double> quantity3(10, std::set<Unit>({Unit(Unit::m), Unit(Unit::s,-1)}));

    EXPECT_EQ(quantity1.value(), 10);
    EXPECT_EQ(quantity1.units().size(), 0);
    EXPECT_EQ(quantity2.value(), 10);
    EXPECT_EQ(quantity2.units().size(), 1);
    EXPECT_EQ(quantity2.units(), std::set<Unit>({Unit::m}));
    EXPECT_EQ(quantity3.value(), 10);
    EXPECT_EQ(quantity3.units().size(), 2);
    EXPECT_EQ(quantity3.units(), std::set<Unit>({Unit(Unit::m), Unit(Unit::s,-1)}));
}

TEST(PhysicsQuantity, AddTwoQuantities) {
    PhysicsQuantity<double> quantity1(10, Unit::m);
    PhysicsQuantity<double> quantity2(20, Unit::m);

    PhysicsQuantity<double> result = quantity1 + quantity2;
    
    EXPECT_EQ(result.value(), 30);
    EXPECT_EQ(result.units().size(), 1);
    EXPECT_EQ(result.units(), std::set<Unit>({Unit::m}));
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
    EXPECT_EQ(result.units(), std::set<Unit>({Unit::m}));
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
    EXPECT_EQ(result.units(), std::set<Unit>({Unit::m, Unit::s}));
}

TEST(PhysicsQuantity, MultiplyByScalar) {
    PhysicsQuantity<double> quantity1(10, Unit::m);
    double quantity2 = 20;

    PhysicsQuantity<double> result = quantity1 * quantity2;

    EXPECT_EQ(result.value(), 200);
    EXPECT_EQ(result.units().size(), 1);
    EXPECT_EQ(result.units(), std::set<Unit>({Unit::m}));
}

TEST(PhysicsQuantity, DivideTwoQuantities) {
    PhysicsQuantity<double> quantity1(10, Unit::m);
    PhysicsQuantity<double> quantity2(20, Unit::s);

    PhysicsQuantity<double> result = quantity1 / quantity2;

    EXPECT_EQ(result.value(), 0.5);
    EXPECT_EQ(result.units().size(), 2);
    EXPECT_EQ(result.units(), std::set<Unit>({Unit::m, Unit(Unit::s,-1)}));
}

TEST(PhysicsQuantity, DivideByScalar) {
    PhysicsQuantity<double> quantity1(10, Unit::m);
    double quantity2 = 20;

    PhysicsQuantity<double> result = quantity1 / quantity2;

    EXPECT_EQ(result.value(), 0.5);
    EXPECT_EQ(result.units().size(), 1);
    EXPECT_EQ(result.units(), std::set<Unit>({Unit(Unit::m)}));
}

TEST(PhysicsQuantity, UnaryMinus) {
    PhysicsQuantity<double> quantity1(10, Unit::m);

    PhysicsQuantity<double> result = -quantity1;

    EXPECT_EQ(result.value(), -10);
    EXPECT_EQ(result.units().size(), 1);
    EXPECT_EQ(result.units(), std::set<Unit>({Unit::m}));
}

TEST(PhysicsQuantity, PrintQuantity) {
    PhysicsQuantity<double> quantity1(10, Unit::m);

    std::string result = quantity1.toString();

    EXPECT_EQ(result, "10 m");
}

TEST(PhysicsQuantity, PrintQuantityWithMultipleUnits) {
    PhysicsQuantity<double> quantity1(10, std::set<Unit>({Unit(Unit::m), Unit(Unit::s,-1)}));

    std::string result = quantity1.toString();

    EXPECT_EQ(result, "10 m s^-1");
}

TEST(PhysicsQuantity, PrintQuantityWithMultipleUnitsAndPowers) {
    PhysicsQuantity<double> quantity1(10, std::set<Unit>({Unit(Unit::m, 2), Unit(Unit::s,-1)}));

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
    EXPECT_EQ(result.units(), std::set<Unit>({Unit::m}));
}

TEST(PhysicsQuantity, DivideDoubleOnTheLeft) {
    PhysicsQuantity<double> quantity1(10, Unit::m);
    double quantity2 = 20;

    PhysicsQuantity<double> result = quantity2 / quantity1;

    EXPECT_EQ(result.value(), 2);
    EXPECT_EQ(result.units().size(), 1);
    EXPECT_EQ(result.units(), std::set<Unit>({Unit(Unit::m, -1)}));
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
    PhysicsQuantity<double> quantity4(5, Unit::m);

    EXPECT_TRUE(quantity1 < quantity2);
    EXPECT_THROW(quantity1 < quantity3, std::invalid_argument);
    EXPECT_FALSE(quantity1 < quantity4);
}

TEST(PhysicsQuantity, LessThanOrEqualOperator) {
    PhysicsQuantity<double> quantity1(10, Unit::m);
    PhysicsQuantity<double> quantity2(20, Unit::m);
    PhysicsQuantity<double> quantity3(10, Unit::s);
    PhysicsQuantity<double> quantity4(10, Unit::m);

    EXPECT_TRUE(quantity1 <= quantity2);
    EXPECT_THROW(quantity1 <= quantity3, std::invalid_argument);
    EXPECT_TRUE(quantity1 <= quantity4);
}

TEST(PhysicsQuantity, GreaterThanOperator) {
    PhysicsQuantity<double> quantity1(10, Unit::m);
    PhysicsQuantity<double> quantity2(20, Unit::m);
    PhysicsQuantity<double> quantity3(10, Unit::s);
    PhysicsQuantity<double> quantity4(5, Unit::m);

    EXPECT_TRUE(quantity2 > quantity1);
    EXPECT_THROW(quantity3 > quantity1, std::invalid_argument);
    EXPECT_FALSE(quantity4 > quantity1);
}

TEST(PhysicsQuantity, GreaterThanOrEqualOperator) {
    PhysicsQuantity<double> quantity1(10, Unit::m);
    PhysicsQuantity<double> quantity2(20, Unit::m);
    PhysicsQuantity<double> quantity3(10, Unit::s);
    PhysicsQuantity<double> quantity4(10, Unit::m);

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
    EXPECT_EQ(quantity1.units(), std::set<Unit>({Unit::m}));
}

TEST(PhysicsQuantity, SubtractAssignOperator) {
    PhysicsQuantity<double> quantity1(10, Unit::m);
    PhysicsQuantity<double> quantity2(20, Unit::m);

    quantity1 -= quantity2;

    EXPECT_EQ(quantity1.value(), -10);
    EXPECT_EQ(quantity1.units().size(), 1);
    EXPECT_EQ(quantity1.units(), std::set<Unit>({Unit::m}));
}

TEST(PhysicsQuantity, MultiplyAssignOperator) {
    PhysicsQuantity<double> quantity1(10, Unit::m);
    PhysicsQuantity<double> quantity2(20, Unit::s);

    quantity1 *= quantity2;

    EXPECT_EQ(quantity1.value(), 200);
    EXPECT_EQ(quantity1.units().size(), 2);
    EXPECT_EQ(quantity1.units(), std::set<Unit>({Unit::m, Unit::s}));
}

TEST(PhysicsQuantity, DivideAssignOperator) {
    PhysicsQuantity<double> quantity1(10, Unit::m);
    PhysicsQuantity<double> quantity2(20, Unit::s);

    quantity1 /= quantity2;

    EXPECT_EQ(quantity1.value(), 0.5);
    EXPECT_EQ(quantity1.units().size(), 2);
    EXPECT_EQ(quantity1.units(), std::set<Unit>({Unit::m, Unit(Unit::s,-1)}));
}

TEST(PhysicsQuantity, MultiplyTwoQuantitiesWithThreeDifferentUnitsAndPowersAndUnitOrder) {
    PhysicsQuantity<double> quantity1(10, std::set<Unit>({Unit(Unit::m, 2), Unit(Unit::s), Unit(Unit::kg, 3)}));
    PhysicsQuantity<double> quantity2(20, std::set<Unit>({Unit(Unit::s, 5), Unit(Unit::m,-1), Unit(Unit::kg, -1)}));

    PhysicsQuantity<double> result = quantity1 * quantity2;

    EXPECT_EQ(result.value(), 200);
    EXPECT_EQ(result.units().size(), 3);
    EXPECT_EQ(result.units(), std::set<Unit>({Unit::m, Unit(Unit::s,6), Unit(Unit::kg,2)}));
} 

TEST(PhysicsQuantity, DivideTwoQuantitiesWithThreeDifferentUnitsAndPowersAndUnitOrder) {
    PhysicsQuantity<double> quantity1(10, std::set<Unit>({Unit(Unit::m, 2), Unit(Unit::s), Unit(Unit::kg, 3)}));
    PhysicsQuantity<double> quantity2(20, std::set<Unit>({Unit(Unit::s, 5), Unit(Unit::m,-1), Unit(Unit::kg, -1)}));

    PhysicsQuantity<double> result = quantity1 / quantity2;

    EXPECT_EQ(result.value(), 0.5);
    EXPECT_EQ(result.units().size(), 3);
    EXPECT_EQ(result.units(), std::set<Unit>({Unit(Unit::m, 3), Unit(Unit::s,-4), Unit(Unit::kg,4)}));
}

TEST(PhysicsQuantity, AddTwoQuantiesWithThreeDifferentUnitsAndPowersAndUnitOrder) {
    PhysicsQuantity<double> quantity1(10, std::set<Unit>({Unit(Unit::m, 2), Unit(Unit::s), Unit(Unit::kg, 3)}));
    PhysicsQuantity<double> quantity2(20, std::set<Unit>({Unit(Unit::s, 5), Unit(Unit::m,-1), Unit(Unit::kg, -1)}));

    EXPECT_THROW(quantity1 + quantity2, std::invalid_argument);
}

TEST(PhysicsQuantity, SubtractTwoQuantiesWithThreeDifferentUnitsAndPowersAndUnitOrder) {
    PhysicsQuantity<double> quantity1(10, std::set<Unit>({Unit(Unit::m, 2), Unit(Unit::s), Unit(Unit::kg, 3)}));
    PhysicsQuantity<double> quantity2(20, std::set<Unit>({Unit(Unit::s, 5), Unit(Unit::m,-1), Unit(Unit::kg, -1)}));

    EXPECT_THROW(quantity1 - quantity2, std::invalid_argument);
}

TEST(PhysicsQuantity, MultiplyTwoQuantiesWithThreeDifferentUnitsAndPowersAndUnitOrderThatResultInAScalar) {
    PhysicsQuantity<double> quantity1(10, std::set<Unit>({Unit(Unit::m, 2), Unit(Unit::s, -5), Unit(Unit::kg, 3)}));
    PhysicsQuantity<double> quantity2(20, std::set<Unit>({Unit(Unit::s, 5), Unit(Unit::m,-2), Unit(Unit::kg, -3)}));

    PhysicsQuantity<double> result = quantity1 * quantity2;

    EXPECT_EQ(result.value(), 200);
    EXPECT_EQ(result.units().size(), 0);
}

TEST(PhysicsQuantity, ConvertCrossSectionFromMeV2tofm_minus2) {
    PhysicsQuantity<double> quantity(10, std::set<Unit>({Unit(Unit::MeV, -2), Unit(Unit::sr,-1)}));

    PhysicsQuantity<double> result = Physics::convert<Unit::MeV, Unit::fm, double>(quantity);
    double quantity_in_fm = quantity.value()*std::pow(Physics::Nuclear::hc,2);
    EXPECT_EQ(result.value(), quantity_in_fm);
    EXPECT_EQ(result.units().size(), 2);
    EXPECT_EQ(result.units(), std::set<Unit>({Unit(Unit::fm, 2), Unit(Unit::sr,-1)})); 
}

TEST(PhysicsQuantity, ConvertCrossSectionFromfm2toMeV_minus2) {
    PhysicsQuantity<double> quantity(10, std::set<Unit>({Unit(Unit::fm, 2), Unit(Unit::sr,-1)}));

    PhysicsQuantity<double> result = Physics::convert<Unit::fm, Unit::MeV, double>(quantity);
    double quantity_in_MeV = quantity.value()/std::pow(Physics::Nuclear::hc,2);
    EXPECT_EQ(result.value(), quantity_in_MeV);
    EXPECT_EQ(result.units().size(), 2);
    EXPECT_EQ(result.units(), std::set<Unit>({Unit(Unit::MeV, -2), Unit(Unit::sr,-1)})); 
}

// prepare all the test with Complex numbers from my library (class Complex)

TEST(PhysicsQuantity, AddTwoQuantitiesComplex) {
    PhysicsQuantity<Complex> quantity1(Complex(10, 20), Unit::m);
    PhysicsQuantity<Complex> quantity2(Complex(20, 30), Unit::m);

    PhysicsQuantity<Complex> result = quantity1 + quantity2;
    
    EXPECT_EQ(result.value(), Complex(30, 50));
    EXPECT_EQ(result.units().size(), 1);
    EXPECT_EQ(result.units(), std::set<Unit>({Unit::m}));
}

TEST(PhysicsQuantity, AddTwoQuantitiesDifferentUnitsComplex) {
    PhysicsQuantity<Complex> quantity1(Complex(10, 20), Unit::m);
    PhysicsQuantity<Complex> quantity2(Complex(20, 30), Unit::s);
    
    EXPECT_THROW(quantity1 + quantity2, std::invalid_argument);
}

TEST(PhysicsQuantity, AddingDoubleToQuantityComplex) {
    PhysicsQuantity<Complex> quantity1(Complex(10, 20), Unit::m);
    Complex quantity2 = 20;
    
    EXPECT_THROW(quantity1 + quantity2, std::invalid_argument);
}

TEST(PhysicsQuantity, SubtractTwoQuantitiesComplex) {
    PhysicsQuantity<Complex> quantity1(Complex(10, 20), Unit::m);
    PhysicsQuantity<Complex> quantity2(Complex(20, 30), Unit::m);

    PhysicsQuantity<Complex> result = quantity1 - quantity2;
    
    EXPECT_EQ(result.value(), Complex(-10, -10));
    EXPECT_EQ(result.units().size(), 1);
    EXPECT_EQ(result.units(), std::set<Unit>({Unit::m}));
}

TEST(PhysicsQuantity, SubtractTwoQuantitiesDifferentUnitsComplex) {
    PhysicsQuantity<Complex> quantity1(Complex(10, 20), Unit::m);
    PhysicsQuantity<Complex> quantity2(Complex(20, 30), Unit::s);
    
    EXPECT_THROW(quantity1 - quantity2, std::invalid_argument);
}

TEST(PhysicsQuantity, SubtractDoubleFromQuantityComplex) {
    PhysicsQuantity<Complex> quantity1(Complex(10, 20), Unit::m);
    Complex quantity2(20, 0);
    
    EXPECT_THROW(quantity1 - quantity2, std::invalid_argument);
}

TEST(PhysicsQuantity, MultiplyTwoQuantitiesComplex) {
    PhysicsQuantity<Complex> quantity1(Complex(10, 20), Unit::m);
    PhysicsQuantity<Complex> quantity2(Complex(20, 30), Unit::s);

    PhysicsQuantity<Complex> result = quantity1 * quantity2;
    
    EXPECT_EQ(result.value(), Complex(-400, 700));
    EXPECT_EQ(result.units().size(), 2);
    EXPECT_EQ(result.units(), std::set<Unit>({Unit::m, Unit::s}));
}

TEST(PhysicsQuantity, MultiplyByScalarComplex) {
    PhysicsQuantity<Complex> quantity1(Complex(10, 20), Unit::m);
    double quantity2 = 20;

    PhysicsQuantity<Complex> result = quantity1 * quantity2;

    EXPECT_EQ(result.value(), Complex(200, 400));
    EXPECT_EQ(result.units().size(), 1);
    EXPECT_EQ(result.units(), std::set<Unit>({Unit::m}));
}

TEST(PhysicsQuantity, DivideTwoQuantitiesComplex) {
    PhysicsQuantity<Complex> quantity1(Complex(10, 20), Unit::m);
    PhysicsQuantity<Complex> quantity2(Complex(20, 30), Unit::s);

    PhysicsQuantity<Complex> result = quantity1 / quantity2;

    EXPECT_EQ(result.value(), Complex(8./13, 1./13));
    EXPECT_EQ(result.units().size(), 2);
    EXPECT_EQ(result.units(), std::set<Unit>({Unit::m, Unit(Unit::s,-1)}));
}   

TEST(PhysicsQuantity, DivideByScalarComplex) {
    PhysicsQuantity<Complex> quantity1(Complex(10, 20), Unit::m);
    double quantity2 = 20;

    PhysicsQuantity<Complex> result = quantity1 / quantity2;

    EXPECT_EQ(result.value(), Complex(0.5, 1));
    EXPECT_EQ(result.units().size(), 1);
    EXPECT_EQ(result.units(), std::set<Unit>({Unit(Unit::m)}));
}

TEST(PhysicsQuantity, UnaryMinusComplex) {
    PhysicsQuantity<Complex> quantity1(Complex(10, 20), Unit::m);

    PhysicsQuantity<Complex> result = -quantity1;

    EXPECT_EQ(result.value(), Complex(-10, -20));
    EXPECT_EQ(result.units().size(), 1);
    EXPECT_EQ(result.units(), std::set<Unit>({Unit::m}));
}

TEST(PhysicsQuantity, PrintQuantityComplex) {
    PhysicsQuantity<Complex> quantity1(Complex(10, 20), Unit::m);

    std::string result = quantity1.toString();

    EXPECT_EQ(result, "(10,20) m");
}


// Write a test for a 3rd power of a quantity 5.6 m^2/s^3
/* TEST(PhysicsQuantity, PowerOfQuantity) {
    PhysicsQuantity<double> quantity1(5.6, std::set<Unit>({Unit(Unit::m, 2), Unit(Unit::s, 3)}));

    PhysicsQuantity<double> result = std::pow(quantity1, 3);

    EXPECT_EQ(result.value(), 175.616);
    EXPECT_EQ(result.units().size(), 5);
    EXPECT_EQ(result.units(), std::set<Unit>({Unit::m, Unit::m, Unit::m, Unit::s, Unit::s, Unit::s}));
} */