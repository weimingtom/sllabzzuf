#ifndef ENGINE_H_INCLUDED
#define ENGINE_H_INCLUDED

#include "SDL/SDL.h"
#include "timer.h"
#include "stage.h"

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480
#define WINDOW_BPP 32
#define FRAMES_PER_SECOND 30

class Engine{
private:

Timer fps;
Stage stage;

SDL_Event event;
SDL_Surface *screen;
bool quit;
void gather_input();

public:
    Engine();
    ~Engine();
    bool running();
    bool flip();
    void get_time();
    void framerate_limit();
    void check_events();
    void display_stage();
};



#endif // ENGINE_H_INCLUDED
