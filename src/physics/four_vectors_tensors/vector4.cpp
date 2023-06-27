#include "vector4.hpp"
#include "column.hpp"
#include "vector3.hpp"

Vector4::Vector4() : Row(4)
{}

Vector4::Vector4(const vector<double> &vec4, State m_state) : Row(vec4), m_state(m_state) {
    if (vec4.size()!=4)
        abort();
    for (int i=0; i<4; i++)
        (*this)[i] = vec4[i];
}

Vector4::Vector4(const Row &row, State state) : Row(row), m_state(state) {
    if (row.size()!=4)
        abort();
}

Vector4::Vector4(const Column &col, State state) : Row(col.transpose()), m_state(state) {
    if (m_cols!=4)
        abort();
}

double Vector4::energy() const {
    return m_line_matrix[0];
}

double &Vector4::operator[](int index) {
    return m_matrix[0][index];
}

const double &Vector4::operator[](int index) const {
    return m_matrix[0][index];
}

double Vector4::norm() const {
    double sum = 0;
    for(int i=1; i<=3; i++)
        sum += (*this)[i]*(*this)[i];
    return sqrt(sum);
}

double Vector4::norm4() const {
    return sqrt((*this)*(*this));
}


Vector3 Vector4::direction() const {
    Vector3 v;
    for(int i=1; i<=3; i++) {
        v[i] = (*this)[i]/norm();
    }
    return v;
}

Vector3 Vector4::vector3() const {
    Vector3 v3;
    for (int i=1; i<4; i++)
        v3[i] = (*this)[i];
    return v3;
}

double Vector4::thetaDeg() const {
    double z_over_r = (*this)[3]/norm();
    if (abs(z_over_r)==1)
        if (z_over_r==1)
            return 0;
        else
            return 180;
    return acos(z_over_r)/acos(-1.)*180.;
}

double Vector4::phiDeg() const {
    double x = (*this)[1];
    double y = (*this)[2];
    if (x==0)
        return (y==0 ? 0 : 180);
    return atan(y/x)/acos(-1.)*180;
}

Vector4::State Vector4::state() const {
    return m_state;
}

void Vector4::setState(State state) {
    m_state = state;
}

void Vector4::lowerIndex() {
    if (Covariant==m_state)
        return;
    for (int i=1;i<4;i++)
        (*this)[i]*= -1;
    m_state = Covariant;
}

void Vector4::raiseIndex() {
    if (Contravariant==m_state)
        return;
    for (int i=1;i<4;i++)
        (*this)[i]*= -1;
    m_state = Contravariant;
}

int Vector4::size() {
    return 4;
}

double Vector4::operator *(const Vector4 &other) const {
    double sp = 0;
    if (m_state==other.state()) {
        for (int i=0; i<4; i++)
            sp += (*this)[i]*(i==0 ? 1 : -1)*other[i];
    }
    else {
        for (int i=0; i<4; i++)
            sp += (*this)[i]*other[i];
    }
    return sp;
}
