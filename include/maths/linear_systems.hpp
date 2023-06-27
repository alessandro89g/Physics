#ifndef LINEARSYSTEMS_HPP
#define LINEARSYSTEMS_HPP

#include "matrix.hpp"

Matrix solveLinearSystem(const Matrix &A, const Matrix &C) {
    Matrix res = A.inverseMatrix()*C;
    return res;
}

#endif // LINEARSYSTEMS_HPP
