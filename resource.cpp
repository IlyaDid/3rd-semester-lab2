#include <iostream>
#include "resource.hpp"
/*!
    Default constructor
*/
resource::resource(){
    this->name = "";
    this->consumption = 0;
    this->production = 0;
    this->price = 0;
}
/*!
    @param name Name of resource
    @param consumption Consumption of resource(kilogramms/day)
    @param production Production of resource(kilogramms/day)
    @param price Price of resource(universal unit/kilogramm)
    
    Full constructor
*/
resource::resource(const std::string& name, const size_t consumption, const size_t production, const size_t price){
    this->name = name;
    this->consumption = consumption;
    this->production = production;
    this->price = price;
}
/*!
    @param name Name of resource
    @param price Price of resource(universal unit/kilogramm)
    
    Partial constructor
*/
resource::resource(const std::string& name, const size_t price){
    this->name = name;
    this->consumption = 0;
    this->production = 0;
    this->price = price;
}
/*!
    @returns name Name of resource
    
    Name getter
*/
std::string resource::getName(){
    return name;
}
/*!
    @returns consumption Consumption of resource(kilogramms/day)
    
    Consumption getter
*/
size_t resource::getConsumption(){
    return consumption;
}
/*!
    @returns production Production of resource(kilogramms/day)
    
    Production getter
*/
size_t resource::getProduction(){
    return production;
}
/*!
    @returns price Price of resource(universal unit/kilogramm)
    
    Price getter
*/
size_t resource::getPrice(){
    return price;
}
/*!
    @param name Name of resource
    
    Name setter
*/
void resource::setName(const std::string& name){
    this->name = name;
}
/*!
    @param consumption Consumption of resource(kilogramms/day)
    
    Consumption setter
*/
void resource::setConsumption(const size_t consumption){
    this->consumption = consumption;
}
/*!
    @param production Production of resource(kilogramms/day)
    
    Production setter
*/
void resource::setProduction(const size_t production){
    this->production = production;
}
/*!
    @param price Price of resource(universal unit/kilogramm)
    
    Price setter
*/
void resource::setPrice(const size_t price){
    this->price = price;
}
/*!
    @param os Output stream
    @param res Resource
    @returns Output stream
    
    Output of resource
*/
std::ostream& operator<<(std::ostream& os, const resource& res){
    std::cout << "Имя: " << res.name << std::endl;
    std::cout << "Потребление: " << res.consumption << std::endl;
    std::cout << "Производство: " << res.production << std::endl;
    std::cout << "Цена: " << res.price << std::endl;
    return os;
}
/*!
    @param is Input stream
    @param res Resource
    @returns Input stream
    
    Input of resource
*/
std::istream& operator>>(std::istream& is, resource& res){
    std::cin >> res.name;
    res.consumption = getNum<size_t>();
    res.production = getNum<size_t>();
    res.price = getNum<size_t>();
    return is;
}
/*!
    @param rv Resource
    @returns Resource
    @throws std::runtime_error Different names addition
    
    Sum of resources with same name(consumption and production are added and price is minimal)
*/
resource resource::operator+(const resource& rv){
    if(name != rv.name)
        throw std::runtime_error("Resources with different name can`t be added");
    consumption += rv.consumption;
    production += rv.production;
    if(price > rv.price)
        price = rv.price;
    return *this;
}
/*!
    @param rv Resource
    @returns Result of comparison
    
    Comparison of resources by name
*/
bool resource::operator<(const resource& rv) const{
    if(name < rv.name) return 1;
    else return 0;
}
bool resource::operator>(const resource& rv) const{
    if(name > rv.name) return 1;
    else return 0;
}
bool resource::operator==(const resource& rv) const{
    if(name == rv.name) return 1;
    else return 0;
}
/*!
    @param rv Multiplier
    @returns Resource
    
    Multiplication of turnover(consumption and production)
*/
resource resource::operator*(const size_t rv){
    consumption *= rv;
    production *= rv;
    return *this;
}
/*!
    @returns Profit
    
    Calculation of weekly profit
*/
long int resource::profit(){
    return (production - consumption)*price*7;
}


