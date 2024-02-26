#ifndef DERIVATIVE_HPP
#define DERIVATIVE_HPP

#include <iostream>
#include <vector>
#include <cmath>
#include "../../include/maths/vectors_matrices/matrix.hpp"
#include "../../include/maths/vectors_matrices/column.hpp"
#include "../../include/maths/numerics.hpp"

namespace Numerics {
#define NMAX 200

using namespace std;


class Derivative {
public:
    static double derive(const std::vector<double>& vector, int position, int order, double step) {
//        cout << "aoisdoasijdoaij" << endl;
        ms_step = (ms_step == step? ms_step : step);
//        cout << "step  " << step << endl;
//        cout << "position  " << position << endl;
        int npoints = vector.size();
        findCoefficients(npoints);
//        ms_coefficients.print();

        Column fun(vector);
        Column res(ms_coefficients*fun);
        return res[order];
    }

private:
    Derivative() {
        ms_step = -1;
        for (int i = 0; i < NMAX; ++i) {
            for (int j = 0; j < NMAX; ++j) {
                ms_coefficients[i][j] = 0.;
            }
        }
    }
    Derivative(const Derivative&) = delete;
    Derivative(const Derivative&&) = delete;

    static void findCoefficients(int dim) {
        Matrix m(dim);
        for (int i = 0; i < dim; ++i) {
            for (int j = 0; j < dim; ++j) {
                if (j==0)
                    m[i][j] = 1;
                else {
                    m[i][j] = pow(i,j)/Numerics::factorial(j);
                }
            }
        }
//        m.print();
        m.invert();
        for (int i=0; i<m.rows(); i++)
            for (int j=0; j<m.cols(); j++)
                m[i][j] /= pow(ms_step,i);
//        m.print();
        ms_coefficients = move(m);
    }

private:
    static Matrix ms_coefficients;
    static double ms_step;
};
}


#endif // DERIVATIVE_HPP
