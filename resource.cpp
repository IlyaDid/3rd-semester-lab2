#include <iostream>
#include "resource.hpp"
resource::resource(){
    this->name = "";
    this->consumption = 0;
    this->production = 0;
    this->price = 0;
}
explicit resource::resource(const std::string& name, const size_t consumption, const size_t production, const size_t price){
    this->name = name;
    this->consumption = consumption;
    this->production = production;
    this->price = price;
}
explicit resource::resource(const std::string& name, const size_t price){
    this->name = name;
    this->consumption = 0;
    this->production = 0;
    this->price = price;
}
std::string resource::getName(){
    return name;
}
size_t resource::getConsumption(){
    return consumption;
}
size_t resource::getProduction(){
    return production;
}
size_t resource::getPrice(){
    return price;
}
void resource::setName(const std::string& name){
    this->name = name;
}
void resource::setConsumption(const size_t consumption){
    this->consumption = consumption;
}
void resource::setProduction(const size_t production){
    this->production = production;
}
void resource::setPrice(const size_t price){
    this->price = price;
}
void resource::init(){
    std::cout << "Enter resource name: ";
    std::cin >> name;
    try{
        std::cout << "Enter consumption: ";
        consumption = getNum<size_t>();
        std::cout << "Enter production: ";
        production = getNum<size_t>();
        std::cout << "Enter price: ";
        price = getNum<size_t>();
    }catch(std::runtime_error& e){
        name = "";
        consumption = 0;
        production = 0;
        price = 0;
        throw std::runtime_error(e.what());
    }
}
void resource::print(){
    std::cout << "Name: " << name << std::endl;
    std::cout << "Consumption: " << consumption << std::endl;
    std::cout << "Production: " << production << std::endl;
    std::cout << "Price: " << price << std::endl;
}
resource resource::operator+(const resource& rv){
    if(name != rv.name)
        throw std::runtime_error("Resources with different name can`t be added");
    consumption += rv.consumption;
    production += rv.production;
    if(price > rv.price)
        price = rv.price;
}
bool resource::operator<=>(const resource& rv){
    if(name == rv.name)
        return 0;
    else if(name < rv.name)
        return -1;
    else
        return 1;
}
resource resource::operator*(const size_t rv){
    consumption *= rv;
    production *= rv;
}
resource *resTable::sort(){
    resource buf;
    for(size_t i = 0; i < size; i++){
        for(size_t j = 0; j < size - 1; j++){
            if(table[j] > table[j+1]){
                buf = table[j+1];
                table[j+1] = table[j];
                table[j] = buf;
            }
        }
    }
}
resTable::resTable(){
    size = 0;
    table = nullptr;
}
resTable::resTable(size_t am, const resource *arr){
    table = new resource[am];
    for(size_t i = 0; i < am; i++)
        table[i] = arr[i];
    this->sort();
}
resTable::resTable(const resTable& t){
    size = t.size;
    table = new resource[size];
    for(size_t i = 0; i < size; i++)
        table[i] = t.table[i];
}
resTable::resTable(resTable&& t){
    size = t.size;
    table = t.table;
    t.size = 0;
    t.table = nullptr;
}
resTable::~resTable(){
    delete[] table;
}