#include "unitvector.hpp"

UnitVector::UnitVector(const Vector3 &vector) {
    Vector3 v(vector.direction());
    for (int i=1; i<4; i++)
        (*this)[i] = v[i];
}
