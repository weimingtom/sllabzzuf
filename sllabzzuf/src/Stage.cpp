#include "stage.h"

Stage::Stage(){

}

Stage::~Stage(){
}

void Stage::display_terrain(SDL_Surface *screen){
    if(screen!=NULL)
    map.drawMap(screen, camera.get_bounds());
}
void Stage::newMap(){
        std::cout << "about to load map.\n";
        map.loadMap("data/newgame.map");
        std::cout << "setting tilesheet for " << map.get_theme() << " theme.\n";
         switch(map.get_theme()){
            case 1: map.set_TileSheet("sprites/tiles_underwater.png");break;
            case 2: map.set_TileSheet("sprites/tiles_ice.png");break;
            default: map.set_TileSheet("sprites/tiles_underground.png");break;
        }
}

int Stage::get_camera_x(){
    return camera.get_x();
}
int Stage::get_camera_y(){
    return camera.get_y();
}
int Stage::get_camera_w(){
    return camera.get_w();
}
int Stage::get_camera_h(){
    return camera.get_h();
}
int Stage::get_mapHeightpx(){
    return map.get_Heightpx();
}
int Stage::get_mapWidthpx(){
    return map.get_Widthpx();
}
void Stage::set_camera_x(int x){
    camera.set_x(x);
}
void Stage::set_camera_y(int y){
    camera.set_y(y);
}
