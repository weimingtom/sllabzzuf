#ifndef OBJECT_H_INCLUDED
#define OBJECT_H_INCLUDED

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include <fstream>
#include <iostream>

#include "Stage.h"

class Object{
protected:
	int x,y,w,h;
	SDL_Surface *sprite;
	SDL_Surface *rawsprite;
	int friction;
	int friction_increment;
public:
	Object();
	Object(int my_x, int my_y);
	Object(int my_x, int my_y, int my_w, int my_h);
	~Object();
	int get_x();
	int get_y();
	int get_w();
	int get_h();
	bool move_x(int amount, int current_x, int current_y, Stage stage);
	bool move_y(int amount, int current_x, int current_y, Stage stage);
};


#endif // OBJECT_H_INCLUDED
