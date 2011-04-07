#ifndef CAMERA_H_INCLUDED
#define CAMERA_H_INCLUDED

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

#include "SDL/SDL.h"

class Camera{
private:
SDL_Rect bounds;
public:
Camera();
SDL_Rect *get_bounds();
int get_x();
int get_y();
int get_w();
int get_h();
void set_x(int x);
void set_y(int y);
};

#endif // CAMERA_H_INCLUDED
