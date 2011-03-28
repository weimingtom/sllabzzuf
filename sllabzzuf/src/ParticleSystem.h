#ifndef PARTICLESYSTEM_H_INCLUDED
#define PARTICLESYSTEM_H_INCLUDED

#include "particle.h"
#include <list>

class ParticleSystem{
private:
    int particles;
    std::list<Particle> pSystem;
public:
    ParticleSystem(int num_particles);
    void particle_factory(int start_x, int start_y, Uint8 color[], int particle_lifespan, Uint8 end_color[], float radians, int start_speed);
    void remove_dead();
    void update_all();
    void draw_particles(SDL_Surface *screen, int camera_x, int camera_y, int mapw, int maph);
    bool is_dead(Particle& particle);
};

#endif // PARTICLESYSTEM_H_INCLUDED
