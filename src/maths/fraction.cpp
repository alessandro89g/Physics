#include "../../include/maths/fraction.hpp"
#include "../../include/maths/number.hpp"

Fraction::Fraction(int numerator, int denominator) : _numerator(numerator), _denominator(denominator){
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
    Number numerator(_numerator);
    Number denominator(_denominator);

    std::set<Factor> numeratorFactors = numerator.factors();
    std::set<Factor> denominatorFactors = denominator.factors();

}
