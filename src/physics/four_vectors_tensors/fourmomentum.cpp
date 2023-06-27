#include "fourmomentum.hpp"
#include "matrix4.hpp"
#include "vector3.hpp"

FourMomentum::FourMomentum()
{

}

FourMomentum::FourMomentum(const vector<double> &vec4, State state)
{
    m_state = state;
    for (int i=0; i<4; i++)
        (*this)[i] = vec4[i];
}

FourMomentum::FourMomentum(double M, const Vector3 &vec3, State state) {
    m_state = state;
    for (int i=1; i<4; i++)
        (*this)[i] = vec3[i];
    (*this)[0] = sqrt(M*M+norm()*norm());
}

Vector4 FourMomentum::fourVelocity() const {
    Vector4 fv;
    for (int i=0; i<4; i++)
        fv[i] = (*this)[i]/energy();
    return fv;
}

FourMomentum FourMomentum::operator +(const FourMomentum &o) const {
    FourMomentum r(*this);
    for (int i=0; i<4;i++)
        r[i]+= o[i];
    return r;
}

FourMomentum FourMomentum::operator -() const {
    FourMomentum r(*this);
    for (int i=0; i<4;i++)
        r[i]*= -1;
    return r;
}

FourMomentum FourMomentum::operator -(const FourMomentum &o) const {
    FourMomentum r(*this);
    for (int i=0; i<4;i++)
        r[i]+= -o[i];
    return r;
}

double FourMomentum::velocity() const {
    return fourVelocity().vector3().norm();
}

double FourMomentum::LorentzGamma() const {
    double v = velocity();
    return pow(1/(1-v*v),0.5);
}

Matrix4 FourMomentum::LorentzBoost() const {
    double v = velocity();
    if (v==0)
        return Matrix4::identityMatrix();

    Matrix4 b;
    Vector3 v3 = -fourVelocity().vector3();
    Matrix4 id = Matrix4::identityMatrix();
    double g = LorentzGamma();


    b[0][0] = g;
    for (int i=1; i<4; i++){
        b[0][i] = b[i][0] = -g*v3[i];

        for(int j=1; j<4; j++)
            b[i][j] = id[i][j] + (g-1)*v3[i]*v3[j]/pow(v,2);
    }
    return b;
}

double FourMomentum::energy() const {
    return m_line_matrix[0];
}

double FourMomentum::norm4() const {
    return sqrt(energy()*energy()-norm()*norm());
}
