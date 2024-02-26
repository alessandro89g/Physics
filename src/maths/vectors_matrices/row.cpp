#include "../../../include/maths/vectors_matrices/row.hpp"
#include "../../../include/maths/vectors_matrices/column.hpp"


Row::Row(int cols) {
    m_cols = cols;
    m_rows = 1;
    createMatrix();
}

Row::Row(const vector<double> &vec) {
    if (vec.size()==0)
        return;
    vector<vector<double>> v;
    v.push_back(vec);
    m_cols = vec.size();
    m_rows = 1;

    createMatrix();

    for (int i=0; i<m_cols; i++)
        m_matrix[0][i] = vec[i];

}

Row Row::operator *(const Matrix &m) {
    if (m_cols!=m.rows())
        abort();
    Row a(m.cols());
    for (int i=0; i<m_cols; i++)
        for (int j=0; j<m.cols(); j++)
            a[j] += m_matrix[0][i]*m[i][j];
    return a;
}

double Row::operator *(const Column &c) {
    if (m_cols!=c.size())
        abort();
    double sum = 0;
    for (int i=0; i<m_cols; i++)
        sum+= m_matrix[0][i]*c[i];
    return sum;
}

Column Row::transpose() const {
    Column a(m_cols);
    for (int i=0; i<m_cols; i++)
        a[i] = m_matrix[0][i];
    return a;
}

const double &Row::operator[](int index) const {
    return m_matrix[0][index];
}

Row Row::operator-() const {
    Row r = (*this);
    for (int i=0; i<m_cols; i++)
        r[i] *= -1;
    return r;
}

bool Row::operator <(const Row &other) const {
    if (m_cols!=other.size())
        abort();
    for (int i=0; i<m_cols; i++) {
        if ((*this)[i]!=0 || other[i]!=0) {
            if ((*this)[i]!=0 && other[i]!=0)
                return (*this)[i] < other[i];
            else if (other[i]==0)
                return false;
            else
                return true;
        }
    }
    return false;
}

bool Row::operator >(const Row &other) const {
    return !(*this < other);
}

bool Row::operator ==(const Row &other) const {
    if (m_cols!=other.size())
        abort();
    for (int i=0; i<m_cols; i++)
        if((*this)[i]!=other[i])
            return false;
    return true;

}

bool Row::operator !=(const Row &other) const {
    return !((*this)==other);
}

pivot Row::getPivot() const {
    for (int i=0; i<m_cols; i++)
        if (m_matrix[0][i]!=0)
            return {i,m_matrix[0][i]};
    return {0,0};
}

int Row::size() const {
    return m_cols;
}

double &Row::operator[](int index) {
    return m_matrix[0][index];
}
