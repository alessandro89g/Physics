#include "../../include/maths/complex.hpp"
#include <string>
#include <limits>

Complex::Complex() : _r(0), _i(0) {
}

Complex::Complex(double real_part) : _r(real_part), _i(0.) {
}

Complex::Complex(double real_part, double imaginary_part) : _r(real_part), _i(imaginary_part) {
}

Complex::Complex(std::pair<double,double> complex_pair) : _r(complex_pair.first), _i(complex_pair.second) {
}

Complex& Complex::conjugate() {
    _i *= -1;
    return *this;
}

std::string Complex::to_string() const {
    if (this->abs() == 0) {
        return "0";
    };

    std::string num;
    std::string sign = (_i>0) ? " + " : " - ";
    std::string absim = std::to_string(std::abs(_i));
    
    if (_r*_i!=0) {
        num = "( " + std::to_string(_r) + sign + absim + " i )";
    }
    else if (_i == 0) {
        num = std::to_string(_r);
    }
    else if (_r == 0) {
        num = std::to_string(_i)   + " i";
    };
    return num;
}

Complex Complex::operator- () const {
    return Complex(-_r, -_i);

}

Complex Complex::operator+ (const Complex& other) const {
    double real = _r + other.real();
    double img  = _i + other.img();
    return Complex(real, img);
}

Complex Complex::operator- (const Complex& other) const {
    double real = _r - other.real();
    double img  = _i - other.img();
    return Complex(real, img);
}
Complex Complex::operator* (const Complex& other) const {
    double real = _r*other.real() - _i*other.img();
    double img  = _i*other.real() + _r*other.img();
    return Complex(real, img);
}
Complex Complex::operator/ (const Complex& other) const {
    double denominator = std::pow(other.abs(),2);
    if (denominator==0)
        return Complex(std::numeric_limits<double>::infinity(), std::numeric_limits<double>::infinity());
    double real = _r*other.real() + _i*other.img();
    double img  = _i*other.real() - _r*other.img();
    real /= denominator;
    img  /= denominator;

    return Complex(real, img);
}
Complex& Complex::operator+= (const Complex& other) {
    *this = *this + other;
    return *this;
}

Complex& Complex::operator-= (const Complex& other){
    *this = *this - other;
    return *this;
}

Complex& Complex::operator*= (const Complex& other){
    *this = *this * other;
    return *this;
}

Complex& Complex::operator/= (const Complex& other){
    *this = *this / other;
    return *this;
}

Complex Complex::operator+ (double other) const {
    return Complex(_r + other, _i);
}

Complex Complex::operator- (double other) const {
    return Complex(_r - other, _i);
}

Complex Complex::operator* (double other) const {
    return Complex(_r*other, _i*other);
}

Complex Complex::operator/ (double other) const {
    return Complex(_r/other, _i/other);
}

Complex& Complex::operator+= (double other) {
    *this = *this + other;
    return *this;
}
Complex& Complex::operator-= (double other) {
    *this = *this - other;
    return *this;
}
Complex& Complex::operator*= (double other) {
    *this = *this * other;
    return *this;
}
Complex& Complex::operator/= (double other) {
    *this = *this / other;
    return *this;
}

Complex operator+ (double other, const Complex& c) {
    return c + other;
}

Complex operator- (double other, const Complex& c) {
    return -c + other;
}

Complex operator* (double other, const Complex& c) {
    return c * other;
}

Complex operator/ (double other, const Complex& c) {
    return Complex(other, 0) / c;
}

std::ostream& operator<< (std::ostream& os, const Complex& c) {
    os << "(" << c.real() << "," << c.img() << ")";
    return os;
}

std::istream& operator>> (std::istream& is, Complex& c) {
    double real, img;
    auto check_char = [&is](char ch) {
        if (is.peek() == ch) {
            is.get(ch);
            return true;
        }
        return false;
    };
    auto remove_white_spaces = [&is, check_char](){
        while (check_char(' '));
    };

    remove_white_spaces(); // remove leading whitespaces

    if (check_char('(')) {  // check that the complex number starts with a '('
                            // if it does, then read the real and 
                            // imaginary parts in the format (real, img)

        remove_white_spaces(); // remove whitespaces after '('

        is >> real;
        
        remove_white_spaces(); // remove whitespaces after real part
        if (!check_char(',')) { 
            is.setstate(std::ios_base::failbit);
            return is;
        }
        remove_white_spaces(); // remove whitespaces after ','

        is >> img;
        
        remove_white_spaces(); // remove whitespaces after imaginary part
        if (!check_char(')')) {
            is.setstate(std::ios_base::failbit);
            return is;
        }
    } else if (check_char('i')) {
        real = 0;
        remove_white_spaces(); // remove whitespaces after 'i'
        is >> img;
    } else {
        double num;
        is >> num;
        if (is.fail()) {
            return is;
        }
        remove_white_spaces(); // remove whitespaces after number
        if (check_char('i')) {
            real = 0;
            img = num;
        } else {
            real = num;
            img = 0;
        }
    }
    
    c.set_real(real);
    c.set_imaginary(img);
    return is;
}