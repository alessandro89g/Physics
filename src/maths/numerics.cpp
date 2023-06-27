#include "numerics.hpp"
#include "vector3.hpp"
#include "physics_constants.hpp"
#include "derivative.hpp"

#define watch(x) cout << (#x) << " is " << (x) << endl


unsigned long Numerics::factorial(int n)
{
    if (n<=1)
        return 1;
    unsigned long fac = 1;
    for (int i = 2; i <= n; ++i) {
        fac*=i;
    }
    return fac;
}



int Numerics::LeviCivita(int i, int j, int k) {
    return (i-j)*(j-k)*(k-i)/2;
}

Vector3 Numerics::operator^(const Vector3 &v1, const Vector3 &v2) {
    Vector3 v;
    for (int i=1;i<4; i++)
        for (int j=1; j<4; j++)
            for(int k=1; k<4; k++)
                v[i] += LeviCivita(i,j,k)*v1[j]*v2[k];
    return v;
}

double Numerics::scalarProduct(const Vector3 &v1, const Vector3 &v2)
{
    return v1*v2;
}

double Numerics::NumerovBound(Function &phi, const std::function<double (double)> &potential,
                            double E, double M, const int l,
                              const double x0, const double x1, const double h) {
    const double cut = 3;
    const int n_cut = (double) cut/h;
    const double h12 = h*h/12;
    const double h512= h12*5;
    const double hbc = Physics::Nuclear::hc;
    const double diff_der_max = 1.e-12;

    phi.fillFunctionX(h,x0,x1);
    const int size = phi.size();

    Function phii(h,x0,cut), phio(h,cut,x1);

    double diff_der;
    double E2;
    double delta, delta2;

    int counter = 0;
    do {
        if (counter==0) {
            E2 = 0;
            delta2 = 0;
        }
        else if (counter == 1) {
            E2 = E;
            delta2 = delta;
            E *= 1.2;
        }
        else {
            double Enew = E-(E-E2)/(delta-delta2)*delta;
            E2 = E;
            E = Enew;
            delta2 = delta;
        }

        function<double(double)> peff = [potential,M,E,l,hbc] (double r) -> double {
            if (r==0)
                return 0;
            return (2*M*(E-potential(r))/pow(hbc,2)-((double)l*(l+1))/(r*r));
        };


        phii[0] = 0;
        phii[1] = phi.x(1);

        for (int i = 2; i<=n_cut; ++i) {
            const double xP1 = phii.x(i);
            const double PP1 = peff(xP1);
            const double PN = peff(xP1-h);
            const double PM1 = peff(xP1-2*h);
            phii[i] = 2*phii[i-1]*(1.-h512*PN)-phii[i-2]*(1.+h12*PM1);
            phii[i] = phii[i]/(1.+h12*PP1);
        }

        const double sizeo = phio.size();
        const double k = sqrt(-2*M*E)/hbc;
        phio[sizeo-1] = exp(-k*x1);
        phio[sizeo-2] = exp(-k*(x1-h));



        for (int i = sizeo-3; i>=0; --i) {
            const double xM1 = phio.x(i);
            const double PP1 = peff(xM1+2*h);
            const double PN = peff(xM1+h);
            const double PM1 = peff(xM1);
            phio[i] = 2*phio[i+1]*(1.-h512*PN)-phio[i+2]*(1.+h12*PP1);
            phio[i] = phio[i]/(1.+h12*PM1);
        }

        const double phi_r_ratio = phii[n_cut]/phio[0];
        phio*= phi_r_ratio;

        const int order = 7;
        vector<double> vo, vi;
        for (int i=0; i<order; i++) {
            vo.push_back(phio[i]);
            vi.push_back(phii[n_cut-i]);
        }
        cout << "counter: " << counter;
        delta2 = delta;
        delta = Derivative::derive(vi,n_cut-order,1,-h) - Derivative::derive(vo,0,1,h);
        diff_der = abs(delta-delta2);

        cout << ";   E: " << E << ";   der_r:  " << Derivative::derive(vo,0,1,h);
        cout << ";   der_l: "<< Derivative::derive(vi,n_cut-order,1,-h);
        cout << ";   delta: " << delta << endl;

        counter++;

    } while(diff_der>diff_der_max && counter < 30);


    for (int i=0; i<=size; i++)
        if (i<=n_cut)
            phi[i] = phii[i];
        else
            phi[i] = phio[i-n_cut];

    double norm = integrateConstantStep(phi,h);
    phi/=norm;

    return E;
}

double Numerics::integrateConstantStep(Function &fun, double step) {
    double sum = (fun[0]+fun[fun.size()-1])/2;
        for (int i=1; i<fun.size()-2; i++)
            sum += fun[i];
        sum *= step;
        return sum;
    }
