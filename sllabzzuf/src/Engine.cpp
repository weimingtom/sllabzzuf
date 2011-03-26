#include "engine.h"

Engine::Engine(){
    quit=false;

    SDL_Init( SDL_INIT_EVERYTHING);
    SDL_WM_SetCaption( "Fuzzball Game v0.0.1", NULL );

    screen = SDL_SetVideoMode( WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_BPP, SDL_SWSURFACE);
    if(screen==NULL){
    std::cout << "screen is still NULL\n";
    quit=true;
    }
    stage.newMap();
    Uint8 *SDL_GetKeyState(int *numkeys);

}

Engine::~Engine(){
    if(screen!=NULL)
    SDL_FreeSurface(screen);
    SDL_Quit();
}

bool Engine::flip(){
    if( SDL_Flip( screen ) == -1 )
    return false;
    return true;
}

bool Engine::running(){
    if(!quit)
    return true;
    return false;
}

void Engine::framerate_limit(){
    if( fps.get_ticks() < 1000 / FRAMES_PER_SECOND )
        SDL_Delay( ( 1000 / FRAMES_PER_SECOND ) - fps.get_ticks());
}

void Engine::check_events(){
         while( SDL_PollEvent( &event ) ){
            gather_input();
            if( event.type == SDL_QUIT ){
                quit=true;
            }
        }
}

void Engine::get_time(){
    fps.start();
}

void Engine::gather_input(){
    if( event.type == SDL_KEYDOWN )
    {
    	Uint8 *keystate = SDL_GetKeyState(NULL);
        switch(event.key.keysym.sym){
            case SDLK_UP:
				 (stage.get_camera_y() - 32) > 0 ? stage.set_camera_y(stage.get_camera_y() - 32) : stage.set_camera_y(0);
				 break;
            case SDLK_DOWN:
				 (stage.get_camera_y() + 32) < stage.get_mapHeightpx() - stage.get_camera_h() ? stage.set_camera_y(stage.get_camera_y() + 32) : stage.set_camera_y(stage.get_mapHeightpx() - stage.get_camera_h());
			 	 break;
			case SDLK_LEFT:
				 (stage.get_camera_x() - 32) > 0 ? stage.set_camera_x(stage.get_camera_x() - 32) : stage.set_camera_x(0);
				 break;
			case SDLK_RIGHT:
				 (stage.get_camera_x() + 32) < stage.get_mapWidthpx() - stage.get_camera_w() ? stage.set_camera_x(stage.get_camera_x() + 32) : stage.set_camera_x(stage.get_mapWidthpx() - stage.get_camera_w());
			 	 break;
        default: break;
        }
    }
}

void Engine::display_stage(){
  stage.display_terrain(screen);
}

