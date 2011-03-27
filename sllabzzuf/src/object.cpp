#include"object.h"

Object::Object(){
    x =0;
    y =0;
    w = 32;
    h = 32;
    sprite=NULL;
    friction=2;
    friction_increment=0;
}

Object::Object(int my_x, int my_y){
    x = my_x;
    y = my_y;
    w = 32;
    h = 32;
    friction=2;
    friction_increment=0;
}

Object::Object(int my_x, int my_y, int my_w, int my_h){
    x = my_x;
    y = my_y;
    w = my_w;
    h = my_h;
    friction=2;
    friction_increment=0;
}

Object::~Object(){
if(sprite!=NULL)
SDL_FreeSurface(sprite);
}

int Object::get_x(){
return x;
}

int Object::get_y(){
    return y;
}

int Object::get_w(){
return w;
}

int Object::get_h(){
    return h;
}

bool Object::move_x(int amount, int current_x, int current_y, Stage stage){
    current_x += amount;
    if(amount>0){
        if(!stage.object_hitTest(1,current_x, current_y)){
        x += amount;
        return true;
        }
    }
    if(amount<0){
        if(!stage.object_hitTest(3,current_x, current_y)){
        x += amount;
        return true;
        }
    }
    return false;
}
bool Object::move_y(int amount, int current_x, int current_y, Stage stage){
    current_y += amount;
    if(amount>0){
        if(!stage.object_hitTest(2,current_x, current_y)){
        y += amount;
        return true;
        }
    }
    if(amount<0){
        if(!stage.object_hitTest(0,current_x, current_y)){
            y += amount;
            return true;
        }
    }
    return false;
}
