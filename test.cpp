#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include <sstream>
#include "resource.hpp"

TEST_CASE("Resource class"){
    SECTION("Constructors"){
        resource r1;
        REQUIRE(r1.getName() == "");
        REQUIRE(r1.getConsumption() == 0);
        REQUIRE(r1.getProduction() == 0);
        REQUIRE(r1.getPrice() == 0);
        resource r2("Fish", 10, 12, 10);
        REQUIRE(r2.getName() == "Fish");
        REQUIRE(r2.getConsumption() == 10);
        REQUIRE(r2.getProduction() == 12);
        REQUIRE(r2.getPrice() == 10);
        resource r3("Meat", 20);
        REQUIRE(r3.getName() == "Meat");
        REQUIRE(r3.getConsumption() == 0);
        REQUIRE(r3.getProduction() == 0);
        REQUIRE(r3.getPrice() == 20);
    }
    SECTION("Setters"){
        resource r;
        r.setName("Car");
        REQUIRE(r.getName() == "Car");
        r.setConsumption(2353482);
        REQUIRE(r.getConsumption() == 2353482);
        r.setProduction(42849244);
        REQUIRE(r.getProduction() == 42849244);
        r.setPrice(2345000);
        REQUIRE(r.getPrice() == 2345000);
    }
    SECTION("Operators"){
        resource r1("Cola", 345, 500, 167);
        resource r2("Cola", 200, 234, 100);
        resource r;
        r = r1 + r2;
        REQUIRE(r.getConsumption() == 545);
        REQUIRE(r.getProduction() == 734);
        REQUIRE(r.getPrice() == 100);
        r1.setName("D");
        bool x = r1 > r2;
        REQUIRE(x == 1);
        x = r1 < r2;
        REQUIRE(x == 0);
        x = (r1 == r2);
        REQUIRE(x == 0);
        resource r3("Cola", 345, 500, 100);
        r3 = r3 * 3;
        REQUIRE(r3.getConsumption() == 3*345);
        REQUIRE(r3.getProduction() == 3*500);
        resource r4;
        std::stringstream in("Cola 200 234 167");
        in >> r4;
        REQUIRE(r4.getName() == "Cola");
        REQUIRE(r4.getConsumption() == 200);
        REQUIRE(r4.getProduction() == 234);
        REQUIRE(r4.getPrice() == 167);
        std::stringstream out;
        out << r4;
        REQUIRE(out.str() == "Имя: Cola\nПотребление: 200\nПроизводство: 234\nЦена: 167\n");
    }
    SECTION("Functional methods"){
        resource r("Cola", 345, 500, 100);
        long int x = r.profit();
        REQUIRE(x == 7*100*(500-345));
    }
    SECTION("Test exception"){
        resource r1("Cola", 100);
        resource r2("Meat", 167);
        REQUIRE_THROWS(r1 = r1 + r2);
    }
}
TEST_CASE("Vector class"){
    SECTION("Constructors"){
        vec v1;
        REQUIRE(v1.size() == 0);
        vec v2(5);
        REQUIRE(v2.size() == 5);
    }
    SECTION("Operators and functional methods"){
        resource r1("Cola", 100);
        resource r2("Meat", 167);
        vec v(2);
        REQUIRE(v.size() == 2);
        v[0] = r1;
        v[1] = r2;
        REQUIRE(v[0].getName() == "Cola");
        REQUIRE(v[0].getPrice() == 100);
        REQUIRE(v[1].getName() == "Meat");
        REQUIRE(v[1].getPrice() == 167);
        resource r3("Fish", 80);
        v.push_back(r3);
        REQUIRE(v[2].getName() == "Fish");
        REQUIRE(v[2].getPrice() == 80);
        v.pop_back();
        REQUIRE(v.size() == 2);
        v.erase("Cola");
        REQUIRE(v[0].getName() == "Meat");
    }
    SECTION("Test exception"){
        resource r1("Cola", 100);
        resource r2("Meat", 167);
        vec v1(2);
        v1[0] = r1;
        v1[1] = r2;
        REQUIRE_THROWS(r1 = v1[2]);
        REQUIRE_THROWS(v1.erase("Fish"));
        vec v2;
        REQUIRE_THROWS(v2.pop_back());
    }
}
TEST_CASE("resTable class"){
    SECTION("Constructors"){
        resource r1("Cola", 100);
        resource r2("Meat", 167);
        std::vector<resource> v;
        v.push_back(r1);
        v.push_back(r2);
        resTable t1(1, v);
        REQUIRE(t1.size() == 1);
        REQUIRE(t1["Cola"].getPrice() == 100);
        resTable t2(t1);
        REQUIRE(t2.size() == 1);
        REQUIRE(t2["Cola"].getPrice() == 100);
        resTable t3(std::move(t2));
        REQUIRE(t3.size() == 1);
        REQUIRE(t3["Cola"].getPrice() == 100);
    }
    SECTION("Operators"){
        resource r1("Cola", 10, 12, 100);
        resTable t1;
        t1 += r1;
        REQUIRE(t1.size() == 1);
        REQUIRE(t1["Cola"].getPrice() == 100);
        t1 = t1 * 2;
        REQUIRE(t1["Cola"].getConsumption() == 20);
        REQUIRE(t1["Cola"].getProduction() == 24);
        resTable &t2 = t1;
        resTable t3;
        t3 = t2;
        REQUIRE(t3["Cola"].getConsumption() == 20);
        REQUIRE(t3["Cola"].getProduction() == 24);
        resTable t4;
        std::stringstream in("1 Cola 200 234 167");
        in >> t4;
        REQUIRE(t4["Cola"].getConsumption() == 200);
        REQUIRE(t4["Cola"].getProduction() == 234);
        REQUIRE(t4["Cola"].getPrice() == 167);
        std::stringstream out;
        out << t4;
        REQUIRE(out.str() == "Имя: Cola Потребление: 200 Производство: 234 Цена: 167\n");
    }
    SECTION("Functional methods"){
        resource r1("Cola", 10, 12, 100);
        resTable t;
        t += r1;
        REQUIRE(t.state() == 1);
        REQUIRE(t.profit() == 7*100*(12 - 10));
        t.erase("Cola");
        REQUIRE(t.size() == 0);
        t += r1;
        t.rename("Cola", "Sprite");
        REQUIRE(t["Sprite"].getConsumption() == 10);
        REQUIRE(t["Sprite"].getProduction() == 12);
        REQUIRE(t["Sprite"].getPrice() == 100);
    }
    SECTION("Test exception"){
        resource r1("Cola", 10, 12, 100);
        resTable t1;
        t1 += r1;
        REQUIRE_THROWS(r1 = t1["Fish"]);
    }
}