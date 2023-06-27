#ifndef UNITVECTOR_H
#define UNITVECTOR_H

#include "vector3.hpp"

class UnitVector : public Vector3
{
public:
    UnitVector() = delete;
    UnitVector(const Vector3& vector);
};

#endif // UNITVECTOR_H
