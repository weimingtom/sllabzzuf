#include "Block.h"

Block::Block(int startx, int starty){
    x=startx;
    y=starty;
    w=64;
    h=64;
    y_acceleration=0;
    y_velocity=0;
}
SDL_Rect Block::get_bounds(){
    SDL_Rect bounds;
    bounds.x=x;
    bounds.y=y;
    bounds.w=w;
    bounds.h=h;
    return bounds;
}
void Block::draw(SDL_Surface *screen, SDL_Rect *camera){
    SDL_Rect portion;
    portion.x=0;
    portion.y=0;
    portion.w=w;
    portion.h=h;
    SDL_BlitSurface( sprite, &portion, screen, &getScreenCoord(camera));
}
SDL_Rect Block::getScreenCoord(SDL_Rect* camera){
	SDL_Rect screenCoord;
	screenCoord.x = x - camera->x;
	screenCoord.y = y - camera->y;
	return screenCoord;
}
bool Block::test_spot(int type, int tile_x, int tile_y){
    if(type!=0){
            if((tile_y + 32 > y)&&(tile_y < y+h)&&(tile_x+32>x)&&(tile_x<x+w)){

                return true;
            }
    }
    return false;
}
bool Block::move_y(int amount, int current_x, int current_y, std::vector<Tile*> tiles, int mapwidthpx, int mapheightpx){
    current_y += amount;
    int type;
    int tile_x = (x/32)*32;
    int tile_y = (y/32)*32;
    //int relative_x= x+(w/3)-tile_x;
    //int relative_y= y-tile_y;
    //int relative_w= x+(2*w/3)-tile_x;
    //int relative_h= y+h-tile_y;
    if((x< 0) || (x+w > mapwidthpx) || (y<0) || (y+h >= mapheightpx)){
        return false;
    }
    type=tiles[tile_x/32 + (((tile_y)/32+1)*(mapwidthpx/32))]->get_type();
    if(test_spot(type, tile_x, tile_y+32)){
        type = tiles[x/32 + 1 + ((y/32+1)*(mapwidthpx/32))]->get_type();
        if(test_spot(type, tile_x+32, tile_y+32)){
            y += amount;
            return true;
        }
    }
    return false;
}
void Block::update(int gravity, std::vector<Tile*> tiles, int mapwidthpx, int mapheightpx){

    y_acceleration=gravity;

    if(y_acceleration<-10)
    y_acceleration=-10;
    if(y_acceleration>10)
    y_acceleration=10;

    y_velocity=y_velocity+y_acceleration;

    if(y_velocity<-15)
    y_velocity=-15;
    if(y_velocity>15)
    y_velocity=15;

    int y_moved = 0;
    int previous_y_moved=-1;
    while(y_moved > previous_y_moved){
        previous_y_moved=y_moved;
        if(y_moved< y_velocity){
            if(y_velocity>0 && move_y(1, x, y, tiles, mapwidthpx, mapheightpx)){
            y_moved+=1;
            }
        }
    }if(!move_y(1, x, y, tiles, mapwidthpx, mapheightpx)){
        y_acceleration=0;
        y_velocity=0;
    }
}
void Block::load_sprite(){
  rawsprite = IMG_Load("sprites/iceblock.png");
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
}
