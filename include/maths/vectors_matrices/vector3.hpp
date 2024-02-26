#ifndef VECTOR3_HPP
#define VECTOR3_HPP
#include <cmath>
#include "../../../include/maths/vectors_matrices/row.hpp"
#include "../../../include/maths/angle.hpp"
#include "../../../include/maths/numerics.hpp"


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
