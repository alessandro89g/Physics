#ifndef PHYSICS_QUANTITY_HPP
#define PHYSICS_QUANTITY_HPP

#pragma once
#include <vector>
#include <optional>
#include "physics_units.hpp"

namespace Physics {

    template<class T = double>
    class PhysicsQuantity
    {
    private:
        T _value;
        std::vector<Unit> _units;

    public:
        PhysicsQuantity(T value);
        explicit PhysicsQuantity(T value, Unit unit);
        explicit PhysicsQuantity(T value, std::vector<Unit> units);

        T value() const;
        std::vector<Unit> units() const;

        PhysicsQuantity operator+(const PhysicsQuantity& other) const;
        PhysicsQuantity operator-(const PhysicsQuantity& other) const;
        PhysicsQuantity operator*(const PhysicsQuantity& other) const;
        PhysicsQuantity operator/(const PhysicsQuantity& other) const;

        PhysicsQuantity& operator+=(const PhysicsQuantity& other);
        PhysicsQuantity& operator-=(const PhysicsQuantity& other);
        PhysicsQuantity& operator*=(const PhysicsQuantity& other);
        PhysicsQuantity& operator/=(const PhysicsQuantity& other);

        PhysicsQuantity<T> operator*(const double& other) const;
        PhysicsQuantity<T> operator/(const double& other) const;


        PhysicsQuantity operator*(const Unit& other) const;
        PhysicsQuantity operator/(const Unit& other) const;
        PhysicsQuantity operator-() const;

        bool operator==(const PhysicsQuantity& other) const;
        bool operator!=(const PhysicsQuantity& other) const;
        bool operator<(const PhysicsQuantity& other) const;
        bool operator>(const PhysicsQuantity& other) const;
        bool operator<=(const PhysicsQuantity& other) const;
        bool operator>=(const PhysicsQuantity& other) const;

        std::string toString() const;
    };




    template<class T>
    std::ostream& operator<<(std::ostream& os, const PhysicsQuantity<T>& quantity) {
        os << quantity.toString();
        return os;
    }

    template<class T>
    PhysicsQuantity<T> operator+(const double& other, const PhysicsQuantity<T>& quantity) {
        return quantity + other;
    }

    template<class T>
    PhysicsQuantity<T> operator-(const double& other, const PhysicsQuantity<T>& quantity) {
        return PhysicsQuantity<T>(other) - quantity;
    }

    template<class T>
    PhysicsQuantity<T> operator*(const double& other, const PhysicsQuantity<T>& quantity) {
        return quantity * other;
    }

    template<class T>
    PhysicsQuantity<T> operator/(const double& other, const PhysicsQuantity<T>& quantity) {
        return PhysicsQuantity<T>(other) / quantity;
    }

//->Contructors
    template <class T>
    PhysicsQuantity<T>::PhysicsQuantity(T value) : _value(value), _units({}) {}
    
    template <class T>
    PhysicsQuantity<T>::PhysicsQuantity(T value, Unit unit) : _value(value), _units({unit}) {}

    template <class T>
    PhysicsQuantity<T>::PhysicsQuantity(T value, std::vector<Unit> units) : _value(value), _units(units) {}
//<-Contructors

//->Setters and Getters
    template <class T>
    T PhysicsQuantity<T>::value() const { return _value; }
    
    template <class T>
    std::vector<Unit> PhysicsQuantity<T>::units() const { return _units; }
//<-Setters and Getters

//->Operators
    template <class T>
    PhysicsQuantity<T> PhysicsQuantity<T>::operator+(const PhysicsQuantity& other) const {
        if (_units != other._units) {
            throw std::invalid_argument("Units do not match");
        }
        return PhysicsQuantity(_value + other._value, _units);
    }

    template <class T>
    PhysicsQuantity<T> PhysicsQuantity<T>::operator-(const PhysicsQuantity& other) const {
        if (_units != other._units) {
            throw std::invalid_argument("Units do not match");
        }
        return PhysicsQuantity(_value - other._value, _units);
    }

    template <class T>
    PhysicsQuantity<T> PhysicsQuantity<T>::operator*(const PhysicsQuantity& other) const {
        std::vector<Unit> new_units = _units * other._units;
        return PhysicsQuantity(_value * other._value, new_units);
    }

    template <class T>
    PhysicsQuantity<T> PhysicsQuantity<T>::operator/(const PhysicsQuantity& other) const {
        std::vector<Unit> new_units = _units / other._units;
        return PhysicsQuantity(_value / other._value, new_units);
    }

    template <class T>
    PhysicsQuantity<T> PhysicsQuantity<T>::operator*(const double& other) const {
        return PhysicsQuantity(_value * other, _units);
    }

    template <class T>
    PhysicsQuantity<T> PhysicsQuantity<T>::operator/(const double& other) const {
        return PhysicsQuantity(_value / other, _units);
    }

    template <class T>
    PhysicsQuantity<T> PhysicsQuantity<T>::operator-() const {
        return PhysicsQuantity(-_value, _units);
    }

    template <class T>
    PhysicsQuantity<T>& PhysicsQuantity<T>::operator+=(const PhysicsQuantity& other) { 
        *this = *this + other;
        return *this; 
    }
    
    template <class T>
    PhysicsQuantity<T>& PhysicsQuantity<T>::operator-=(const PhysicsQuantity& other) {
        *this = *this - other;
        return *this; 
    }
    
    template <class T>
    PhysicsQuantity<T>& PhysicsQuantity<T>::operator*=(const PhysicsQuantity& other) { 
        *this = *this * other;
        return *this; 
    }
    
    template <class T>
    PhysicsQuantity<T>& PhysicsQuantity<T>::operator/=(const PhysicsQuantity& other) { 
        *this = *this / other;
        return *this; 
    }
//<-Operators

//->Coparison operators
    template <class T>
    bool PhysicsQuantity<T>::operator==(const PhysicsQuantity& other) const {
        return _value == other._value && _units == other._units;
    }
    template <class T>
    bool PhysicsQuantity<T>::operator!=(const PhysicsQuantity& other) const {
        return !(*this == other);
    }
    template <class T>
    bool PhysicsQuantity<T>::operator<(const PhysicsQuantity& other) const {
        if (_units != other._units) {
            throw std::invalid_argument("Units do not match");
        }
        return _value < other._value;
    }
    template <class T>
    bool PhysicsQuantity<T>::operator>(const PhysicsQuantity& other) const {
        return !(*this < other) && !(*this == other);
    }
    template <class T>
    bool PhysicsQuantity<T>::operator<=(const PhysicsQuantity& other) const {
        return *this < other || *this == other;
    }
    template <class T>
    bool PhysicsQuantity<T>::operator>=(const PhysicsQuantity& other) const {
        return *this > other || *this == other;
    
    }
//<-Coparison operators

//->Other methods
    template <class T>
    std::string PhysicsQuantity<T>::toString() const {
        std::stringstream result;
        result << _value;
        for (auto unit : _units) {
            result << " " + unit.to_string();
        }
        return result.str();
    }
//<-Other methods
}

#endif // PHYSICS_QUANTITY_HPP