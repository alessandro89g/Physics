#include "vector3.hpp"

Vector3::Vector3(): Row(3) {}

Vector3::Vector3(const vector<double> &v) : Row(v) {
    if (v.size()!=3)
        abort();
}

Vector3::Vector3(const Row &row) : Row(row) {
    if (row.size()!=3)
        abort();
}


const double &Vector3::operator[](int index) const {
    return m_matrix[0][index-1];
}

double Vector3::norm() const {
    double sum = (*this)*(*this);
    return sqrt(sum);
}

Vector3 Vector3::direction() const {
    Vector3 v(*this);
    for(int i=1; i<=3; i++) {
        v[i]/=norm();
    }
    return v;
}

double Vector3::thetaDeg() const {
    double z_over_r = (*this)[3]/norm();
    if (abs(z_over_r)==1)
        if (z_over_r==1)
            return 0;
        else
            return 180;
    return acos(z_over_r)/acos(-1.)*180.;
}

double Vector3::phiDeg() const {
    double x = (*this)[1];
    double y = (*this)[2];
    if (x==0)
        return (y==0 ? 0 : 180);
    return atan(y/x)/acos(-1.)*180;
}

int Vector3::size() {
    return 3;
}

double Vector3::operator *(const Vector3 &other) const {
    double sum = 0;
    for (int i = 1; i <=3; ++i) {
        sum += (*this)[i]*other[i];
    }
    return sum;
}

double &Vector3::operator[](int index) {
    return m_matrix[0][index-1];
}
