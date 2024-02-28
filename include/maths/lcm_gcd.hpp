#include "number.hpp"
#include <initializer_list>
#include <set>

unsigned int gcd() {
    return 0;
}

unsigned int gcd(const int a) {
    return std::abs(a);
}

unsigned int gcd(const std::initializer_list<int>& Numbers) {
    if (Numbers.size() == 0) {
        return 0;
    }
    if (Numbers.size() == 1) {
        return std::abs(*(Numbers.begin()));
    }
    
    std::set<unsigned int> numbers;
    
    for(int number: Numbers)
        if (number!=0)
            numbers.insert(std::abs(number));
    

    unsigned long long result = 1;
    const std::vector<unsigned int> primes = Number::first_20_000_primes();

    unsigned int n0 = *(numbers.begin());
    Number smallest(static_cast<unsigned long long>(n0));
    std::set<Factor> factors = smallest.factors();
    for (const Factor& factor: factors) {
        unsigned int prime = factor.prime;
        unsigned short power = factor.power;
        auto it = numbers.begin();
        it++;
        for (; it != numbers.end(); it++) {
            unsigned short power_this = 0;
            unsigned int n = (*it);
            while(n % prime == 0) {
                n /= prime;
                power_this++;
            }
            if (power > power_this) {
                power = power_this;
            }           
        }
        result *= std::pow(prime, power);
    }
    return result;
}

unsigned int lcm() {
    return 0;
}

unsigned int lcm(const int n) {
    return std::abs(n);
}

unsigned int lcm(const std::initializer_list<int>& Numbers) {
    if (Numbers.size() == 0) {
        return 0;
    }
    if (Numbers.size() == 1) {
        return std::abs(*(Numbers.begin()));
    }
    
    std::set<unsigned int> numbers;
    for (int number: Numbers)
        if (number!=0)
            numbers.insert(std::abs(number));

    unsigned int result = 1;

    const std::vector<unsigned int> primes = Number::first_20_000_primes();
    unsigned int max = 1.*(*(numbers.rbegin()))/2.0+1;

    for (int i=0; i<max; i++) {
        unsigned int prime = primes[i];
        unsigned short power = 0;

        for (int n: numbers) {
            unsigned short power_this = 0;
            while(n % prime == 0) {
                n /= prime;
                power_this++;
            }
            if (power_this > power) {
                power = power_this;
            }
        }
        result *= std::pow(prime, power);
    }
    return result;
}