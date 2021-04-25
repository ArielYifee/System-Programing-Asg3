#include <map>
#include "NumberWithUnits.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <math.h>
#include <string>
#include <utility>
#include <algorithm>
#include <exception>

using namespace std;
using namespace ariel;

const double EPS = 0.0001;

namespace ariel {
    static std::map<std::string, std::map<std::string, double>> units;

    double NumberWithUnits::change_unit(const NumberWithUnits &unit1) const{
        if(unit == unit1.getUnit()){
            return unit1.getSize();
        }
        return unit1.getSize()*units[unit1.getUnit()][unit];
    }

    bool NumberWithUnits::check_unit(const NumberWithUnits &unit1) const{
        return unit == unit1.getUnit() || units[unit].find(unit1.getUnit()) != units[unit].end();
    }
    static void sync_units(const std::string &src_unit, const std::string &dest_unit){
        for(auto &unit : units[dest_unit]){
            if(unit.first != src_unit){
                double size = units[src_unit][dest_unit]*unit.second;
                units[src_unit][unit.first] = size;
                units[unit.first][src_unit] = 1/size;
            }
        }
    }

    NumberWithUnits::NumberWithUnits(double size, const string& unit){
        if(units.find(unit) == units.end()){
            throw invalid_argument(unit + " invalid unit");
        }
        this->size = size;
        this->unit = unit;
    }
    void NumberWithUnits::read_units(ifstream &file){
        string unit1;
        string unit2;
        string junk;
        double U1size = 0;
        double U2size = 0;
        while(file >> U1size >> unit1 >> junk >> U2size >> unit2){
            units[unit1][unit2] = U2size;
            units[unit2][unit1] = 1/U2size;
            sync_units(unit1, unit2);
            sync_units(unit2, unit1);
        }
    }
    NumberWithUnits NumberWithUnits::operator+(const NumberWithUnits &other) const{
        if(!check_unit(other)){
            throw invalid_argument("Units do not match - ["+other.getUnit()+"] cannot be converted to ["+unit+"]");
        }
        return NumberWithUnits(size + change_unit(other), unit);
    }
    NumberWithUnits &NumberWithUnits::operator+=(const NumberWithUnits &other){
        if(!check_unit(other)){
            throw invalid_argument("Units do not match - ["+other.getUnit()+"] cannot be converted to ["+unit+"]");
        }
        size += change_unit(other);
        return *this;
    }
    NumberWithUnits NumberWithUnits::operator+() const{
        return NumberWithUnits(size, unit);
    }
    NumberWithUnits NumberWithUnits::operator-(const NumberWithUnits &other) const{
        if(!check_unit(other)){
            throw invalid_argument("Units do not match - ["+other.getUnit()+"] cannot be converted to ["+unit+"]");
        }
        return NumberWithUnits(size - change_unit(other), unit);
    
    }
    NumberWithUnits &NumberWithUnits::operator-=(const NumberWithUnits &other){
        if(!check_unit(other)){
            throw invalid_argument("Units do not match - ["+other.getUnit()+"] cannot be converted to ["+unit+"]");
        }
        size -= change_unit(other);
        return *this;
    }
    NumberWithUnits NumberWithUnits::operator-() const{
        return NumberWithUnits(-size, unit);
    }
    bool NumberWithUnits::operator<(const NumberWithUnits &other) const{
        if(!check_unit(other)){
            throw invalid_argument("Units do not match - ["+other.getUnit()+"] cannot be converted to ["+unit+"]");
        }
        return size < change_unit(other);
    }
    bool NumberWithUnits::operator<=(const NumberWithUnits &other) const{
        if(!check_unit(other)){
            throw invalid_argument("Units do not match - ["+other.getUnit()+"] cannot be converted to ["+unit+"]");
        }
        return size <= change_unit(other);
    }
    bool NumberWithUnits::operator>=(const NumberWithUnits &other) const{
        if(!check_unit(other)){
            throw invalid_argument("Units do not match - ["+other.getUnit()+"] cannot be converted to ["+unit+"]");
        }
        return size >= change_unit(other);
    }
    bool NumberWithUnits::operator>(const NumberWithUnits &other) const{
        if(!check_unit(other)){
            throw invalid_argument("Units do not match - ["+other.getUnit()+"] cannot be converted to ["+unit+"]");
        }
        return size > change_unit(other);
    }
    bool NumberWithUnits::operator==(const NumberWithUnits &other) const{
        if(!check_unit(other)){
            throw invalid_argument("Units do not match - ["+other.getUnit()+"] cannot be converted to ["+unit+"]");
        }
        return (fabs(size - change_unit(other)) <= EPS);
    }
    bool NumberWithUnits::operator!=(const NumberWithUnits &other) const{
        return !(*this==other);
    }
    NumberWithUnits &NumberWithUnits::operator++(){
        size++;
        return *this;
    }
    NumberWithUnits NumberWithUnits::operator++(int){
        return NumberWithUnits(size ++, unit);
    }
    NumberWithUnits &NumberWithUnits::operator--(){
        size --;
        return *this;
    }
    NumberWithUnits NumberWithUnits::operator--(int){
        return NumberWithUnits(size --, unit);
    }
    NumberWithUnits operator*(double number, const NumberWithUnits &unit){
        return NumberWithUnits(number * unit.getSize(), unit.getUnit());
    }
    NumberWithUnits operator*(const NumberWithUnits &unit, double number){
        return NumberWithUnits(number * unit.getSize(), unit.getUnit());
    }

    istream &operator>>(istream &input, NumberWithUnits &unit){
        string str;
        getline(input, str, ']');
        str.erase(std::remove_if(str.begin(), str.end(), (int(*) (int)) std::isspace), str.end());
        string delimiter1 = "[";
        string delimiter2 = "]";
        size_t pos = 0;
        string array[2];
        pos = str.find(delimiter1);
        array[0] = str.substr(0,pos);
        str.erase(0,pos+delimiter1.length());
        pos = str.find(delimiter2);
        array[1] = str.substr(0, pos);
        unit = NumberWithUnits(stod(array[0]), array[1]);
        return input;
    }
    ostream &operator<<(ostream &output, const NumberWithUnits &unit){
        return output << unit.getSize() << "[" << unit.getUnit() << "]";
    }
    string NumberWithUnits::getUnit() const{
        return unit;
    }
    double NumberWithUnits::getSize() const{
        return size;
    }
}