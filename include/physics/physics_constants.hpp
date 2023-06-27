#ifndef PHYSICS_CONSTANTS_HPP
#define PHYSICS_CONSTANTS_HPP

namespace Physics {

const double c = 299'792'458; //m/s
const double h = 6.6260700e-34; // J s
const double eps0 = 8.8541878176e-12;
const double pi = 3.1415926535897931;
const double hb = h/(2*pi);
const double alpha = 1./137.035999084;
const double hc = hb*c;
const double qe = 1.60217663e-19;   // C
const double eV = qe; // 1 eV
const double MeV = 1.e6*eV;
const double fm = 1.e-15; //m
const double me = 9.1093837e-31; // kg
const double Mn = 1.674927471e-27; // kg
const double Mp = 1.67262192e-27; // kg

inline double convertJtoMeV(const double num) {
    return num*c*c/eV*1.e-6;
}
namespace Nuclear {
const double hc = Physics::hc/fm/eV*1.e-6; // MeV fm
const double me = convertJtoMeV(Physics::me); // MeV
const double Mn = convertJtoMeV(Physics::Mn); // MeV
const double Mp = convertJtoMeV(Physics::Mp); // MeV
const double M = 0.5*(Mn+Mp); // MeV
}
}


#endif // PHYSICS_CONSTANTS_HPP