/*!
    Default constructor
*/
vec::vec(){
    arr = nullptr;
    sz = 0;
}
/*!
    @param sz Size of vector
    @throws std::bad_alloc Bad alloc
    
    Constructor by size
*/
vec::vec(const size_t& sz){
    try{
        arr = new resource[sz];
    }catch(std::bad_alloc& e){  
        this->sz = 0;
        throw std::bad_alloc(e);
    }
    this->sz = sz;
}
/*!
    @param rv Vector to copy
    @returns Vector
    
    Copy assignment operator
*/
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
/*!
    @param rv Vector to move
    @returns Vector
    
    Move assignment operator
*/
vec &vec::operator=(vec&& rv){
    arr = rv.arr;
    sz = rv.sz;
    rv.arr = nullptr;
    rv.sz = 0;
    return *this;
}
/*!
    Destructor
*/
vec::~vec(){
    if(arr)
        delete[] arr;
    sz = 0;
}
/*!
    @param pos Position in vector
    @returns Resource
    @throws std::runtime_error Access to unallocated memory
    
    Access to element of vector by position
*/
resource &vec::operator[](const size_t& pos){
    if(pos >= sz)
        throw std::runtime_error("Accessing unallocated memory");
    return arr[pos];
}
/*!
    @param res Resource
    @throws std::bad_alloc Bad alloc
    
    Adds resource to the end of vector
*/
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
/*!
    @throws std::runtime_error Empty array
    @throws std::bad_alloc Bad alloc
    
    Deletes resource from the end of vector
*/
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
/*!
    @param name Name of element
    @throws std::runtime_error Out of range
    
    Deletes element by name
*/
void vec::erase(const std::string& name){
    size_t pos = 0;
    while(arr[pos].getName() != name){
        if(pos == sz - 1)
            throw std::runtime_error("Out of range");
        pos++;
    }
    for(size_t i = pos; i < sz - 1; i++)
        arr[pos] = arr[pos+1];
    pop_back();
}
/*!
    @returns Size of vector
    
    Get size of vector
*/
size_t vec::size(){
    return sz;
}


/*!
    @returns Size of table
    
    Get size of table
*/
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
/*!
    @param am Size
    @param arr Vector of resources
    
    Constructor by copying from vector
*/
resTable::resTable(const size_t& am, const std::vector<resource>& arr){
    table = vec(am);
    for(size_t i = 0; i < am; i++)
        table[i] = arr[i];
    this->sort();
}
/*!
    @param t Resource table
    
    Copy constructor
*/
resTable::resTable(const resTable& t){
    table = t.table;
}
/*!
    @param t Resource table
    
    Move constructor
*/
resTable::resTable(resTable&& t){
    table = t.table;
}
/*!
    @param os Output stream
    @param res Resource table
    @returns Output stream
    
    Output of resource table
*/
std::ostream& operator<<(std::ostream& os, resTable& res){
    for(size_t i = 0; i < res.size(); i++){
        std::cout << "Имя: " << res.table[i].getName() << " " << "Потребление: " << res.table[i].getConsumption() << " ";
        std::cout << "Производство: " << res.table[i].getProduction() << " " << "Цена: " << res.table[i].getPrice() << std::endl;
    }
    return os;
}
/*!
    @param is Input stream
    @param res Resource table
    @returns Input stream
    
    Input of resource table
*/
std::istream& operator>>(std::istream& is, resTable& res){
    resource buf;
    size_t sz = getNum<size_t>();
    for(size_t i = 0; i < sz; i++){
        std::cin >> buf;
        res += buf;
    }
    return is;
}
/*!
    @param name Name of resource
    @returns Resource
    @throws std::runtime_error Not found
    
    Access to element of table by its name
*/
resource &resTable::operator[](const std::string& name){
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
/*!
    @param rv Resource
    @returns Resource table
    @throws std::runtime_error Already in table
    
    Adding new element to table
*/
resTable resTable::operator+=(const resource& rv){
    resource buf(rv);
    try{
        (*this)[buf.getName()];
        throw std::runtime_error("Resource already in table");
    }catch(std::runtime_error& e1){
        table.push_back(buf);
        sort();
        return *this;
    }
    return *this;
}
/*!
    @param rv Multiplier
    @returns Resource table
    
    Multiplies turnover of all elements
*/
resTable resTable::operator*(const size_t& rv){
    for(size_t i = 0; i < table.size(); i++)
        table[i] = table[i] * rv;
    return *this;
}
/*!
    @param rv Resource table
    @returns Resource table
    
    Copy assignment operator
*/
resTable &resTable::operator=(resTable& rv){
    if(this != &rv)
        table = rv.table;
    return *this;
}
/*!
    @param rv Resource table
    @returns Resource table
    
    Move assignment operator
*/
resTable &resTable::operator=(resTable&& rv){
    if(this != &rv)
        table = rv.table;
    return *this;
}
/*!
    @returns Empty or Full
    
    State of table
*/
int resTable::state(){
    if(!table.size())
        return 0;
    else
        return 1;
}
/*!
    @param name Name of resource
    
    Delete element by name
*/
void resTable::erase(const std::string& name){
    table.erase(name);
}
/*!
    @returns Profit
    
    Calculates profit of all resources in table
*/
size_t resTable::profit(){
    size_t profit = 0;
    for(size_t i = 0; i < table.size(); i++)
        profit += table[i].profit();
    return profit;
}
/*!
    @param name Resource name
    @param newname New resource name
    
    Renames element
*/
void resTable::rename(const std::string& name, const std::string& newname){
    resource &res = (*this)[name];
    res.setName(newname);
    sort();
}