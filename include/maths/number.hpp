#ifndef FACTORIZATION_HPP
#define FACTORIZATION_HPP
#include <vector>
#include <set>
#include <cmath>
#include <stdexcept>
#include <iostream>

struct Factor {
    int prime;
    int power;

    Factor(int prime, int power) : prime(prime), power(power) {}
    bool operator<(const Factor& other) const {
        return prime < other.prime;
    }
    bool operator==(const Factor& other) const {
        return prime == other.prime && power == other.power;
    }
    bool operator!=(const Factor& other) const {
        return !(*this == other);
    }
    bool operator>(const Factor& other) const {
        return !(*this < other) && *this != other;
    }
    bool operator<=(const Factor& other) const {
        return *this < other || *this == other;
    }
    bool operator>=(const Factor& other) const {
        return *this > other || *this == other;
    }
    Factor operator*(const Factor& other) const {
        if (prime != other.prime) {
            throw std::invalid_argument("Cannot multiply factors with different primes");
        }
        return Factor(prime, power + other.power);
    }
    Factor operator/(const Factor& other) const {
        if (prime != other.prime) {
            throw std::invalid_argument("Cannot divide factors with different primes");
        }
        return Factor(prime, power - other.power);
    }
};

class Number {
public:
    Number() : _number(0) {}
    Number(int number);
    Number(unsigned long long number);
    Number(double number);

    unsigned long long get() const;
    void set(unsigned long long number);

    std::set<Factor> factors() const;

    Number operator+(const Number& other) const;
    Number operator-(const Number& other) const;
    Number operator*(const Number& other) const;
    Number operator/(const Number& other) const;
    bool operator==(const Number& other) const;
    bool operator!=(const Number& other) const;
    bool operator<(const Number& other) const;
    bool operator>(const Number& other) const;
    bool operator<=(const Number& other) const;
    bool operator>=(const Number& other) const;

    

private:
    unsigned long long _number = 0;
    std::set<Factor> _factors;
    static const std::vector<int> sp_prime_numbers;

    void factorize();
};

std::ostream& operator<<(std::ostream& os, const Factor& factor);

#endif // FACTORIZATION_HPP