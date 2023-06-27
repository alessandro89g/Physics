#ifndef NUMERICS_HPP
#define NUMERICS_HPP

#include<iostream>
#include<math.h>
#include<vector>
#include "angle.hpp"
#include "function.hpp"
#include <functional>

class Vector3;
class Matrix;

#define NMAX 200

namespace Numerics {

    int LeviCivita(int i, int j, int k);
    Vector3 operator^ (const Vector3& v1, const Vector3& v2);
    Vector3 crossProduct (const Vector3& v1, const Vector3& v2);
    double scalarProduct (const Vector3& v1, const Vector3& v2);

    unsigned long factorial(int n);
    template<typename T>
    void swap(T& a, T& b) {
        T c = b;
        b = a;
        a = c;
    }

    template<typename F>
    double findZero(const F& fun, double kp) {
        double kp0 = kp;
        double de0 = (*fun)(kp0);

        double kp1 = kp*1.1;
        double de1 = (*fun)(kp1);

        do {
            kp = kp1 - de1*(kp1-kp0)/(de1-de0);
            double de = (*fun)(kp);
            if (abs(de1)<abs(de0)) {
                kp0 = kp1;
                de0 = de1;
            }
            kp1 = kp;
            de1 = de;

        } while(abs(de1)>1.e-9);
        return kp1;
    }


    double NumerovBound(Function& phi, const std::function<double(double)> &potential,
                      double E, double M, const int l,
                        const double x0, const double x1, const double h);

    double integrateConstantStep(Function &fun, double step);

}

#endif // NUMERICS_HPP
