#include <iostream>
#include "resource.hpp"
resource &res_create(){
    std::string name;
    size_t cons, prod, price;
    std::cout << "Введите наименование: ";
    std::cin >> name;
    std::cout << "Введите потребление(кг/д): ";
    try{
        cons = getNum<size_t>();
        std::cout << "Введите производство(кг/д): ";
        prod = getNum<size_t>();
        std::cout << "Введите цену(у.е/кг): ";
        price = getNum<size_t>();
    }catch(std::runtime_error& e){
        std::cerr << e.what();
        resource res;
        return res;
    }
    resource res(name, cons, prod, price);
    return res;
}
resource &res_create_small(){
    std::string name;
    size_t price;
    std::cout << "Введите наименование: ";
    std::cin >> name;
    std::cout << "Введите цену(у.е/кг): ";
    try{
        price = getNum<size_t>();
    }catch(std::runtime_error& e){
        std::cerr << e.what();
        resource res;
        return res;
    }
    resource res(name, price);
    return res;
}
void res_get_name(resource& res){
    std::cout << "Наименование: " << res.getName() << std::endl;
}
void res_get_cons(resource& res){
    std::cout << "Потребление: " << res.getConsumption() << std::endl;
}
void res_get_prod(resource& res){
    std::cout << "Производство: " << res.getProduction() << std::endl;
}
void res_get_price(resource& res){
    std::cout << "Цена: " << res.getPrice() << std::endl;
}
void res_set_name(resource& res){
    std::string name;
    std::cout << "Введите наименование: ";
    std::cin >> name;
    res.setName(name);
}
void res_set_cons(resource& res){
    size_t cons;
    std::cout << "Введите потребление: ";
    try{
        cons = getNum<size_t>();
    }catch(std::runtime_error& e){
        std::cerr << e.what();
        return;
    }
    res.setConsumption(cons);
}
void res_set_prod(resource& res){
    size_t prod;
    std::cout << "Введите производство: ";
    try{
        prod = getNum<size_t>();
    }catch(std::runtime_error& e){
        std::cerr << e.what();
        return;
    }
    res.setProduction(prod);
}
void res_set_price(resource& res){
    size_t price;
    std::cout << "Введите цену: ";
    try{
        price = getNum<size_t>();
    }catch(std::runtime_error& e){
        std::cerr << e.what();
        return;
    }
    res.setPrice(price);
}
void res_sum(resource& l, const resource& r){
    try{
        l = l + r;
    }catch(std::runtime_error& e){
        std::cerr << e.what();
    }
}
void res_equal(const resource& l, const resource& r){
    
}
void res_profit(resource& res){
    std::cout << "Ориентировочная прибыльность: " << res.profit() << std::endl;
}
void res_turnov(resource& res){
    size_t n;
    std::cout << "Введите множитель оборота: ";
    try{
        n = getNum<size_t>();
    }catch(std::runtime_error& e){
        std::cerr << e.what();
        return;
    }
    res = res * n;
}
