#ifndef ANGLE_HPP
#define ANGLE_HPP

#include <cmath>

class Angle {
public:
    Angle();
    Angle(double angle_rad);
    Angle(const Angle& angle) = default;
    Angle(Angle&& angle) = default;

    inline operator double () const {
        return m_rad;
    }
    inline double toDeg() const {
        return m_rad*180./pi;
    }

    static inline double Pi() {
        return pi;
    }

    static inline double AngletoDegree(const Angle& angle) {
        return angle.toDeg();
    }

    static Angle AnglefromDegree(double angleDeg) {
        return Angle(angleDeg*Angle::Pi()/180);
    }

private:
    double m_rad;
    constexpr static double pi = 3.141592653589793;
};



#endif // ANGLE_HPP
