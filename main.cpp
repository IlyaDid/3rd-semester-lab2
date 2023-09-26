#include <iostream>
#include "resource.hpp"
#include "menu.hpp"
int main(){
    size_t menu;
    resource res ,res2;
    do{
        try{
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
                default:
                    std::cout << "Введите корректную опцию" << std::endl;
                    break;
            }
        }catch(std::runtime_error& e){
            std::cerr << e.what();
            break;
        }
    }while(menu!=0);
    return 0;
}