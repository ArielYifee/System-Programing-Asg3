#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <string>

#pragma once

namespace ariel{
    class NumberWithUnits{
    public:
        NumberWithUnits(double, const std::string &);
        static void read_units(std::ifstream &file);
        NumberWithUnits operator+(const NumberWithUnits &other) const;
        NumberWithUnits &operator+=(const NumberWithUnits &other);
        NumberWithUnits operator+() const;
        NumberWithUnits operator-(const NumberWithUnits &other) const;
        NumberWithUnits &operator-=(const NumberWithUnits &other);
        NumberWithUnits operator-() const;
        bool operator<(const NumberWithUnits &other) const;
        bool operator<=(const NumberWithUnits &other) const;
        bool operator>=(const NumberWithUnits &other) const;
        bool operator>(const NumberWithUnits &other) const;
        bool operator==(const NumberWithUnits &other) const;
        bool operator!=(const NumberWithUnits &other) const;
        NumberWithUnits &operator++();   //++a
        NumberWithUnits operator++(int); //a++
        NumberWithUnits &operator--();   //--a
        NumberWithUnits operator--(int); //a--
        friend NumberWithUnits operator*(double number, const NumberWithUnits &unit);
        friend NumberWithUnits operator*(const NumberWithUnits &unit, double number);
        friend std::istream &operator>>(std::istream &input, NumberWithUnits &unit);
        friend std::ostream &operator<<(std::ostream &output, const NumberWithUnits &unit);
        std::string getUnit() const;
        double getSize() const;
    private:
        double size;
        std::string unit;
        bool check_unit(const NumberWithUnits &unit) const;
        double change_unit(const NumberWithUnits &unit) const;
    };
};