#include <gtest/gtest.h>
#include "../include/physics/physics_constants_quantities.hpp"

TEST(PhysicsConstantsQuantities, PrintAll) {
    std::cout << "c: " << Physics::Quantities::c << std::endl;
    std::cout << "h: " << Physics::Quantities::h << std::endl;
    std::cout << "eps0: " << Physics::Quantities::eps0 << std::endl;
    std::cout << "pi: " << Physics::Quantities::pi << std::endl;
    std::cout << "hb: " << Physics::Quantities::hb << std::endl;
    std::cout << "alpha^-1: " << 1./Physics::Quantities::alpha << std::endl;
    std::cout << "hc: " << Physics::Quantities::hc << std::endl;
    std::cout << "qe: " << Physics::Quantities::qe << std::endl;
    std::cout << "eV: " << Physics::Quantities::eV << std::endl;
    std::cout << "MeV: " << Physics::Quantities::MeV << std::endl;
    std::cout << "fm: " << Physics::Quantities::fm << std::endl;
    std::cout << "me: " << Physics::Quantities::me << std::endl;
    std::cout << "Mn: " << Physics::Quantities::Mn << std::endl;
    std::cout << "Mp: " << Physics::Quantities::Mp << std::endl;
    std::cout << "hc: " << Physics::Quantities::Nuclear::hc << std::endl;
    std::cout << "me: " << Physics::Quantities::Nuclear::me << std::endl;
    std::cout << "Mn: " << Physics::Quantities::Nuclear::Mn << std::endl;
    std::cout << "Mp: " << Physics::Quantities::Nuclear::Mp << std::endl;
    std::cout << "M: " << Physics::Quantities::Nuclear::M << std::endl;
}