#include "engine.h"

Engine::Engine(){
    quit=false;

    SDL_Init( SDL_INIT_EVERYTHING);
    SDL_WM_SetCaption( "Fuzzball Game v0.0.4", NULL );

    screen = SDL_SetVideoMode( WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_BPP, SDL_SWSURFACE);
    if(screen==NULL){
    std::cout << "screen is still NULL\n";
    quit=true;
    }
    stage.newMap(player.get_map_filename());
    player.load_sprite();
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
        Uint8 *keystate = SDL_GetKeyState(NULL);
        if(keystate[SDLK_LEFT] && !keystate[SDLK_RIGHT]){
        player.set_user_x_move(-5);
        player.nextFrame();
        }
        else if(keystate[SDLK_RIGHT] && !keystate[SDLK_LEFT]){
        player.set_user_x_move(5);
        player.nextFrame();
        }
        else
        player.setFrame(2);
        if(!keystate[SDLK_LEFT] && !keystate[SDLK_RIGHT])
        player.set_user_x_move(0);

}

void Engine::get_time(){
    fps.start();
}

void Engine::gather_input(){
    Uint8 *keystate = SDL_GetKeyState(NULL);
    if( event.type == SDL_KEYDOWN )
    {
        switch(event.key.keysym.sym){
            case SDLK_w: stage.rotate(0);
            player.set_x(stage.get_mapWidthpx()-32-player.get_x());
            player.set_y(stage.get_mapHeightpx()-32-player.get_y());
            break;
            case SDLK_z: player.jump(stage);break;
            case SDLK_x: if(keystate[SDLK_LEFT] && !keystate[SDLK_RIGHT] && !keystate[SDLK_UP] && !keystate[SDLK_DOWN]){
                            player.dash(3);
                            }if(!keystate[SDLK_LEFT] && keystate[SDLK_RIGHT] && !keystate[SDLK_UP] && !keystate[SDLK_DOWN]){
                            player.dash(1);
                            }if(!keystate[SDLK_LEFT] && !keystate[SDLK_RIGHT] && keystate[SDLK_UP] && !keystate[SDLK_DOWN]){
                            player.dash(0);
                            }if(!keystate[SDLK_LEFT] && !keystate[SDLK_RIGHT] && !keystate[SDLK_UP] && keystate[SDLK_DOWN]){
                            player.dash(2);}break;
			case SDLK_LEFT: player.set_faceing_left(true);
				 break;
			case SDLK_RIGHT: player.set_faceing_left(false);
			 	 break;
        default: break;
        }
    }else if(event.type == SDL_KEYUP){
        switch(event.key.keysym.sym){
            case SDLK_LEFT: if(keystate[SDLK_RIGHT]){player.set_faceing_left(false);}break;
            case SDLK_RIGHT: if(keystate[SDLK_LEFT]){player.set_faceing_left(true);}break;
            default: break;
        }
    }



}
void Engine::update_objects(){
    player.move_player(stage);
}
void Engine::display(){
  stage.center_camera(player.get_x(), player.get_y(), player.get_w(), player.get_h());
  stage.display_terrain(screen);
  player.display_player(screen, stage.get_camera_x(), stage.get_camera_y());
  player.manage_particle_systems();
  player.display_all_particles(screen, stage.get_camera_x(), stage.get_camera_y(), stage.get_mapWidthpx(), stage.get_mapHeightpx());
}

