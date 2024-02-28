#include "../../include/maths/fraction.hpp"
#include "../../include/maths/number.hpp"
#include "../../include/maths/lcm_gcd.hpp"

Fraction::Fraction(int numerator) : _numerator(numerator), _denominator(1) {
}

Fraction::Fraction(int numerator, int denominator) 
            : _numerator(denominator < 0 ? -numerator : numerator), 
              _denominator(denominator < 0 ? -denominator : denominator)
{
    if (denominator == 0) {
        throw std::invalid_argument("Denominator cannot be zero");
    }
    simplify();
}

int Fraction::getNumerator() const {
    return _numerator;
}

int Fraction::getDenominator() const {
    return _denominator;
}

Fraction Fraction::operator-() const {
    return Fraction(-_numerator, _denominator);
}


Fraction Fraction::operator+(const Fraction& other) const {
    int newNumerator = _numerator * other._denominator + other._numerator * _denominator;
    int newDenominator = _denominator * other._denominator;
    return Fraction(newNumerator, newDenominator);
}
Fraction Fraction::operator-(const Fraction& other) const {
    int newNumerator = _numerator * other._denominator - other._numerator * _denominator;
    int newDenominator = _denominator * other._denominator;
    return Fraction(newNumerator, newDenominator);
}
Fraction Fraction::operator*(const Fraction& other) const {
    int newNumerator = _numerator * other._numerator;
    int newDenominator = _denominator * other._denominator;
    return Fraction(newNumerator, newDenominator);
}
Fraction Fraction::operator/(const Fraction& other) const {
    int newNumerator = _numerator * other._denominator;
    int newDenominator = _denominator * other._numerator;
    return Fraction(newNumerator, newDenominator);
}

Fraction& Fraction::operator+=(const Fraction& other) {
    *this = *this + other;
    return *this;
}
Fraction& Fraction::operator-=(const Fraction& other) {
    *this = *this - other;
    return *this;
}
Fraction& Fraction::operator*=(const Fraction& other) {
    *this = *this * other;
    return *this;
}
Fraction& Fraction::operator/=(const Fraction& other) {
    *this = *this / other;
    return *this;
}

bool Fraction::operator==(const Fraction& other) const {
    return _numerator == other._numerator && _denominator == other._denominator;
}
bool Fraction::operator!=(const Fraction& other) const {
    return !(*this == other);
}
bool Fraction::operator<(const Fraction& other) const {
    return _numerator * other._denominator < other._numerator * _denominator;
}
bool Fraction::operator>(const Fraction& other) const {
    return _numerator * other._denominator > other._numerator * _denominator;
}
bool Fraction::operator<=(const Fraction& other) const {
    return _numerator * other._denominator <= other._numerator * _denominator;
}
bool Fraction::operator>=(const Fraction& other) const {
    return _numerator * other._denominator >= other._numerator * _denominator;
}
void Fraction::simplify() {
    const unsigned int GCD = gcd({_numerator, (int) _denominator});
    _numerator /= GCD;
    _denominator /= GCD;
}

std::ostream& operator<<(std::ostream& os, const Fraction& fraction) {
    os << " " << fraction._numerator << "/" << fraction._denominator << " ";
    return os;
}



Fraction operator+(int n, const Fraction& f) {
    return f + n;
}
Fraction operator-(int n, const Fraction& f) {
    return Fraction(n) - f;
}
Fraction operator*(int n, const Fraction& f) {
    return f * n;
}
Fraction operator/(int n, const Fraction& f) {
    return Fraction(n) / f;
}