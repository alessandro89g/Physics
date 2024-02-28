#ifndef FRACTION_HPP
#define FRACTION_HPP
#include <iostream>
#include <stdexcept>
#include <vector>


class Fraction {
public:
    Fraction(int numerator);
    Fraction(int numerator, int denominator);
    int getNumerator() const;
    int getDenominator() const;
    Fraction operator-() const;
    Fraction operator+(const Fraction& other) const;
    Fraction operator-(const Fraction& other) const;
    Fraction operator*(const Fraction& other) const;
    Fraction operator/(const Fraction& other) const;
    Fraction& operator+=(const Fraction& other);
    Fraction& operator-=(const Fraction& other);
    Fraction& operator*=(const Fraction& other);
    Fraction& operator/=(const Fraction& other);
    bool operator==(const Fraction& other) const;
    bool operator!=(const Fraction& other) const;
    bool operator<(const Fraction& other) const;
    bool operator>(const Fraction& other) const;
    bool operator<=(const Fraction& other) const;
    bool operator>=(const Fraction& other) const;
    friend std::ostream& operator<<(std::ostream& os, const Fraction& fraction);
    explicit operator double() const { return (double) _numerator / _denominator; }
private:
    int _numerator;
    unsigned int _denominator;
    void simplify();
};

Fraction operator+(int n, const Fraction& f);
Fraction operator-(int n, const Fraction& f);
Fraction operator*(int n, const Fraction& f);
Fraction operator/(int n, const Fraction& f);


#endif // FRACTION_HPP