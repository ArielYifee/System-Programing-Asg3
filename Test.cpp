#include "doctest.h"
#include "NumberWithUnits.hpp"
#include <map>
#include <math.h>
#include <algorithm>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

using namespace ariel;
using namespace std;


TEST_CASE("test the constructor"){
    ifstream units_file{"units.txt"};
    NumberWithUnits::read_units(units_file);
    CHECK_THROWS(NumberWithUnits check0(300, "celsius"));
    CHECK_NOTHROW(NumberWithUnits check1(5, "km"));
    CHECK_NOTHROW(NumberWithUnits check2(5, "m"));
    CHECK_NOTHROW(NumberWithUnits check3(5, "kg"));
    CHECK_NOTHROW(NumberWithUnits check4(5, "ton"));
    CHECK_NOTHROW(NumberWithUnits check5(5, "hour"));
    CHECK_NOTHROW(NumberWithUnits check6(5, "min"));
    CHECK_NOTHROW(NumberWithUnits check7(5, "USD"));
    CHECK_NOTHROW(NumberWithUnits check8(5, "ILS"));
}
TEST_CASE("test reader"){
    ifstream units_file{"units.txt"};
    CHECK_NOTHROW(NumberWithUnits::read_units(units_file););
}
TEST_CASE("test all the + operators"){
    ifstream units_file{"units.txt"};
    NumberWithUnits::read_units(units_file);
    NumberWithUnits A(5, "km");
    NumberWithUnits B(300, "m");
    NumberWithUnits C(300, "kg");
    CHECK_THROWS(A+C);
    CHECK_EQ((A+B).getSize(),5.3);
    CHECK_EQ((B+A).getSize(),5300);
    CHECK_EQ((A++).getSize(),5);
    CHECK_EQ((++A).getSize(),7);
    CHECK_EQ((A+=B).getSize(),7.3);
    CHECK_EQ((B++).getSize(),300);
    CHECK_EQ((++B).getSize(),302);
    CHECK_EQ((B+=A).getSize(),7602);
}
TEST_CASE("test all the - operators"){
    ifstream units_file{"units.txt"};
    NumberWithUnits::read_units(units_file);
    NumberWithUnits A(5, "ton");
    NumberWithUnits B(300, "kg");
    NumberWithUnits C(300, "km");
    CHECK_THROWS(A-C);
    CHECK_EQ((A-B).getSize(),4.7);
    CHECK_EQ((B-A).getSize(),-4700);
    CHECK_EQ((A--).getSize(),5);
    CHECK_EQ((--A).getSize(),3);
    CHECK_EQ((A-=B).getSize(),2.7);
    CHECK_EQ((B--).getSize(),300);
    CHECK_EQ((--B).getSize(),298);
    CHECK_EQ((B-=A).getSize(),-2402);
    CHECK_EQ((-B).getSize(),2402);
}

TEST_CASE("test all the comperation operators"){
    ifstream units_file{"units.txt"};
    NumberWithUnits::read_units(units_file);
    NumberWithUnits A(5, "ton");
    NumberWithUnits B(5000, "kg");
    NumberWithUnits C(3, "km");
    NumberWithUnits D(3000, "m");
    NumberWithUnits E(121, "min");
    NumberWithUnits F(2, "hour");
    bool c;
    CHECK((A == B) == true);
    CHECK((B == A) == true);
    CHECK_THROWS(c = (A == C));
    CHECK_THROWS(c = (C == B));
    CHECK((F > E) == false);
    CHECK((F < E) == true);
    CHECK((F <= E) == true);
    CHECK((F >= E) == false);
    CHECK_THROWS(c = (F <= D));
    CHECK_THROWS(c = (F >= D));
    CHECK((C != D) == false);
    CHECK_THROWS(c = (C != A));
}
TEST_CASE("test * operators"){
    ifstream units_file{"units.txt"};
    NumberWithUnits::read_units(units_file);
    NumberWithUnits A(3, "ton");
    NumberWithUnits B(3, "km");
    CHECK((A*5).getSize() == 15);  
    CHECK((5*B).getSize() == 15);
}
TEST_CASE("test cout operator"){
    ifstream units_file{"units.txt"};
    NumberWithUnits::read_units(units_file);
    NumberWithUnits A(3, "ton");
    NumberWithUnits B(3, "km");
    ostringstream C;
    ostringstream D;
    C << A;
    D << B;
    CHECK_EQ(C.str(), "3[ton]");
    CHECK_EQ(D.str(), "3[km]");    
}
TEST_CASE("test cin operator"){
    ifstream units_file{"units.txt"};
    NumberWithUnits::read_units(units_file);
    NumberWithUnits A(3, "ton");
    NumberWithUnits B(3, "km");
    istringstream sample_input1{"700 [ kg ]"};
    istringstream sample_input2{"50 [ m ]"};
    istringstream sample_input3{"50 [ celsius ]"};
    sample_input1 >> A;
    CHECK_THROWS(sample_input3 >> B);
    sample_input2 >> B;
    CHECK_EQ(A, NumberWithUnits(700, "kg"));
    CHECK_EQ(B, NumberWithUnits(50, "m"));
}