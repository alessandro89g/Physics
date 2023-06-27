#ifndef FOURMOMENTUM_HPP
#define FOURMOMENTUM_HPP

#include "vector4.hpp"

class Matrix4;

class FourMomentum : public Vector4
{
public:
    FourMomentum();
    FourMomentum(const vector<double>& vec4, State state = Contravariant);
    FourMomentum(double M, const Vector3& vec3, State state = Contravariant);

    Vector4 fourVelocity() const;

    FourMomentum operator + (const FourMomentum& o) const;
    FourMomentum operator - (const FourMomentum& o) const;
    FourMomentum operator -() const;

    double velocity() const;
    double LorentzGamma() const;
    Matrix4 LorentzBoost() const;

    double norm4() const override;

    double energy() const;

private:
};

#endif // FOURMOMENTUM_HPP
