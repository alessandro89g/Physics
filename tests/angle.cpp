#include <gtest/gtest.h>
#include "../include/maths/angle.hpp"

TEST(Angle, DefaultConstructor) {
    Angle a;
    EXPECT_EQ(a, 0);
}

TEST(Angle, Constructor) {
    Angle a(3.14);
    EXPECT_EQ(a, 3.14);
}

TEST(Angle, CopyConstructor) {
    Angle a(3.14);
    Angle b(a);
    EXPECT_EQ(b, 3.14);
}

TEST(Angle, MoveConstructor) {
    Angle a(3.14);
    Angle b(std::move(a));
    EXPECT_EQ(b, 3.14);
}

TEST(Angle, Pi) {
    EXPECT_EQ(Angle::Pi(), 3.141592653589793);
}

TEST(Angle, AngletoDegree) {
    Angle a(4*atan(1.0));
    EXPECT_EQ(Angle::AngletoDegree(a), 180);
}

TEST(Angle, AnglefromDegree) {
    Angle a = Angle::AnglefromDegree(180);
    EXPECT_EQ(a, 3.141592653589793);
}

TEST(Angle, toDeg) {
    Angle a(4*atan(1.0));
    EXPECT_EQ(a.toDeg(), 180);
}

TEST(Angle, Conversion) {
    Angle a(3.14);
    double b = a;
    EXPECT_EQ(b, 3.14);
}

TEST(Angle, PiConst) {
    Angle a;
    EXPECT_EQ(a.Pi(), 3.141592653589793);
}

TEST(Angle, AngletoDegreeConst) {
    Angle a(4*atan(1.0));
    EXPECT_EQ(a.AngletoDegree(a), 180);
}

TEST(Angle, AnglefromDegreeConst) {
    Angle a = a.AnglefromDegree(180);
    EXPECT_EQ(a, 3.141592653589793);
}

TEST(Angle, toDegConst) {
    Angle a(4*atan(1.0));
    EXPECT_EQ(a.toDeg(), 180);
}
