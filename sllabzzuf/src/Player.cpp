#include "player.h"
#include <time.h>
#include <stdlib.h>

Player::Player(){
    map_filename="";
    load_profile();
    faceing_left=false;
    frame=1;
    framebuffer=0;
    frame_dir_left=false;
    user_x_acc=0;
    user_y_acc=0;
    x_velocity=0;
    y_velocity=0;
    x_acceleration=0;
    y_acceleration=0;
    jump_timer=0;
    dash_timer=0;
    dash_direction;
    active_spell=1;
    srand(time(0));
}
int Player::get_active_spell(){
    return active_spell;
}
void Player::load_sprite(){
  rawsprite = IMG_Load("sprites/fuzzy.png");
    if( rawsprite != NULL )
    {
        sprite = SDL_DisplayFormat( rawsprite );
        SDL_FreeSurface( rawsprite );
        if( sprite != NULL )
        {
            SDL_SetColorKey( sprite, SDL_SRCCOLORKEY, SDL_MapRGB( sprite->format, 0xFF, 0, 0xFF ) );
        }else{
        std::cout << "Player's sprite is still NULL!\n";
        }
    }else{
    std::cout << "Player's rawsprite is still NULL!\n";
    }
    clip_fuzzy();
}
void Player::set_user_x_move(int amount){
    user_x_acc=amount;
}
void Player::set_user_y_move(int amount){
    user_y_acc=amount;
}
void Player::move_player(Stage stage){
    int surface_friction;
    int surface_type=stage.get_theme();
    int x_vel, y_vel;
    int x_acc, y_acc;

    x_acceleration=user_x_acc;
    y_acceleration=user_y_acc+stage.get_gravity();

    if(x_acceleration>3)
    x_acceleration=3;
    if(x_acceleration<-3)
    x_acceleration=-3;
    if(y_acceleration<-10)
    y_acceleration=-10;
    if(y_acceleration>10)
    y_acceleration=10;


    if(jump_timer>0){
        y_acceleration-=15;
        jump_timer-=1;
    }

    if(dash_timer>0){
        switch(dash_direction){
            case 0: y_acceleration -= dash_timer*2;x_acceleration=x_acceleration/2;break;
            case 1: x_acceleration += dash_timer*2;y_acceleration=y_acceleration/2;break;
            case 2: y_acceleration += dash_timer*2;x_acceleration=x_acceleration/2;break;
            case 3: x_acceleration -= dash_timer*2;y_acceleration=y_acceleration/2;break;
            default:break;
        }
        Uint8 red, green, blue;
        Uint8 redend, greenend, blueend;
        Uint8 color[3];
        Uint8 end_color[3];
        float radians=atan2((float)y_velocity,(float)x_velocity);
        for (std::list<ParticleSystem>::iterator it=systems.begin(); it!=systems.end(); ++it){
            it->remove_dead();
            it->update_all();
            red=(rand() %150) + 80;
            green=(rand() %50) + 10;
            blue=(rand() %50) +10;
            redend=255-(rand()%100);
            greenend=250-(rand()%50);
            blueend=250-(rand()%50);
            color[0]=red;
            color[1]=green;
            color[2]=blue;
            end_color[0]=redend;
            end_color[1]=greenend;
            end_color[2]=blueend;
            it->particle_factory(x+16,y+16,color,(rand()%20)+10,end_color,radians,5);
        }
        dash_timer-=1;
    }else if(dash_timer>-20){
        dash_timer-=1;
    }
    x_velocity=x_velocity+x_acceleration;
    y_velocity=y_velocity+y_acceleration;

    if(x_velocity>15 && dash_timer>-10 && (dash_direction==1 || dash_direction == 3))
    x_velocity=15;
    else if(x_velocity>6 )
    x_velocity=6;
    if(x_velocity<-15 && dash_timer>-10 && (dash_direction==1 || dash_direction == 3))
    x_velocity=-15;
    else if(x_velocity<-6 )
    x_velocity=-6;
    if(y_velocity<-15)
    y_velocity=-15;
    if(y_velocity>15)
    y_velocity=15;

    int x_moved = 0;
    int y_moved = 0;
    int previous_x_moved=-1;
    int previous_y_moved=-1;
    surface_friction=0;
    while(x_moved>previous_x_moved || y_moved > previous_y_moved){
        previous_x_moved=x_moved;
        previous_y_moved=y_moved;
        if(x_moved< abs(x_velocity)){
            //std::cout << "x_velocity: " << x_velocity;
            if(x_velocity>0 && move_x(1, x, y, stage)){
            //std::cout << "x_moved=" << x_moved;
            x_moved+=1;
            }if(x_velocity<=0 && move_x(-1, x, y, stage)){
            //std::cout << "x_moved=" << x_moved;
            x_moved+=1;
            }
        }if(y_moved< abs(y_velocity)){
            if(y_velocity>0 && move_y(1, x, y, stage)){
            y_moved+=1;
            surface_friction=0;
            }
            if(y_velocity<=0 && move_y(-1, x, y, stage)){
            y_moved+=1;
            surface_friction=0;
            }else{

                switch(surface_type){
                case 0: surface_friction=friction+4;break;
                case 1: surface_friction=friction+2;break;
                case 2: surface_friction=friction;break;
                default:surface_friction=friction+4;break;
                }
                if(x_acceleration==0 && friction_increment>=40){
                    friction_increment=0;
                    if(x_velocity>surface_friction)
                        x_velocity-=surface_friction;
                    else if(x_velocity< -surface_friction)
                        x_velocity+=surface_friction;
                    else
                        x_velocity=0;
                }else{
                friction_increment+=1;
                }
            }
        }
    }if(!move_y(1, x, y, stage)){
        y_acceleration=0;
        y_velocity=0;
    }
}
void Player::manage_particle_systems(){
    float radians=atan2((float)y_velocity,(float)x_velocity);
    for (std::list<ParticleSystem>::iterator it=systems.begin(); it!=systems.end(); ++it){
        it->update_all();
        it->remove_dead();
    }
}
void Player::display_all_particles(SDL_Surface *screen, int camera_x, int camera_y, int mapw, int maph){
     for (std::list<ParticleSystem>::iterator it=systems.begin(); it!=systems.end(); ++it){
        it->draw_particles(screen, camera_x, camera_y, mapw, maph);
     }
}
void Player::dash(int direction){
    if(dash_timer<=-20){
    dash_direction=direction;
    dash_timer=7;
    ParticleSystem newsystem(30);
    systems.push_back(newsystem);
    }
}
void Player::jump(Stage stage){
    if(!move_y(1, x, y, stage)){
        jump_timer=3;
        if(dash_timer<=0){
        dash_timer=-20;
        }
    }else{
    move_y(-1, x, y, stage);
    }
}
void Player::display_player(SDL_Surface *screen, int camera_x, int camera_y){
    SDL_Rect offset;
    offset.x = x - camera_x;
    offset.y = y - camera_y;
    if(screen!=NULL){
        if(faceing_left)
        SDL_BlitSurface( sprite, &fuzzLEFT[frame], screen, &offset );
        else
        SDL_BlitSurface( sprite, &fuzzRIGHT[frame], screen, &offset );
    }
}

