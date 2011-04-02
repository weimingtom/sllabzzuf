/*
 * Tile.cpp
 *
 *  Created on: Jan 30, 2011
 *      Author: Admin
 */

#include "Tile.h"

Tile::Tile (int x, int y, int my_type){
    box.x = x;
    box.y = y;

    box.w = 32;
    box.h = 32;
	type = my_type;

}

int Tile::get_type(){
    return type;
}
void Tile::set_type(int t){
	type = t;
}
SDL_Rect *Tile::get_box(){
    return &box;
}
void Tile::set_x(int new_x){
    box.x=new_x;
}
void Tile::set_y(int new_y){
    box.y=new_y;
}
