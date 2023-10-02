#include <iostream>
#include "resource.hpp"
#include "menu.hpp"
int main(){
    size_t menu;
    resource res , res2;
    resTable table;
    std::cout << "Введите тестируемый класс:" << std::endl;
    std::cout << "1. Простой класс" << std::endl;
    std::cout << "2. Сложный класс" << std::endl;
    menu = getNum<size_t>();
    if(menu == 1){
        do{
            try{
                std::cout << "0. Выход" << std::endl;
                std::cout << "1. Конструктор полный" << std::endl;
                std::cout << "2. Конструктор частичный" << std::endl;
                std::cout << "3. Вывести имя" << std::endl;
                std::cout << "4. Вывести потребление" << std::endl;
                std::cout << "5. Вывести производство" << std::endl;
                std::cout << "6. Вывести цену" << std::endl;
                std::cout << "7. Ввести имя" << std::endl;
                std::cout << "8. Ввести потребление" << std::endl;
                std::cout << "9. Ввести производство" << std::endl;
                std::cout << "10. Ввести цену" << std::endl;
                std::cout << "11. Сумма ресурсов" << std::endl;
                std::cout << "12. Сравнение ресурсов" << std::endl;
                std::cout << "13. Вычисление прибыли" << std::endl;
                std::cout << "14. Умножение оборота" << std::endl;
                std::cout << "15. Вывод в консоль" << std::endl;
                std::cout << "Введите пункт от 0 до 15: ";
                menu = getNum<size_t>();
                switch(menu){
                    case 0:
                        break;
                    case 1:
                        res = res_create();
                        break;
                    case 2:
                        res = res_create_small();
                        break;
                    case 3:
                        res_get_name(res);
                        break;
                    case 4:
                        res_get_cons(res);
                        break;
                    case 5:
                        res_get_prod(res);
                        break;
                    case 6:
                        res_get_price(res);
                        break;
                    case 7:
                        res_set_name(res);
                        break;
                    case 8:
                        res_set_cons(res);
                        break;
                    case 9:
                        res_set_prod(res);
                        break;
                    case 10:
                        res_set_price(res);
                        break;
                    case 11:
                        res2 = res_create();
                        res_sum(res, res2);
                        break;
                    case 12:
                        res2 = res_create();
                        res_equal(res, res2);
                        break;
                    case 13:
                        res_profit(res);
                        break;
                    case 14:
                        res_turnov(res);
                        break;
                    case 15:
                        res_print(res);
                        break;
                    default:
                        std::cout << "Введите корректную опцию" << std::endl;
                        break;
                }
            }catch(std::runtime_error& e){
                std::cerr << e.what();
                break;
            }
        }while(menu!=0);
    }else if(menu == 2){
        do{
            try{
                std::cout << "0. Выход" << std::endl;
                std::cout << "1. Ввод" << std::endl;
                std::cout << "2. Конструктор загрузки из массива" << std::endl;
                std::cout << "3. Конструктор копирования" << std::endl;
                std::cout << "4. Конструктор перемещения" << std::endl;
                std::cout << "5. Добавить запись" << std::endl;
                std::cout << "6. Вывести запись" << std::endl;
                std::cout << "7. Состояние таблицы" << std::endl;
                std::cout << "8. Удалить запись" << std::endl;
                std::cout << "9. Вычислить прибыльность" << std::endl;
                std::cout << "10. Увеличить оборот" << std::endl;
                std::cout << "11. Переименовать запись" << std::endl;
                std::cout << "12. Вывод" << std::endl;
                std::cout << "Введите пункт от 0 до 12: ";
                menu = getNum<size_t>();
                switch(menu){
                    case 0:
                        break;
                    case 1:
                        table = table_input();
                        break;
                    case 2:
                        table = table_load();
                        break;
                    case 3:
                        table = table_copy();
                        break;
                    case 4:
                        table = table_move();
                        break;
                    case 5:
                        table_add(table);
                        break;
                    case 6:
                        table_get(table);
                        break;
                    case 7:
                        table_state(table);
                        break;
                    case 8:
                        table_erase(table);
                        break;
                    case 9:
                        table_profit(table);
                        break;
                    case 10:
                        table_turnov(table);
                        break;
                    case 11:
                        table_rename(table);
                        break;
                    case 12:
                        table_print(table);
                        break;
                    default:
                        std::cout << "Введите корректную опцию" << std::endl;
                        break;
                }
            }catch(std::runtime_error& e){
                std::cerr << e.what();
                break;
            }
        }while(menu!=0);
    }else
        std::cout << "Введите корректную опцию" << std::endl;
    return 0;
}