void Player::load_profile(){
	std::cout << "Loading profile.dat \n";
	std::ifstream profile("data/profile.dat", std::ifstream::in);

	if(profile != NULL){
		std::cout << "ifstream successfull, loading variables.\n";

        profile >> map_filename;
        profile >> x;
        profile >> y;
        profile >> hp;
        profile >> max_hp;
        profile >> spell_bonus;
        profile >> spells_known;

		profile.close();
        std::cout << "load profile finished\n";
	}else{
    profile.close();
	std::cout << "Loading profile.dat failed\nMaking a new one.\n";
	map_filename = "newgame";
	x = 128; y = 96; hp = 5; max_hp = 5; spell_bonus = 0; spells_known =1;
	save_profile();
	load_profile();
	}
	mp = 0; w = 32; h= 32; weight=100;
}

void Player::save_profile(){
    std::ofstream save("data/profile.dat");
    save<< map_filename<<"\n"<<x<<" "<<y<<"\n"<<hp<<" "<<max_hp<<" "<<spell_bonus<<" "<<spells_known<<"\n";
    save.close();
}
int Player::get_max_hp(){
return max_hp;
}

int Player::get_mp(){
return mp;
}

int Player::get_spell_bonus(){
return spell_bonus;
}

int Player::get_spells_known(){
return spells_known;
}

std::string Player::get_map_filename(){
return map_filename;
}

void Player::set_map_filename(std::string filename){
map_filename = filename;
}

void Player::add_spell_bonus(int amount){
spell_bonus += amount;
}

void Player::add_max_hp(int amount){
max_hp += amount;
}

void Player::add_mp(int amount){
mp += amount;
}

void Player::add_spells_known(int amount){
spells_known += amount;
}
void Player::set_faceing_left(bool face){
faceing_left=face;
}
void Player::setFrame(int framenum){
frame=framenum;
}
void Player::nextFrame(){
    if(framebuffer>3){
        if(frame==0){
        frame=1;
        frame_dir_left=false;
        }
        if(frame==1 && frame_dir_left)
        frame=0;
        if(frame==1 && !frame_dir_left)
        frame=2;
        if(frame==2){
        frame=1;
        frame_dir_left=true;
        }
        framebuffer=0;
    }else{
    framebuffer+=1;
    }
}
void Player::clip_fuzzy(){
    int fuzz_WIDTH = 32;
    int fuzz_HEIGHT = 32;
    //Clip the sprite sheet
	fuzzLEFT[0].x=0;
	fuzzLEFT[0].y=0;
	fuzzLEFT[0].w=fuzz_WIDTH;
	fuzzLEFT[0].h=fuzz_HEIGHT;

	fuzzLEFT[1].x=fuzz_WIDTH;
	fuzzLEFT[1].y=0;
	fuzzLEFT[1].w=fuzz_WIDTH;
	fuzzLEFT[1].h=fuzz_HEIGHT;

	fuzzLEFT[2].x=fuzz_WIDTH *2;
	fuzzLEFT[2].y=0;
	fuzzLEFT[2].w=fuzz_WIDTH;
	fuzzLEFT[2].h=fuzz_HEIGHT;

	fuzzRIGHT[0].x=0;
	fuzzRIGHT[0].y=fuzz_HEIGHT;
	fuzzRIGHT[0].w=fuzz_WIDTH;
	fuzzRIGHT[0].h=fuzz_HEIGHT;

	fuzzRIGHT[1].x=fuzz_WIDTH;
	fuzzRIGHT[1].y=fuzz_HEIGHT;
	fuzzRIGHT[1].w=fuzz_WIDTH;
	fuzzRIGHT[1].h=fuzz_HEIGHT;

	fuzzRIGHT[2].x=fuzz_WIDTH * 2;
	fuzzRIGHT[2].y=fuzz_HEIGHT;
	fuzzRIGHT[2].w=fuzz_WIDTH;
	fuzzRIGHT[2].h=fuzz_HEIGHT;

}
