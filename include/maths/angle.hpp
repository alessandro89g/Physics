#ifndef ANGLE_HPP
#define ANGLE_HPP

#include <cmath>

class Angle {
public:
    Angle() : m_rad(0) {
    }
    Angle(double angle_rad) : m_rad(angle_rad) {
    }
    Angle(const Angle& angle) = default;
    Angle(Angle&& angle) = default;

    static double Pi() {
        return pi;
    }

    static double AngletoDegree(const Angle& angle) {
        return angle.toDeg();
    }

    static Angle AnglefromDegree(double angleDeg) {
        return Angle(angleDeg*Angle::Pi()/180);
    }

    operator double () const {
        return m_rad;
    }
    double toDeg() const  {
        return m_rad*180./pi;
    }

private:
    double m_rad;
    constexpr static double pi = 3.141592653589793;
};



#endif // ANGLE_HPP
