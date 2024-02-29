#ifndef LCM_GCD_HPP
#define LCM_GCD_HPP

#include "number.hpp"
#include <initializer_list>
#include <set>

unsigned int gcd();

unsigned int gcd(const int a);

unsigned int gcd(const std::initializer_list<int>& Numbers);

unsigned int lcm();

unsigned int lcm(const int n);

unsigned int lcm(const std::initializer_list<int>& Numbers);

#endif // LCM_GCD_HPP