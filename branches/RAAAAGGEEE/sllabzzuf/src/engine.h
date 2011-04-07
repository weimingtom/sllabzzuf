#ifndef ENGINE_H_INCLUDED
#define ENGINE_H_INCLUDED

#include "SDL/SDL.h"
#include "Timer.h"
#include "Stage.h"
#include "Player.h"

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480
#define WINDOW_BPP 32
#define FRAMES_PER_SECOND 30
#define WN 640, 480, 32, SDL_SWSURFACE|SDL_DOUBLEBUF
#define FS 640, 480, 32, SDL_DOUBLEBUF|SDL_FULLSCREEN

class Engine{
private:
	SDL_Surface *screen;

	Timer fps;
	Player player;
	Stage stage;

	SDL_Event event;
	Mix_Chunk *dash;
	bool quit;
	void gather_input();
	bool finished;

	int lastTicks;

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
