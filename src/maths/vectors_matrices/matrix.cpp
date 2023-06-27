#include "matrix.hpp"
#include "row.hpp"
#include "column.hpp"

Matrix::Matrix(): m_rows(0), m_cols(0), m_line_matrix(nullptr), m_matrix(nullptr)
{

}

Matrix::Matrix(int dim) : m_rows(dim), m_cols(dim), m_line_matrix(nullptr), m_matrix(nullptr)
{
    createMatrix();
}

Matrix::Matrix(int rows, int cols) : m_rows(rows), m_cols(cols), m_line_matrix(nullptr), m_matrix(nullptr){
    createMatrix();
}

Matrix::Matrix(const vector<vector<double> > &matrix) : m_rows(matrix.size())
            , m_line_matrix(nullptr), m_matrix(nullptr) {
    if (matrix.size()==0)
        return;

    m_cols = matrix[0].size();

    int row=0;
    int col;

    createMatrix();

    for(const vector<double>& v : matrix) {
        col = 0;
        for (double el : v){
            m_matrix[row][col] = el;
            col++;
        }
        row++;
    }
}

Matrix::~Matrix() {
    deleteMatrix();
}

Matrix::Matrix(const Matrix &other) : m_rows(other.m_rows), m_cols(other.m_cols)
    , m_line_matrix(nullptr), m_matrix(nullptr)
{
    createMatrix();
    copyMatrix(other.m_matrix, m_rows, m_cols);
}

Matrix::Matrix(Matrix &&other) : m_rows(other.m_rows), m_cols(other.m_cols),
    m_matrix(other.m_matrix), m_line_matrix(other.m_line_matrix)
{
    other.m_line_matrix = nullptr;
    other.m_matrix = nullptr;
}

void Matrix::print() const {
    cout << "===========================" << endl;
    for (int i=0; i<m_rows; i++){
        for (int j=0; j<m_cols; j++)
            cout << m_matrix[i][j] << "  ";
        cout << endl;
    }
    cout << "===========================" << endl;
}

double *&Matrix::operator [](int index) const {
    return m_matrix[index];
}

Matrix Matrix::operator *=(double val)
{
    for (int i=0; i< m_rows; ++i)
        for(int j=0; j<m_cols; ++j)
            m_matrix[i][j] = m_matrix[i][j] * val;
    return *this;
}

Column Matrix::operator *(const Column &c) {
    if (m_cols!=c.size())
        abort();
    Column res(m_rows);

    for (int i=0; i< m_rows; i++)
        for (int j=0; j< c.size(); j++)
            res[i] += m_matrix[i][j]*c[j];
    return res;
}

Matrix Matrix::operator *(double val) const {
    Matrix res = *this;
    res *= val;
    return res;
}

Matrix Matrix::operator +=(const Matrix &other) {
    checkSize(other);
    for (int i = 0; i < m_rows; ++i)
        for(int j=0; j<m_cols; ++j)
            m_matrix[i][j] += other.m_matrix[i][j];
    return *this;
}



Matrix Matrix::operator *(const Matrix& other) const {
    if (m_cols != other.m_rows)
        abort();

    Matrix res(m_rows,other.m_cols);

    for (int i = 0; i < m_rows; ++i) {
        for (int k = 0; k < other.m_rows; ++k) {
            res[i][k] = 0;
            for (int j = 0; j < m_cols; ++j) {
                res[i][k] += m_matrix[i][j]*other[j][k];
            }
        }
    }
    return res;
}

Matrix Matrix::operator +(const Matrix& other) const
{
    checkSize(other);

    Matrix res = *this;
    for(int i=0; i<m_rows; i++)
        for(int j=0; j< m_cols; j++)
            res[i][j] += other[i][j];
    return res;
}

Matrix Matrix::operator -=(const Matrix &other) {
    checkSize(other);
    for (int i = 0; i < m_rows; ++i)
        for(int j=0; j<m_cols; ++j)
            m_matrix[i][j] -= other.m_matrix[i][j];
    return *this;
}

Matrix Matrix::operator - (const Matrix& other) const {
    checkSize(other);

    Matrix res = other*(-1);
    res = res + (*this);
    return res;
}

Matrix Matrix::operator /=(double val)
{
    for (int i = 0; i < m_rows; ++i)
        for(int j=0; j<m_cols; ++j)
            m_matrix[i][j]/= val;
    return *this;
}

Matrix Matrix::operator /(double val) const
{
    Matrix res = *this;

    for (int i=0; i< m_rows; ++i)
        for(int j=0; j<m_cols; ++j)
            res.m_matrix[i][j] /= val;
    return res;
}

Matrix& Matrix::operator =(const Matrix &other)
{
    m_rows = other.m_rows;
    m_cols = other.m_cols;
    createMatrix();
    copyMatrix(other.m_matrix, m_rows, m_cols);
    return *this;
}

bool Matrix::operator ==(const Matrix &other) const {
    checkSize(other);
    for (int i=0; i< m_rows; ++i)
        for(int j=0; j<m_cols; ++j)
            if (m_matrix[i][j] != other.m_matrix[i][j])
                return false;
    return true;
}

