#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <iostream>
#include <malloc.h>
#include <vector>

using namespace std;

class Column;
class Row;

struct pivot {
    int index;
    double val;
};

class Matrix
{
public:
    Matrix();
    Matrix(int dim);
    Matrix(int rows, int cols);
    Matrix(const vector<vector<double>>& matrix);
    ~Matrix();

    Matrix(const Matrix& other);
    Matrix(Matrix&& other);

    void print() const;

    double * & operator [] (int index) const;


    Matrix operator *= (double val);
    Matrix operator * (const Matrix& other) const;
    Matrix operator * (double val) const;
    Column operator *(const Column& c);
    Matrix operator += (const Matrix& other);
    Matrix operator + (const Matrix& other) const;
    Matrix operator -= (const Matrix& other);
    Matrix operator - (const Matrix& other) const;
    Matrix operator /= (double val);
    Matrix operator / (double val) const;
    Matrix &operator =(const Matrix& other);
    bool operator == (const Matrix& other) const;


    bool sameSize(const Matrix& other) const;
    double **getMatrix();

    int rows() const;
    void setRows(int newRows);

    int cols() const;
    void setCols(int newCols);

    void exchangeRows(size_t row1, size_t row2);
    void exchangeCols(size_t col1, size_t col2);
    Matrix transpose() const;

    Row rowAt(int index) const;
    Column colAt(int index) const;

    static Matrix identityMatrix (int size);

    void orderMatrix();
    Matrix inverseMatrix() const;
    void invert();

    operator double** () {
        return m_matrix;
    }

protected:
    int m_rows;
    int m_cols;
    double *m_line_matrix;
    double **m_matrix;

protected:
    void createMatrix();
    void deleteMatrix();
    void copyMatrix(double **matrix, int rows, int cols);
    void checkSize(const Matrix& other) const;
};

#endif // MATRIX_HPP
