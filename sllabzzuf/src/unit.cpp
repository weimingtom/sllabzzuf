#include "unit.h"

Unit::Unit(){
x=0;
y=0;
max_hp=5;
}

Unit::Unit(int new_x, int new_y, int new_max_hp){
    x=new_x;
    y=new_y;
    max_hp=new_max_hp;
    hp=new_max_hp;
}

int Unit::get_weight(){
return weight;
}

int Unit::get_current_hp(){
return hp;
}

void Unit::move_x(int amount){
    x+=amount;
}

void Unit::move_y(int amount){
    y+=amount;
}

bool Unit::is_alive(){
    if(hp>0)
    return true;
    return false;
}
