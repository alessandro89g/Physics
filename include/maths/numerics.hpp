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

    double findZero(const std::function<double(double)>& fun, double kp);

    struct NumerovX {
        const double x0;
        const double x1;
        const double step;
    };
    struct NumerovFunctionBoundaries  {
        NumerovFunctionBoundaries(const std::function<double (double, double)>& yi,
                                  const std::function<double (double, double)>& yo) : yi(yi), yo(yo){}
        const std::function<double (double, double)> yi;
        const std::function<double (double, double)> yo;
    };

    struct NumerovInputs {
        NumerovInputs(Function& phi, double Ei, NumerovX x, std::function<double(double,double)> g,
                      NumerovFunctionBoundaries y_boundaries) : phi(phi), Ei(Ei), x(x), g(g), y_boundaries(y_boundaries){}

        Function &phi;
        double Ei;
        NumerovX x;
        std::function<double(double,double)> g;
        NumerovFunctionBoundaries y_boundaries;
    };

    std::function<double(double,double)> NumerovGeneratingFunction(
        const std::function<double(double)>& potential, int orbital_angular_momentum, double mass);

    double NumerovBound(Function& phi, const std::function<double (double, double)> &g,
                      const double Ei, const double x0, const double x1, const double h,
                        const std::function<double (double, double)> &yi,
                        const std::function<double (double, double)> &yo);

    double NumerovBound(NumerovInputs& inputs);

    void NumerovUnbound(Function& phi, const std::function<double (double, double)> &g,
                        const double E, const double x0, const double x1, const double h,
                        const std::function<double (double, double)> &yi);
    void NumerovUnbound(NumerovInputs& inputs);

    double integrateConstantStep(Function &fun, double step);

}

#endif // NUMERICS_HPP