bool Matrix::sameSize(const Matrix &other) const {
    if (m_cols!=other.m_cols || m_rows!=m_rows)
        return false;
    return true;
}

double **Matrix::getMatrix() {
    return m_matrix;
}

int Matrix::rows() const
{
    return m_rows;
}

void Matrix::setRows(int newRows)
{
    deleteMatrix();
    m_rows = newRows;
    createMatrix();
}

int Matrix::cols() const
{
    return m_cols;
}

void Matrix::setCols(int newCols)
{
    deleteMatrix();
    m_cols = newCols;
    createMatrix();
}

void Matrix::exchangeRows(size_t row1, size_t row2) {
    for (int i=0; i< m_cols; i++) {
        double t = m_matrix[row2][i];
        m_matrix[row2][i] = m_matrix[row1][i];
        m_matrix[row1][i] = t;
    }
}

void Matrix::exchangeCols(size_t col1, size_t col2) {
    for (int i=0; i< m_rows; i++) {
        double t = m_matrix[i][col2];
        m_matrix[i][col2] = m_matrix[i][col1];
        m_matrix[i][col1] = t;
    }
}

Matrix Matrix::transpose() const {
    Matrix a(m_cols, m_rows);
    for (int i=0; i<a.rows(); i++)
        for (int j=0; j<a.cols(); j++) {
            a.m_matrix[i][j] = m_matrix[j][i];
        }
    return a;
}

Row Matrix::rowAt(int index) const {
    Row r(m_cols);
    for (int i=0; i<m_cols; i++)
        r[i] = m_matrix[index][i];
    return r;
}

Column Matrix::colAt(int index) const {
    Column c(m_rows);
    for (int i=0; i<m_rows; i++)
        c[i] = m_matrix[i][index];
    return c;
}

Matrix Matrix::identityMatrix(int size) {
    if (size<=0)
        abort();
    Matrix id(size);
    for (int i=0; i<size; i++)
        id[i][i] = 1;
    return id;

}

void Matrix::orderMatrix() {
    int n = m_rows;
    bool swapped;

    for (int i = 0; i < n - 1; ++i) {
        swapped = false;

        for (int j = 0; j < n - i - 1; ++j) {
            if (rowAt(j) < rowAt(j + 1)) {
                exchangeRows(j,j+1);
                swapped = true;
            }
        }
        if (!swapped)
            break;
    }
}

void Matrix::deleteMatrix()
{
    if (m_line_matrix!=nullptr)
        delete[] m_line_matrix;
    if (m_matrix!=nullptr)
        delete[] m_matrix;
}

void Matrix::createMatrix() {
    if (m_line_matrix!=nullptr)
        deleteMatrix();

    m_line_matrix = new double[m_rows*m_cols];
    m_matrix = new double*[m_rows];

    for (int i=0; i<m_rows*m_cols; i++)
        m_line_matrix[i] = 0;

    for (int i=0; i<m_rows; i++)
        m_matrix[i] = m_line_matrix + m_cols*i;

}

void Matrix::copyMatrix(double **matrix, int rows, int cols)
{
    for (int i=0; i< rows; ++i)
        for(int j=0; j<cols; ++j)
            m_matrix[i][j] = matrix[i][j];
}

void Matrix::checkSize(const Matrix &other) const {
    if (!sameSize(other))
        abort();
}




Matrix Matrix::inverseMatrix() const {
    //Preparing the matrix
    if (this->cols()<1)
        return Matrix();
    Matrix i3 = Matrix::identityMatrix(this->cols());
    Matrix t(m_rows,2*m_cols);
//    t.print();
    for (int i=0; i<t.rows(); i++)
        for (int j=0; j< t.cols(); j++)
            if (j<t.cols()/2)
                t[i][j] = m_matrix[i][j];
            else
                t[i][j] = i3[i][j-t.cols()/2];

    //Ordering the rows
    t.orderMatrix();


    //Going down
    for (int i=0; i<t.rows(); ++i) {
        pivot pi = t.rowAt(i).getPivot();
        for (int j=i+1; j<t.rows(); j++) {
            double pj = -t[j][pi.index];
            if (pj!=0)
                for (int k=0; k<t.cols(); ++k)
                    t[j][k] = t[i][k]*pj + t[j][k]*pi.val;
        }
    }

    //Going up
    for (int i=t.rows()-1; i>0; --i) {
        double pi = t[i][i];
        for (int j=i-1; j>=0; --j) {
            double pj = t[j][i];
            for (int k=0; k<t.cols(); ++k)
                t[j][k] = t[j][k]*pi-t[i][k]*pj;
        }
    }

    //Normalizing
    for (int i=0; i<t.rows(); i++){
        double pi = t[i][i];
        for (int j=0; j<t.cols(); j++)
            t[i][j]/=pi;
    }

    Matrix inverse(m_rows, m_cols);
    for (int i=0; i<m_rows; i++)
        for (int j=0; j<m_rows; j++)
            inverse[i][j] = t[i][j+m_cols];

    return inverse;
}

void Matrix::invert() {
    Matrix inv = inverseMatrix();
    *this = move(inv);
}
