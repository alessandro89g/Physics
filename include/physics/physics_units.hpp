#ifndef PHYSICS_UNITS_HPP
#define PHYSICS_UNITS_HPP
#include <stdexcept>
#include <vector>
#include <set>
#include <iostream>
#include <string>

namespace Physics {
 
class Unit {
public:
    enum UnitType {
        m,
        km,
        fm,
        nm,
        s,
        ms,
        ns,
        Hz,
        MHz,
        GHz,
        kg,
        g,
        u,
        C,
        K,
        F,
        J,
        eV,
        MeV,
        rad,
        deg,
        sr,
        N,
        Pa,
        T,
        mol,
        cd
    };

    Unit() = delete;
    constexpr Unit(UnitType type) : _type(type), _power(1) {}
    Unit(UnitType type, short power) : _type(type), _power(power) {
        if (power == 0) {
            throw std::invalid_argument("Power cannot be zero");
        }
    }

    UnitType getType() const { return _type; }
    short getPower() const { return _power; }
    
    constexpr bool operator==(Unit a) const { return _type == a._type && _power == a._power ; }
    constexpr bool operator!=(Unit a) const { return !(*this==a); }
    
    Unit operator+(const Unit& other) const {
        if (*this != other) {
            throw std::invalid_argument("Units do not match");
        }
        return *this;
    }
    Unit operator-(const Unit& other) const {
        if (*this != other) {
            throw std::invalid_argument("Units do not match");
        }
        return *this;
    }
    std::optional<std::vector<Unit>> operator*(const Unit& other) const {
        if (_type == other._type && _power + other._power == 0) {
            return std::optional<std::vector<Unit>>();
        }
        if (_type == other._type) {
            return std::optional<std::vector<Unit>>({Unit(_type, _power + other._power)});
        }
        return std::optional<std::vector<Unit>>({*this, other});
    }
    
    std::optional<std::vector<Unit>> operator/(const Unit& other) const {
        if (_type == other._type && _power - other._power == 0) {
            return std::optional<std::vector<Unit>>();
        }
        if (_type == other._type) {
            return std::optional<std::vector<Unit>>({Unit(_type, _power - other._power)});
        }
        return std::optional<std::vector<Unit>>({*this, Unit(other._type, -other._power)});
    }

    Unit& operator+=(const Unit& other) {
        *this = *this + other;
        return *this;
    }
    Unit& operator-=(const Unit& other) {
        *this = *this - other;
        return *this;
    }

    std::string to_string() const;

    friend std::ostream& operator<<(std::ostream& os, const Unit& unit) {
        os << unit.to_string();
        return os;
    }

private:
    UnitType _type;
    short _power;
};





std::string Unit::to_string() const {
    if (_power == 0) {
        return "";
    }
    std::string unit;
    switch (_type) {
    case UnitType::m:
        unit = "m";
        break;
    case UnitType::km:
        unit = "km";
        break;
    case UnitType::fm:
        unit = "fm";
        break;
    case UnitType::nm:
        unit = "nm";
        break;
    case UnitType::s:
        unit = "s";
        break;
    case UnitType::ms:
        unit = "ms";
        break;
    case UnitType::ns:
        unit = "ns";
        break;
    case UnitType::Hz:
        unit = "Hz";
        break;
    case UnitType::MHz:
        unit = "MHz";
        break;
    case UnitType::GHz:
        unit = "GHz";
        break;
    case UnitType::kg:
        unit = "kg";
        break;
    case UnitType::g:
        unit = "g";
        break;
    case UnitType::u:
        unit = "u";
        break;
    case UnitType::C:
        unit = "C";
        break;
    case UnitType::K:
        unit = "K";
        break;
    case UnitType::F:
        unit = "F";
        break;
    case UnitType::J:
        unit = "J";
        break;
    case UnitType::eV:
        unit = "eV";
        break;
    case UnitType::MeV:
        unit = "MeV";
        break;
    case UnitType::rad:
        unit = "rad";
        break;
    case UnitType::deg:
        unit = "deg";
        break;
    case UnitType::sr:
        unit = "sr";
        break;
    case UnitType::N:
        unit = "N";
        break;
    case UnitType::Pa:
        unit = "Pa";
        break;
    case UnitType::T:
        unit = "T";
        break;
    case UnitType::mol:
        unit = "mol";
        break;
    case UnitType::cd:
        unit = "cd";
        break;
    }
    if (_power != 1) {
        unit += "^" + std::to_string(_power);
    }
    return unit;
}

std::vector<Unit> operator*(const std::vector<Unit>& a, const std::vector<Unit>& b) {
    std::vector<Unit> result;
    std::set<Unit::UnitType> types;
    for (auto unit : a) {
        types.insert(unit.getType());
    }
    for (auto unit : b) {
        types.insert(unit.getType());
    }
    for (auto type : types) {
        short power = 0;
        for (auto unit : a) {
            if (unit.getType() == type) {
                power += unit.getPower();
            }
        }
        for (auto unit : b) {
            if (unit.getType() == type) {
                power += unit.getPower();
            }
        }
        if (power != 0) {
            result.push_back(Unit(type, power));
        }
    }
    return result;
}

std::vector<Unit> operator/(const std::vector<Unit>& a, const std::vector<Unit>& b) {
    std::vector<Unit> result;
    std::set<Unit::UnitType> types;
    for (auto unit : a) {
        types.insert(unit.getType());
    }
    for (auto unit : b) {
        types.insert(unit.getType());
    }
    for (auto type : types) {
        short power = 0;
        for (auto unit : a) {
            if (unit.getType() == type) {
                power += unit.getPower();
            }
        }
        for (auto unit : b) {
            if (unit.getType() == type) {
                power -= unit.getPower();
            }
        }
        if (power != 0) {
            result.push_back(Unit(type, power));
        }
    }
    return result;
}

std::vector<Unit>& operator*=(std::vector<Unit>& a, const std::vector<Unit>& b) {
    a = a * b;
    return a;
}

std::vector<Unit>& operator/=(std::vector<Unit>& a, const std::vector<Unit>& b) {
    a = a / b;
    return a;
}

} // namespace Physics

#endif // PHYSICS_UNITS_HPP