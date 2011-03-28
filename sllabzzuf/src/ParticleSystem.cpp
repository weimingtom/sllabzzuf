#include "particlesystem.h"
#include <iostream>

ParticleSystem::ParticleSystem(int num_particles){
    particles=num_particles;
}
bool ParticleSystem::is_dead(Particle& particle){
    bool val=particle.is_dead();
    return val;
}
void ParticleSystem::particle_factory(int start_x, int start_y, Uint8 color[], int particle_lifespan, Uint8 end_color[], float radians, int start_speed){
    if(particles>0){
    Particle particle(start_x, start_y, color, particle_lifespan, end_color, radians, start_speed);
    pSystem.push_back(particle);
    }
    particles-=1;
}
void ParticleSystem::remove_dead(){
     for (std::list<Particle>::iterator it=pSystem.begin(); it!=pSystem.end(); ++it){
        if(it->is_dead())
        it = pSystem.erase(it);
     }
}
void ParticleSystem::update_all(){
     for (std::list<Particle>::iterator it=pSystem.begin(); it!=pSystem.end(); ++it){
        it->update_self();
     }
}
void ParticleSystem::draw_particles(SDL_Surface *screen, int camera_x, int camera_y, int mapw, int maph){
    int x, y;
    Uint8 red, green, blue;
    Uint32 color;
    Uint32 *bufp;
    for (std::list<Particle>::iterator it=pSystem.begin(); it!=pSystem.end(); ++it){
        if(it->get_x()-camera_x <= 0 || it->get_x()-camera_x+2 >=640 || it->get_y()-camera_y <=0 || it->get_y()-camera_y+2 >=480){
        it->suicide();
        }else{
        x = it->get_x()-camera_x;
        y = it->get_y()-camera_y;

        red = it->get_red();
        green = it->get_green();
        blue = it->get_blue();
        color = SDL_MapRGB(screen->format, red, green, blue);

        //std::cout << "red = " << (int)red << ", green = " << (int)green << ", blue= " << (int)blue << " x= "<< x << " y= " << y << ".\n";
        bufp = (Uint32 *)screen->pixels + (y+2)*screen->pitch/4 + (x+1);
        *bufp = color;
        bufp = (Uint32 *)screen->pixels + (y+1)*screen->pitch/4 + (x+2);
        *bufp = color;
        bufp = (Uint32 *)screen->pixels + (y+1)*screen->pitch/4 + x;
        *bufp = color;
        bufp = (Uint32 *)screen->pixels + y*screen->pitch/4 + (x+1);
        *bufp = color;
        bufp = (Uint32 *)screen->pixels + (y+1)*screen->pitch/4 + (x+1);
        *bufp = color;
        SDL_UpdateRect(screen, x, y, 3, 3);

        }
    }
}
