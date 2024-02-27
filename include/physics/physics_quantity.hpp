#ifndef PHYSICS_QUANTITY_HPP
#define PHYSICS_QUANTITY_HPP

#pragma once
#include <set>
#include <optional>
#include "physics_units.hpp"
#include "physics_constants.hpp"
#include "../maths/complex.hpp"

namespace Physics {

    template<class T = double>
    class PhysicsQuantity
    {
    private:
        T _value;
        std::set<Unit> _units;

    public:
        PhysicsQuantity(T value);
        explicit PhysicsQuantity(T value, Unit unit);
        explicit PhysicsQuantity(T value, std::set<Unit> units);

        T value() const;
        std::set<Unit> units() const;

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
        void eraseUnit(Unit::UnitType type) {
            for (auto it = _units.begin(); it != _units.end(); ++it) {
                if (it->getType() == type) {
                    _units.erase(it);
                    break;
                }
            }
        }
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
    PhysicsQuantity<T>::PhysicsQuantity(T value, std::set<Unit> units) : _value(value), _units(units) {}
//<-Contructors

//->Setters and Getters
    template <class T>
    T PhysicsQuantity<T>::value() const { return _value; }
    
    template <class T>
    std::set<Unit> PhysicsQuantity<T>::units() const { return _units; }
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
        std::set<Unit> new_units = _units * other._units;
        return PhysicsQuantity(_value * other._value, new_units);
    }

    template <class T>
    PhysicsQuantity<T> PhysicsQuantity<T>::operator/(const PhysicsQuantity& other) const {
        std::set<Unit> new_units = _units / other._units;
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


    template <Unit::UnitType type1, Unit::UnitType type2, typename T>
    PhysicsQuantity<T> convert(const PhysicsQuantity<T>& quantity) {
        throw std::invalid_argument("Conversion not implemented");
    }

    // write the prototype for partially specialized template function convert with type1 = MeV and type2 = fm
    // and return type of PhysicsQuantity<T>
    

    template <>
    PhysicsQuantity<double> convert<Unit::UnitType::MeV, Unit::UnitType::fm> (const PhysicsQuantity<double>& quantityMeV) {
        auto quantity = quantityMeV;

        short power = 0;
        for (auto& unit : quantity.units()) {
            if (unit.getType() == Unit::UnitType::MeV) {
                power = unit.getPower();
            }
        }
        if (power == 0)
            return quantityMeV;

        // To complete. Remove MeV from set of units and update fm if it is already in units or add it to the set
        quantity.eraseUnit(Unit::UnitType::MeV);
        quantity *= PhysicsQuantity(
            1./ pow(Nuclear::hc, power),
            Unit(Unit::UnitType::fm, -power)
        );

        return quantity;
    }

    template <>
    PhysicsQuantity<Complex> convert<Unit::UnitType::MeV, Unit::UnitType::fm> (const PhysicsQuantity<Complex>& quantityMeV) {
        auto quantity = quantityMeV;

        short power = 0;
        for (auto& unit : quantity.units()) {
            if (unit.getType() == Unit::UnitType::MeV) {
                power = unit.getPower();
            }
        }
        if (power == 0)
            return quantityMeV;

        // To complete. Remove MeV from set of units and update fm if it is already in units or add it to the set
        quantity.eraseUnit(Unit::UnitType::MeV);
        quantity *= PhysicsQuantity(
            Complex(1.)/ pow(Nuclear::hc, power),
            Unit(Unit::UnitType::fm, -power)
        );

        return quantity;
    }


    template <>
    PhysicsQuantity<double> convert<Unit::UnitType::fm, Unit::UnitType::MeV> (const PhysicsQuantity<double>& quantityfm) {
        auto quantity = quantityfm;

        short power = 0;
        for (auto& unit : quantity.units()) {
            if (unit.getType() == Unit::UnitType::fm) {
                power = unit.getPower();
            }
        }
        if (power == 0)
            return quantityfm;

        // To complete. Remove MeV from set of units and update fm if it is already in units or add it to the set
        quantity.eraseUnit(Unit::UnitType::fm);
        quantity *= PhysicsQuantity(
            1./ pow(Nuclear::hc, power),
            Unit(Unit::UnitType::MeV, -power)
        );

        return quantity;
    }

    template <>
    PhysicsQuantity<Complex> convert<Unit::UnitType::fm, Unit::UnitType::MeV> (const PhysicsQuantity<Complex>& quantityfm) {
        auto quantity = quantityfm;

        short power = 0;
        for (auto& unit : quantity.units()) {
            if (unit.getType() == Unit::UnitType::fm) {
                power = unit.getPower();
            }
        }
        if (power == 0)
            return quantity;

        // To complete. Remove MeV from set of units and update fm if it is already in units or add it to the set
        quantity.eraseUnit(Unit::UnitType::fm);
        quantity *= PhysicsQuantity(
            Complex(1.)/ pow(Nuclear::hc, power),
            Unit(Unit::UnitType::MeV, -power)
        );

        return quantity;
    }
}


#endif // PHYSICS_QUANTITY_HPP