#ifndef VECTOR3_HPP
#define VECTOR3_HPP
#include "row.hpp"
#include "math.h"
#include "angle.hpp"
#include "numerics.hpp"


class Vector3 : public Row
{
public:
    Vector3();
    Vector3(const vector<double>& v);
    Vector3(const Row& row);


    double norm() const;

    double thetaDeg() const;
    double phiDeg() const;

    int size();

    const double &operator[] (int index) const;
    double &operator[] (int index);
    double operator * (const Vector3& other) const;
    Vector3 operator ^(const Vector3 &other) const {
        return Numerics::crossProduct(*this,other);
    }
    Vector3 direction() const;
protected:
};

#endif // VECTOR3_HPP
