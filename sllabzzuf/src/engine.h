#ifndef ENGINE_H_INCLUDED
#define ENGINE_H_INCLUDED

#include "SDL/SDL.h"
#include "timer.h"
#include "stage.h"
#include "player.h"

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480
#define WINDOW_BPP 32
#define FRAMES_PER_SECOND 30

class Engine{
private:

SDL_Surface *screen;

int lastTime;
Player player;
Stage stage;

SDL_Event event;

bool quit;
void gather_input();
bool finished;

public:
    Engine();
    ~Engine();
    bool running();
    bool flip();
    void get_time();
    void framerate_limit();
    void check_events();
    void display();
    void update_objects();
};



#endif // ENGINE_H_INCLUDED
