#include "Particle.h"

Particle::Particle(int start_x, int start_y, Uint8 color[], int particle_lifespan, Uint8 end_color[], float radians, int start_speed){
    speed=start_speed;
    red=color[0];
    green=color[1];
    blue=color[2];
    Uint8 final_red=end_color[0];
    Uint8 final_green=end_color[1];
    Uint8 final_blue=end_color[2];
    lifespan=particle_lifespan;
    red_rate=(final_red-red)/lifespan;
    blue_rate=(final_blue-blue)/lifespan;
    green_rate=(final_green-green)/lifespan;
    orientation=radians;
    x=start_x+(rand()%30)-15;
    y=start_y+(rand()%30)-15;
    life_timer=0;
    srand ( time(0) );
    magnitude=rand()%4;
    period=rand()%10-5;
    sin_based=true;
}
void Particle::update_self(){
    if(sin_based){
        orientation = orientation+(magnitude*(sin(life_timer)+period))/2;
        x+= (int)(speed*(cos(orientation)));
        y+= (int)(speed*(sin(orientation)));
    }
    red+=red_rate;
    blue+=blue_rate;
    green+=green_rate;
    life_timer+=1;
    speed-=1;
}
Uint8 Particle::get_red(){
return red;
}
Uint8 Particle::get_green(){
return green;
}
Uint8 Particle::get_blue(){
return blue;
}
int Particle::get_x(){
    return x;
}
int Particle::get_y(){
    return y;
}
void Particle::suicide(){
    life_timer=lifespan+1;
}
bool Particle::is_dead(){
    return (life_timer>lifespan);
}

