#ifndef MENU_HPP_
#define MENU_HPP_
resource &res_create();
resource &res_create_small();
void res_get_name(resource& res);
void res_get_cons(resource& res);
void res_get_prod(resource& res);
void res_get_price(resource& res);
void res_set_name(resource& res);
void res_set_cons(resource& res);
void res_set_prod(resource& res);
void res_set_price(resource& res);
void res_sum(resource& l, const resource& r);
void res_equal(const resource& l, const resource& r);
void res_profit(resource& res);
void res_turnov(resource& res);
#endif