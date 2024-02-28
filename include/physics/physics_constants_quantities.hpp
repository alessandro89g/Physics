#ifndef PHYSICS_CONSTANTS_QUANTITY_HPP
#define PHYSICS_CONSTANTS_QUANTITY_HPP

#include "physics_units.hpp"
#include "physics_quantity.hpp"

#define set_unit(...) std::set<Unit>({__VA_ARGS__})

namespace Physics::Quantities {

    const PhysicsQuantity<double> c(299'792'458, set_unit(Unit::m, Unit(Unit::s, -1)));
    const PhysicsQuantity<double> h(6.6260700e-34, set_unit(Unit::J, Unit::s));
    const PhysicsQuantity<double> eps0 = 8.8541878176e-12;
    const PhysicsQuantity<double> pi = 3.1415926535897931;
    const PhysicsQuantity<double> hb = h/(2*pi);
    const PhysicsQuantity<double> alpha = 1./137.035999084;
    const PhysicsQuantity<double> hc = hb*c;
    const PhysicsQuantity<double> qe(1.60217663e-19, set_unit(Unit::C));
    const PhysicsQuantity<double> eV(qe.value(), set_unit(Unit::J));
    const PhysicsQuantity<double> MeV = 1.e6*eV;
    const PhysicsQuantity<double> fm(1.e-15, set_unit(Unit::m));
    const PhysicsQuantity<double> me(9.1093837e-31, set_unit(Unit::kg));
    const PhysicsQuantity<double> Mn(1.674927471e-27, set_unit(Unit::kg));
    const PhysicsQuantity<double> Mp(1.67262192e-27, set_unit(Unit::kg));

    inline double convertJtoMeV(const double num) {
        return num*c.value()*c.value()/eV.value()*1.e-6;
    }
    namespace Nuclear {
        const PhysicsQuantity<double> hc = PhysicsQuantity((Quantities::hc/fm/eV*1.e-6).value(), set_unit(Unit::MeV, Unit::fm));
        const PhysicsQuantity<double> me = PhysicsQuantity(convertJtoMeV((Quantities::me).value()), set_unit(Unit::MeV));
        const PhysicsQuantity<double> Mn = PhysicsQuantity(convertJtoMeV((Quantities::Mn).value()), set_unit(Unit::MeV));
        const PhysicsQuantity<double> Mp = PhysicsQuantity(convertJtoMeV((Quantities::Mp).value()), set_unit(Unit::MeV));
        const PhysicsQuantity<double> M = 0.5*(Mn+Mp); // MeV
    }
}


#endif // PHYSICS_CONSTANTS_QUANTITY_HPP
