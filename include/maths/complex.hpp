#ifndef COMPLEX_HPP
#define COMPLEX_HPP

#include <iostream>
#include <cmath>
#include <string>
#include <utility>

class Complex {
public:
    Complex();
    Complex(double real_part);
    Complex(double real_part, double imaginary_part);
    Complex(std::pair<double,double> complex_pair);

    inline double abs() const {
        if( _i ==0 && _r == 0 ) {
            return 0;
        } else if( _i == 0 ) {
            return std::abs(_r);
        } else if( _r == 0 ) {
            return std::abs(_i);
        }
        return std::sqrt( _r*_r + _i*_i );
    }
    inline double img() const {
        return _i;
    }
    double real() const {
        return _r;
    }
    Complex& conjugate();
    static Complex conjugate(const Complex& complex) {
        return Complex(complex.real(), -complex.img());
    }
    Complex operator- () const;
    std::string to_string() const;
    Complex operator+ (const Complex& other) const;
    Complex operator- (const Complex& other) const;
    Complex operator* (const Complex& other) const;
    Complex operator/ (const Complex& other) const;
    Complex& operator+= (const Complex& other);
    Complex& operator-= (const Complex& other);
    Complex& operator*= (const Complex& other);
    Complex& operator/= (const Complex& other);

    Complex operator+ (double other) const;
    Complex operator- (double other) const;
    Complex operator* (double other) const;
    Complex operator/ (double other) const;
    Complex& operator+= (double other);
    Complex& operator-= (double other);
    Complex& operator*= (double other);
    Complex& operator/= (double other);

    friend Complex operator+ (double other, const Complex& c);
    friend Complex operator- (double other, const Complex& c);
    friend Complex operator* (double other, const Complex& c);
    friend Complex operator/ (double other, const Complex& c);
    friend std::ostream& operator<< (std::ostream& os, const Complex& c);
    friend std::istream& operator>> (std::istream& is, Complex& c);

    inline void set_real(double re) {
        _r = re;
    }
    inline void set_imaginary(double img) {
        _i = img;
    }    
private:
    double _r;  // real part
    double _i;  // imaginary part
};

Complex operator+ (double other, const Complex& c);
Complex operator- (double other, const Complex& c);
Complex operator* (double other, const Complex& c);
Complex operator/ (double other, const Complex& c);
std::ostream& operator<< (std::ostream& os, const Complex& c);
std::istream& operator>> (std::istream& is, Complex& c);


#endif // COMPLEX_HPP