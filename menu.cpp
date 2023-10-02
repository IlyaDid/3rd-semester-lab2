#include <iostream>
#include "resource.hpp"
resource input(){
    resource res;
    std::cout << "Введите по очереди: наименование, потребление(кг/д), производство(кг/д), цену(у.е/кг)" << std::endl;
    std::cin >> res;
    return res;
}
resource res_create(){
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
resource res_create_small(){
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
    if((l <=> r) == 0)
        std::cout << "Ресурсы равны" << std::endl;
    else if((l <=> r) > 0) std::cout << "Первый ресурс < второго" << std::endl;
    else if((l <=> r) < 0) std::cout << "Второй ресурс < первого" << std::endl;
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
void res_print(resource &res){
    std::cout << res;
}


resTable table_input(){
    resTable res;
    std::cout << "Введите количество записей в таблице, а после последовательно вводите каждый ресурс (наименование, потребление, производство, цену)" << std::endl;
    std::cin >> res;
    return res;
}
resTable table_load(){
    size_t sz;
    resource buf;
    std::cout << "Введите кол-во записей в массиве: ";
    sz = getNum<size_t>();
    std::vector<resource> arr;
    for(size_t i = 0; i < sz; i++){
        std::cin >> buf;
        arr.push_back(buf);
    }
    std::cout << "Введите кол-во записей для загрузки в таблицу: ";
    sz = getNum<size_t>();
    resTable table(sz, arr);
    return table;
}
resTable table_copy(){
    resTable res, copy;
    std::cout << "Введите количество записей в таблице, а после последовательно вводите каждый ресурс (наименование, потребление, производство, цену)" << std::endl;
    std::cin >> res;
    copy = resTable(res);
    return copy;
}
resTable table_move(){
    resTable res, move;
    std::cout << "Введите количество записей в таблице, а после последовательно вводите каждый ресурс (наименование, потребление, производство, цену)" << std::endl;
    std::cin >> res;
    move = std::move(res);
    return move;
}
void table_add(resTable& table){
    resource buf = input();
    table += buf;
}
void table_get(resTable& table){
    std::string name;
    std::cout << "Введите наименование ресурса: ";
    std::cin >> name;
    std::cout << table[name];
}
void table_state(resTable& table){
    int state = table.state();
    if(state)
        std::cout << "Таблица заполнена" << std::endl;
    else
        std::cout << "Таблица пуста" << std::endl;
}
void table_erase(resTable& table){
    std::string name;
    std::cout << "Введите наименование ресурса: ";
    std::cin >> name;
    table.erase(name);
}
void table_profit(resTable& table){
    std::cout << "Общая прибыльность: " << table.profit() << std::endl;
}
void table_turnov(resTable& table){
    size_t n;
    std::cout << "Введите множитель оборота: ";
    n = getNum<size_t>();
    table = table * n;
}
void table_rename(resTable& table){
    std::string name, newname;
    std::cout << "Введите наименование ресурса: ";
    std::cin >> name;
    std::cout << "Введите новое наименование ресурса: ";
    std::cin >> newname;
    table.rename(name, newname);
}
void table_print(resTable& table){
    std::cout << table;
}