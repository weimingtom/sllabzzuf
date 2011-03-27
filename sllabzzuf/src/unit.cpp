#include "unit.h"

Unit::Unit(){
x=0;
y=0;
hp=5;
}

Unit::Unit(int new_x, int new_y, int new_hp){
    x=new_x;
    y=new_y;
    hp=new_hp;
}

int Unit::get_weight(){
return weight;
}

int Unit::get_hp(){
return hp;
}

bool Unit::is_alive(){
    if(hp>0)
    return true;
    return false;
}
