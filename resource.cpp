#include <iostream>
#include "resource.hpp"
resource::resource(){
    this->name = "";
    this->consumption = 0;
    this->production = 0;
    this->price = 0;
}
resource::resource(const std::string& name, const size_t consumption, const size_t production, const size_t price){
    this->name = name;
    this->consumption = consumption;
    this->production = production;
    this->price = price;
}
resource::resource(const std::string& name, const size_t price){
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
std::ostream& operator<<(std::ostream& os, const resource& res){
    std::cout << "Имя: " << res.name << std::endl;
    std::cout << "Потребление: " << res.consumption << std::endl;
    std::cout << "Производство: " << res.production << std::endl;
    std::cout << "Цена: " << res.price << std::endl;
    return os;
}
std::istream& operator>>(std::istream& is, resource& res){
    std::cin >> res.name;
    res.consumption = getNum<size_t>();
    res.production = getNum<size_t>();
    res.price = getNum<size_t>();
    return is;
}
resource resource::operator+(const resource& rv){
    if(name != rv.name)
        throw std::runtime_error("Resources with different name can`t be added");
    consumption += rv.consumption;
    production += rv.production;
    if(price > rv.price)
        price = rv.price;
    return *this;
}
bool resource::operator<=>(const resource& rv) const{
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
    return *this;
}
long int resource::profit(){
    return (production - consumption)*price*7;
}


vec::vec(){
    arr = nullptr;
    sz = 0;
}
vec::vec(const size_t& sz){
    try{
        arr = new resource[sz];
    }catch(std::bad_alloc& e){
        this->sz = 0;
        throw std::bad_alloc(e);
    }
    this->sz = sz;
}
vec &vec::operator=(const vec& rv){
    if (this != &rv){
        if (sz != rv.sz){
            arr = new resource[rv.sz];
            sz = rv.sz;
        }
        std::copy(rv.arr, rv.arr + sz, arr);
    }
    return *this;
}
vec &vec::operator=(const vec&& rv){
    return *this;
}
vec::~vec(){
    if(arr)
        delete[] arr;
    sz = 0;
}
resource& vec::operator[](const size_t& pos){
    if(pos >= sz)
        throw std::runtime_error("Accessing unallocated memory");
    return arr[pos]; 
}
void vec::push_back(resource& res){
    resource *tmp;
    try{
        tmp = new resource[sz+1];
    }catch(std::bad_alloc& e){
        throw std::bad_alloc(e);
    }
    std::copy(arr, arr + sz, tmp);
    delete[] arr;
    arr = tmp;
    arr[sz] = res;
    sz++;
}
void vec::pop_back(){
    if(sz == 0)
        throw std::runtime_error("Array is already empty");
    else if(sz == 1){
        delete[] arr;
        sz = 0;
        arr = nullptr;
        return;
    }
    resource *tmp;
    try{
        tmp = new resource[sz-1];
    }catch(std::bad_alloc& e){
        throw std::bad_alloc(e);
    }
    std::copy(arr, arr + sz - 1, tmp);
    delete[] arr;
    arr = tmp;
    sz--;
}
size_t vec::size(){
    return sz;
}


size_t resTable::size(){
    return table.size();
}
void resTable::sort(){
    resource buf;
    for(size_t i = 0; i < table.size(); i++){
        for(size_t j = 0; j < table.size() - 1; j++){
            if(table[j] > table[j+1]){
                buf = table[j+1];
                table[j+1] = table[j];
                table[j] = buf;
            }
        }
    }
}
resTable::resTable(const size_t& am, const std::vector<resource>& arr){
    try{
        table = vec(am);
    }catch(std::bad_alloc& e){
        throw std::bad_alloc(e);
    }
    for(size_t i = 0; i < am; i++)
        table[i] = arr[i];
    this->sort();
}
resTable::resTable(const resTable& t){
    try{
        table = t.table;
    }catch(std::bad_alloc& e){
        throw std::bad_alloc(e);
    }
}
resTable::resTable(const resTable&& t){
    try{
        table = t.table;
    }catch(std::bad_alloc& e){
        throw std::bad_alloc(e);
    }
}
std::ostream& operator<<(std::ostream& os, resTable& res){
    for(size_t i = 0; i < res.size(); i++){
        std::cout << "Имя: " << res.table[i].getName() << " " << "Потребление: " << res.table[i].getConsumption() << " ";
        std::cout << "Производство: " << res.table[i].getProduction() << " " << "Цена: " << res.table[i].getPrice() << std::endl;
    }
    return os;
}
std::istream& operator>>(std::istream& is, resTable& res){
    resource buf;
    size_t sz = getNum<size_t>();
    for(size_t i = 0; i < sz; i++){
        std::cin >> buf;
        res += buf;
    }
    return is;
}
resource& resTable::operator[](const std::string& name){
    if(this->size() == 0)
        throw std::runtime_error("Resource not found");
    size_t left = 0, right = table.size() - 1, middle;
    while(left <= right){
        middle = (left + right)/2;
        if(table[middle].getName() > name)
            right = middle - 1;
        else if(table[middle].getName() < name)
            left = middle + 1;
        else
            return table[middle];
    }
    throw std::runtime_error("Resource not found");
}
resTable resTable::operator+=(const resource& rv){
    resource buf(rv);
    try{
        (*this)[buf.getName()];
        throw std::runtime_error("Resource already in table");
    }catch(std::runtime_error& e1){
        try{
            table.push_back(buf);
            return *this;
        }catch(std::bad_alloc& e2){
            throw std::bad_alloc(e2);
        }
    }
    return *this;
}
resTable resTable::operator*(const size_t& rv){
    for(size_t i = 0; i < table.size(); i++)
        table[i] = table[i] * rv;
    return *this;
}
resTable &resTable::operator=(resTable& rv){
    if(this != &rv)
        table = rv.table;
    return *this;
}
resTable &resTable::operator=(const resTable&& rv){
    if(this != &rv)
        table = rv.table;
    return *this;
}
int resTable::state(){
    if(!table.size())
        return 0;
    else
        return 1;
}
void resTable::erase(const std::string& name){
    try{
        resource& res = (*this)[name];
        res = table[this->size()-1];
        table.pop_back();
        sort();
    }catch(std::bad_alloc& e1){
        throw std::bad_alloc(e1);
    }catch(std::runtime_error& e2){
        throw std::runtime_error(e2.what());
    }
}
size_t resTable::profit(){
    size_t profit = 0;
    for(size_t i = 0; i < table.size(); i++)
        profit += table[i].profit();
    return profit;
}
void resTable::rename(const std::string& name, const std::string& newname){
    try{
        resource& res = (*this)[name];
        res.setName(newname);
    }catch(std::runtime_error& e){
        throw std::runtime_error(e.what());
    }
}