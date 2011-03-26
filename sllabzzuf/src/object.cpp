#include"object.h"

Object::Object(){
    x =0;
    y =0;
    w = 32;
    h = 32;
}

Object::Object(int my_x, int my_y){
    x = my_x;
    y = my_y;
    w = 32;
    h = 32;
}

Object::Object(int my_x, int my_y, int my_w, int my_h){
    x = my_x;
    y = my_y;
    w = my_w;
    h = my_h;
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
