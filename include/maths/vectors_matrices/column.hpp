#ifndef COLUMN_HPP
#define COLUMN_HPP

#include "matrix.hpp"
#include "row.hpp"

class Row;

class Column : public Matrix
{
public:
    Column() = delete;
    Column(int rows);
    Column(vector<double> vec);

    void exchangeColumns() = delete;
    Row transpose() const;
    double &operator[] (int index);
    const double &operator[] (int index) const;

    int cols() const = delete;
    int rows() const = delete;
    int size() const;

};

#endif // COLUMN_HPP
