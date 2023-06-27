#include "matrix4.hpp"

Matrix4::Matrix4() : Matrix(4) {}

Matrix4::Matrix4(const Vector4 &v41, const Vector4 &v42) : Matrix(4) {
    m_index1 = v41.state();
    m_index2 = v42.state();
    for (int i=0; i<4; i++)
        for(int j=0; j<4; j++)
            (*this)[i][j] = v41[i]*v42[j];
}

Matrix4::Matrix4(const Matrix &m) : Matrix(m) {
    m_index1 = Vector4::Contravariant;
    m_index2 = Vector4::Contravariant;
}

Matrix4 Matrix4::metricTensor() {
    Matrix4 g;
    g.setIndex(Vector4::Covariant);

    for (int i=0; i<4; i++)
        g[i][i] = (i==0 ? 1 : -1);
    return g;
}

Matrix4 Matrix4::identityMatrix() {
    return Matrix::identityMatrix(4);
}

void Matrix4::setIndex(int index, Vector4::State state) {
    if (index !=1 && index!=2)
        abort();
    if (index==1)
        m_index1 = state;
    else
        m_index2 = state;
}

void Matrix4::setIndex(Vector4::State state) {
    setIndex(1,state);
    setIndex(2,state);
}

void Matrix4::lowerIndex(int index) {
    if (index!=1 && index !=2)
        abort();
    if (index==1) {
        if (m_index1==Vector4::Covariant)
            return;
        for (int i=1; i<4; i++)
            for(int j=0; j<4; j++)
                (*this)[i][j]*=(-1);
        m_index1 = Vector4::Covariant;
    }
    else {
        if (m_index2==Vector4::Covariant)
            return;
        for (int i=0; i<4; i++)
            for(int j=1; j<4; j++)
                (*this)[i][j]*=(-1);
        m_index2 = Vector4::Covariant;
    }
}

void Matrix4::raiseIndex(int index) {
    if (index!=1 && index !=2)
        abort();
    if (index==1) {
        if (m_index1==Vector4::Contravariant)
            return;
        for (int i=1; i<4; i++)
            for(int j=0; j<4; j++)
                (*this)[i][j]*=(-1);
        m_index1 = Vector4::Contravariant;
    }
    else {
        if (m_index2==Vector4::Contravariant)
            return;
        for (int i=0; i<4; i++)
            for(int j=1; j<4; j++)
                (*this)[i][j]*=(-1);
        m_index2 = Vector4::Contravariant;
    }
}

void Matrix4::lowerIndex() {
    lowerIndex(1);
    lowerIndex(2);
}

void Matrix4::raiseIndex() {
    raiseIndex(1);
    raiseIndex(2);
}

void Matrix4::indexesState() const {
    cout << "( ";
    if (m_index1==Vector4::Covariant)
        cout << "COVARIANT , ";
    else
        cout << "CONTRAVARIANT , ";
    if (m_index2==Vector4::Covariant)
        cout << "COVARIANT )";
    else
        cout << "CONTRAVARIANT )";
    cout << '\n';
}

Vector4 Matrix4::operator *(Vector4 v) const {
    Vector4 r;
    if (m_index2==v.state()){
        if (v.state()==Vector4::Contravariant)
            v.setState(Vector4::Covariant);
        else
            v.setState(Vector4::Contravariant);
    }

    for (int i=0; i<4; i++)
        for(int j=0; j<4;j++)
            r[i] += (*this)[i][j]*v[j];

    r.setState(m_index1);
    return r;
}

int Matrix4::size() const {
    return 4;
}
