#ifndef PARTICLE_H_INCLUDED
#define PARTICLE_H_INCLUDED

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include <time.h>
#include <stdlib.h>
#include <cmath>

class Particle{
    private:
    int x, y;
    Uint8 red, blue, green;
    Uint8 red_rate, blue_rate, green_rate;
    int life_timer, lifespan;
    int speed;
    float orientation;
    bool sin_based;
    int magnitude, period;
    Uint8 color[3];
    public:
    Particle(int start_x, int start_y, Uint8 color[], int particle_lifespan, Uint8 end_color[], float radians, int speed);
    void update_self();
    Uint8 get_red();
    Uint8 get_green();
    Uint8 get_blue();
    int get_x();
    int get_y();
    bool is_dead();
    void suicide();

};

#endif // PARTICLE_H_INCLUDED
