/*
 * Tile.h
 *
 *  Created on: Jan 30, 2011
 *      Author: Admin
 */

#ifndef TILE_H_
#define TILE_H_

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"

#include <vector>
#include <map>
#include <fstream>
#include <iostream>

class Tile{
private:
    SDL_Rect box;
    int type;

public:
    //Initializes the variables
    Tile (int x, int y, int type);

    //Get the tile type
    int get_type();
    void set_type(int t);
    //Get the collision box
    SDL_Rect *get_box();
};


#endif /* TILE_H_ */
