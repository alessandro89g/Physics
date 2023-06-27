#ifndef PHYSICS_HPP
#define PHYSICS_HPP
#include "physics_constants.hpp"
#include "fourmomentum.hpp"
#include "matrix4.hpp"
#include "unitvector.hpp"

namespace Physics {
    namespace Relativity {

        const Matrix4 Metric = Matrix4::metricTensor();
        const Matrix4 Id4 = Matrix4::identityMatrix();
        const Matrix Id3 = Matrix::identityMatrix(3);

        Vector3 velocity(const Vector4& momentum) {
            Vector3 v(momentum.vector3());
            v/= momentum.energy();
            return v;
        }
        double LorentzGamma(double v) {
            return 1./sqrt(1-v*v);
        }
        double LorentzGamma(const Vector4& momentum) {
            return LorentzGamma(velocity(momentum).norm());
        }

    }
    inline double energy(double m, double p) {
        return sqrt(m*m + p*p);
    }
    inline double energyNR(double m, double p) {
        return p*p/(2*m);
    }

    double MandesteinS(const FourMomentum& p1, const FourMomentum p2) {
        FourMomentum P0 = p1+p2;
        double s = P0*P0;
        return s;
    }
    double MandesteinT(const FourMomentum& p1, const FourMomentum p3) {
        FourMomentum Q = p1-p3;
        double t = Q*Q;
        return t;
    }
    double MandesteinU(const FourMomentum& p1, const FourMomentum p4) {
        FourMomentum PU = p1-p4;
        double u = PU*PU;
        return u;
    }
    double Q2(const FourMomentum& p1, const FourMomentum p3) {
        return -MandesteinT(p1,p3);
    }

    Matrix4 LorentzBoost(const Vector3 v) {
        if (v.norm()==0)
            return Matrix4::identityMatrix();

        double g = Relativity::LorentzGamma(v.norm());
        Matrix4 L;
        L[0][0] = g;
        for (int i=1; i<4; i++) {
            L[0][i] = -v[i]*g;
            L[i][0] = -v[i]*g;
        }
        for(int i=1; i<4; i++)
            for(int j=1; j<4; j++) {
                if (i==j)
                    L[i][j] = 1;
                else
                    L[i][j] = 0;
                L[i][j] += (g-1)*v[i]*v[j]/pow(v.norm(),2);
            }
        return L;
    }
    Matrix4 LorentzBoost(const Vector4 momentum) {
        Vector3 v = Relativity::velocity(momentum);
        Matrix4 L = LorentzBoost(v);
//        L.print();
        return L;
    }

    Matrix4 rotationMatrix(const UnitVector& v, const Angle& theta) {
        Matrix4 R;
        for(int i=0; i<4; i++){
            R[0][i] = R[i][0] = (i==0 ? 1 : 0);
        }

        for (int i=1; i<4; i++)
            for (int j=1; j<4; j++) {
                R[i][j] = (i==j ? cos(theta) : 0) + v[i]*v[j]*(1-cos(theta));
            }
        R[1][2] -= v[3]*sin(theta);
        R[1][3] += v[2]*sin(theta);
        R[2][1] += v[3]*sin(theta);
        R[2][3] -= v[1]*sin(theta);
        R[3][1] -= v[2]*sin(theta);
        R[3][2] += v[1]*sin(theta);
        return R;
    }
    Matrix4 rotationMatrixX(const Angle& theta) {
        Vector3 n({1,0,0});
        return rotationMatrix(n,theta);
    }
    Matrix4 rotationMatrixY(const Angle& theta) {
        Vector3 n({0,1,0});
        return rotationMatrix(n,theta);
    }
    Matrix4 rotationMatrixZ(const Angle& theta) {
        Vector3 n({0,0,1});
        return rotationMatrix(n,theta);
    }

}

#endif // PHYSICS_HPP
