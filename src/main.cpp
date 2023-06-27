#include <iostream>
#include <functional>
#include <iomanip>
#include <random>

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


    NumerovInputs in(phi,Ei,{x0,x1,step},g,NumerovFunctionBoundaries(yi,yo));

    double E = NumerovBound(in);
    cout << E << endl;
    phi.exportFunction("test2.dat");

    vector<double> v(100);
    random_device rnd_device;
    // Specify the engine and distribution.
    mt19937 mersenne_engine {rnd_device()};  // Generates random integers
    uniform_int_distribution<int> dist {(int)x0,(int)100000*x1};

    auto gen = [&dist, &mersenne_engine](){
        return dist(mersenne_engine)/100000.;
    };
    generate(v.begin(),v.end(),gen);
    sort(v.begin(),v.end(),less<double>());


    Function phi2(v, [&phi] (double x) -> double{
        return phi(x);
    });
    phi2.exportFunction("random.dat");

}
