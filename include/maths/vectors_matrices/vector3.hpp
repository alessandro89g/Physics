#ifndef VECTOR3_HPP
#define VECTOR3_HPP
#include "row.hpp"
#include "math.h"
#include "angle.hpp"


class Vector3 : public Row
{
public:
    Vector3();
    Vector3(const vector<double>& v);
    Vector3(const Row& row);

    double &operator[] (int index);
    const double &operator[] (int index) const;
    double operator * (const Vector3& other) const;

    double norm() const;
    Vector3 direction() const;

    double thetaDeg() const;
    double phiDeg() const;

    int size();

protected:
};

#endif // VECTOR3_HPP
