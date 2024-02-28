#ifndef FRACTION_HPP
#define FRACTION_HPP
#include <iostream>
#include <stdexcept>
#include <vector>


class Fraction {
public:
    Fraction(int numerator, int denominator);
    int getNumerator() const;
    int getDenominator() const;
    Fraction operator+(const Fraction& other) const;
    Fraction operator-(const Fraction& other) const;
    Fraction operator*(const Fraction& other) const;
    Fraction operator/(const Fraction& other) const;
    bool operator==(const Fraction& other) const;
    bool operator!=(const Fraction& other) const;
    bool operator<(const Fraction& other) const;
    bool operator>(const Fraction& other) const;
    bool operator<=(const Fraction& other) const;
    bool operator>=(const Fraction& other) const;
    friend std::ostream& operator<<(std::ostream& os, const Fraction& fraction);
private:
    int _numerator;
    int _denominator;
    void simplify();
};

std::ostream& operator<<(std::ostream& os, const Fraction& fraction) {
    os << " " << fraction._numerator << "/" << fraction._denominator + " ";
    return os;
}


#endif // FRACTION_HPP