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
    double Ei = -2.;
    double mu = (Nuclear::Mp*Nuclear::Mn)/(Nuclear::Mp+Nuclear::Mn);



    function<double(double)> potential = [](double r)  -> double {
            const double r0 = 2.0536;
            if (r<r0)
                return -35;
            else
                return 0;};

    function<double(double,double)> g = NumerovGeneratingFunction(potential,0,mu);

    function<double(double,double)> yi = [] (double r, double E) -> double {
        return r;
    };
    function<double(double,double)> yo = [mu] (double r, double E) -> double {
        double k = sqrt(2*mu*abs(E))/Nuclear::hc;
        return exp(-k*r);
    };




    double E = NumerovBound(phi, g ,Ei, x0, x1, step,yi, yo);
    cout << E << endl;
    cout << phi.exportFunction("test.dat") << endl;

    NumerovInputs in(phi,Ei,{x0,x1,step},g,NumerovFunctionBoundaries(yi,yo));

    E = NumerovBound(in);
    cout << E << endl;
    cout << phi.exportFunction("test2.dat") << endl;

    double Es = 10.;
    NumerovUnbound(phi,g,Es,x0,x1,step,yi);
    phi.exportFunction("unbound.dat");

    NumerovInputs in2(phi,Es,{x0,x1,step},g,NumerovFunctionBoundaries(yi,yo));
    NumerovUnbound(in2);
    phi.exportFunction("unbound2.dat");
    cout << "END" <<endl;

}
