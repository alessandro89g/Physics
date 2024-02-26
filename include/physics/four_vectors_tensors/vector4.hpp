#ifndef VECTOR4_HPP
#define VECTOR4_HPP
#include "../../../include/maths/vectors_matrices/row.hpp"

class Vector3;

class Vector4 : public Row
{
public:
    enum State {Contravariant, Covariant};
    Vector4();
    Vector4(const vector<double>& vec4, State m_state = Contravariant);
    Vector4(const Row& row, State state = Contravariant);
    Vector4(const Column& col, State state = Contravariant);

    double energy() const;

    double &operator[] (int index);
    const double &operator[] (int index) const;
    double operator * (const Vector4& other) const;

    double norm() const;
    virtual double norm4() const;

    Vector3 direction() const;
    Vector3 vector3() const;

    double thetaDeg() const;

    double phiDeg() const;

    State state() const;
    void setState(State state);
    void lowerIndex();
    void raiseIndex();

    int size();

protected:
    State m_state = Contravariant;
};

#endif // VECTOR4_HPP
