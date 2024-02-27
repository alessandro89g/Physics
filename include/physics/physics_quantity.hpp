#ifndef PHYSICS_QUANTITY_HPP
#define PHYSICS_QUANTITY_HPP

#include <vector>
#include "physics_units.hpp"

namespace Physics {

    template<class T = double>
    class PhysicsQuantity
    {
    private:
        T _value;
        std::vector<Unit> _units;

    public:
        PhysicsQuantity(T value) : _value(value), _units({}) {}
        PhysicsQuantity(T value, Unit unit) : _value(value), _units({unit}) {}
        PhysicsQuantity(T value, std::vector<Unit> units) : _value(value), _units(units) {}

        T value() const { return _value; }
        std::vector<Unit> units() const { return _units; }

        PhysicsQuantity operator+(const PhysicsQuantity& other) const {
            if (_units != other._units) {
                throw std::invalid_argument("Units do not match");
            }
            return PhysicsQuantity(_value + other._value, _units);
        }

        PhysicsQuantity operator-(const PhysicsQuantity& other) const {
            if (_units != other._units) {
                throw std::invalid_argument("Units do not match");
            }
            return PhysicsQuantity(_value - other._value, _units);
        }

        PhysicsQuantity operator*(const PhysicsQuantity& other) const {
            std::vector<Unit> new_units = _units;
            new_units.insert(new_units.end(), other._units.begin(), other._units.end());
            return PhysicsQuantity(_value * other._value, new_units);
        }

        PhysicsQuantity operator/(const PhysicsQuantity& other) const {
            std::vector<Unit> new_units = _units;
            for (auto unit : other._units) {
                new_units.erase(std::remove(new_units.begin(), new_units.end(), unit), new_units.end());
            }
            return PhysicsQuantity(_value / other._value, new_units);
        }

        template <class U>
        PhysicsQuantity operator*(const U& other) const {
            return PhysicsQuantity(_value * other, _units);
        }

        template <class U>
        PhysicsQuantity operator/(const U& other) const {
            return PhysicsQuantity(_value / other, _units);
        }

        PhysicsQuantity operator*(const Unit& other) const {
            std::vector<Unit> units = _units * other._units;
            T value = _value * other._value;
            return PhysicsQuantity(value, units);
        }

        PhysicsQuantity operator/(const Unit& other) const {
            std::vector<Unit> units = _units / other._units;
            T value = _value / other._value;
            return PhysicsQuantity(value, units);
        }

        PhysicsQuantity operator-() const {
            return PhysicsQuantity(-_value, _units);
        }
    };
}


#endif // PHYSICS_QUANTITY_HPP