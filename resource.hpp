#include <string>
#include <map>
#ifndef RESOURCE_HPP_
#define RESOURCE_HPP_
class resource{
private:
    std::string name;
    size_t consumption; //Kilogramms per day
    size_t production; //Kilogramms per day
    size_t price; //Conventional unit per kilogramm
public:
    resource();
    explicit resource(const std::string& name, const size_t consumption, const size_t production, const size_t price);
    explicit resource(const std::string& name, const size_t price);
    std::string getName();
    size_t getConsumption();
    size_t getProduction();
    size_t getPrice();
    void setName(const std::string& name);
    void setConsumption(const size_t consumption);
    void setProduction(const size_t production);
    void setPrice(const size_t price);
    void init();
    void print();
    resource operator+(const resource& rv);
    bool operator<=>(const resource& rv);
    resource operator*(const size_t rv);
    long int profit();
};
class resTable{
private:
    size_t size;
    resource *table;
    resource *sort();
public:
    resTable();
    resTable(size_t am, const resource *arr);
    resTable(const resTable& t);
    resTable(resTable&& t);
    ~resTable();
    resTable operator+=(const resource& rv);
    resource& operator[](const std::string& name);
    resTable operator*(const size_t rv);
    int state();
    void erase(std::string& name);
    size_t profit();
    void rename(std::string& name, std::string& newname);
};
template <class T>
T getNum(T min = std::numeric_limits<T>::min(), T max = std::numeric_limits<T>::max()){
    T a;
    while (true) {
        std::cin >> a;
        if (std::cin.eof()) // обнаружен конец файла
            throw std::runtime_error("Failed to read number: EOF");
        else if (std::cin.bad()) // обнаружена невосстановимая ошибка входного потока
            throw std::runtime_error(std::string("Failed to read number: ") + strerror(errno));
        else if (std::cin.fail()) { // прочие ошибки (неправильный формат ввода)
            std::cin.clear(); // очищаем флаги состояния потока
        // игнорируем все символы до конца строки
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "You are wrong; repeat please!" << std::endl;
    }
    else{
        //std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        if (a >= min && a <= max) // если число входит в заданный диапазон
            return a;
    }
    }
}
#endif