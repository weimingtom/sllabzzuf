#include "stage.h"

Stage::Stage(){
    gravity=3;
}

Stage::~Stage(){
}
int Stage::get_gravity(){
    return gravity;
}
bool Stage::object_hitTest(int direction, int x, int y){
    return map.solid_collision(direction, x, y, 32, 32);
}
void Stage::display_terrain(SDL_Surface *screen){
    if(screen!=NULL)
    map.drawMap(screen, camera.get_bounds());
}
void Stage::newMap(std::string mapname){
        std::cout << "about to load map: data/" << mapname <<".map\n";
        std::string filepath= "data/" + mapname + ".map";
        map.loadMap(filepath);
        std::cout << "setting tilesheet for " << map.get_theme() << " theme.\n";
         switch(map.get_theme()){
            case 1: map.set_TileSheet("sprites/tiles_underwater.png");break;
            case 2: map.set_TileSheet("sprites/tiles_ice.png");break;
            default: map.set_TileSheet("sprites/tiles_underground.png");break;
        }
}
int Stage::get_theme(){
    return map.get_theme();
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
void Stage::rotate(int direction){
    if(direction==0){
        map.rotateUp();
    }
}
void Stage::center_camera(int player_x, int player_y, int player_w, int player_h){
    camera.set_x((player_x + player_w / 2 ) - SCREEN_WIDTH / 2);
    camera.set_y((player_y + player_h / 2 ) - SCREEN_HEIGHT / 2);
    if( camera.get_x() < 0 )
        camera.set_x(0);
    if( camera.get_y() < 0 )
        camera.set_y(0);
    if( camera.get_x() > get_mapWidthpx() - camera.get_w() )
        camera.set_x(get_mapWidthpx() - camera.get_w());
    if( camera.get_y() > get_mapHeightpx() - camera.get_h() ){
        camera.set_y(get_mapHeightpx() - camera.get_h());
    }
}
