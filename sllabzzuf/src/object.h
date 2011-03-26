#ifndef OBJECT_H_INCLUDED
#define OBJECT_H_INCLUDED

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"

class Object{
protected:
int x,y,w,h;
SDL_Surface *sprite;
public:
Object();
Object(int my_x, int my_y);
Object(int my_x, int my_y, int my_w, int my_h);
~Object();
int get_x();
int get_y();
};


#endif // OBJECT_H_INCLUDED
