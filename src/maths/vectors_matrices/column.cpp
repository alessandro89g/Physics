#include "../../../include/maths/vectors_matrices/column.hpp"
#include "../../../include/maths/vectors_matrices/row.hpp"
#include "../../../include/maths/vectors_matrices/matrix.hpp"

Column::Column(int rows) {
    m_rows = rows;
    m_cols = 1;
    createMatrix();
}

Column::Column(vector<double> vec) {
    m_rows = vec.size();
    m_cols = 1;

    createMatrix();

    for (int i=0; i<m_rows; i++)
        m_matrix[i][0] = vec[i];
}

Row Column::transpose() const {
    Row c(m_rows);
    for (int i=0; i<m_rows; i++)
        c[i] = m_matrix[i][0];

    return c;
}

const double &Column::operator[](int index) const {
    return m_matrix[index][0];
}

int Column::size() const {
    return m_rows;
}

double &Column::operator[](int index) {
    return m_matrix[index][0];
}
