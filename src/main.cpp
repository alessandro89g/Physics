#include <iostream>
#include <functional>
#include <iomanip>

#include "physics.hpp"
#include "numerics.hpp"
#include "derivative.hpp"
#include "function.hpp"


using namespace std;
using namespace Numerics;
using namespace Physics;

int main()
{
    const double range = 20.;
    const double step = 0.001;

    const double x0 = 0.;
    const double x1 = x0+range;

    Function phi;
    function<double(double)> potential = [](double r)  -> double {
            const double r0 = 2.0536;
            if (r<r0)
                return -35;
            else
                return 0;};

    double Ei = -2.;
    double mu = (Nuclear::Mp*Nuclear::Mn)/(Nuclear::Mp+Nuclear::Mn);
    double E = NumerovBound(phi, potential ,Ei, mu, 0, x0, x1, step);
    cout << E << endl;

    cout << phi.exportFunction("test.dat") << endl;

}
