#ifndef ROW_HPP
#define ROW_HPP

#include "matrix.hpp"

class Column;
struct pivot;

class Row : public Matrix
{
public:
    Row() = delete;
    Row(int cols);
    Row(const vector<double>& vec);

    void exchangeRows() = delete;
    double operator * (const Row& r) = delete;
    double operator * (const Column& c);
    Row operator * (const Matrix& m);
    double &operator[] (int index);
    const double &operator[] (int index) const;
    Row operator-() const;
    Column transpose() const;

    bool operator < (const Row& other) const;
    bool operator > (const Row& other) const;
    bool operator == (const Row& other) const;
    bool operator != (const Row& other) const;

    pivot getPivot() const;

    int cols() const = delete;
    int rows() const = delete;
    int size() const;
};

#endif // ROW_HPP
